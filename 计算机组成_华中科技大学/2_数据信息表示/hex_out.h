#pragma once
#include <stdio.h>
void hex_out(char a) { //输出8位数据的十六进制值
    const char HEX[] = "0123456789ABCDEF";
    printf("%c%c", HEX[(a & 0xF0) >> 4], HEX[a & 0x0F]);
}

void out_1byte(char *addr) { hex_out(*(addr + 0)); } //用十六进制输出地址中的8位数据机器码

void out_2byte(char *addr) { //用十六进制输出地址中的16位数据机器码
    //小端口模式优先输出高字节
    hex_out(*(addr + 1));
    hex_out(*(addr + 0));
}

void out_4byte(char *addr) { //用十六进制输出地址中的32位数据机器码
    //小端口模式优先输出高字节
    int i;
    for (i = 3; i >= 0; i--)
        hex_out(*(addr + i));
}