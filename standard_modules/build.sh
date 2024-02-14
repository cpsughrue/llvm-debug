COMPILER="/home/cpsughrue/repos/llvm-project-fork/build/bin/clang++"

$COMPILER -std=c++20 A.cppm --precompile -o A.pcm
$COMPILER -std=c++20 B.cppm --precompile -fmodule-file=A=A.pcm -o B.pcm

$COMPILER -std=c++20 use.cpp -fmodule-file=A=A.pcm -fmodule-file=B=B.pcm A.pcm B.pcm -o use

rm A.pcm B.pcm use