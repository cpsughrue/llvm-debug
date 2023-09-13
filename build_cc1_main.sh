COMPILER=~/repos/llvm-project-fork/build/bin/clang++

$COMPILER -cc1 -fmodule-build-daemon -triple x86_64-unkown-linux-gnu -invalid_flag -o main.cpp.o -x c++ main.cpp

FILE="main.cpp.o"
if [[ -f $FILE ]]; then
    rm $FILE
fi
