#include <iostream>
#include <cstdlib>
#include <cctype>
#include <cmath>
#include "stack.h"
using namespace std;

// Functions performed while taking input. 
void parsePositive(int &counter, string str, string &temp, Stack<int> &s);
void parseNegative(int &counter, string str, string &temp, Stack<int> &s);
void executeCommand(char ch, Stack<int> &s);

// Functions called from letter commands. 
void printTop(Stack<int> s); // p
void topAndPop(Stack<int> &s); // n
void printStack(Stack<int> s); // f
void clearStack(Stack<int> &s); // c
void duplicateTop(Stack<int> &s); // d
void swapTopTwo(Stack<int> &s); // r

// Supported Math Operations
void add(Stack<int> &s); // +
void subtract(Stack<int> &s); // -
void multiply(Stack<int> &s); // *
void divide(Stack<int> &s); // /
void mod(Stack<int> &s); // %

// Extra Credit
void power(Stack<int> &s); // ^
void sqrRoot(Stack<int> &s); // v
void divideAndMod(Stack<int> &s); // ~

int main() {
    // PRE: Input from user is done in postfix notation. 
    // POST: Calculations are done depending on order of values pushed onto stack.
    Stack<int> operands;
    string s;
    string temp = "";

    while (cin) { // Terminate program with CTRL+D. 
        try {
            // Step 1: Get input of the entire line
            cin >> ws;
            getline(cin, s);

            // Step 2: Iterate through the line, parse and execute commands as needed. 
            for (int i = 0; i < s.length(); i++) {
                if (isdigit(s[i])) parsePositive(i, s, temp, operands);
                else if (s[i] == '_') parseNegative(i, s, temp, operands);
                else if (s[i] == '#') i = s.length() - 1; // Allow for comments
                else executeCommand(s[i], operands);
            }
            s = "";
            temp = "";

        } catch (OutOfMemory err) {
            cerr << "dc: number is outside range of type int" << endl;
        } catch (DataError err) {
            cerr << "dc: invalid expression" << endl;
        } catch (Overflow err) {
            cerr << "dc: stack is full" << endl;
        }
    }

    return 0;
}

void parsePositive(int &counter, string str, string &temp, Stack<int> &s) {
    // PRE: Driver program must be iterating through the input string and have
    //      a stack instantiated. 
    // POST: Parses the first instance of a positive integer while iterating and
    //       pushes that integer to the stack.
    for (counter = counter; isdigit(str[counter]); counter++) temp += str[counter];
    counter--;

    // Make the user re-input a line and stop parsing current line when decimal point
    // is inputted.
    if (str[counter] == '.') {
        counter = str.length() - 1;
        throw DataError();
    }

    // Check if outside upper bound of an int
    if (atol(temp.c_str()) > 2147483647) {
        temp = "";
        throw OutOfMemory();
    }

    if (s.isFull()) {
        temp = "";
        throw Overflow();
    } else {
        s.push(atoi(temp.c_str()));
        temp = "";
    }
}

void parseNegative(int &counter, string str, string &temp, Stack<int> &s) {
    // PRE: Driver program must be iterating through the input string and have
    //      a stack instantiated. 
    // POST: Parses the first instance of a negative integer while iterating and
    //      pushes that integer to the stack. 
    temp += "-";
    counter++;
    for (counter = counter; isdigit(str[counter]); counter++) temp += str[counter];
    counter--; // Prevents accidentally skipping a character in the input string.

    // Make the user re-input a line and stop parsing current line when decimal point
    // is inputted. 
    if (str[counter] == '.') {
        counter = str.length() - 1;
        throw DataError();
    }

    // Check if outside lower bound for an int
    if (atol(temp.c_str()) < -2147483647) {
        temp = "";
        throw OutOfMemory();
    }
    
    if (s.isFull()) {
        temp = "";
        throw Overflow();
    } else {
        if (temp == "-") s.push(0);
        else s.push(atoi(temp.c_str()));
        temp = "";
    }
}

void printTop(Stack<int> s) {
    // PRE: The stack contains at least one element when passed as an argument.
    // POST: Outputs the integer at the top of the stack. 
    if (s.isEmpty()) throw Underflow();
    else cout << s.top() << endl;
}

void topAndPop(Stack<int> &s) {
    // PRE: The stack contains at least one element when passed as an argument.
    // POST: Outputs and pops the integer at the top of the stack. 
    if (s.isEmpty()) throw Underflow();
    else cout << s.topAndPop() << " ";
}

void printStack(Stack<int> s) {
    // PRE: The stack contains at least one element when passed as an argument.
    // POST: Outputs all contents contained in the stack.
    if (s.isEmpty()) {
        throw Underflow();
    } else {
        while (!s.isEmpty()) {
            cout << s.top() << endl;
            s.pop();
        }
    }
}

void clearStack(Stack<int> &s) {
    // PRE: The stack has already been initialized when passed as an argument. 
    // POST: Removes all contents of the stack.
    s.makeEmpty();
}

void duplicateTop(Stack<int> &s) {
    // PRE: The stack contains at least one element when passed as an argument.
    // POST: Pushes onto the stack another copy of the value at the top of stack.
    if (s.isFull()) {
        throw Overflow();
    } else if (s.isEmpty()) {
        throw Underflow();
    } else {
        int copy = s.top();
        s.push(copy);
    }
}

