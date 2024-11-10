@echo off
REM Check if the input file is provided as an argument
IF "%~1"=="" (
    echo Usage: %0 ^<input_file.ll^>
    exit /b 1
)

REM Assign input file name to a variable
set input_file=%~1

REM Check if the input file exists
IF NOT EXIST "%input_file%" (
    echo Error: Input file '%input_file%' does not exist.
    exit /b 1
)

REM Extract the filename without extension
for %%F in ("%input_file%") do set filename_no_ext=%%~nF

REM Perform the conversion using llvm-as
llvm-as "%input_file%" -o "%filename_no_ext%.bc"

REM Check if conversion was successful
IF ERRORLEVEL 1 (
    echo Error: Conversion failed.
    exit /b 1
)

REM Create Object Files (.o)
llc -relocation-model=pic -filetype=obj "%input_file%" -o "%filename_no_ext%.o"

REM Create a static library (.lib) using llvm-lib
llvm-lib /out:"%filename_no_ext%.lib" "%filename_no_ext%.o" 

REM Check if library creation was successful
IF ERRORLEVEL 1 (
    echo Error: Library creation failed.
    exit /b 1
)

echo Conversion and library creation successful. Output file: %filename_no_ext%.lib
