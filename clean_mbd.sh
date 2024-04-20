# kill all running daemon process if exists
PID=$(ps -aux | grep cc1 | grep -v grep | awk '{print $2}')
if [[ -n $PID ]]; then
    kill $PID
fi

# remove clang directory from tmp if exists
find /tmp/ -type d -name 'clang-*' 2>/dev/null -exec rm -rf {} \;

