#!/usr/bin/env python3
import os
import sys
import subprocess
import argparse
import difflib
import time
import re
import shutil
from concurrent.futures import ThreadPoolExecutor, as_completed
from pathlib import Path

class Colors:
    HEADER = '\033[95m'
    OKBLUE = '\033[94m'
    OKGREEN = '\033[92m'
    WARNING = '\033[93m'
    FAIL = '\033[91m'
    BOLD = '\033[1m'
    ENDC = '\033[0m'

def print_progress_bar(iteration, total, failed, start_time, bar_length=40):
    """
    Prints a progress bar with percentage, elapsed time, ETA, and failure count.
    Output: ▕██████░░░░▏ 60.0% | ⏳ 3.5s | 🏁 ETA: 2.3s | ❌ 0
    """
    percent = 100 * (iteration / float(total))
    filled_length = int(bar_length * iteration // total)
    
    status_color = Colors.FAIL if failed > 0 else Colors.OKGREEN
    
    bar = '█' * filled_length + '░' * (bar_length - filled_length)
    elapsed = time.time() - start_time
    
    # --- ETA Calculation ---
    if iteration > 0:
        avg_time_per_test = elapsed / iteration
        remaining_tests = total - iteration
        eta_seconds = avg_time_per_test * remaining_tests
        
        if eta_seconds > 60:
            eta_str = f"{int(eta_seconds // 60)}m {int(eta_seconds % 60)}s"
        else:
            eta_str = f"{eta_seconds:.1f}s"
    else:
        eta_str = "..."
    # -----------------------

    # \r moves cursor to start, \033[K clears line
    sys.stdout.write(f'\r\033[K{status_color}▕{bar}▏{Colors.ENDC} {Colors.BOLD}{percent:.1f}%{Colors.ENDC} | ⏳ {elapsed:.1f}s | 🏁 ETA: {eta_str} | ❌ {failed}')
    sys.stdout.flush()

def get_expected_error_code(file_path):
    """
    Scans the first 5 lines of the file for // EXPECT_ERROR: kCode
    Returns the code string if found, else None.
    """
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

def run_single_test(compiler_bin, file_path, update_mode, mode, temp_root):
    try:
        start_time = time.time()
        
        # 1. CHECK FOR DIAGNOSTIC MODE (Does the file expect an error?)
        expected_error_code = get_expected_error_code(file_path)

        # --- PATH A: DIAGNOSTIC TEST (Expect Compilation Failure) ---
        if expected_error_code:
            run_cmd = [str(compiler_bin), str(file_path)]
            
            result = subprocess.run(run_cmd, capture_output=True, text=True, timeout=5)
            duration = (time.time() - start_time) * 1000
            
            output = result.stderr + result.stdout 
            
            if expected_error_code in output:
                 return True, f"{Colors.OKGREEN}[PASS (DIAG)]{Colors.ENDC} {file_path.name} (Found {expected_error_code}) ({duration:.1f}ms)"
            else:
                return False, f"{Colors.FAIL}[FAIL (DIAG)]{Colors.ENDC} {file_path.name}\nExpected Error: {expected_error_code}\nGot Output:\n{output} ({duration:.1f}ms)"

        # --- PATH B: EXECUTION TEST (Expect Success + Golden File Output) ---
        
        if mode == "aot":
            test_temp_dir = temp_root / file_path.stem
            test_temp_dir.mkdir(parents=True, exist_ok=True)
            
            compile_cmd = [str(compiler_bin), str(file_path), f'--output-dir={test_temp_dir}']
            compile_result = subprocess.run(compile_cmd, capture_output=True, text=True)
            
            if compile_result.returncode != 0:
                return False, f"{Colors.FAIL}[COMPILE FAIL]{Colors.ENDC} {file_path.name}\n{compile_result.stderr}\n{compile_result.stdout}"
            
            binary_name = file_path.stem
            binary_path = test_temp_dir / "bin" / binary_name
            
            if not binary_path.exists():
                 return False, f"{Colors.FAIL}[MISSING BINARY]{Colors.ENDC} Expected at: {binary_path}"
            
            run_cmd = [str(binary_path)]
        else:
            run_cmd = [str(compiler_bin), str(file_path)]

        result = subprocess.run(run_cmd, capture_output=True, text=True, timeout=5)
        duration = (time.time() - start_time) * 1000
        actual_output = result.stdout
        stderr_output = result.stderr

        if mode == "aot" and temp_root.exists():
             shutil.rmtree(test_temp_dir, ignore_errors=True)

        expect_file = file_path.with_suffix(".expect")
        
        if update_mode:
            with open(expect_file, 'w') as f: f.write(actual_output)
            return True, f"{Colors.OKBLUE}[UPDATED]{Colors.ENDC} {file_path.name}"

        if not expect_file.exists():
            return False, f"{Colors.WARNING}[MISSING]{Colors.ENDC} {file_path.name} (No .expect file)"

        with open(expect_file, 'r') as f: expected_output = f.read()

        if actual_output == expected_output:
            return True, f"{Colors.OKGREEN}[PASS (COMPILED)]{Colors.ENDC} {file_path.name} ({duration:.1f}ms)"
        else:
            diff = list(difflib.unified_diff(
                expected_output.splitlines(keepends=True),
                actual_output.splitlines(keepends=True),
                fromfile='Expected',
                tofile='Actual',
                n=3
            ))
            diff_text = "".join(diff)
            if not diff_text and actual_output != expected_output:
                diff_text = f"{Colors.WARNING}--- INVISIBLE DIFF ---{Colors.ENDC}\nExp: {repr(expected_output)}\nAct: {repr(actual_output)}\n"
            if stderr_output: diff_text += f"\n{Colors.WARNING}--- STDERR ---{Colors.ENDC}\n{stderr_output}"
            return False, f"{Colors.FAIL}[FAIL (COMPILED)]{Colors.ENDC} {file_path.name}\n{diff_text}"

    except subprocess.TimeoutExpired:
        return False, f"{Colors.FAIL}[TIMEOUT]{Colors.ENDC} {file_path.name}"
    except Exception as e:
        return False, f"{Colors.FAIL}[ERROR]{Colors.ENDC} {file_path.name}: {str(e)}"

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--bin", required=True, help="Path to compiler executable")
    parser.add_argument("--dir", required=True, help="Path to fixtures")
    parser.add_argument("--update", action="store_true", help="Update expect files")
    parser.add_argument("--filter", type=str, help="Regex filter")
    parser.add_argument("--mode", choices=["jit", "aot"], default="jit", help="Execution mode")
    parser.add_argument("--parallel", action="store_true", help="Run tests in parallel")
    args = parser.parse_args()

    compiler_path = Path(args.bin)
    test_dir = Path(args.dir)
    temp_root = Path("build/bin/test_artifacts")

    if not compiler_path.exists():
        print(f"{Colors.FAIL}Compiler not found at: {compiler_path}{Colors.ENDC}")
        sys.exit(1)

    print(f"{Colors.OKGREEN}Compiler found at: {compiler_path}{Colors.ENDC}")

    all_tests = sorted(list(test_dir.rglob("*.fg")))
    
    if args.filter:
        try:
            pattern = re.compile(args.filter)
            all_tests = [t for t in all_tests if pattern.search(t.name)]
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
        "passed_diag": 0
    }
    
    total = len(all_tests)
    suite_start_time = time.time()
    
    print_progress_bar(0, total, 0, suite_start_time)

    def handle_result(success, msg):
        stats["completed"] += 1
        if not success:
            stats["failed"] += 1
        elif "PASS (COMPILED)" in msg:
            stats["passed_compiled"] += 1
        elif "PASS (DIAG)" in msg:
            stats["passed_diag"] += 1
        
        sys.stdout.write('\r\033[K')
        
        if not success or "UPDATED" in msg: 
             print(msg)
        elif "PASS" in msg and total < 3000: 
             print(msg)
             
        print_progress_bar(stats["completed"], total, stats["failed"], suite_start_time)

    use_parallel = args.parallel

    if use_parallel:
        with ThreadPoolExecutor() as executor:
            future_to_test = {
                executor.submit(run_single_test, compiler_path, t, args.update, args.mode, temp_root): t 
                for t in all_tests
            }
            for future in as_completed(future_to_test):
                success, msg = future.result()
                handle_result(success, msg)
    else:
        for t in all_tests:
            success, msg = run_single_test(compiler_path, t, args.update, args.mode, temp_root)
            handle_result(success, msg)

    print()
    print("-" * 60)

    if stats["failed"] > 0:
        print(f"{Colors.FAIL}❌ Failed: {stats['failed']}/{total}{Colors.ENDC}")
        sys.exit(1)
    else:
        duration = time.time() - suite_start_time
        breakdown = f"({stats['passed_compiled']} Compiled, {stats['passed_diag']} Diag)"
        print(f"{Colors.OKGREEN}✅ All {total} tests passed {breakdown} in {duration:.2f}s!{Colors.ENDC}")
        sys.exit(0)

if __name__ == "__main__":
    main()