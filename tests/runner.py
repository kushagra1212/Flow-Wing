#!/usr/bin/env python3
import os
import sys
import subprocess
import argparse
import difflib
import time
import re
import shutil
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path

class Colors:
    HEADER = '\033[95m'
    OKBLUE = '\033[94m'
    OKGREEN = '\033[92m'
    WARNING = '\033[93m'
    FAIL = '\033[91m'
    ENDC = '\033[0m'

def run_single_test(compiler_bin, file_path, update_mode, mode, temp_root):
    try:
        start_time = time.time()
        
        # --- AOT MODE: COMPILE THEN RUN ---
        if mode == "aot":
            # 1. Create a specific temp dir for this test to avoid collisions
            # e.g., build/bin/test_artifacts/hello-world/
            test_temp_dir = temp_root / file_path.stem
            test_temp_dir.mkdir(parents=True, exist_ok=True)

            # 2. Compile
            # Output rule: --output-dir="DIR" -> places binary at "DIR/bin/filename"
            compile_cmd = [
                str(compiler_bin), 
                str(file_path), 
                f'--output-dir={test_temp_dir}'
            ]
            
            compile_result = subprocess.run(
                compile_cmd, capture_output=True, text=True
            )
            
            if compile_result.returncode != 0:
                return False, f"{Colors.FAIL}[COMPILE FAIL]{Colors.ENDC} {file_path.name}\n{compile_result.stderr}\n{compile_result.stdout}"

            # 3. Locate Binary
            # Based on your log: "myfiles/bin/hello-world"
            binary_name = file_path.stem
            binary_path = test_temp_dir / "bin" / binary_name

            
            if not binary_path.exists():
                 return False, f"{Colors.FAIL}[MISSING BINARY]{Colors.ENDC} Expected at: {binary_path}"

            # 4. Set command to run the generated binary
            run_cmd = [str(binary_path)]

        # --- JIT MODE: RUN DIRECTLY ---
        else:
            run_cmd = [str(compiler_bin), str(file_path)]

        # --- EXECUTE ---
        # Run either the JIT compiler OR the AOT compiled binary
        result = subprocess.run(
            run_cmd,
            capture_output=True,
            text=True,
            timeout=5
        )
        duration = (time.time() - start_time) * 1000

        actual_output = result.stdout
        stderr_output = result.stderr

        # --- CLEANUP (AOT only) ---
        if mode == "aot" and temp_root.exists():
             # We clean up the specific test folder we made
             shutil.rmtree(test_temp_dir, ignore_errors=True)

        # --- VERIFICATION ---
        expect_file = file_path.with_suffix(".expect")

        if update_mode:
            with open(expect_file, 'w') as f:
                f.write(actual_output)
            return True, f"{Colors.OKBLUE}[UPDATED]{Colors.ENDC} {file_path.name}"

        if not expect_file.exists():
            return False, f"{Colors.WARNING}[MISSING]{Colors.ENDC} {file_path.name} (No .expect file)"

        with open(expect_file, 'r') as f:
            expected_output = f.read()

        if actual_output == expected_output:
            return True, f"{Colors.OKGREEN}[PASS]{Colors.ENDC} {file_path.name} ({duration:.1f}ms)"
        else:
            diff = difflib.unified_diff(
                expected_output.splitlines(),
                actual_output.splitlines(),
                fromfile='Expected',
                tofile='Actual',
                lineterm=''
            )
            diff_text = "\n".join(list(diff))
            if stderr_output:
                 diff_text += f"\n{Colors.WARNING}--- STDERR ---{Colors.ENDC}\n{stderr_output}"
            
            return False, f"{Colors.FAIL}[FAIL]{Colors.ENDC} {file_path.name}\n{diff_text}"

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
    # NEW ARGUMENT
    parser.add_argument("--mode", choices=["jit", "aot"], default="jit", help="Execution mode")
    args = parser.parse_args()

    compiler_path = Path(args.bin)
    test_dir = Path(args.dir)

    # Directory for temporary AOT binaries
    # We use a subfolder in build/bin so it's ignored by git usually
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
    
    failed = 0
    with ThreadPoolExecutor() as executor:
        # Pass new args: args.mode and temp_root
        futures = {executor.submit(run_single_test, compiler_path, t, args.update, args.mode, temp_root): t for t in all_tests}
        for future in futures:
            success, msg = future.result()
            print(msg)
            if not success: failed += 1

    if failed > 0:
        print(f"\n{Colors.FAIL}{failed} tests failed.{Colors.ENDC}")
        sys.exit(1)
    else:
        print(f"\n{Colors.OKGREEN}All tests passed!{Colors.ENDC}")
        sys.exit(0)

if __name__ == "__main__":
    main()