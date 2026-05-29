#ifndef SAFE_ARITHMETIC_H
#define SAFE_ARITHMETIC_H

#include <limits>

/*----------------------------------------------------------------------------------
* SafeArithmetic Module
*
* This module centralizes all defensive arithmetic logic into a single, reusable
* component. Each function preserves the step based behavior of the original CS-405
* assignment while adding complete overflow and underflow protection for both
* positive and negative values. The design focuses on predictable behavior, secure
* handling of numeric boundaries, and clear separation of concerns. Returning the
* last safe value and signaling failure avoids undefined behavior and supports
* safer system level code. 
* ---------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------
* safe_add
* 
* Performs addition in controlled increments. Boundary checks are done before each
* update to prevent undefined behavior. Both positive overflow and negative 
* underflow are validated to ensure complete coverage across all numeric types.
* ---------------------------------------------------------------------------------*/
template <typename T>
T safe_add(T const& start, T const& value, unsigned long int const& steps, bool& success)
{
	success = true;
	T result = start;

	for (unsigned long int i = 0; i < steps; ++i)
	{
		// --- Overflow check: Positive increment: ensure next addition stays within MAX ---
		if (value > 0 && result > std::numeric_limits<T>::max() - value)
		{
			success = false;
			return result;
		}

		// --- Underflow check: Negative increment: ensure next addition stays within MIN ---
		if (value < 0 && result < std::numeric_limits<T>::min() - value)
		{
			success = false;
			return result;
		}
		result = result + value;
	}
	return result;
}

/*----------------------------------------------------------------------------------
* safe_subtract
*
* Subtraction is validation in both directions. Subtracting a positive value risks
* underflow and subtracting a negative value risks overflow. Checking both cases
* ensures the function never performs an unsafe update.
* ---------------------------------------------------------------------------------*/
template <typename T>
T safe_subtract(T const& start, T const& value, unsigned long int const& steps, bool& success)
{
	success = true;
	T result = start;

	for (unsigned long int i = 0; i < steps; ++i)
	{
		// --- Underflow check: Positive decrement: ensure next subtraction stays within MIN ---
		if (value > 0 && result < std::numeric_limits<T>::min() + value)
		{
			success = false;
			return result;
		}

		// --- Overflow check: Negative decrement: ensure next subtraction stays within MAX ---
		if (value < 0 && result > std::numeric_limits<T>::max() + value)
		{
			success = false;
			return result;
		}
		result = result - value;
	}
	return result;
}

/*----------------------------------------------------------------------------------
* safe_multiply
*
* Positive and negative multipliers are validated using division?based checks to
* ensure the result remains within the type’s representable MIN–MAX range before 
* performing the multiplication. Multiplying by zero is treated as a fast-exit 
* because it is always safe and avoids unnecessary iteration.
* ---------------------------------------------------------------------------------*/
template <typename T>
T safe_multiply(T const& start, T const& value, unsigned long int const& steps, bool& success)
{
	success = true;
	T result = start;

	for (unsigned long int i = 0; i < steps; ++i)
	{
		// --- Multiply by zero is always safe and avoids unnecessary work ---
		if (result == 0 || value == 0)
		{
			return 0;
		}

		// --- Positive Multiplier ---
		if (value > 0)
		{
			// Overflow check: ensure multiplication stays within MAX
			if (result > std::numeric_limits<T>::max() / value)
			{
				success = false;
				return result;
			}

			// Underflow check: ensure multiplication stays within MIN
			if (result < std::numeric_limits<T>::min() / value)
			{
				success = false;
				return result;
			}
		}

		// --- Negative Multiplier ---
		else if (value < 0)
		{
			// Overflow check: ensure multiplication stays within MAX
			if (result < std::numeric_limits<T>::min() / value)
			{
				success = false;
				return result;
			}

			// Underflow check: ensure multiplication stays within MIN
			if (result > std::numeric_limits<T>::max() / value)
			{
				success = false;
				return result;
			}
		}
		result = result * value;
	}
	return result;
}

/*----------------------------------------------------------------------------------
* safe_divide
*
* Division is validated for two critical failure cases. Divide-by-zero is always
* invalid, and the MIN / -1 case overflows for signed integers. Both condiditons
* are checked before performing the operation to prevent undefined behavior.
* ---------------------------------------------------------------------------------*/
template <typename T>
T safe_divide(T const& start, T const& value, unsigned long int const& steps, bool& success)
{
	success = true;
	T result = start;

	for (unsigned long int i = 0; i < steps; ++i)
	{
		// --- Division by zero is not allowed ---
		if (value == 0)
		{
			success = false;
			return result;
		}

		// --- MIN / -1 is a known overflow case for signed integers ---
		if (result == std::numeric_limits<T>::min() && value == -1)
		{
			success = false;
			return result;
		}
		result = result / value;
	}
	return result;
}

#endif // SAFE_ARITHMETIC_H