void swapTopTwo(Stack<int> &s) {
    // PRE: The stack contains at least 2 elements when passed as an argument.
    // POST: Swaps the positions of the top and next top values of the stack. 
    int temp[2];
    if (s.isEmpty()) {
        throw Underflow();
    } else {
        for (int i = 0; i < 2; i++) temp[i] = s.topAndPop();
        for (int i = 0; i < 2; i++) s.push(temp[i]);
    }
}

void add(Stack<int> &s) {
    // PRE: The stack contains at least 2 elements when passed as an argument.
    // POST: Pushes the result of the two popped operands. 
    if (s.isEmpty()) {
        throw Underflow();
    } else {
        int op1 = s.topAndPop();
        int op2 = s.topAndPop();
        long sum = op2 + op1;

        // Check if outside bounds for an int
        if (sum < -2147483647 || sum > 2147483647) throw OutOfMemory();
        else s.push((int)sum);
    }
}

void subtract(Stack<int> &s) {
    // PRE: The stack contains at least 2 elements when passed as an argument.
    // POST: Pushes the result of the two popped operands.
    if (s.isEmpty()) {
        throw Underflow();
    } else {
        int op1 = s.topAndPop();
        int op2 = s.topAndPop(); 
        long difference = op2 - op1;

        // Check if outside bounds for an int
        if (difference < -2147483647 || difference > 2147483647) throw OutOfMemory();
        else s.push((int)difference);
        
    }
}

void multiply(Stack<int> &s) {
    // PRE: The stack contains at least 2 elements when passed as an argument.
    // POST: Pushes the result of the two popped operands.
    if (s.isEmpty()) {
        throw Underflow();
    } else {
        int op1 = s.topAndPop();
        int op2 = s.topAndPop();
        long product = op2 * op1;

        // Check if outside bounds for an int
        if (product < -2147483647 || product > 2147483647) throw OutOfMemory();
        else s.push((int)product);
    }
}

void divide(Stack<int> &s) {
    // PRE: The stack contains at least 2 elements when passed as an argument.
    // POST: Pushes the result of the two popped operands.
    if (s.isEmpty()) {
        throw Underflow();
    } else {
        int op1 = s.topAndPop();    
        int op2 = s.topAndPop();

        if (op1 == 0) {
            throw DivisionByZero();
        } else {
            long quotient = op2 / op1;
            // Check if outside bounds for an int
            if (quotient < -2147483647 || quotient > 2147483647) throw OutOfMemory();
            else s.push((int)quotient);
        }
    } 
}

void mod(Stack<int> &s) {
    // PRE: The stack contains at least 2 elements when passed as an argument.
    // POST: Pushes the result of the two popped operands.
    if (s.isEmpty()) {
        throw Underflow();
    } else {
        int op1 = s.topAndPop();
        int op2 = s.topAndPop();
        if (op1 == 0) throw DivisionByZero();
        else s.push(op2 % op1);
    }
}

void power(Stack<int> &s) {
    // PRE: The stack contains at least 2 elements when passed as an argument.
    // POST: Pushes the result of the two popped operands.
    if (s.isEmpty()) {
        throw Underflow();
    } else {
        int op1 = s.topAndPop();
        int op2 = s.topAndPop();
        long product = trunc(pow(op2, op1));

        // Check if outside bounds for an int
        if (product < -2147483647 || product > 2147483647) throw OutOfMemory();
        else s.push((int)product);
    }
}

void sqrRoot(Stack<int> &s) {
    // PRE: The stack contains at least 1 element when passed as an argument.
    // POST: Pushes the square root of the popped operand to the top of the stack.
    int op1 = s.topAndPop();
    if (op1 < 0) throw DataError();
    else s.push(round(sqrt(op1)));
}

void divideAndMod(Stack<int> &s) {
    // PRE: The stack contains at least 2 elements when passed as an argument.
    // POST: Pushes the result of the quotient then remainder. 
    if (s.isEmpty()) {
        throw Underflow();
    } else {
        int op1 = s.topAndPop();
        int op2 = s.topAndPop();

        if (op1 == 0) {
            throw DivisionByZero();
        } else {
            long quotient = op2 / op1;
            int remainder = op2 % op1;
            // Check if outside bounds for an int
            if (quotient < -2147483647 || quotient > 2147483647) {
                throw OutOfMemory();
            } else {
                s.push(quotient);
                s.push(remainder);
            }
        }
    }
}

void executeCommand(char ch, Stack<int> &s) {
    // PRE: Input has been taken from a full line and stack has been instantiated. 
    // POST: Program will execute specified commands or operations based on case. 
    try {
        switch (ch) {
            case 'p':
                printTop(s);
                break;

            case 'n':
                topAndPop(s);
                break;

            case 'f':
                printStack(s);
                break;

            case 'c':
                clearStack(s);
                break;

            case 'd':
                duplicateTop(s);
                break;

            case 'r':
                swapTopTwo(s);
                break;

            case '+':
                add(s);
                break;

            case '-':
                subtract(s);
                break;

            case '*':
                multiply(s);
                break;

            case '/':
                divide(s);
                break;

            case '%':
                mod(s);
                break;

            case '^':
                power(s);
                break;

            case 'v':
                sqrRoot(s);
                break;

            case '~':
                divideAndMod(s);
                break;

            case ' ':
                break;
            
            default: 
                throw DataError();
                break;
        }
    } catch (Underflow err) {
        cerr << "dc: stack is empty" << endl;
    } catch (DivisionByZero err) {
        cerr << "dc: division by zero" << endl;
    }
}

