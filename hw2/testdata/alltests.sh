#!/bin/bash

# alltests.sh executable-or-.py

TIMEOUT=30
CYCLES=100

if [[ $# != 1 ]]
then
  echo "Usage: $0 path-to-executable-program-or-main.py"
  exit 0
fi

EXECMD="$1"
# if [[ ${EXECMD##*.} = "py" ]]
# then
#   EXECMD="python3 $EXECMD"
# fi

echo "Running $EXECMD ..."
echo "Differences to expected output in basic tests:"

# Go through all input data files
for i in *.in
do
  # ../cpp/model_solution/a.out <$i >$(basename $i .in)-cpp.out
  # python3 ../python/model_solution/main.py <$i >$(basename $i .in)-python.out
  echo $i ":"
  $EXECMD <$i | diff -w --unified - $(basename $i .in).out
done

echo ""
echo "Performance tests (timeout $TIMEOUT seconds):"

for n in 10 30 100 300 1000 3000 10000 30000 # 100000 300000 1000000 3000000 10000000
do
  echo -n $n " , "
  echo "P $n $CYCLES" | timeout $TIMEOUT $EXECMD >/dev/null
  if [[ $? != 0 ]]
  then
    echo "Timeout!"
    break
  fi
done
echo ""
