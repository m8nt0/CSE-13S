#!/bin/bash

# Zero argument
./coolness > output.txt
diff -q output.txt noInputs.txt
if [ $? -eq 0 ]; then
  echo "Successful of Matching"
else
  echo "Unsuccessful of Matching"
fi

# Only T
./coolness 32.0 > output.txt
diff -q output.txt oneInput.txt
if [ $? -eq 0 ]; then
  echo "Successful of Matching"
else
  echo "Unsuccessful of Matching"
fi

# Both T and V provided
./coolness 32.5 10.0 > output.txt
diff -q output.txt twoInput.txt
if [ $? -eq 0 ]; then
  echo "Successful of Matching"
else
  echo "Unsuccessful of Matching"
fi

# Passed the capstone of TEMP
# It tests if an error occurs and if it does, it will say succesful
./coolness 116.0 10.0
if [ $? -eq 1 ]; then
  echo "Returned an Error: Successful"
else
  echo "Failed: Unsuccessful in returning Error"
fi

# Didn't surpass the wind limit
./coolness 25.0 0.2
if [ $? -eq 1 ]; then
  echo "Returned an Error: Successful"
else
  echo "Failed: Unsuccessful in returning Error"
fi

# More arguments provided
./coolness 25.0 10.0 15.0
if [ $? -eq 1 ]; then
  echo "Returned an Error: Successful"
else
  echo "Failed: Unsuccessful in returning Error"
fi

rm -f output.txt

