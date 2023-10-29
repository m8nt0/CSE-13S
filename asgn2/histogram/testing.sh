#!/bin/bash

#basically used to test
formula() {
    echo -e "$1"
    echo -e "$2" | ./histogram
}

formula  "Simple 1-10 input" "1 2 3 4 5 6 7 8 9 10"

formula  "First Example demonstrated" "3 -4 5 1 7 0 8 0 15 12 3 5 3 3 3 3 3"

formula  "Second Example demonstrated" "3 -4 5 1 7 0 8 0 15 12 3 5 18 19 20 30 7 12 50 34 32 19 44"

formula  "Third Example demonstrated" "150"

formula  "Putting values outside the intial limit" "100 200 300"

formula  "Putting a high number first try" "500"

formula  "Input with more numbers than the initial range" "1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16"

