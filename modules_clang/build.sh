COMPILER="/home/cpsughrue/repos/llvm-project-fork/build/bin/clang++"

$COMPILER -fmodule-build-daemon use.cpp -o use  -fmodules -fmodule-map-file=module.modulemap 

