# Build a Modern Computer from First Principles: From Nand to Tetris

课程分为两部分，[Nand2Tetris Part1](https://www.coursera.org/learn/nand2tetris1)关注硬件，[Nand2Tetris Part2](https://www.coursera.org/learn/nand2tetris2)关注软件。

课程体验非常棒。这门课既可以是一门帮助计算机初学者建立对计算机整体认知的入门课程，也可以是给已经对计算机有所了解的同学一个亲自动手机会的实践课程。

多说无益，如对这门课感兴趣，请自行体验。如果不需要Coursera证书的话，这门课可以免费旁听。[课程官网](https://www.nand2tetris.org/software)非常友好的提供了Test Script和其他各种工具，你不必付费就能使用这些工具完成课程内容，以及自行验证Project是否达到预期。详情请参见Coursera课程视频。

本repository的各项目(除peer-graded外)均已满分通过Coursera测试点，供大家参考。虽然通过了测试，但终究是有所不逮，项目中仍然有许多可以改进的地方（尤其是那惨不忍睹的compiler），欢迎大家提issue或用其他方式助我改进。

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
2. 了解翻译过程中的各种细节（如，怎样处理Symbols）
3. 通过编程或非编程的方式，实现Assembler

### [project07 VMTranslator1](projects/07/)
1. 学习为什么要在高级语言和汇编语言间设立虚拟机(中间层)。
2. 了解本课程的虚拟机中间层设计思想。
3. 学习并实践如何把虚拟机指令翻译成汇编指令(第一部分只实现堆栈运算部分)。

### [project08 VMTranslator2](projects/08/)
1. 学习程序的虚拟机级和机器级表示。
2. 在project07的基础上修改，实现完整的VMTranslator。

### [project09 JackLanguage](projects/09/)
1. 介绍了Jack语言(本课程设计的一个类Java语言)的语法和特性。
2. 利用Jack语言编写有趣的程序，例如俄罗斯方块。

### [project10 JackAnalyzer](projects/10/)
1. 了解如何实现一个编译器。
2. 学习语法分析(特别的，要能对Jack语言进行语法分析)。
3. 利用任意一个你熟悉的高级语言，实现JackAnalyzer(相当于生成记号流)。

### [project11 JackCompiler](projects/11/)
1. 学习如何把Jack命令翻译成虚拟机指令。
2. 在project10的基础上，增加代码生成功能。

### [project12 OperatingSystem](projects/12/)
1. 了解操作系统对于高级语言程序员的意义(填补高级语言到机器指令间的空缺)。
2. 利用Jack语言编写一个操作系统，实现以下八个class：Math, Memory, Screen, Output, Keyboard, String, Array, Sys。