# RISC-V-Simulator

The primary objective of this project is to design and implement a RISC-V Simulator capable of running the given RISC-V assembly instructions using a C++ program with Cache options.

## Table of Contents

- [Overview](#overview)
- [Instructions](#instructions)
- [Project Expandability](#project-expandability)
- [Installation](#Installation)
- [Project Structure](#project-structure)
- [File Descriptions](#file-descriptions)
- [Features](#features)

## Overview

The project is designed to implement a RISC-V simulator which is capable of running the RISC-V assembly instructions using C++ program with Command line interface.This supports only a subset of instructions i.e only R, I, S, B, U and J type instructions not any pseudo instructions.The simulator is enhanced with the cache simulation which supports 3 types of replacement policies(FIFO,LRU,RANDOM) and two write policies(WB with no allocate and WT with allocate)

## Instructions

- The application is space sencitive. So bad spaces will cause the application to give error.
- If any comment is present after a instrection there shoud be atleast one space between instructon and comment.
- Project can handle upto 4096 lines excluding comments.

## Project Expandability

- If needed more instructions can be added to the `risc_v.h` file.
- New Instruction type can be added by making a function in `instruction.h`.
- The maximum line of input file can be increased by just changing the 4096 in `data.h` and `data.cpp`.
- The application can be made to support for pseudo-instructions by adding a new function in `instruction.h`
- The project can be made to support for more than one file by making a loop in `main.cpp`.
- We can improve the application by adding a GUI to it.

## Installation

Make can be used to install the application into your personal repo or folder:

```console
make all
```

Make all will compile the files and give you a riscv_asm.exe file which can be run using:

```console
./riscv_sim.exe
```

Specific .o files can be compiled by the following commands:

```console
make data.o
make encorder.o
make instruction.o
make main.o
make lineRunner.o
make parser.o
make utils.o
make cpu.o
make memory.o
make executor.o
```

Then clean can be used to clean all the files:

```console
make clean
```

## Project Structure

The project is organized as follows:\
├─ src\
│ ├── cpu.cpp \
│ ├── data.cpp \
│ ├── encoder.cpp \
│ ├── executor.cpp \
│ ├── instruction.cpp \
│ ├── lineRunner.cpp \
│ ├── main.cpp \
│ ├── memory.cpp \
│ ├── parser.cpp \
│ └── utils.cpp \
├── include \
│ ├── cpu.h \
│ ├── data.h \
│ ├── encoder.h \
│ ├── executor.h \
│ ├── instruction.h \
│ ├── lineRunner.h \
│ ├── memory.h \
│ ├── parser.h \
│ ├── risc-v.h \
│ └── utils.h \
├── Makefile \
├── README.md \
└── report.pdf 

## File Descriptions

- **src/**: Contains all the source code files.

  - `encoder.cpp`: conatains the implementation of encoding functionalities of the instruction.
  - `instruction.cpp`: Contains Implementation of instruction functionalities.
  - `parser.cpp` : Implementation of parsing functionalities.
  - `utils.cpp` Implementation of common utility functions.
  - `lineRunner.cpp` It contains all the functions for each instruction
  - `data.cpp`: Contains the strings and maps to store the data of the instructions.
  - `cpu.cpp`: Implements the functionalities of register store and register load.
  - `memory.cpp`: Implemests the memory opertions
  - `executor.cpp`: Contains the implementation details required for execution of the decoded instructions.
  - `main.cpp`: The entry point of the application.

- **include/**: Contains all the Header files for the above source code files used in the project and an additional risc-v.h file.
  - `risc-v.h`: Contains the information about registers and instruction ,their corresponding opcode,funct values.
- **Makefile**: Configuration file for Make to build the project..
- **Report**: Contains the brief description each file and functions in them.Example usage of the project and the output of the project.