COMPILER=/home/cpsughrue/repos/llvm-project-fork/build/bin/clang++

$COMPILER -fmodule-build-daemon sources/main.cpp sources/add.cpp -o app
rm app
