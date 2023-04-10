# Implementation Guide

Functions' Descriptions 
- [Mintlify](https://mintlify.com/)
---
### Preparing development environment
1. Create layer’s folders
    1. Create a folder for each layer
    2. All folders should be in **upper case**
    3. Ex: MCAL, HAL, APP, … etc

2. Create diver’s folders and files
    1. Create a folder for each driver
        1. Each folder contains only one .c file and at least one .h file
        2. All files names should be in **lower case**
    2. All driver folders names should be in **lower case**
    3. Ex: dio, timer, pwm, … etc.

3. Add header file guard
    1. All header files must include the header file guard
---
### Drivers implementation and code convention
1. All drivers provided in the design document should be implemented

2. All drivers should be tested against different test cases

3. Function’s descriptions should be included

4. Don’t use magic numbers, use Macros or Enums instead

5. Follow a proper indentation in your code

6. Use a meaningful name for your variables

7. Follow the below naming for the functions
    1. MODULENAME_functionName

8. Follow this convention for naming variables
    1. typeIndicator_scopeIndicator_variableName
    2. typeIndicators (u8, u16, u32, i8, i16, st (struct), en (enum), arr (array), ..
    etc)
    3. scopeIndicators (g (global), gs (global static), a (argument))
