#!/bin/bash

COMMAND='clang++ -g -o sorting -I ../../common -I ../../data_structures *.cpp'
echo "$COMMAND"
$COMMAND
EXITCODE=$?

if [[ $EXITCODE = 0 ]]
then
  echo "executable 'sorting' built successfully"
fi

exit $EXITCODE
