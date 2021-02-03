#include "Function.h" 

#pragma warning(disable : 4996)

//���ڲ���LINE OPERATIONS��ָ���ļ��Ĳ�����ǰ���Ǹ��ļ�������ڣ������ر����һ��
//����ר���ж�ָ���ļ��Ƿ����,�ж�ָ���ļ��Ƿ���ڣ������ڷ���1�����򷵻�0�� 
int is_existing(const char* fileName)
{
	//��ֻ����ʽ�򿪸��ļ������򿪳ɹ���˵���ļ��Ѿ����ڣ��޷�����ͬĿ¼�µ�ͬ���ļ��� 
	FILE* fp = fopen(fileName, "r");
	if (fp) {
		fclose(fp);   //�ǵùر��ļ��� 
		return 1;
	}
	return 0;
}

//��ָ�����ƴ���һ���µ��ı��ļ�,�����ظ��ļ���ָ�롣
//ע��:��FILEָ��������ļ��ɶ���д,������ϼǵùر��ļ��� 
FILE* creatFile(const char* fileName)
{
	if (is_existing(fileName)) {
		return NULL;   //���ļ��Ѵ��ڣ�����һ����ָ�롣 
	}
	//�ļ������ڣ�˵�����ļ��ɴ���: 	
	FILE* fp = fopen(fileName, "w+");
	return fp;
}

//����һ�����ļ�fileName_new�����ļ�fileName_cpy�����ݿ��������ļ�fileName_new��
//���ɹ�����1�����򷵻�0��
int copyFile(const char* fileName_new, const char* fileName_cpy)
{
	//�ж����������Ƿ�ɹ��� 
	FILE* fpn = creatFile(fileName_new);
	if (!fpn) {
		return 0;
	}
	FILE* fpc = fopen(fileName_cpy, "r");
	if (!fpc) {
		return 0;
	}
	//��fileName_cpy�ļ��������������fileName_new�� 
	char temp = '\0';
	while ((temp = fgetc(fpc)) != EOF) {
		fputc(temp, fpn);
	}
	fclose(fpn);
	fclose(fpc);
	return 1;
}

//��ʾָ���ļ����ݡ� 
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

