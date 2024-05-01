# Project Setup Instructions Mac-OS

Follow these steps to set up the project:

1. **Clone the current repository**
    ```
    git clone https://github.com/kushagra1212/Flow-Wing
    ```

2. **Check the Clang version**
    ```
    /usr/bin/clang --version
    ```

3. **Install the necessary tools**
    - Install LLVM 17
        ```
        brew install llvm@17
        ```
    - Install Google Test
        ```
        brew install googletest
        ```
    - Install CMake (version 3.22 or higher)
        ```
        brew install cmake
        ```
    - Install Ninja
        ```
        brew install ninja
        ```

4. **Update ~/.zshrc**
    - Add the following line to your `~/.zshrc` file to update your PATH:
        ```
        export PATH="/opt/homebrew/opt/llvm@17:$PATH"
        export PATH="/opt/homebrew/opt/llvm@17/bin:$PATH"
        ```
    - Then, source your `~/.zshrc` file to apply the changes:
        ```
        source ~/.zshrc
        ```
