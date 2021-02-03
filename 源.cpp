#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include "Function.h"     

#pragma warning(disable : 4996) 

//ע��:�û���ֹ����changeLog.txt�ļ���
//����Change Log���ļ���
void preserLog(FILE* changeLog, const char* log)
{
	fseek(changeLog, 0, SEEK_END);
	const char* temp = log;
	while (*temp) {
		fputc(*temp++, changeLog);
	}
}
//��ʾchangeLog.txt�е����ݡ�
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
	//��w+��ʽ��changeLog.txt�ļ�,�û�ÿ�δ򿪱�Ӧ�ó���
	//�����µ��ļ��洢�û�������Ϣ������ԭ����Ϣ�� 
	FILE* changeLog = fopen("changeLog.txt", "w+");
	if(!changeLog){
		printf("\n����: changeLog.txt�ļ�����ʧ��!");
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
			//ע��:�����������Ϊ�������������ɸ�ֵ��
			char fileName[FILE_NAME_SIZE];
			char fileName1[FILE_NAME_SIZE];
			char fileName2[FILE_NAME_SIZE];
		case 1:
			{
				printf("\n*******************  Creat File  ********************");
				printf("\n\n��������Ҫ�������ļ���(xx.txt): ");
				scanf("%s", fileName);
				fflush(stdin);
				FILE* fp = creatFile(fileName);
				if (!fp) {
					printf("\n\n����:�ļ�����ʧ�ܣ�");
				}
				else {
					fclose(fp);
					printf("\n\n�ɹ�����һ�����ı��ļ����ļ���Ϊ: %s", fileName);
				}

				preserLog(changeLog, "Creat File\n");
				break;
			}
		case 2:
			{
				printf("\n*******************  Copy File  ********************");
				printf("\n\n��������Ҫ�´������ļ���: ");
				scanf("%s", fileName1);
				printf("\n\n��������Ҫ�������ļ���: ");
				scanf("%s", fileName2);
				fflush(stdin);
				int i = copyFile(fileName1, fileName2);
				if (!i) {
					printf("\n\n����:�ļ���������ʧ�ܣ�");
				}
				else {
					printf("\n\n�ɹ���%s�ļ����ݿ��������ļ�%s", fileName2, fileName1);
				}

				preserLog(changeLog, "Copy File\n");
				break;
			}
		case 3:
			{
				printf("\n*******************  Delete File  ********************");
				printf("\n\n��������Ҫɾ�����ļ���: ");
				scanf("%s", fileName);
				fflush(stdin);
				int i = remove(fileName);
				if (i == 0) {
					printf("\n\n�ɹ���%s�ļ�ɾ��", fileName);
				}
				else {
					printf("\n\n����:�ļ�ɾ��ʧ�ܣ�");
				}

				preserLog(changeLog, "Delete File\n");
				break;
			}
		case 4:
			{
				printf("\n*******************  Show File  ********************");
				printf("\n\n��������Ҫ�򿪵��ļ���: ");
				scanf("%s", fileName);
				fflush(stdin);
				if (!is_existing(fileName)) {
					printf("\n\n����:���ļ������ڣ�");
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
				printf("\n\n��������Ҫ�������ļ���: ");
				scanf("%s", fileName);
				char text[LINE_SIZE] = "\0";
				printf("\n\n������������ӵ��ַ���: ");
				scanf("%s", text);
				fflush(stdin);
				int i = appendLine(fileName, text);
				if (!i) {
					printf("\n\n����:�ַ������ʧ�ܣ�");
				}
				else {
					printf("\n\n�ַ�����ӳɹ���");
				}

				preserLog(changeLog, "Append Line\n");
				break;
			}
		case 6:
			{
				printf("\n*******************  Delete Line  *********************");
				printf("\n\n��������Ҫ�������ļ���: ");
				scanf("%s", fileName);
				printf("\n\n��������Ҫɾ�����к�: ");
				int line_num = 0;
				scanf("%d", &line_num);
				fflush(stdin);
				int i = deleteLine(fileName, line_num);
				if (!i) {
					printf("\n\n����:ɾ������ʧ�ܣ�");
				}
				else {
					printf("\n\nɾ�������ɹ���");
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
				printf("\n\n��������Ҫ�������ļ���: ");
				scanf("%s", fileName);
				char text[LINE_SIZE] = "\0";
				printf("\n\n��������Ҫ������ַ���: ");
				scanf("%s", text);
				printf("\n\n��������Ҫ�������к�: ");
				int line_num = 0;
				scanf("%d", &line_num);
				fflush(stdin);
				int i = insertLine(fileName, line_num, text);
				if (!i) {
					printf("\n\n����:����ʧ�ܣ�");
				}
				else {
					printf("\n\n�ַ�������ɹ���");
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
				printf("\n\n��������Ҫ�������ļ���: ");
				scanf("%s", fileName);
				printf("\n\n��������Ҫ��ʾ���к�: ");
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
				printf("\n\n��������Ҫ��ȡ�������ļ���: ");
				scanf("%s", fileName);
				fflush(stdin);
				int i = getLine_num(fileName);
				if (i == -1) {
					printf("\n\n����:��ȡ�к�ʧ��:");
				}
				else {
					printf("\n\n%s�ļ�����%d��", fileName,i);
				}

				preserLog(changeLog, "Show Number of Lines\n");
				break;
			}
		case 11:
			{
				printf("\n*******************   Edit File   *******************");
				printf("\n\n��������Ҫ�򿪵��ļ���: ");
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
