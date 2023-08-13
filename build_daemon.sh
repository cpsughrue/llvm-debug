COMPILER=/home/cpsughrue/repos/llvm-project-fork/build/bin/clang++

# kill running daemon process if exists
PID=$(ps -aux | grep cc1 | grep -v grep | awk '{print $2}')
if [[ -n $PID ]]; then
    kill $PID
fi

# remove log file if exists
FILE="DaemonSocket.sock"
if [[ -f $FILE ]]; then
    rm $FILE
fi

# remove log file if exists
FILE="daemon.err"
if [[ -f $FILE ]]; then
    rm $FILE
fi

# remove log file if exists
FILE="daemon.out"
if [[ -f $FILE ]]; then
    rm $FILE
fi

# invoke daemon
$COMPILER -cc1modbuildd /tmp/clang-ALDKFJHALDKJF/clang-mbd 
