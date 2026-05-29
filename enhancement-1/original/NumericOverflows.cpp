// NumericOverflows.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

/*************************
 * Sarah Hayduk (SH)
 * CS405 1-3 Activity
 * 1/5/2026
 *************************/
#include <iostream>     // std::cout
#include <limits>       // std::numeric_limits

/// <summary>
/// Template function to abstract away the logic of:
///   start + (increment * steps)
/// </summary>
/// <typeparam name="T">A type that with basic math functions</typeparam>
/// <param name="start">The number to start with</param>
/// <param name="increment">How much to add each step</param>
/// <param name="steps">The number of steps to iterate</param>
/// <returns>start + (increment * steps)</returns>
template <typename T>
// add boolean success. rubric hints to this with saying (true or false) in the prompt (SH)
T add_numbers(T const& start, T const& increment, unsigned long int const& steps, bool& success)
{
    // The add_numbers template function will overflow in the second method call
    //        You need to change the add_numbers method to:
    //        1. Detect when an overflow will happen
    //        2. Prevent it from happening
    //        3. Return the correct value when no overflow happened or
    //        4. Return something to tell test_overflow the addition failed
    //        NOTE: The add_numbers method must remain a template in the NumericFunctions header.

    // start success as true. will be set to false if overflow is detected (SH)
    success = true;
    T result = start;

    for (unsigned long int i = 0; i < steps; ++i)
    {
        // 1. Detect when an overflow will happen
        // check if adding increment will cause result to exceed max value for the type (SH)
        if (increment > 0 && result > std::numeric_limits<T>::max() - increment)
        {
            // 2. Prevent it from happening
            // if result exceeds max, set success to false, do not perform addition, return to last safe value (SH)
            success = false; // 4. Return something to tell test_overflow the addition failed
            return result; // return current non-overflow value (SH)
        }

        // 3. Return the correct value when no overflow happened
        result += increment;
    }

    return result;
}

/// <summary>
/// Template function to abstract away the logic of:
///   start - (increment * steps)
/// </summary>
/// <typeparam name="T">A type that with basic math functions</typeparam>
/// <param name="start">The number to start with</param>
/// <param name="increment">How much to subtract each step</param>
/// <param name="steps">The number of steps to iterate</param>
/// <returns>start - (increment * steps)</returns>

template <typename T>
// add boolean success. rubric hints to this with saying (true or false) in the prompt (SH)
T subtract_numbers(T const& start, T const& decrement, unsigned long int const& steps, bool& success)
{
    // The subtract_numbers template function will underflow in the second method call
    //        You need to change the subtract_numbers method to:
    //        1. Detect when an underflow will happen
    //        2. Prevent it from happening
    //        3. Return the correct value when no underflow happened or
    //        4. Return something to tell test_underflow the subtraction failed
    //        NOTE: The subtract_numbers method must remain a template in the NumericFunctions header.

    // start success as true. will be set to false if underflow is detected (SH)
    success = true;
    T result = start;

    for (unsigned long int i = 0; i < steps; ++i)
    {
        // 1. Detect when an underflow will happen
        // check if adding decrement will cause result to go below min value for the type (SH)
        if (decrement > 0 && result < std::numeric_limits<T>::min() + decrement)
        {
            // 2 Prevent it from happening
            // if result below min, set success to false, do not perform subtraction, return to last safe value (SH)
            success = false; // 4 Return something to tell test_underflow the subtraction failed
            return result; // return current non-underflow value (SH)
        }
        // 3 Return the correct value when no underflow happened
        result -= decrement;
    }

    return result;
}


//  NOTE:
//    You will see the unary ('+') operator used in front of the variables in the test_XXX methods.
//    This forces the output to be a number for cases where cout would assume it is a character. 

