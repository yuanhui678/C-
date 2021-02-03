#ifndef FUNCTION_H
#define FUNCTION_H

#include <stdio.h>
#include <stdlib.h>
#include<string.h>

//一行字符的长度，包括末尾换行符'\n'。注意:由于每个汉字占两个字节，为了避免在处理汉字文档时
//出现乱码问题,LINE_SIZE的值必须为奇数。(由于文本格式设置为按行读写，每行的大小为LINE_SIZE
//,且汉字与ASII字符占用字节数不同，故若ASII字符与汉字无序存储在行中，可能导致乱码)。
#define LINE_SIZE 99   
 //文件名的长度。
#define FILE_NAME_SIZE 32   

int is_existing(const char* fileName);

FILE* creatFile(const char* fileName);

int copyFile(const char* fileName_new, const char* fileName_cpy);

void showFile(const char* fileName);

void textEdit(const char* fileName);

int getLine_num(const char* fileName);

FILE* lineTracer(const char* fileName, int line_num);

int insertLine(const char* fileName, int line_num, const char* text);

int appendLine(const char* fileName, const char* text);

int deleteLine(const char* fileName, int line_num);

void showLine(const char* fileName, int line_num);

int mai_menu();

#endif

