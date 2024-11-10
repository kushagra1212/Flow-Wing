cmake -G "Ninja" -DTESTS_ENABLED=OFF -DCMAKE_BUILD_TYPE=Release -DLLVM_TARGETS_TO_BUILD=X64 -DLLVM_DIR="C:\\llvm\\lib\\cmake\\llvm" -DCMAKE_TOOLCHAIN_FILE="C:\\vcpkg\\scripts\\buildsystems\\vcpkg.cmake" -DZLIB_INCLUDE_DIR="C:\\vcpkg\\installed\\x64-windows\\include" -DZLIB_LIBRARY="C:\\vcpkg\\installed\\x64-windows\\lib\\zlib.lib" -DCMAKE_MODULE_PATH="C:\\vcpkg\\installed\\x64-windows\\share" -DCMAKE_PREFIX_PATH="C:\\vcpkg\\installed\\x64-windows"  --fresh ..









clang++ -o build/bin/test build/objects/flowmain.obj -LC:\Users\kusha\Flow-Wing\lib\win-x86_64\lib -lucrt -llegacy_stdio_definitions -lbuilt_in_module -lgc -lflowwing_string -Wl,/ENTRY:flowmain -Wl,/SUBSYSTEM:CONSOLE -Wl,/IGNORE:4210
