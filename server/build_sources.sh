COMPILER=/home/connor/llvm/llvm-project-fork/build/bin/clang++

#TIME=$(date +%s)
#echo $TIME

TIME=$(uuidgen)


$COMPILER -fbuild-session-timestamp=$TIME sources/main.cpp sources/add.cpp -o app
rm app
