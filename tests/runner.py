#!/usr/bin/env python3
import os
import sys
import subprocess
import argparse
import difflib
import time
import re
import shutil
import threading
import tempfile  # <--- NEW IMPORT
import platform
from concurrent.futures import ThreadPoolExecutor, as_completed
from pathlib import Path

# Subprocess output encoding: use UTF-8 so compiler/binary output decodes correctly on Windows (avoid cp1252 UnicodeDecodeError).
SUBPROCESS_ENCODING = "utf-8"
SUBPROCESS_ERRORS = "replace"  # Replace invalid bytes instead of raising

class Colors:
    HEADER = '\033[95m'
    OKBLUE = '\033[94m'
    OKGREEN = '\033[92m'
    WARNING = '\033[93m'
    FAIL = '\033[91m'
    BOLD = '\033[1m'
    ENDC = '\033[0m'

def _stdout_supports_unicode():
    """Use ASCII progress bar when stdout encoding can't represent Unicode (e.g. Windows cp1252 in CI)."""
    if platform.system() == 'Windows':
        return False
    enc = getattr(sys.stdout, 'encoding', None) or ''
    return enc and enc.lower() in ('utf-8', 'utf8', 'utf-16', 'utf-32')

def print_progress_bar(iteration, total, failed, skipped, start_time, bar_length=40):
    percent = 100 * (iteration / float(total))
    filled_length = int(bar_length * iteration // total)
    status_color = Colors.FAIL if failed > 0 else Colors.OKGREEN
    elapsed = time.time() - start_time
    if iteration > 0:
        avg_time_per_test = elapsed / iteration
        remaining_tests = total - iteration
        eta_seconds = avg_time_per_test * remaining_tests
        eta_str = f"{int(eta_seconds // 60)}m {int(eta_seconds % 60)}s" if eta_seconds > 60 else f"{eta_seconds:.1f}s"
    else:
        eta_str = "..."

    use_unicode = _stdout_supports_unicode()
    if use_unicode:
        bar = '█' * filled_length + '░' * (bar_length - filled_length)
        line = f'\r\033[K{status_color}▕{bar}▏{Colors.ENDC} {Colors.BOLD}{percent:.1f}%{Colors.ENDC} | ⏳ {elapsed:.1f}s | 🏁 ETA: {eta_str} | ❌ {failed} | {Colors.WARNING}⏭ {skipped}{Colors.ENDC}'
    else:
        bar_ascii = '=' * filled_length + '-' * (bar_length - filled_length)
        line = f'\r\033[K{status_color}[{bar_ascii}]{Colors.ENDC} {Colors.BOLD}{percent:.1f}%{Colors.ENDC} | {elapsed:.1f}s | ETA: {eta_str} | failed: {failed} | {Colors.WARNING}skipped: {skipped}{Colors.ENDC}'
    try:
        sys.stdout.write(line)
    except UnicodeEncodeError:
        bar_ascii = '=' * filled_length + '-' * (bar_length - filled_length)
        line = f'\r[{bar_ascii}] {percent:.1f}% | {elapsed:.1f}s | ETA: {eta_str} | failed: {failed} | skipped: {skipped}'
        sys.stdout.write(line)
    sys.stdout.flush()

def strip_ansi_codes(text):
    ansi_escape = re.compile(r'\x1B(?:[@-Z\\-_]|\[[0-?]*[ -/]*[@-~])')
    return ansi_escape.sub('', text)

def get_expected_error_code(file_path):
    try:
        with open(file_path, 'r', encoding='utf-8') as f:
            for _ in range(5):
                line = f.readline()
                match = re.search(r'/;\s*EXPECT_ERROR:\s*(\w+)', line)
                if match:
                    return match.group(1)
    except Exception:
        pass
    return None

def run_single_test(compiler_bin, file_path, update_mode, mode, temp_root, failed_dirs, dir_lock, keep_going):
    parent_dir = file_path.parent

    if not keep_going:
        with dir_lock:
            if parent_dir in failed_dirs:
                return None, f"{Colors.WARNING}[SKIPPED]{Colors.ENDC} {file_path.name} (Directory failed)"

    # We create a temporary directory for THIS specific test run.
    # We set TMPDIR so the compiler creates its 'fg_tmp' inside here,
    # completely isolated from other tests running in parallel.
    with tempfile.TemporaryDirectory() as private_temp_dir:
        
        # Prepare environment variables
        run_env = os.environ.copy()
        run_env["TMPDIR"] = private_temp_dir
        run_env["TEMP"] = private_temp_dir
        run_env["TMP"] = private_temp_dir

        try:
            start_time = time.time()
            expected_error_code = get_expected_error_code(file_path)

            # --- PATH A: DIAGNOSTIC TEST (EXPECT_ERROR) ---
            if expected_error_code:
                if mode == "aot":
                    # AOT: compiler only compiles; it does not run the program. So we must
                    # compile to a temp dir, then run the binary to see runtime errors.
                    aot_build_dir = Path(private_temp_dir) / "aot_build"
                    aot_build_dir.mkdir(parents=True, exist_ok=True)
                    compile_cmd = [str(compiler_bin), str(file_path), f'--output-dir={aot_build_dir}']
                    compile_result = subprocess.run(compile_cmd, capture_output=True, text=True, timeout=15, env=run_env, encoding=SUBPROCESS_ENCODING, errors=SUBPROCESS_ERRORS)
                    duration = (time.time() - start_time) * 1000
                    if compile_result.returncode != 0:
                        output = (compile_result.stderr or '') + (compile_result.stdout or '')
                        output = strip_ansi_codes(output)
                        if expected_error_code in output:
                            return True, f"{Colors.OKGREEN}[PASS (DIAG)]{Colors.ENDC} {file_path.name} (Found {expected_error_code}) ({duration:.1f}ms)"
                        if not keep_going:
                            with dir_lock: failed_dirs.add(parent_dir)
                        return False, f"{Colors.FAIL}[FAIL (DIAG)]{Colors.ENDC} {file_path.name}\nExpected Error: {expected_error_code}\nGot Compiler Output:\n{output} ({duration:.1f}ms)"
                    binary_name = file_path.stem
                    binary_path = aot_build_dir / "bin" / binary_name
                    if not binary_path.exists() and (aot_build_dir / "bin" / f"{binary_name}.exe").exists():
                        binary_path = aot_build_dir / "bin" / f"{binary_name}.exe"
                    if not binary_path.exists():
                        if not keep_going:
                            with dir_lock: failed_dirs.add(parent_dir)
                        return False, f"{Colors.FAIL}[FAIL (DIAG)]{Colors.ENDC} {file_path.name}\nExpected Error: {expected_error_code}\nCompilation succeeded but binary not found at: {binary_path}"
                    run_result = subprocess.run([str(binary_path)], capture_output=True, text=True, timeout=5, env=run_env, encoding=SUBPROCESS_ENCODING, errors=SUBPROCESS_ERRORS)
                    duration = (time.time() - start_time) * 1000
                    output = (run_result.stderr or '') + (run_result.stdout or '')
                    output = strip_ansi_codes(output)
                    if expected_error_code in output:
                        return True, f"{Colors.OKGREEN}[PASS (DIAG)]{Colors.ENDC} {file_path.name} (Found {expected_error_code}) ({duration:.1f}ms)"
                    if not keep_going:
                        with dir_lock: failed_dirs.add(parent_dir)
                    return False, f"{Colors.FAIL}[FAIL (DIAG)]{Colors.ENDC} {file_path.name}\nExpected Error: {expected_error_code}\nGot Binary Output:\n{output} ({duration:.1f}ms)"
                else:
                    # JIT: compiler compiles and runs in process, so one invocation gets both compile and runtime errors.
                    run_cmd = [str(compiler_bin), str(file_path)]
                    result = subprocess.run(run_cmd, capture_output=True, text=True, timeout=5, env=run_env, encoding=SUBPROCESS_ENCODING, errors=SUBPROCESS_ERRORS)
                    duration = (time.time() - start_time) * 1000
                    output = (result.stderr or '') + (result.stdout or '')
                    output = strip_ansi_codes(output)
                    if expected_error_code in output:
                        return True, f"{Colors.OKGREEN}[PASS (DIAG)]{Colors.ENDC} {file_path.name} (Found {expected_error_code}) ({duration:.1f}ms)"
                    if not keep_going:
                        with dir_lock: failed_dirs.add(parent_dir)
                    return False, f"{Colors.FAIL}[FAIL (DIAG)]{Colors.ENDC} {file_path.name}\nExpected Error: {expected_error_code}\nGot Output:\n{output} ({duration:.1f}ms)"

            # --- PATH B: EXECUTION TEST ---
            if mode == "aot":
                test_temp_dir = temp_root / file_path.stem
                test_temp_dir.mkdir(parents=True, exist_ok=True)
                compile_cmd = [str(compiler_bin), str(file_path), f'--output-dir={test_temp_dir}']
                
                # Use env=run_env here
                compile_result = subprocess.run(compile_cmd, capture_output=True, text=True, env=run_env, encoding=SUBPROCESS_ENCODING, errors=SUBPROCESS_ERRORS)
                
                if compile_result.returncode != 0:
                    # If an .expect file exists, this might be an intentional
                    # "runtime error at init / compile time" test.
                    # Compare the compiler's output against the expect file.
                    expect_file = file_path.with_suffix(".expect")
                    if expect_file.exists() or update_mode:
                        raw_compile_out = (compile_result.stdout or '') + (compile_result.stderr or '')
                        actual_compile_out = strip_ansi_codes(raw_compile_out)
                        duration = (time.time() - start_time) * 1000
                        if update_mode:
                            action_tag = "[UPDATED]" if expect_file.exists() else "[CREATED]"
                            try:
                                with open(expect_file, 'w', encoding='utf-8') as f: f.write(actual_compile_out)
                                return True, f"{Colors.OKBLUE}{action_tag}{Colors.ENDC} {file_path.name}"
                            except Exception as e:
                                return False, f"{Colors.FAIL}[WRITE ERROR]{Colors.ENDC} Could not write {expect_file}: {e}"
                        with open(expect_file, 'r', encoding='utf-8') as f:
                            expected_compile_out = f.read()
                        if actual_compile_out == expected_compile_out:
                            return True, f"{Colors.OKGREEN}[PASS (COMPILED)]{Colors.ENDC} {file_path.name} ({duration:.1f}ms)"
                        else:
                            def to_lines(text):
                                lines = text.splitlines(keepends=True)
                                if lines and not lines[-1].endswith('\n'):
                                    lines[-1] += '\n'
                                    lines.append('\\ No newline at end of file\n')
                                return lines
                            diff = list(difflib.unified_diff(
                                to_lines(expected_compile_out),
                                to_lines(actual_compile_out),
                                fromfile='Expected',
                                tofile='Actual',
                                n=3
                            ))
                            diff_text = "".join(diff) or f"Exp: {repr(expected_compile_out)}\nAct: {repr(actual_compile_out)}\n"
                            if not keep_going:
                                with dir_lock: failed_dirs.add(parent_dir)
                            return False, f"{Colors.FAIL}[FAIL (COMPILED)]{Colors.ENDC} {file_path.name}\n{diff_text}"
                    # No expect file — genuine compile failure
                    if not keep_going:
                        with dir_lock: failed_dirs.add(parent_dir)
                    return False, f"{Colors.FAIL}[COMPILE FAIL]{Colors.ENDC} {file_path.name}\n{compile_result.stderr or ''}\n{compile_result.stdout or ''}"
                
                binary_name = file_path.stem
                binary_path = test_temp_dir / "bin" / binary_name
                # On Windows the compiler is likely to emit an .exe, while on Unix
                # it will be a bare binary with no extension. Check both so that
                # Windows AOT tests don't fail with a spurious "missing binary".
                if not binary_path.exists():
                    exe_candidate = binary_path.with_suffix(binary_path.suffix + ".exe")
                    if exe_candidate.exists():
                        binary_path = exe_candidate
                    else:
                        if not keep_going:
                            with dir_lock:
                                failed_dirs.add(parent_dir)
                        return False, f"{Colors.FAIL}[MISSING BINARY]{Colors.ENDC} Expected at: {binary_path}"
                run_cmd = [str(binary_path)]
            else:
                run_cmd = [str(compiler_bin), str(file_path)]

            # Use env=run_env here
            result = subprocess.run(run_cmd, capture_output=True, text=True, timeout=5, env=run_env, encoding=SUBPROCESS_ENCODING, errors=SUBPROCESS_ERRORS)
            duration = (time.time() - start_time) * 1000
            
            raw_output = (result.stdout or '') + (result.stderr or '')
            actual_output = strip_ansi_codes(raw_output)
            stderr_output = result.stderr or ''

            if mode == "aot" and temp_root.exists():
                 shutil.rmtree(test_temp_dir, ignore_errors=True)

            expect_file = file_path.with_suffix(".expect")
            
            if update_mode or not expect_file.exists():
                action_tag = "[UPDATED]" if expect_file.exists() else "[CREATED]"
                try:
                    with open(expect_file, 'w', encoding='utf-8') as f: f.write(actual_output)
                    return True, f"{Colors.OKBLUE}{action_tag}{Colors.ENDC} {file_path.name}"
                except Exception as e:
                    if not keep_going:
                        with dir_lock: failed_dirs.add(parent_dir)
                    return False, f"{Colors.FAIL}[WRITE ERROR]{Colors.ENDC} Could not write {expect_file}: {e}"

            with open(expect_file, 'r', encoding='utf-8') as f: expected_output = f.read()

            if actual_output == expected_output:
                return True, f"{Colors.OKGREEN}[PASS (COMPILED)]{Colors.ENDC} {file_path.name} ({duration:.1f}ms)"
            else:
                # Normalize lines for diff: ensure each line ends with \n so the
                # unified diff never joins a '-' line and a '+' line on the same
                # output row (the unreadable "foo+bar" rendering).
                def to_lines(text):
                    lines = text.splitlines(keepends=True)
                    if lines and not lines[-1].endswith('\n'):
                        lines[-1] += '\n'
                        lines.append('\\ No newline at end of file\n')
                    return lines

                diff = list(difflib.unified_diff(
                    to_lines(expected_output),
                    to_lines(actual_output),
                    fromfile='Expected',
                    tofile='Actual',
                    n=3
                ))
                diff_text = "".join(diff)
                if not diff_text and actual_output != expected_output:
                    diff_text = f"{Colors.WARNING}--- INVISIBLE DIFF ---{Colors.ENDC}\nExp: {repr(expected_output)}\nAct: {repr(actual_output)}\n"
                if stderr_output and stderr_output not in raw_output: 
                    diff_text += f"\n{Colors.WARNING}--- STDERR ---{Colors.ENDC}\n{stderr_output}"
                
                if not keep_going:
                    with dir_lock: failed_dirs.add(parent_dir)
                return False, f"{Colors.FAIL}[FAIL (COMPILED)]{Colors.ENDC} {file_path.name}\n{diff_text}"

        except subprocess.TimeoutExpired:
            if not keep_going:
                with dir_lock: failed_dirs.add(parent_dir)
            return False, f"{Colors.FAIL}[TIMEOUT]{Colors.ENDC} {file_path.name}"
        except Exception as e:
            if not keep_going:
                with dir_lock: failed_dirs.add(parent_dir)
            return False, f"{Colors.FAIL}[ERROR]{Colors.ENDC} {file_path.name}: {str(e)}"

def _ensure_stdout_unicode_safe():
    """On Windows, reconfigure stdout to UTF-8 so compiler output (e.g. ▶) prints without UnicodeEncodeError."""
    if platform.system() != 'Windows':
        return
    enc = getattr(sys.stdout, 'encoding', None) or ''
    if enc and enc.lower() not in ('utf-8', 'utf8'):
        try:
            sys.stdout.reconfigure(encoding='utf-8', errors='replace')
        except (AttributeError, OSError):
            pass  # reconfigure not available or failed


def _safe_print(text):
    """Print text, avoiding UnicodeEncodeError on Windows cp1252 (e.g. when msg contains ▶ from compiler)."""
    try:
        print(text)
    except UnicodeEncodeError:
        enc = getattr(sys.stdout, 'encoding', None) or 'ascii'
        sys.stdout.buffer.write((text + '\n').encode(enc, errors='replace'))

def main():
    _ensure_stdout_unicode_safe()
    parser = argparse.ArgumentParser()
    parser.add_argument("--bin", required=True, help="Path to compiler executable")
    parser.add_argument("--dir", required=True, help="Path to fixtures")
    parser.add_argument("--update", action="store_true", help="Force update of existing expect files")
    parser.add_argument("--filter", type=str, help="Regex filter")
    parser.add_argument("--mode", choices=["jit", "aot"], default="jit", help="Execution mode")
    parser.add_argument("--parallel", action="store_true", help="Run tests in parallel")
    parser.add_argument("--keep-going", action="store_true", help="Run all tests in a directory even if one fails")
    args = parser.parse_args()

    compiler_path = Path(args.bin)
    test_dir = Path(args.dir)
    temp_root = Path("build/bin/test_artifacts")

    if not compiler_path.exists():
        print(f"{Colors.FAIL}Compiler not found at: {compiler_path}{Colors.ENDC}")
        sys.exit(1)

    print(f"{Colors.OKGREEN}Compiler found at: {compiler_path}{Colors.ENDC}")

    all_tests = sorted(list(test_dir.rglob("*.fg")))

    # Verbatim mirrors of tests/fixtures/Z_BringTest and Z_ModuleTest (see
    # LatestTests/*/legacy_Z_*). They often rely on old bring/module behavior
    # and are skipped when scanning a broad --dir unless:
    #   - FLOWWING_RUN_LEGACY_Z=1, or
    #   - --dir points inside a legacy_Z_* folder (run that tree only).
    def _filter_legacy_z_mirrors(paths):
        if os.environ.get("FLOWWING_RUN_LEGACY_Z") == "1":
            return paths
        legacy_marker = "legacy_Z_"
        if legacy_marker in str(test_dir.resolve()):
            return paths
        return [p for p in paths if legacy_marker not in str(p)]

    all_tests = _filter_legacy_z_mirrors(all_tests)

    if args.filter:
        try:
            pattern = re.compile(args.filter)
            all_tests = [t for t in all_tests if pattern.search(str(t))]
        except re.error:
            print(f"{Colors.FAIL}Invalid regex pattern: {args.filter}{Colors.ENDC}")
            sys.exit(1)

    if not all_tests:
        print("No tests found.")
        sys.exit(0)

    print(f"{Colors.HEADER}Running {len(all_tests)} tests ({args.mode.upper()})...{Colors.ENDC}")
    print("-" * 60) 
    
    stats = {
        "failed": 0,
        "completed": 0,
        "passed_compiled": 0,
        "passed_diag": 0,
        "skipped": 0
    }
    
    failed_dirs = set()
    failed_files = [] 
    dir_lock = threading.Lock()

    total = len(all_tests)
    suite_start_time = time.time()
    
    print_progress_bar(0, total, 0, 0, suite_start_time)

    def handle_result(success, msg, file_path):
        stats["completed"] += 1
        
        if success is None: 
            stats["skipped"] += 1
        elif not success:
            stats["failed"] += 1
            failed_files.append(file_path)
        elif "PASS (COMPILED)" in msg:
            stats["passed_compiled"] += 1
        elif "PASS (DIAG)" in msg:
            stats["passed_diag"] += 1
        
        sys.stdout.write('\r\033[K')
        
        if success is False or "UPDATED" in msg or "CREATED" in msg: 
             _safe_print(msg)
        elif success is True and total < 3000: 
             _safe_print(msg)
             
        print_progress_bar(stats["completed"], total, stats["failed"], stats["skipped"], suite_start_time)

    use_parallel = args.parallel

    if use_parallel:
        with ThreadPoolExecutor() as executor:
            future_to_test = {
                executor.submit(run_single_test, compiler_path, t, args.update, args.mode, temp_root, failed_dirs, dir_lock, args.keep_going): t 
                for t in all_tests
            }
            for future in as_completed(future_to_test):
                test_path = future_to_test[future]
                success, msg = future.result()
                handle_result(success, msg, test_path)
    else:
        for t in all_tests:
            success, msg = run_single_test(compiler_path, t, args.update, args.mode, temp_root, failed_dirs, dir_lock, args.keep_going)
            handle_result(success, msg, t)

    print()
    print("-" * 60)

    _bullet = "*" if platform.system() == 'Windows' else "•"
    _fail_mark = "Failed:" if platform.system() == 'Windows' else "❌ Failed:"
    _ok_mark = "OK" if platform.system() == 'Windows' else "✅"
    if stats["failed"] > 0:
        print(f"\n{Colors.HEADER}Failed Test Summary:{Colors.ENDC}")
        for f in failed_files:
            print(f"{Colors.FAIL}{_bullet} {f}{Colors.ENDC}")
        print("-" * 60)
        
        print(f"{Colors.FAIL}{_fail_mark} {stats['failed']}, Skipped: {stats['skipped']}, Passed: {stats['passed_compiled'] + stats['passed_diag']}{Colors.ENDC}")
        sys.exit(1)
    else:
        duration = time.time() - suite_start_time
        breakdown = f"({stats['passed_compiled']} Compiled, {stats['passed_diag']} Diag)"
        print(f"{Colors.OKGREEN}{_ok_mark} All {total} tests passed {breakdown} in {duration:.2f}s!{Colors.ENDC}")
        sys.exit(0)

if __name__ == "__main__":
    main()