# RISC-V-Simulator

The primary objective of this project is to design and implement a RISC-V Simulator capable of running the given RISC-V assembly instructions using a C++ program.

## Table of Contents

- [Overview](#overview)
- [Instructions](#instructions)
- [Project Expandability](#project-expandability)
- [Installation](#Installation)
- [Project Structure](#project-structure)
- [File Descriptions](#file-descriptions)
- [Features](#features)

## Overview

This project focuses on supporting a subset of the RISC-V instruction set, specifically the base integer instruction set (RV32I), which is commonly used in educational and industrial applications. The simulator is designed to handle different instruction formats such as R-type,I-type,S-type,B-type,U-type and J-type instructions but doesn't support for pseudo-instructions that simplify assembly programming.

## Instructions

- The application is space sencitive. So bad spaces will cause the application to give error.
- If any comment is present after a instrection there shoud be atleast one space between instructon and comment.
- Project can handle upto 4096 lines excluding comments.

## Project Expandability

- If needed more instructions can be added to the `risc_v.h` file.
- New Instruction type can be added by making a function in `instruction.h`.
- The maximum line of input file can be increased by just chenging the 50 in `data.h` and `data.cpp`.
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
│ ├── data.cpp \
│ ├── encoder.cpp \
│ ├── instruction.cpp \
│ ├── parser.cpp \
│ ├── main.cpp \
│ ├── utils.cpp \
│ ├── cpu.cpp \
│ ├── executor.cpp \
│ └── memory.cpp \
├── include \
│ ├── data.h \
│ ├── encoder.h \
│ ├── instruction.h \
│ ├── parser.h \
│ ├── risc-v.h \
│ ├── utils.h \
│ ├── cpu.h \
│ ├── executor.h \
│ └── memory.h \
├── test_cases \
├── Makefile \
└── README.md

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