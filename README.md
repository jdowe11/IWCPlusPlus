# IWCPlusPlus

## Introduction

IWC++ is a runtime language that is interpreted with a program build in c++.

## About IWC++
**Syntax**

Variables - are not strictly typed and can be dynamically changed.

    Ex 1. var = 1
    Ex 2. var = 3.14
    Ex 3. var = "hello world"

Output - uses > operator to determine direction of output, but not required for outputing to console.

    Ex 1. tell("hello)            --> outputs "hello" to the terminal
    Ex 2. tell(var) > con         --> outputs what is stored in var to the terminal
    Ex 3. tell(data) > log.txt    --> outputs what is stored in var to a file log.txt

Input - uses < and << operators to determine input (< for whitespace or << for newlines). Must specify the stream

    Ex 1. var < con               --> takes input from the console and stops at first whitespace
    Ex 2. var << con              --> takes input from the console and stops at first newline
    Ex 3. var < log.txt           --> takes input from log.txt

## How to Build/Compile/Run IWC++
**Building from Source Code**

This repository comes with a makefile for building. Just run the command below:
    
    make

Once the command is ran, there should be an executable called iwcpp.
To run IWC++ code, ensure your file extension is .iwc, and run the following command

    ./iwcpp <file_name>.iwc

Congratulations! You have ran your first IWC++ program!

## Misc
There are example files inside of the [examples](https://github.com/jdowe11/IWCPlusPlus/tree/main/examples) folder.
