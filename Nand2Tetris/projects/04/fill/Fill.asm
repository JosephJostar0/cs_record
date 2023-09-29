// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Fill.asm

// Runs an infinite loop that listens to the keyboard input.
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel;
// the screen should remain fully black as long as the key is pressed. 
// When no key is pressed, the program clears the screen, i.e. writes
// "white" in every pixel;
// the screen should remain fully clear as long as no key is pressed.

// Put your code here.

//  while True:
//      if not Press_key:
//          WIGHT_screen()
//          continue
//      BLACK_screen()

    @KBD
    D = A
    @R0
    M = D
    @SCREEN
    D = A
    @R0
    M = M - D //RAM[0] = KBD - SCREEN

(LOOP)
    @KBD
    D = M
    @LIGHT
    D;JEQ

//DARK
    @value
    M = -1
    @PRINT
    0;JMP

(LIGHT)
    @value
    M = 0

(PRINT)
    @R0
    D = M
    @i
    M = D // i = RAM[0] = KBD - SCREEN

    @SCREEN
    D = A
    @addr
    M = D // addr = SCREEN

    (CHANGE)
        @i
        D = M
        @LOOP
        D;JEQ // if i == 0: goto LOOP

        @value
        D = M
        @addr
        A = M
        M = D // RAN[addr] = value

        @i
        M = M - 1 // i = i - 1

        @addr
        M = M + 1 // addr = addr + 1

        @CHANGE
        0;JMP
