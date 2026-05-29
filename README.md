# Software Engineering and Design: Numeric Overflow Coding Activity (C++)
This repository contains the original and enhanced versions of my Numeric Overflow Coding Activity. The artifact began as a CS 405 Secure Coding assignment focused on detecting numeric overflow and underflow in C++. The original implementation was a single monolithic `.cpp` file with basic arithmetic functions and only partial protections against unsafe behavior.

## Overview

For this enhancement, I refactored the program into a more modular and maintainable design by introducing a dedicated `SafeArithmetic.h` component. This module encapsulates all overflow and underflow detection for addition, subtraction, multiplication, and division. Separating the computational logic from the testing and output code improves clarity, maintainability, and overall reliability.

The enhancement reflects a stronger engineering approach: each arithmetic function handles a single responsibility, edge cases are fully validated, and the program avoids undefined behavior by returning the last safe value when an operation would overflow or underflow. This redesign aligns with secure coding principles and demonstrates a more disciplined, systems‑level mindset.

## Key Improvements

- Introduction of a reusable `SafeArithmetic` module  
- Complete overflow and underflow detection across all operations  
- Separation of concerns between arithmetic logic and program flow  
- More predictable and secure behavior for all numeric types  
- Cleaner structure that supports testing and future extension  

## Repository Structure
/original
The initial single‑file implementation from CS 405 Secure Coding

/enhanced
Refactored version featuring the new SafeArithmetic module

/zips
Full project ZIPs for SNHU submission (original and enhanced)

## Related Artifacts
Additional documentation, narrative, and demo video for this enhancement are available in my portfolio: https://sarahhayduk.github.io/

## Technologies Used

- C++  
- Visual Studio

This enhancement demonstrates my ability to transform a small academic exercise into a modular, secure, and professionally relevant software component. It highlights growth in defensive coding, system‑level reasoning, and the application of well‑founded engineering practices.


