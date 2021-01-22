// pep8simulator.cpp
// ComputerOnFire
//
// ends with zz
// this made storing variables to memory easier, and allows you to copy pep8 instructions directly in
// input.txt is the input file
// instructions seperated by line
//
// example:
// 500048
// 500069
// zz
// Hi
//

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

struct combo1 {
    unsigned int right : 3;
    unsigned int mid : 1;
    unsigned int left : 4;
};
struct combo2 {
    unsigned int right : 3;
    unsigned int left : 5;
};
struct combo3 {
    unsigned int right : 1;
    unsigned int left : 7;
};

union uint24 {
    
    struct instruction {
        union opFull {
            struct operand {
                unsigned int right : 8;
                unsigned int left : 8;
            } op;
            unsigned int whole : 16;
        } oper;
        union specifier {
            combo1 com1;
            combo2 com2;
            combo3 com3;
            unsigned int whole : 8;
        } speci;
    } split;
    unsigned int fullInstr : 24;

 } instr;//global scope, thanks :)

int lineCount(ifstream file) {
    string s;
    int ltotal = 0;
    while (!file.eof()) {
        getline(file, s);
         ++ltotal;
    }
    return ltotal;
}
 
unsigned int rotateLeft(unsigned int x, unsigned int n) {
    if (!n) return x;
    return (x << n) | (x >> (24 - n));//rotates a 24 bit int to the left by n
}
unsigned int rotateRight(unsigned int x, unsigned int n) {
    if (!n) return x;
    return (x >> n) | (x << (24 - n));//rotates a 24 bit int to the right by n
}
int main()
{
    struct pep8 {
        uint24 memory[256] = {};
        uint16_t registers[4] = { 0,0,0,0 };//A, X, PC, SP
    }pep;
    ifstream file("input.txt");
    if (!file.is_open()) {
    cout << "File not found!" << endl;
}

    else
    {
        string line;
        while (getline(file, line)) {
            istringstream iss(line);
            //uint24 a;
            instr.fullInstr = stoi(line, 0, 16);
            pep.memory[pep.registers[2]].fullInstr = instr.fullInstr; //register 2 is the program counter
            //a little hackey but it works
            pep.memory[pep.registers[2]].split.oper.whole = instr.fullInstr & 0xff; //splits work for accessing operand and specifier
            pep.memory[pep.registers[2]].split.speci.whole = instr.fullInstr >> 16; //but the whole number is 16 when done this way
            cout << "Registers: ";
            for (int i = 0; i < 4; ++i) {
                cout << pep.registers[i] << " ";
            }
            switch (pep.memory[pep.registers[2]].split.speci.com3.left) {//interperates instructions

            case 0:
                //return 0;
                break;
            case 12://0001 100r
                //bitwise invert r
                pep.registers[instr.split.speci.com3.right] = ~pep.registers[instr.split.speci.com3.right];
                break;
            case 14://0001 110r
                //shift left r
                pep.registers[instr.split.speci.com3.right] = pep.registers[instr.split.speci.com3.right] << 1;
                break;
            case 15:
                //shift right r
                pep.registers[instr.split.speci.com3.right] = pep.registers[instr.split.speci.com3.right] >> 1;
                break;
            case 16:
                //rotate left r
                pep.registers[instr.split.speci.com3.right] = rotateLeft(instr.split.speci.com3.right, 1);
                break;
            case 17:
                //rotate right r
                pep.registers[instr.split.speci.com3.right] = rotateRight(instr.split.speci.com3.right, 1);
                break;
            }
            //cout << pep.memory[pep.registers[2]].split.speci.com2.left << endl;
            switch (pep.memory[pep.registers[2]].split.speci.com2.left) {
            case 6:
                //decimal input
                unsigned int input;
                cout << "Input Decimal: ";
                cin >> input;
                pep.memory[instr.split.oper.op.right].split.oper.whole = input & 0xFFFF; //force input to 8 bits
                break;
            case 7:
                //decimal output
                unsigned int output;
                output = (pep.memory[pep.registers[2]].split.speci.com2.right == 1) ? pep.memory[instr.split.oper.op.right].split.oper.whole : instr.split.oper.whole;//conditional to differentiate direct and immediate addressing
                cout << "Output: "  << output << endl;
                cout << endl;
                break;
            case 9:
                //character input
                char chinput;
                cout << "Input Char: ";
                cin >> chinput;
                pep.memory[instr.split.oper.op.right].split.oper.whole = input & 0xFFFF;
                break;
            case 10:
                //character output
                char choutput;
                choutput = (pep.memory[pep.registers[2]].split.speci.com2.right == 1) ? pep.memory[instr.split.oper.op.right].split.oper.whole : instr.split.oper.whole;
                cout << "Output: " << choutput << endl;
                cout << endl;
                break;
            }
            //cout << pep.memory[pep.registers[2]].split.speci.com1.left << endl; test thingy
            switch (pep.memory[pep.registers[2]].split.speci.com1.left) {
            case 7:
                //add to r
                cout << pep.registers[instr.split.speci.com1.mid];
                cout << ((pep.memory[pep.registers[2]].split.speci.com2.right == 1) ? pep.memory[instr.split.oper.op.right].split.oper.whole : instr.split.oper.whole);
                pep.registers[instr.split.speci.com1.mid] = pep.registers[instr.split.speci.com1.mid] + ((pep.memory[pep.registers[2]].split.speci.com2.right == 1) ? pep.memory[instr.split.oper.op.right].split.oper.whole : instr.split.oper.whole);
                break;
            case 8:
                //subtract from r
                pep.registers[instr.split.speci.com1.mid] -= (pep.memory[pep.registers[2]].split.speci.com2.right == 1) ? pep.memory[instr.split.oper.op.right].split.oper.whole : instr.split.oper.whole;
                break;
            case 9:
                //bitwise AND to r
                pep.registers[instr.split.speci.com1.mid] = pep.registers[instr.split.speci.com1.mid] & ((instr.split.speci.com1.right) ? pep.memory[instr.split.oper.op.right].split.oper.whole : instr.split.oper.whole);
                break;
            case 10:
                //bitwise OR to r
                pep.registers[instr.split.speci.com1.mid] = pep.registers[instr.split.speci.com1.mid] | ((instr.split.speci.com1.right) ? pep.memory[instr.split.oper.op.right].split.oper.whole : instr.split.oper.whole) ;
                break;
            case 12:
                //load r from memory
                pep.registers[instr.split.speci.com1.mid] = (pep.memory[pep.registers[2]].split.speci.com2.right == 1) ? pep.memory[instr.split.oper.op.right].split.oper.whole : instr.split.oper.whole;
                break;
            case 13:
                //load byte r from memory
                pep.registers[instr.split.speci.com1.mid] = (pep.memory[pep.registers[2]].split.speci.com2.right == 1) ? pep.memory[instr.split.oper.op.right].split.oper.whole : instr.split.oper.whole ;
                break;
            case 14:
                //store r to memory
                pep.memory[instr.split.oper.op.right].split.oper.whole = pep.registers[instr.split.speci.com1.mid];
                break;
            case 15:
                //store byte r to memory
                pep.memory[instr.split.oper.op.right].split.oper.whole = pep.registers[instr.split.speci.com1.mid];
                break;
            }
            cout << endl;
            pep.registers[2]++;
            //pep.registers[3]++;//3 byte per line, inputs stored in left operand
            if (line.find("zz") != string::npos) {
                return 0;//end program at zz (had trouble with 0000 0000 stop and storing inputs)
            }
           
        }
        file.close();
    }
    return 0;
}
