#!/bin/bash
x=0
while [ $x -le 500 ]
do
  echo "Welcome $x times"
  touch "plot$x.js"
  x=$(( $x + 1 ))
done
