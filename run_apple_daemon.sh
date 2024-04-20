COMPILER="/home/cpsughrue/repos/llvm-project-apple/build/bin/clang++"

$COMPILER -cc1depscand -run $PWD/apple-daemon -long-running
