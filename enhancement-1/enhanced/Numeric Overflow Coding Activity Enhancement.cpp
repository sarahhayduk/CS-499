// Numeric Overflow Coding Activity Enhancement.cpp : This file contains the 'main' function. Program execution begins and ends there.

/********************************
 * Sarah Hayduk
 * SNHU CS-499 Capstone
 * Enhancement Category 1
 * Software Engineering & Design
 ********************************/

#include <iostream>
#include <limits>
#include "SafeArithmetic.h"

/*----------------------------------------------------------------------------------
* test_overflow
*
* This function checks overflow behavior across all arithmetic operations. Each
* test block uses the same parameter pattern (start, value, steps) to match the
* SafeArithmetic module. Scope blocks keep the variables isolated and avoid naming
* conflicts or shadowed variables while keeping the structure consistent.
* Division cannot overflow for unsigned integers. For signed integers, the only
* overflow case occurs when dividing the minimum representable value by -1.
* ---------------------------------------------------------------------------------*/

template <typename T>
void test_overflow()
{
    std::cout << "\nOverflow Test of Type = " << typeid(T).name() << std::endl;

    bool success = true;
    T result = 0;

    // --------------- ADDITION OVERFLOW ---------------
    {
        T start = 0;
        T value = std::numeric_limits<T>::max() / 5;
        unsigned long int steps = 5;

        // --- Addition without overflow ---
        std::cout << "\tAddition Without Overflow (" << +start << ", " << +value << ", " << steps << ") = ";
        result = safe_add<T>(start, value, steps, success);
        std::cout << +result << std::endl;

        // --- Addition with overflow ---
        std::cout << "\tAddition With Overflow (" << +start << ", " << +value << ", " << (steps + 1) << ") = ";
        result = safe_add<T>(start, value, steps + 1, success);
        std::cout << "[Overflow Detected: " << std::boolalpha << !success << "], Safe Result = " << +result << std::endl;
    }

    // --------------- SUBTRACTION OVERFLOW ---------------
    {
        T start = 0;
        T value = std::numeric_limits<T>::max() / 5;
        unsigned long int steps = 5;

        // Unary minus operator applied only to signed types
        if constexpr (std::is_signed<T>::value)
        {
            value = -value;
        }

        // --- Subtraction without overflow ---
        std::cout << "\tSubtraction Without Overflow (" << +start << ", " << +value << ", " << steps << ") = ";
        result = safe_subtract<T>(start, value, 1, success);
        std::cout << +result << std::endl;

        // --- Subtraction with overflow ---
        std::cout << "\tSubtraction With Overflow (" << +start << ", " << +value << ", " << (steps + 1) << ") = ";
        result = safe_subtract<T>(start, value, steps + 1, success);
        std::cout << "[Overflow Detected: " << std::boolalpha << !success << "], Safe Result = " << +result << std::endl;
    }

    // --------------- MULTIPLICATION OVERFLOW ---------------
    {
        T start = std::numeric_limits<T>::max() / 3;
        T value = 2;
        unsigned long int steps = 1;

        // --- Multiplication without overflow ---
        std::cout << "\tMultiplication Without Overflow (" << +start << ", " << +value << ", " << steps << ") = ";
        result = safe_multiply<T>(start, value, steps, success);
        std::cout << +result << std::endl;

        // --- Multiplication with overflow ---
        std::cout << "\tMultiplication With Overflow (" << +start << ", " << +value << ", " << (steps + 1) << ") = ";
        result = safe_multiply<T>(start, value, steps + 1, success);
        std::cout << "[Overflow Detected: " << std::boolalpha << !success << "], Safe Result = " << +result << std::endl;
    }

    // --------------- DIVISION OVERFLOW ---------------
    {
        T start = std::numeric_limits<T>::min();
        T value = 1;
        unsigned long int steps = 1;

        // --- Division without overflow ---
        std::cout << "\tDivision Without Overflow (" << +start << ", " << +value << ", " << steps << ") = ";
        result = safe_divide<T>(start, value, steps, success);
        std::cout << +result << std::endl;

        // --- Division with overflow ---
        if constexpr (std::is_signed<T>::value)
        {
            value = -value; // Unary minus operator applied only to signed types
        }

        std::cout << "\tDivision With Overflow (" << +start << ", " << +value << ", " << +steps << ") = ";
        result = safe_divide<T>(start, value, steps, success);
        std::cout << "[Overflow Detected: " << std::boolalpha << !success << "], Safe Result = " << +result << std::endl;
    }
}

