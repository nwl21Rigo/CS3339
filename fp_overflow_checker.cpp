#include <bitset>
#include <cmath>
#include <cstring>
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

// For this homework you will write a program that will automatically detect
// floating-point overflow in C++ programs. You can limit yourself to the type
// of overflow that occurs in the examples we studied in class. The examples can
// be found in our course Git repo. Your program will receive two inputs as
// floating-point values, analyze them and then tell the user (i) if an overflow
// will1 occur and (2) what is the minimum threshold for the overflow to occur.
// Essentially, you want to find the smallest floating-point value for which an
// increment by the loop-counter value is lost because there aren’t enough bits
// in the fraction segment. This homework will enhance your understanding of
// data representation in memory and the pitfalls offloating-point arithmetic.
// It will also give you some practice in bit manipulation in C++, which can be
// an effective tool for improving program efficiency.

// function to convert a floating point number to binary(iee754))
string floatToBinary(float num) {
  bitset<32> binary;
  memcpy(&binary, &num, sizeof(float));
  string sign = binary.test(31) ? "1" : "0";
  string exponent = binary.to_string().substr(1, 8);
  string fraction = binary.to_string().substr(9);
  return sign + " " + exponent + " " + fraction;
}

int main(int argc, char *argv[]) {
  // check that the command line arguments are 3
  if (argc != 3) {
    cout << "usage: " << endl;
    cout << "\t./fp_overflow_checker loop_bound loop_counter" << endl;
    cout << endl;
    cout << "\tloop_bound is a positive floating-point value" << endl;
    cout << "\tloop_counter is a positive floating-point value" << endl;
    cout << endl;
    return 0;
  }
  // initialize variables
  float loopBound, loopCounter;
  // parse input(command_line_arguments)
  loopBound = stof(argv[1]);
  loopCounter = stof(argv[2]);

  // display both values into ieee754 binary
  cout << endl;
  cout << "Loop bound:   " << floatToBinary(loopBound) << endl;
  cout << "Loop counter: " << floatToBinary(loopCounter) << endl;
  cout << endl;

  // check for overflow
  float threshold = loopCounter + (1 << 24);
  if (loopBound > threshold) {
    // if overflow occurs, print warning message
    cout << "WARNING: Possible overflow" << endl;
    cout << "Overflow threshold: " << endl;
    cout << "\t" << threshold << endl;
    // now in binary
    cout << "\t" << floatToBinary(threshold) << endl;
  } else {
    // no overflow statement
    cout << "There is no overflow!" << endl;
  }
  return 0;
}
