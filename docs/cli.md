# FlowWing CLI

### Example use of the FlowWing CLI in the terminal to use Raylib with FlowWing Platform MacOS

```bash

flowing --F=code.fg -O3 -L=path-of-raylib-library-directory -l=raylib  -framework=CoreFoundation -framework=CoreGraphics -framework=Cocoa -framework=IOKit -framework=CoreVideo


```

# Web Server

/Users/apple/code/per/Flow-Wing/targets/aot-compiler/aot-compiler-build/FlowWing --F=server.fg -O3 -L=/Users/apple/code/per/Flow-Wing/docs/local/modules -l=server -e=main && build/bin/server

## Creating dynamic lib c

clang -fPIC -shared -o libwing.so flow-wing-server/server.c -I/opt/homebrew/include -L/opt/homebrew/lib

## Creating static lib c++

clang++ -std=c++20 -fPIC -shared -o libcrow.so crowex.cpp -I/opt/homebrew/include -L/opt/homebrew/lib

## Link

'/Users/apple/code/per/Flow-Wing/targets/aot-compiler/aot-compiler-build/FlowWing --F=flow-wing-server/server.fg -O3 -L=/Users/apple/code/per/Flow-Wing/docs/local/modules/flow-wing-server -l=wing && build/bin/server

## Local Development

### For Mac

export DYLD_LIBRARY_PATH=/Users/apple/code/per/Flow-Wing/lib/mac-silicon/lib:$DYLD_LIBRARY_PATH

### For Linux

export LD_LIBRARY_PATH=/home/kushagra/code/Flow-Wing/lib/linux-x86_64/lib:$LD_LIBRARY_PATH
export  LDFLAGS="-L/usr/lib/:/home/kushagra/code/Flow-Wing/lib/linux-x86_64/lib"
### Symbolic link

ln -s /Users/apple/code/per/Flow-Wing/lib/mac-silicon/lib /opt/homebrew/lib/FlowWing/lib

### Creating Static lib for built in modules

llc -opaque-pointers -relocation-model=pic -filetype=asm temp/libbuilt_in_module.ll -o temp/libbuilt_in_module.s
clang-17 -c -fPIC temp/libbuilt_in_module.s -o temp/libbuilt_in_module.o
or

llc -opaque-pointers -relocation-model=pic -filetype=obj temp/libbuilt_in_module.ll -o temp/libbuilt_in_module.o

ar rcs libbuilt_in_module.a temp/libbuilt_in_module.o

## Creating Dynamic lib (Linux/Mac)

clang-17 -shared -o libbuilt_in_module.so temp/libbuilt_in_module.o

# Check for Memory Leaks

./FlowWing -F=v.fg && leaks -atExit -- build/bin/v | grep LEAK:
