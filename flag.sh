COMPILER=~/repos/llvm-project-fork/build/bin/clang++

$COMPILER -fmodule-build-daemon main.cpp

FILE="a.out"
if [[ -f $FILE ]]; then
    rm $FILE
fi