/*----------------------------------------------------------------------------------
* test_underflow
*
* This function checks underflow behavior across all arithmetic operations. Each
* test block uses the same parameter pattern (start, value, steps) to match the
* SafeArithmetic module. Scope blocks keep the variables isolated and avoid naming
* conflicts or shadowed variables while keeping the structure consistent.
* Division cannot underflow for these numeric types because the result always moves 
* toward zero. Division underflow is replaced by divide-by-zero checks.
* ---------------------------------------------------------------------------------*/
template <typename T>
void test_underflow()
{
    std::cout << "\nUnderflow Test of Type = " << typeid(T).name() << std::endl;
    
    bool success = true;
    T result = 0;

    // --------------- ADDITION UNDERFLOW ---------------
    {
        T start = std::numeric_limits<T>::min() + 1;
        T value = std::numeric_limits<T>::max() / 5;
        unsigned long int steps = 1;

        // Unary minus operator applied only to signed types
        if constexpr (std::is_signed<T>::value)
        {
            value = -value;
        }

        // Addition without underflow
        std::cout << "\tAddition Without Underflow (" << +start << ", " << +value << ", " << steps << ") = ";
        result = safe_add<T>(start, value, steps, success);
        std::cout << +result << std::endl;

        // Addition with underflow
        std::cout << "\tAddition With Underflow (" << +start << ", " << +value << ", " << (steps + 1) << ") = ";
        result = safe_add<T>(start, value, steps + 1, success);
        std::cout << "[Underflow Detected: " << std::boolalpha << !success << "], Safe Result = " << +result << std::endl;
    }

    // --------------- SUBTRACTION UNDERFLOW ---------------
    {
        T start = std::numeric_limits<T>::min();
        T value = std::numeric_limits<T>::max() / 3;
        unsigned long int steps = 1;

        // Subtraction without overflow
        std::cout << "\tSubtraction Without Underflow (" << +start << ", " << +value << ", " << steps << ") = ";
        result = safe_subtract<T>(start, value, steps, success);
        std::cout << +result << std::endl;

        // Subtraction with underflow
        std::cout << "\tSubtraction With Underflow (" << +start << ", " << +value << ", " << (steps + 1) << ") = ";
        result = safe_subtract<T>(start, value, steps + 1, success);
        std::cout << "[Underflow Detected: " << std::boolalpha << !success << "], Safe Result = " << +result << std::endl;
    }

    // --------------- MULTIPLICATION UDNERFLOW ---------------
    {
        T start = std::numeric_limits<T>::min() / 3;
        T value = 2;
        unsigned long int steps = 1;

        // Multiplication without underflow
        std::cout << "\tMultiplication Without Underflow (" << +start << ", " << +value << ", " << steps << ") = ";
        result = safe_multiply<T>(start, value, steps, success);
        std::cout << +result << std::endl;

        // Multiplication with underflow
        std::cout << "\tMultiplication With Underflow (" << +start << ", " << +value << ", " << (steps + 1) << ") = ";
        result = safe_multiply<T>(start, value, steps + 1, success);
        std::cout << "[Underflow Detected: " << std::boolalpha << !success << "], Safe Result = " << +result << std::endl;
    }

    // --------------- DIVISION FAILURE (DIVIDE BY ZERO) ---------------
    {
        T start = std::numeric_limits<T>::max();
        T value = 0;
        unsigned long int steps = 1;

        // Divide by zero
        std::cout << "\tDivision By Zero (" << +start << ", " << +value << ", " << steps << ") = ";
        result = safe_divide<T>(start, value, steps, success);
        std::cout << "[Divide-By-Zero Detected: " << std::boolalpha << !success << "], Safe Result = " << +result << std::endl;
    }
}

/*----------------------------------------------------------------------------------
* do_overflow_tests
* ---------------------------------------------------------------------------------*/
void do_overflow_tests(const std::string& star_line)
{
    std::cout << std::endl << star_line << std::endl;
    std::cout << "****** Running Overflow Tests ******" << std::endl;
    std::cout << star_line << std::endl;

    // Testing C++ primative times see: https://www.geeksforgeeks.org/c-data-types/
    // signed integers
    test_overflow<char>();
    test_overflow<wchar_t>();
    test_overflow<short int>();
    test_overflow<int>();
    test_overflow<long>();
    test_overflow<long long>();

    // unsigned integers
    test_overflow<unsigned char>();
    test_overflow<unsigned short int>();
    test_overflow<unsigned int>();
    test_overflow<unsigned long>();
    test_overflow<unsigned long long>();

    // real numbers
    test_overflow<float>();
    test_overflow<double>();
    test_overflow<long double>();
}

/*----------------------------------------------------------------------------------
* do_underflow_tests
* ---------------------------------------------------------------------------------*/
void do_underflow_tests(const std::string& star_line)
{
    std::cout << std::endl << star_line << std::endl;
    std::cout << "****** Running Underflow Tests *****" << std::endl;
    std::cout << star_line << std::endl;

    // Testing C++ primative times see: https://www.geeksforgeeks.org/c-data-types/
    // signed integers
    test_underflow<char>();
    test_underflow<wchar_t>();
    test_underflow<short int>();
    test_underflow<int>();
    test_underflow<long>();
    test_underflow<long long>();

    // unsigned integers
    test_underflow<unsigned char>();
    test_underflow<unsigned short int>();
    test_underflow<unsigned int>();
    test_underflow<unsigned long>();
    test_underflow<unsigned long long>();

    // real numbers
    test_underflow<float>();
    test_underflow<double>();
    test_underflow<long double>();
}

/*----------------------------------------------------------------------------------
* main
* 
* Entry point into the application. Runs the overflow and underflow tests.
* Retuns 0 when complete.
* ---------------------------------------------------------------------------------*/
int main()
{
    // Create a string of "*" to use in the console
    const std::string star_line = std::string(36, '*');

    std::cout << "Starting Numeric Overflow / Underflow Tests!" << std::endl;

    // Run the tests
    do_overflow_tests(star_line);
    do_underflow_tests(star_line);

    std::cout << std::endl << "All Numeric Underflow / Overflow Tests Complete!" << std::endl;
    std::cout << "\nCS-499 Computer Science Capstone\nRefactor by: Sarah Hayduk" << std::endl;

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu
