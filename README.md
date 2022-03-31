# DC Calculator Program

Designed by: Ervin Pangilinan

Semester: Spring 2022 (v1.0) March 18, 2022

Course: CSC 245 - Data Stuctures & Algorithms Analysis 

Language Used: C++

## Objective
The goal of this project is to recreate the dc calculator found
in Linux terminals. The client program is designed with an implementation
file of a stack class. Input is taken from the keyboard in postfix
notation and will continue to do so until the user specifies the end
of file with CTRL+D.

## Command Line Syntax
    ./a.out

## Features
The base features for modifying the implemented stack are listed below along with
their respective commands:

- printing the top value of the stack (p)
- printing the top value value of the stack and popping it (n)
- printing the entire stack (f)
- clearing the entire stack (c)
- duplicating the top value of the stack (d)
- swapping the top two values of the stack (r)

The base math operations are listed below, along with their respective
symbols:

NOTE: The operations are done in the following order:

    (second-popped value) [operator] (first-popped value)

- addition (+)
- subtraction (-)
- multiplication (*)
- division (/)
- modulus (%)

Additional features are listed below:
- exponentiate (^)
- square root with truncated result (v) 
   *NOTE: This will only pop one value instead of two.
- quotient and remainder (~)
- reading the remainder of a line of input as a comment (#)
- error handling to prevent input of doubles and numbers larger or smaller than the bounds of a standard int

## Sample Input
Input is taken from the keyboard going line by line until end of input is reached.
An example is listed below:

    2 3 +
    p
    6 - p
    4 6 * + p
    2 / p
    4 % p
    2 100 +
    3 4 5 f
    5d*p
    rf2pc
    f
    <CTRL+D>

This input is taken in postfix notation and exception handling is done for any
instances of DataErrors, Stack Overflows, Stack Underflows, DivisionByZero, and
OutOfMemory errors. 

## Sample Output
Output will be shown on-screen depending on the operands and operators that were
previously inputted.
An example is listed below:

    5
    -1
    23
    11
    3
    5 4 3 102 3
    25
    5 25 4 3 102 3
    2

If an exception is caught, the program will output the following:

    dc: [error]

## OOP Design
Along with the implementation of a stack class, the following classes
are included in the client program:

- iostream
- cstdlib
- cctype
- cmath

## Program Outline
The client program can be split into 3 different steps:

- Step 1: Taking input
- Step 2: Parsing integers
- Step 3: Performing commands and operations

## Taking Input
The program runs until <CTRL+D> or end of file is met, so the program
will continue to process each line of input. To parse through a line
of input, the program iterates through the input line and determines
what case to follow depending on what each character is. The next 2
steps outline what the program will execute if the character can be
treated as an operand or operator.

## Parsing Integers
While iterating through the input line, if the program determines that the
character is a digit, the program will record the character at that index
and will concatenate to a string until a non-operand is met. When a non-operand
is found, the program will convert the operand string into an integer and push
it onto the stack. For negative numbers, if a '_' is found, the program will first
concatenate a '-' onto the operand string then continue as normal for a positive 
integer.

Possible exceptions that can arise are DataErrors from inputting a double value
and OutOfMemory errors from inputting integers that are outside the range of a
standard int. When these exceptions occur, the program will not parse the input
and instead skips the rest of the line.

## Performing Operations & Commands
When a symbol is reached that denotes a operation or command, it will perform
the given action based on the symbol and continues to iterate through the input
string. This action is applicable to all stack commands and math operations.



