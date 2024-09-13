
# FlowWing CLI



### Example use of the FlowWing CLI in the terminal to use Raylib with FlowWing Platform MacOS

```bash

flowing --F=code.fg -O3 -L=path-of-raylib-library-directory -l=raylib  -framework=CoreFoundation -framework=CoreGraphics -framework=Cocoa -framework=IOKit -framework=CoreVideo 


```

# Web Server

```
 /Users/apple/code/per/Flow-Wing/targets/aot-compiler/aot-compiler-build/FlowWing --F=crow.fg -O3 -L=/Users/apple/code/per/Flow-Wing/docs/local/modules -l=crow  && build/bin/crow

  ```

/Users/apple/code/per/Flow-Wing/targets/aot-compiler/aot-compiler-build/FlowWing --F=server.fg -O3 -L=/Users/apple/code/per/Flow-Wing/docs/local/modules -l=server -e=main  && build/bin/server


## Creating dynamic lib c 

clang -fPIC -shared -o libwing.so flow-wing-server/server.c -I/opt/homebrew/include -L/opt/homebrew/lib        


## Creating static lib c++
clang++ -std=c++20 -fPIC -shared -o libcrow.so crowex.cpp -I/opt/homebrew/include -L/opt/homebrew/lib      

## Link 

 /Users/apple/code/per/Flow-Wing/targets/aot-compiler/aot-compiler-build/FlowWing --F=crow.fg -O3 -L=/Users/apple/code/per/Flow-Wing/docs/local/modules -l=crow&& build/bin/crow 


  /Users/apple/code/per/Flow-Wing/targets/aot-compiler/aot-compiler-build/FlowWing --F=flow-wing-server/server.fg -O3 -L=/Users/apple/code/per/Flow-Wing/docs/local/modules/flow-wing-server -l=wing && build/bin/server

## Local Development

 export DYLD_LIBRARY_PATH=/Users/apple/code/per/Flow-Wing/lib/mac-silicon/lib:$DYLD_LIBRARY_PATH    

 ### Symbolic link

 ln -s /Users/apple/code/per/Flow-Wing/lib/mac-silicon/lib /opt/homebrew/lib/FlowWing/lib