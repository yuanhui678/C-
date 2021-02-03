#include "Function.h" 

#pragma warning(disable : 4996)

//由于部分LINE OPERATIONS对指定文件的操作的前提是该文件必须存在，所以特别添加一个
//函数专门判断指定文件是否存在,判断指定文件是否存在，若存在返回1，否则返回0。 
int is_existing(const char* fileName)
{
	//用只读方式打开该文件，若打开成功，说明文件已经存在，无法创建同目录下的同名文件。 
	FILE* fp = fopen(fileName, "r");
	if (fp) {
		fclose(fp);   //记得关闭文件。 
		return 1;
	}
	return 0;
}

//以指定名称创建一个新的文本文件,并返回该文件的指针。
//注意:该FILE指针关联的文件可读可写,操作完毕记得关闭文件。 
FILE* creatFile(const char* fileName)
{
	if (is_existing(fileName)) {
		return NULL;   //若文件已存在，返回一个空指针。 
	}
	//文件不存在，说明该文件可创建: 	
	FILE* fp = fopen(fileName, "w+");
	return fp;
}

//创建一个新文件fileName_new并将文件fileName_cpy的内容拷贝至新文件fileName_new。
//若成功返回1，否则返回0。
int copyFile(const char* fileName_new, const char* fileName_cpy)
{
	//判断两个件打开是否成功。 
	FILE* fpn = creatFile(fileName_new);
	if (!fpn) {
		return 0;
	}
	FILE* fpc = fopen(fileName_cpy, "r");
	if (!fpc) {
		return 0;
	}
	//将fileName_cpy文件数据逐个拷贝至fileName_new。 
	char temp = '\0';
	while ((temp = fgetc(fpc)) != EOF) {
		fputc(temp, fpn);
	}
	fclose(fpn);
	fclose(fpc);
	return 1;
}

//显示指定文件内容。 
void showFile(const char* fileName)
{
	FILE* fp = fopen(fileName, "r");
	if (!fp) {
		return;
	}
	printf("\n=====================================================================\n");
	char temp = '\0';
	while ((temp = fgetc(fp)) != EOF) {
		putchar(temp);
	}
	/*int i = 0;
	for (; i < getLine_num(fileName) * LINE_SIZE; ++i) {
		putchar(fgetc(fp));
	}*/
	printf("=====================================================================\n");
	fclose(fp);
}

//打开指定文件并在尾部追加数据。
void textEdit(const char* fileName)
{
	FILE* fp = fopen(fileName, "a");
	if (!fp) {
		printf("\n错误: 文件打开失败\n");
		return;
	}
	printf("\n请在下方编辑您的文本(按Ctrl+Z结束): ");
	printf("\n=====================================================================\n");
	//用index索引当前正在写入到磁盘文件中的数据是一行中的第几个(一行中未写入数据，则index=0)。
	int line_index = 0;
	char temp = '\0';
	while ((temp = getchar()) != EOF) {
		if (line_index == LINE_SIZE - 1) {
			fputc('\n', fp);
			fputc(temp, fp);
			line_index = 1;
		}
		else {
			if (temp == '\n') {
				int i = 1;
				for (; i < LINE_SIZE - line_index; ++i) {
					fputc(' ', fp);
				}
				fputc(temp, fp);
				line_index = 0;
			}
			else {
				fputc(temp, fp);
				++line_index;
			}
		}
	}
	fclose(fp);
}

//获取指定文件的总行数。获取成功，返回行数，否则返回-1。 
int getLine_num(const char* fileName)
{
	FILE* fp = fopen(fileName, "r");
	if (!fp) {
		return -1;
	}
	fseek(fp, 0L, SEEK_END);
	int i = 0;
	i = ftell(fp);
	fclose(fp);
	return i / LINE_SIZE;
}

//将指定文件的位置标记定位到指定行并返回此时与该文件关联的FILE类型指针。
//line_nun表示用户要将文件位置标记定位到的指定行号。 
FILE* lineTracer(const char* fileName, int line_num)
{
	if (!is_existing(fileName)) {
		return NULL;
	}

	int lines_amount = getLine_num(fileName);  //获取fileName文件的总行数。

	//读取已经存在的文件，用r方式打开文件。
	FILE* fp = fopen(fileName, "r");
	if (!fp) {
		return fp;
	}

	if (line_num == lines_amount + 1) {  //1-若用户指定行号为文件尾部(即总行数+1)。 
		fseek(fp, 0, SEEK_END);
	}
	else if (line_num > lines_amount + 1) {    //2-若用户指定的行号超过文件总行数+1，则程序异常退出。 
		return NULL;  //$注意:若此函数调用出错，则返回0，故在该函数调用处无需在检查参数是否合法。	
	}
	else if (line_num <= lines_amount / 2) {  //3-若用户指定的行数不到总行数的一半,让文件位置标记从文件起始 
		fseek(fp, (line_num - 1) * LINE_SIZE, SEEK_SET);  //位置开始定位。 
	}
	else {
		fseek(fp, -(lines_amount - line_num + 1) * LINE_SIZE, SEEK_END);  //4-否则，从尾部开始定位。 
	}
	return fp;
}

