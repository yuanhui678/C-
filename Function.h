#ifndef FUNCTION_H
#define FUNCTION_H

#include <stdio.h>
#include <stdlib.h>
#include<string.h>

//һ���ַ��ĳ��ȣ�����ĩβ���з�'\n'��ע��:����ÿ������ռ�����ֽڣ�Ϊ�˱����ڴ������ĵ�ʱ
//������������,LINE_SIZE��ֵ����Ϊ������(�����ı���ʽ����Ϊ���ж�д��ÿ�еĴ�СΪLINE_SIZE
//,�Һ�����ASII�ַ�ռ���ֽ�����ͬ������ASII�ַ��뺺������洢�����У����ܵ�������)��
#define LINE_SIZE 99   
 //�ļ����ĳ��ȡ�
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

