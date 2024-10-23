# AOT Installer for FlowWing

This file contains the instructions to create an AOT installer for FlowWing.

## Commands for AOT Compiler

- For Ubuntu (Debian) / Linux

- From the root of the FlowWing repository directory

  ```bash
  cd scripts/dev
  sudo ./run-aot-compiler-dev.sh
  ```

```
    cmake -G Ninja -DTESTS_ENABLED=OFF -DCMAKE_BUILD_TYPE=Release ..
    ninja
      cpack -G DEB
    cd release
    sudo dpkg -i FlowWing-0.0.1-Linux.deb
```

# Create Home Brew Installer

tar -cvf FlowWing-0.0.1.tar.gz FlowWing-0.0.1

a FlowWing-0.0.1
a FlowWing-0.0.1/.DS_Store
a FlowWing-0.0.1/bin
a FlowWing-0.0.1/lib
a FlowWing-0.0.1/lib/libflowwing_map.so
a FlowWing-0.0.1/lib/libflowwing_string.a
a FlowWing-0.0.1/lib/libraylib.a
a FlowWing-0.0.1/lib/libflowwing_vector.so
a FlowWing-0.0.1/lib/libbuilt_in_module.a
a FlowWing-0.0.1/lib/modules
a FlowWing-0.0.1/lib/modules/Str-module.fg
a FlowWing-0.0.1/lib/modules/Map-module.fg
a FlowWing-0.0.1/lib/modules/Err-module.fg
a FlowWing-0.0.1/lib/modules/Vec-module.fg
a FlowWing-0.0.1/lib/modules/File-module.fg
a FlowWing-0.0.1/bin/FlowWing

shasum -a 256 FlowWing-0.0.1.tar.gz
