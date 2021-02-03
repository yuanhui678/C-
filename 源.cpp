#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include "Function.h"     

#pragma warning(disable : 4996) 

//注意:用户禁止操作changeLog.txt文件。
//保存Change Log至文件。
void preserLog(FILE* changeLog, const char* log)
{
	fseek(changeLog, 0, SEEK_END);
	const char* temp = log;
	while (*temp) {
		fputc(*temp++, changeLog);
	}
}
//显示changeLog.txt中的内容。
void showLog(FILE* changeLog)
{
	fseek(changeLog, 0, SEEK_SET);
	char c = '\0';
	printf("\n\n");
	while ((c = fgetc(changeLog)) != EOF) {
		putchar(c);
	}
}

int main() 
{
	//以w+方式打开changeLog.txt文件,用户每次打开本应用程序，
	//建立新的文件存储用户操作信息并覆盖原有信息。 
	FILE* changeLog = fopen("changeLog.txt", "w+");
	if(!changeLog){
		printf("\n错误: changeLog.txt文件创建失败!");
		exit(0);
	} 

	int flag = 0;

	while (1) {
		flag = mai_menu();
		system("cls");
		if (flag == 12) {
			break;
		}
		switch (flag)
		{
			//注意:以下三个语句为变量声明，不可赋值。
			char fileName[FILE_NAME_SIZE];
			char fileName1[FILE_NAME_SIZE];
			char fileName2[FILE_NAME_SIZE];
		case 1:
			{
				printf("\n*******************  Creat File  ********************");
				printf("\n\n请输入您要创建的文件名(xx.txt): ");
				scanf("%s", fileName);
				fflush(stdin);
				FILE* fp = creatFile(fileName);
				if (!fp) {
					printf("\n\n错误:文件创建失败！");
				}
				else {
					fclose(fp);
					printf("\n\n成功创建一个空文本文件，文件名为: %s", fileName);
				}

				preserLog(changeLog, "Creat File\n");
				break;
			}
		case 2:
			{
				printf("\n*******************  Copy File  ********************");
				printf("\n\n请输入您要新创建的文件名: ");
				scanf("%s", fileName1);
				printf("\n\n请输入您要拷贝的文件名: ");
				scanf("%s", fileName2);
				fflush(stdin);
				int i = copyFile(fileName1, fileName2);
				if (!i) {
					printf("\n\n错误:文件拷贝操作失败！");
				}
				else {
					printf("\n\n成功将%s文件内容拷贝至新文件%s", fileName2, fileName1);
				}

				preserLog(changeLog, "Copy File\n");
				break;
			}
		case 3:
			{
				printf("\n*******************  Delete File  ********************");
				printf("\n\n请输入您要删除的文件名: ");
				scanf("%s", fileName);
				fflush(stdin);
				int i = remove(fileName);
				if (i == 0) {
					printf("\n\n成功将%s文件删除", fileName);
				}
				else {
					printf("\n\n错误:文件删除失败！");
				}

				preserLog(changeLog, "Delete File\n");
				break;
			}
		case 4:
			{
				printf("\n*******************  Show File  ********************");
				printf("\n\n请输入您要打开的文件名: ");
				scanf("%s", fileName);
				fflush(stdin);
				if (!is_existing(fileName)) {
					printf("\n\n错误:该文件不存在！");
				}
				else {
					showFile(fileName);
				}

				preserLog(changeLog, "Show File\n");
				break;
			}
		case 5:
			{
				printf("\n*******************  Append Line  ********************");
				printf("\n\n请输入您要操作的文件名: ");
				scanf("%s", fileName);
				char text[LINE_SIZE] = "\0";
				printf("\n\n请输入您想添加的字符串: ");
				scanf("%s", text);
				fflush(stdin);
				int i = appendLine(fileName, text);
				if (!i) {
					printf("\n\n错误:字符串添加失败！");
				}
				else {
					printf("\n\n字符串添加成功！");
				}

				preserLog(changeLog, "Append Line\n");
				break;
			}
		case 6:
			{
				printf("\n*******************  Delete Line  *********************");
				printf("\n\n请输入您要操作的文件名: ");
				scanf("%s", fileName);
				printf("\n\n请输入您要删除的行号: ");
				int line_num = 0;
				scanf("%d", &line_num);
				fflush(stdin);
				int i = deleteLine(fileName, line_num);
				if (!i) {
					printf("\n\n错误:删除操作失败！");
				}
				else {
					printf("\n\n删除操作成功！");
				}

				char log[64] = "Delete Line -> ";
				char tmp[16] = "\0";
				itoa(line_num, tmp, 10);
				strcat(tmp, "\n");
				strcat(log, tmp);
				preserLog(changeLog, log);
				break;
			}
		case 7:
			{
				printf("\n*******************  Insert Line  *********************");
				printf("\n\n请输入您要操作的文件名: ");
				scanf("%s", fileName);
				char text[LINE_SIZE] = "\0";
				printf("\n\n请输入您要插入的字符串: ");
				scanf("%s", text);
				printf("\n\n请输入您要操作的行号: ");
				int line_num = 0;
				scanf("%d", &line_num);
				fflush(stdin);
				int i = insertLine(fileName, line_num, text);
				if (!i) {
					printf("\n\n错误:操作失败！");
				}
				else {
					printf("\n\n字符串插入成功！");
				}

				char log[64] = "Insert Line -> ";
				char tmp[16] = "\0";
				itoa(line_num, tmp, 10);
				strcat(tmp, "\n");
				strcat(log, tmp);
				preserLog(changeLog, log);
				break;
			}
		case 8:
			{
				printf("\n*******************  Show Line  ********************");
				printf("\n\n请输入您要操作的文件名: ");
				scanf("%s", fileName);
				printf("\n\n请输入您要显示的行号: ");
				int line_num = 0;
				scanf("%d", &line_num);
				fflush(stdin);
				showLine(fileName, line_num);

				char log[64] = "Show Line -> ";
				char tmp[16] = "\0";
				itoa(line_num, tmp, 10);
				strcat(tmp, "\n");
				strcat(log, tmp);
				preserLog(changeLog, log);
				break;
			}
		case 9:
			{
			printf("\n*******************  Show Change Log  ********************");
			showLog(changeLog);

			preserLog(changeLog, "Show Change Log\n");
			break;
			}
		case 10:
			{
				printf("\n******************  Show Number of Lines ******************");
				printf("\n\n请输入您要获取行数的文件名: ");
				scanf("%s", fileName);
				fflush(stdin);
				int i = getLine_num(fileName);
				if (i == -1) {
					printf("\n\n错误:获取行号失败:");
				}
				else {
					printf("\n\n%s文件共有%d行", fileName,i);
				}

				preserLog(changeLog, "Show Number of Lines\n");
				break;
			}
		case 11:
			{
				printf("\n*******************   Edit File   *******************");
				printf("\n\n请输入您要打开的文件名: ");
				scanf("%s", fileName);
				getchar();
				fflush(stdin);
				fflush(stdout);
				textEdit(fileName);

				preserLog(changeLog, "Edit File\n");
				break;
			}
		}
		printf("\n\n");
		system("pause");
		system("cls");
	}
	fclose(changeLog);
	system("pause");
	return 0;
}