//��ָ���ļ�����β��׷�����ݡ�
void textEdit(const char* fileName)
{
	FILE* fp = fopen(fileName, "a");
	if (!fp) {
		printf("\n����: �ļ���ʧ��\n");
		return;
	}
	printf("\n�����·��༭�����ı�(��Ctrl+Z����): ");
	printf("\n=====================================================================\n");
	//��index������ǰ����д�뵽�����ļ��е�������һ���еĵڼ���(һ����δд�����ݣ���index=0)��
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

//��ȡָ���ļ�������������ȡ�ɹ����������������򷵻�-1�� 
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

//��ָ���ļ���λ�ñ�Ƕ�λ��ָ���в����ش�ʱ����ļ�������FILE����ָ�롣
//line_nun��ʾ�û�Ҫ���ļ�λ�ñ�Ƕ�λ����ָ���кš� 
FILE* lineTracer(const char* fileName, int line_num)
{
	if (!is_existing(fileName)) {
		return NULL;
	}

	int lines_amount = getLine_num(fileName);  //��ȡfileName�ļ�����������

	//��ȡ�Ѿ����ڵ��ļ�����r��ʽ���ļ���
	FILE* fp = fopen(fileName, "r");
	if (!fp) {
		return fp;
	}

	if (line_num == lines_amount + 1) {  //1-���û�ָ���к�Ϊ�ļ�β��(��������+1)�� 
		fseek(fp, 0, SEEK_END);
	}
	else if (line_num > lines_amount + 1) {    //2-���û�ָ�����кų����ļ�������+1��������쳣�˳��� 
		return NULL;  //$ע��:���˺������ó����򷵻�0�����ڸú������ô������ڼ������Ƿ�Ϸ���	
	}
	else if (line_num <= lines_amount / 2) {  //3-���û�ָ��������������������һ��,���ļ�λ�ñ�Ǵ��ļ���ʼ 
		fseek(fp, (line_num - 1) * LINE_SIZE, SEEK_SET);  //λ�ÿ�ʼ��λ�� 
	}
	else {
		fseek(fp, -(lines_amount - line_num + 1) * LINE_SIZE, SEEK_END);  //4-���򣬴�β����ʼ��λ�� 
	}
	return fp;
}

//��ָ���ļ���ָ���кŴ�����һ���ַ�(ȱ���ַ������Կո���䣬ĩβ�Ի��з�����),��ӳɹ�
//��1,ʧ�ܷ���0��
//ע��:text������ֽ�������С��LINE_SIZE�� 
int insertLine(const char* fileName, int line_num, const char* text)
{
	//���ļ������ڻ���textΪ��ָ�����text���鳬��һ�еĳ��ȣ�����0�� 
	if (!is_existing(fileName) || !text || strlen(text) >= LINE_SIZE) {
		return 0;
	}
	
	FILE* fp1 = fopen(fileName, "r");
	//�ڶ���������ʱ�ռ����ļ��е����ݡ�
	fseek(fp1, 0, SEEK_END);
	char* p = (char*)malloc(ftell(fp1) + LINE_SIZE + 1);
	//�ļ�λ��ָ�뷵���ļ�ͷ����
	fseek(fp1, 0, SEEK_SET);  
	//sum��ʾ����λ��֮ǰ�����ֽ�����
	int sum = (line_num - 1) * LINE_SIZE; 
	//��fileName��ָ���к�֮ǰ���ַ�һһ��������̬�ڴ档
	int i = 0;
	for (; i < sum; ) {
		p[i++] = fgetc(fp1);   
	}
	//��ָ���ı���������ʱ��̬�ڴ�:
	//��line_indexָʾ�����Ѿ�д����ֽ�����
	int line_index = 0;  //�տ�ʼһ����ûд�롣  
	const char* temp = text;
	for (; line_index < strlen(text); ++line_index) {
		p[i++] = *temp++;
	}
	for (; line_index < LINE_SIZE - 1; ++line_index) {
		p[i++] = ' ';
	}
	p[i++] = '\n';
	//ָ���ַ���������ϣ�����������ԭ�ļ��е�ʣ������:
	while (!feof(fp1)) {
		p[i++] = fgetc(fp1);
	}
	p[i] = '\0';  
	//ȫ���ı�������ϣ��������ر��ļ�������д�ķ�ʽ��ͬ���ļ������ڴ�����д�룬
	//�����ǵ�ԭ�ļ����ݡ�
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

//��һ��ָ���ı����������ָ���ļ�β���������ɹ�����1�����򷵻�0��
//ע��:text������ֽ�������С��LINE_SIZE��
int appendLine(const char* fileName, const char* text)
{
	//���ļ������ڻ���textΪ��ָ�����text���鳬��һ�еĳ��ȣ�����0�� 
	if (!is_existing(fileName) || !text || strlen(text) >= LINE_SIZE) {
		return 0;
	}
	FILE* fp = fopen(fileName, "a");

	int line_index = 0;  //�տ�ʼһ����ûд�롣  
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

//ɾ��ָ���ļ���ָ���У������ɹ�����1�����򷵻�0��
int deleteLine(const char* fileName, int line_num)
{
	FILE* fp1 = fopen(fileName, "r");
	if (!fp1) {
		return 0;
	}
	//�ڶ���������ʱ�ռ����ļ��е����ݡ�
	fseek(fp1, 0, SEEK_END);
	char* p = (char*)malloc(ftell(fp1) - LINE_SIZE + 1);
	//�ļ�λ��ָ�뷵���ļ�ͷ����
	fseek(fp1, 0, SEEK_SET);
	//sum��ʾ����λ��֮ǰ�����ֽ�����
	int sum = (line_num - 1) * LINE_SIZE;
	//��fileName��ָ���к�֮ǰ���ַ�һһ��������̬�ڴ档
	int i = 0;
	for (; i < sum; ) {
		p[i++] = fgetc(fp1);
	}
	//���ļ�λ��ָ��ӵ�ǰλ�ú���LINE_SIZE��ƫ������
	fseek(fp1, LINE_SIZE + 1, SEEK_CUR);
	//�û�ָ���б�����������������ԭ�ļ��е�ʣ������:
	while (!feof(fp1)) {
		p[i++] = fgetc(fp1);
	}
	p[i] = '\0';
	//ȫ���ı�������ϣ��������ر��ļ�������д�ķ�ʽ��ͬ���ļ������ڴ�����д�룬
	//�����ǵ�ԭ�ļ����ݡ�
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
	printf("\n\n%d�е�����Ϊ:\n\n",line_num);
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
	printf("\n\n����������(����): ");
	int ret = 0;
	scanf("%d", &ret);
	while (ret < 1 || ret > 12) {
		fflush(stdin);
		printf("\n��Ч���룬����������:");
		scanf("%d", &ret);
	}
	return ret;
}










