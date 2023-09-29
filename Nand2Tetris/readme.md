# Build a Modern Computer from First Principles: From Nand to Tetris

课程分为两部分，[Nand2Tetris Part1](https://www.coursera.org/learn/nand2tetris1)关注硬件，[Nand2Tetris Part2](https://www.coursera.org/learn/nand2tetris2)关注软件。

## Project 概览
### [project01 Boolean Functions and Gate Logic](projects/01/)
1. 用Nand实现其他基础逻辑门 And Or Xor Not Mux Dmux...
2. 使用上一步实现的逻辑门，构建16位的逻辑门 And16 DMux4Way DMux8Way Mux16 Mux4Way16 Not16...

### [project02 Boolean Arithmetic and ALU](projects/02/)
1. 使用project1中已实现的逻辑门，构建半加器、全加器
2. 使用上一步实现的全加器，构建ALU (Arithmetic and Logic Unit)

### [project03 RAM&PC](projects/03/)
1. 使用project1中已实现的逻辑门，以及课程提供的DFF (Data Flip Flop) 构建1bit记忆单元。
2. 基于上一步的1bit记忆单元，构建16位Register
3. 基于上一步的16位寄存器，构建各个容量的RAM
4. 基于第2步的寄存器和project2的加法器，构建PC (Program Counter)

### [project04 Machine Language](projects/04/)
1. 初步接触机器语言和汇编语言
2. 了解如何控制IO设备
3. 使用汇编语言编写程序

### [project05 Computer Architecture](projects/05/)
1. 了解冯诺依曼体系结构和哈佛体系结构
2. 了解如何构建哈佛结构的计算机
3. 使用之前project已经实现的RAM、ALU、Register构建CPU和Memory
4. 连接CPU和Memory，构建整台计算机

### [project06 Assembler](projects/06/)
1. 了解如何把汇编语言转翻译机器指令
2. 了解翻译过程中的各种细节（如，如何处理Symbols）
3. 通过编程或非编程的方式，实现Assembler
