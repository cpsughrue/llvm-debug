COMPILER=~/repos/llvm-project-fork/build/bin/clang++

$COMPILER main.cpp 

FILE="a.out"
if [[ -f $FILE ]]; then
    rm $FILE
fi
