COMPILER="/home/cpsughrue/repos/llvm-project-fork/build/bin/clang++"

$COMPILER -fmodule-build-daemon clang_modules/use.cpp -o use  -fmodules -fmodule-map-file=clang_modules/module.modulemap 

