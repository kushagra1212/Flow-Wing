
import os
import subprocess
from colorama import Fore, Style


# Define paths based on current script location
current_file_path = os.path.realpath(__file__)
current_dir_path = os.path.dirname(current_file_path)
build_dir_path = os.path.join(current_dir_path, "..", "all-targets", "jit-compiler", "build")
lib_dir_path = os.path.join(current_dir_path, "..", "src", "lib")


# Build commands
llc_command = [
    "llc",
    "-mtriple=wasm32-unknown-wasi",
    "-filetype=obj",
    "-o",
    os.path.join(build_dir_path, "my_module.o"),
    os.path.join(build_dir_path, "my_module.ll"),
]

wasm_ld_command = [
    "wasm-ld",
    "--no-entry",
    "--export-dynamic",
    "--import-memory",
    "-L",
    os.path.join(lib_dir_path, "wasi"),
    os.path.join(build_dir_path, "my_module.o"),
    os.path.join(lib_dir_path, "wasm32-wasi", "libc.a"),
    os.path.join(lib_dir_path, "wasm32-wasi", "libm.a"),
    "-lclang_rt.builtins-wasm32",
    "-o",
    os.path.join(build_dir_path, "my_module.wasm"),
]


# Execute commands and display output with status messages and colors
def run_command(command, message):
    print(f"\n{Fore.GREEN}{message}:")
    completed_process = subprocess.run(command, capture_output=True)
    if completed_process.returncode == 0:
        print(f"{Fore.GREEN}Success!{Style.RESET_ALL}")
    else:
        print(f"{Fore.RED}Failure!{Style.RESET_ALL}")
        print(f"{Fore.YELLOW}Error output:\n{completed_process.stderr.decode()}{Style.RESET_ALL}")


run_command(llc_command, "Compiling my_module.ll to object file")
run_command(wasm_ld_command, "Linking object file and libraries to create my_module.wasm")

print(f"\n{Fore.CYAN}Build completed.{Style.RESET_ALL}")




















































