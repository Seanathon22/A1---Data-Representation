# CS 3503 Assignment 2 - Number Representation

## Author
Sean Sprinkle

## Description
This project extends the number base conversion utility from Assignment 1. 
It includes advanced techniques such as direct mapping between number systems and signed number representations used in modern CPUs.

## Functions Implemented
- oct_to_bin: Direct 3-bit octal to binary mapping
- oct_to_hex: Octal to hexadecimal conversion via binary intermediate
- hex_to_bin: Direct 4-bit hex to binary mapping
- to_sign_magnitude: 32-bit signed integer representation
- to_ones_complement: 32-bit one's complement representation
- to_twos_complement: 32-bit two's complement representation

## Build Instructions
```bash
gcc -o convert convert.c main.c
./convert
cat output.txt
