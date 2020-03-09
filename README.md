# Pep8Simulator

#PEP8 SIMULATOR PROJECT

GOAL: Write a PEP/8 machine language simulator that simulates the PEP/8 computer and instruction set for only the following instructions:

Instruction Specifier 	Instruction 	Addressing Modes 	Status Bits
0000 0000 	Stop execution 	NA	
0001 100r 	Bitwise invert r 	NA	NZ
0001 110r 	Arithmetic shift left r 	NA	NZVC
0001 111r 	Arithmetic shift right r 	NA	NZC
0010 000r 	Rotate left r 	NA	C
0010 001r 	Rotate right r 	NA	C
0011 0aaa 	Decimal input trap 	d	NZV
0011 1aaa 	Decimal output trap 	d, i	
0100 1aaa 	Character input 	d	
0101 0aaa 	Character output 	d, i	
0111 raaa 	Add to r 	d, i	NZVC
1000 raaa 	Subtract from r 	d, i	NZVC
1001 raaa 	Bitwise AND to r 	d, i	NZ
1010 raaa 	Bitwise OR to r 	d, i	NZ
1100 raaa 	Load r from memory 	d, i	NZ
1101 raaa 	Load byte from memory 	d, i	NZ
1110 raaa 	Store r to memory 	d	
1111 raaa 	Store byte r to memory 	d	






Here are some specifics.

1.	Use an array to represent the memory.
2.	Use variables or arrays for the PEP8 registers. I recommend putting it all into a structure. I also recommend using an array of 16 bit values for A, X, PC, SP so that you can use the r bit from the instructions to point directly to A or X. You do NOT have to include the Status bits.
3.	Use unions of structures to break up the registers and instructions into the correct bits (for example, use a structure that can be unioned to break up the 8 bit specifier into the following bit combos (4, 1, 3), (5, 3), (7, 1), (8). This will allow you to instantly extract the instruction, register and addressing modes from each instruction. Also use a union to break up the 16 bit operand into two 8 bit values.
4.	Have the instructions be inputted either through the command line or better yet, through a file, in the following format for each instruction:
a.	6 Hexadecimal characters per instruction
5.	After each instruction in the program is executed, output the PEP8 machine register values.