//在指定文件的指定行号处插入一行字符(缺少字符部分以空格填充，末尾以换行符结束),添加成功
//回1,失败返回0。
//注意:text数组的字节数必须小于LINE_SIZE。 
int insertLine(const char* fileName, int line_num, const char* text)
{
	//若文件不存在或者text为空指针或者text数组超过一行的长度，返回0。 
	if (!is_existing(fileName) || !text || strlen(text) >= LINE_SIZE) {
		return 0;
	}
	
	FILE* fp1 = fopen(fileName, "r");
	//在堆区开辟临时空间存放文件中的内容。
	fseek(fp1, 0, SEEK_END);
	char* p = (char*)malloc(ftell(fp1) + LINE_SIZE + 1);
	//文件位置指针返回文件头部。
	fseek(fp1, 0, SEEK_SET);  
	//sum表示插入位置之前的总字节数。
	int sum = (line_num - 1) * LINE_SIZE; 
	//将fileName中指定行号之前的字符一一拷贝至动态内存。
	int i = 0;
	for (; i < sum; ) {
		p[i++] = fgetc(fp1);   
	}
	//将指定文本拷贝至临时动态内存:
	//用line_index指示该行已经写入的字节数。
	int line_index = 0;  //刚开始一个都没写入。  
	const char* temp = text;
	for (; line_index < strlen(text); ++line_index) {
		p[i++] = *temp++;
	}
	for (; line_index < LINE_SIZE - 1; ++line_index) {
		p[i++] = ' ';
	}
	p[i++] = '\n';
	//指定字符串拷贝完毕，接下来拷贝原文件中的剩余内容:
	while (!feof(fp1)) {
		p[i++] = fgetc(fp1);
	}
	p[i] = '\0';  
	//全部文本拷贝完毕，接下来关闭文件，再以写的方式打开同名文件并将内存数据写入，
	//将覆盖掉原文件内容。
	fclose(fp1);
	FILE* fp2 = fopen(fileName, "w");
	if (!fp2) {
		return 0;
	}
	temp = p;
	while (*temp) {
		fputc(*temp++, fp2);
	}
	free(p);
	fclose(fp2);
	return 1;
}

//将一行指定文本内容添加至指定文件尾部。操作成功返回1，否则返回0。
//注意:text数组的字节数必须小于LINE_SIZE。
int appendLine(const char* fileName, const char* text)
{
	//若文件不存在或者text为空指针或者text数组超过一行的长度，返回0。 
	if (!is_existing(fileName) || !text || strlen(text) >= LINE_SIZE) {
		return 0;
	}
	FILE* fp = fopen(fileName, "a");

	int line_index = 0;  //刚开始一个都没写入。  
	const char* temp = text;
	for (; line_index < strlen(text); ++line_index) {
		fputc(*temp++, fp);
	}
	for (; line_index < LINE_SIZE - 1; ++line_index) {
		fputc(' ', fp);
	}
	fputc('\n', fp);
	fclose(fp);
	return 1;
}

//删除指定文件的指定行，操作成功返回1，否则返回0。
int deleteLine(const char* fileName, int line_num)
{
	FILE* fp1 = fopen(fileName, "r");
	if (!fp1) {
		return 0;
	}
	//在堆区开辟临时空间存放文件中的内容。
	fseek(fp1, 0, SEEK_END);
	char* p = (char*)malloc(ftell(fp1) - LINE_SIZE + 1);
	//文件位置指针返回文件头部。
	fseek(fp1, 0, SEEK_SET);
	//sum表示插入位置之前的总字节数。
	int sum = (line_num - 1) * LINE_SIZE;
	//将fileName中指定行号之前的字符一一拷贝至动态内存。
	int i = 0;
	for (; i < sum; ) {
		p[i++] = fgetc(fp1);
	}
	//将文件位置指针从当前位置后移LINE_SIZE个偏移量。
	fseek(fp1, LINE_SIZE + 1, SEEK_CUR);
	//用户指定行被跳过，接下来拷贝原文件中的剩余内容:
	while (!feof(fp1)) {
		p[i++] = fgetc(fp1);
	}
	p[i] = '\0';
	//全部文本拷贝完毕，接下来关闭文件，再以写的方式打开同名文件并将内存数据写入，
	//将覆盖掉原文件内容。
	fclose(fp1);
	FILE* fp2 = fopen(fileName, "w");
	if (!fp2) {
		return 0;
	}
	const char* temp = p;
	while (*temp) {
		fputc(*temp++, fp2);
	}
	free(p);
	fclose(fp2);
	return 1;
}

void showLine(const char* fileName, int line_num)
{
	if (!is_existing(fileName)) {
		return;
	}
	FILE* fp = lineTracer(fileName, line_num);
	if (!fp) {
		return;
	}
	int i = 0;
	printf("\n\n%d行的内容为:\n\n",line_num);
	for (; i < LINE_SIZE; ++i) {
		putchar(fgetc(fp));
	}
	fclose(fp);
}

int mai_menu()
{
	printf("\n--   1.Creat File");
	printf("\n--   2.Copy File");
	printf("\n--   3.Delete File");
	printf("\n--   4.Show File");
	printf("\n--   5.Append Line");
	printf("\n--   6.Delete Line");
	printf("\n--   7.Insert Line");
	printf("\n--   8.Show Line");
	printf("\n--   9.Show Change Log");
	printf("\n--   10.Show Number of Lines");
	printf("\n--   11.Edit File");
	printf("\n--   12.Qiut");
	printf("\n\n请输入命令(数字): ");
	int ret = 0;
	scanf("%d", &ret);
	while (ret < 1 || ret > 12) {
		fflush(stdin);
		printf("\n无效输入，请重新输入:");
		scanf("%d", &ret);
	}
	return ret;
}