template <typename T>
void test_overflow()
{
    //  You need to change the test_overflow method to:
    //        1. Detect when an add_numbers failed
    //        2. Inform the user the overflow happened
    //        3. A successful result displays the same result as before you changed the method
    //        NOTE: You cannot change anything between START / END DO NOT CHANGE
    //              The test_overflow method must remain a template in the NumericOverflows source file
    //
    //  There are more than one possible solution to this problem. 
    //  The solution must work for all of the data types used to call test_overflow() in main().

    // START DO NOT CHANGE
    //  how many times will we iterate
    const unsigned long int steps = 5;
    // how much will we add each step (result should be: start + (increment * steps))
    const T increment = std::numeric_limits<T>::max() / steps;
    // whats our starting point
    const T start = 0;

    std::cout << "Overflow Test of Type = " << typeid(T).name() << std::endl;
    // END DO NOT CHANGE

    // 1. Detect success/failue from add_numbers() (SH)
    bool success = true;

    std::cout << "\tAdding Numbers Without Overflow (" << +start << ", " << +increment << ", " << steps << ") = ";
    T result = add_numbers<T>(start, increment, steps, success);
    // 3. A successful result displays the same result as before you changed the method (did not change cout statement)
    std::cout << +result << std::endl;

    std::cout << "\tAdding Numbers With Overflow (" << +start << ", " << +increment << ", " << (steps + 1) << ") = ";
    result = add_numbers<T>(start, increment, steps + 1, success);
   
    // 2. Inform the user if overflow happened, output last non-overflow value
    // use boolalpha to print true or false rather than 1 or 0 for clarity. !success to opposite the true/false output (SH)
    std::cout << "overflow_happened=" << std::boolalpha << !success << ", safe_result=" << +result << std::endl;

}

template <typename T>
void test_underflow()
{
    //  You need to change the test_underflow method to:
    //        1. Detect when an subtract_numbers failed
    //        2. Inform the user the underflow happened
    //        3. A successful result displays the same result as before you changed the method
    //        NOTE: You cannot change anything between START / END DO NOT CHANGE
    //              The test_underflow method must remain a template in the NumericOverflows source file
    //
    //  There are more than one possible solution to this problem. 
    //  The solution must work for all of the data types used to call test_overflow() in main().

    // START DO NOT CHANGE
    //  how many times will we iterate
    const unsigned long int steps = 5;
    // how much will we subtract each step (result should be: start - (increment * steps))
    const T decrement = std::numeric_limits<T>::max() / steps;
    // whats our starting point
    const T start = std::numeric_limits<T>::max();

    std::cout << "Underflow Test of Type = " << typeid(T).name() << std::endl;
    // END DO NOT CHANGE

    // 1. Detect success/failue from subtract_numbers() (SH)
    bool success = true;

    std::cout << "\tSubtracting Numbers Without Overflow (" << +start << ", " << +decrement << ", " << steps << ") = ";
    auto result = subtract_numbers<T>(start, decrement, steps, success);
    // 3. A successful result displays the same result as before you changed the method (did not change cout statement)
    std::cout << +result << std::endl;

    std::cout << "\tSubtracting Numbers With Overflow (" << +start << ", " << +decrement << ", " << (steps + 1) << ") = ";
    result = subtract_numbers<T>(start, decrement, steps + 1, success);

    // 2. Inform the user if underflow happened, output last non-underflow value
    // use boolalpha to print true or false rather than 1 or 0 for clarity. !success to opposite the true/false output (SH)
    std::cout << "underflow_happened=" << std::boolalpha << !success << ", safe_result=" << +result << std::endl;
}

void do_overflow_tests(const std::string& star_line)
{
    std::cout << std::endl << star_line << std::endl;
    std::cout << "*** Running Overflow Tests *** [Sarah Hayduk]" << std::endl; // added my name for screenshots (SH)
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

void do_underflow_tests(const std::string& star_line)
{
    std::cout << std::endl << star_line << std::endl;
    std::cout << "*** Running Undeflow Tests *** [Sarah Hayduk]" << std::endl; // added my name for screenshots (SH)
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

/// <summary>
/// Entry point into the application
/// </summary>
/// <returns>0 when complete</returns>
int main()
{
    //  create a string of "*" to use in the console
    const std::string star_line = std::string(50, '*');

    std::cout << "Starting Numeric Underflow / Overflow Tests!" << std::endl;

    // run the overflow tests
    do_overflow_tests(star_line);

    // run the underflow tests
    do_underflow_tests(star_line);

    std::cout << std::endl << "All Numeric Underflow / Overflow Tests Complete!" << std::endl;

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu