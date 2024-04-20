COMPILER="/home/cpsughrue/repos/llvm-project-fork/build/bin/clang++"

$COMPILER -std=c++20 -fmodules -fmodule-file=A=standard_modules/A.cppm -fmodule-file=B=standard_modules/B.cppm standard_modules/use.cpp -o use