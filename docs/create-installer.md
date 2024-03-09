# AOT Installer for FlowWing

This file contains the instructions to create an AOT installer for FlowWing.

## Commands for AOT Compiler
 
- For Ubuntu (Debian) / Linux

- From the root of the FlowWing repository directory

  ```bash   
  cd dev-tools
  sudo ./run-aot-compiler-dev.sh
  ```

```
    cmake -G Ninja -DTESTS_ENABLED=OFF -DCMAKE_BUILD_TYPE=Release ..
    ninja
      cpack -G DEB
    cd release
    sudo dpkg -i FlowWing-0.0.1-Linux.deb   
```