COMPILER="/home/cpsughrue/repos/llvm-project-fork/build/bin/clang++"

$COMPILER -fmodule-build-daemon -fmodules -fmodule-map-file=modules/module.modulemap modules/use.cpp -o use

