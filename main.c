
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int boolean;

typedef struct _person person;
struct _person
{
	/* data */
	char name[10];
	char sexy[6];
	unsigned int id;
	int wages;
	float height;
	float weight;
	struct _person *prev;
	struct _person *next;
};

static char password[16] = "ashdyz1234";
static char userName[16] = "stupid0121";

person *head;
person *tail;

static boolean isManeger = 0;
//输出提示信息
void printTitle()
{
	printf("--------------------------------------------------\n");
	printf("|------------------------------------------------|\n");
	printf("||						||\n");
	printf("||		身份管理系统V1.0		||\n");
	printf("||						||\n");
	printf("|------------------------------------------------|\n");
	printf("--------------------------------------------------\n");
}
//输入提示信息
void printOpTip()
{
	printf("\n\n\t\t  选择你的操作\n\n");
	printf("\t\t1.管理员账号登录\n\n");
	printf("\t\t2.录入身份信息\n\n");
	printf("\t\t3.查找身份信息\n\n");
	printf("\t\t4.修改身份信息\n\n");
	printf("\t\t5.退出管理员账号\n\n");
	printf("\t\t6.查看所有信息\n\n");
	printf("\t\t7.信息导出txt文档\n\n");
	printf("\t\t8.从txt文档导入信息\n\n");
	printf("\t\t9.重新查看菜单\n\n");
	printf("\t\t10.退出系统\n\n");
	printf("\t\t11.版本信息\n\n");
	printf("\t\t12.删除身份信息\n\n");
}

//输出单个节点人员信息
void printfNodeInfo(person *ndoe)
{
	printf("\t\tID：%d\n", ndoe->id);
	printf("\t\t姓名：%s\n", ndoe->name);
	printf("\t\t性别:%s\n", ndoe->sexy);
	printf("\t\t身高(cm):%.1f\n", ndoe->height);
	printf("\t\t体重(kg):%.1f\n", ndoe->weight);
	printf("\t\t收入(yuan):%d\n", ndoe->wages);
}
//初始化链表
void initPersonTable()
{
	head = (person *)malloc(sizeof(person));
	if (head == NULL)
	{
		printf("\t\t内存错误，系统异常\n");
		exit(0);
	}
	tail = (person *)malloc(sizeof(person));
	if (tail == NULL)
	{
		printf("\t\t内存错误，系统异常\n");
		exit(0);
	}
	/*数据赋值避免异常错误*/
	strcpy(head->name, "head");
	strcpy(head->sexy, "none");
	head->id = -1;
	head->wages = -1;
	head->height = -1;
	head->weight = -1;

	strcpy(tail->name, "tail");
	strcpy(tail->sexy, "none");
	tail->id = -1;
	tail->wages = -1;
	tail->height = -1;
	tail->weight = -1;
	/*数据赋值结束*/
	head->prev = NULL;
	head->next = tail;
	tail->prev = head;
	tail->next = NULL;
}
//插入信息
void insertPerson()
{
	person *node;
	person *insertLoc;
	insertLoc = tail->prev;
	node = (person *)malloc(sizeof(person));
	if (node == NULL)
	{
		printf("\t\t内存错误，系统异常\n");
		exit(0);
	}
	printf("\t\t请输入ID：\n");
	scanf("%d", &(node->id));
	printf("\t\t请输入姓名：\n");
	scanf("%s", node->name);
	printf("\t\t请输入性别:\n");
	scanf("%s", node->sexy);
	printf("\t\t请输入身高(cm):\n");
	scanf("%f", &(node->height));
	printf("\t\t请输入体重(kg):\n");
	scanf("%f", &(node->weight));
	printf("\t\t请输入收入(yuan):\n");
	scanf("%d", &(node->wages));

	printf(">>>>>>>>>>>>数据本地写入完成，正在写入数据库中>>>>\n");
	tail->prev = node;
	node->next = tail;
	node->prev = insertLoc;
	insertLoc->next = node;
}
//展示全部人员信息
void showAllPerson()
{
	person *p;
	for (p = head->next; p != tail; p = p->next)
	{
		printfNodeInfo(p);
	}
}
//判断是否是管理员给出提示
boolean manegerOrNot(char passwordInput[16], char userNameInput[16])
{
	if ((0 == strcmp(passwordInput, password)) && (0 == strcmp(userNameInput, userName)))
	{
		printf("\t\t管理员身份验证成功\n");
		return 1;
	}
	else
	{
		printf("\t\t管理员身份验证失败，请联系管理员！\n");
		return 0;
	}
}
//选择操作
int chooseOp()
{
	int op;
	scanf("%d", &op);
	return op;
}
//提示输入账号密码
void tipsInputUserNameAndPassword()
{
	char passwordInput[16];
	char userNameInput[16];
	printf("\t\t请输入您的管理员账号：\n");
	scanf("%s", userNameInput);
	printf("\t\t请输入您的管理员密码：\n");
	scanf("%s", passwordInput);
	isManeger = manegerOrNot(passwordInput, userNameInput);
}
//判断是否是管理员
void adjustIsManager()
{
	if (isManeger == 0)
	{
		printf("\t\t您没有权限进行该操作，请联系管理员!\n");
	}
	else
	{
		printf("\t\t请根据下面提示输入!\n\n");
	}
}

//退出管理员账号
void exitManeger()
{
	if (isManeger == 0)
	{
		printf("\t\t您没有处于管理员权限，错误操作!\n");
	}
	else
	{
		isManeger = 0;
	}
}

//根据ID查找
person *findInfoByID()
{
	unsigned int findID;
	printf("\t\t请输入查找ID：\n");
	scanf("%d", &findID);
	printf("\t\t查找中>>>>>>>已找到\n");
	person *search;
	for (search = head->next; search != tail; search = search->next)
	{
		if (findID == search->id)
		{
			return search;
		}
	}
	return NULL;
}
//根据姓名查找
person *findInfoByName()
{
	char findName[16];
	person *search;
	printf("\t\t请输入查找姓名：\n");
	scanf("%s", findName);
	printf("\t\t查找中>>>>>>>\n");
	for (search = head->next; search != tail; search = search->next)
	{
		if (0 == strcmp(search->name, findName))
		{
			return search;
		}
	}
	return NULL;
}

//查找信息
person* findInfo()
{
	int findWay = -1;
	person *findNode;
	printf("\t\t请输入查找方式：\n");
	printf("\t\t1.根据ID查找\n");
	printf("\t\t2.根据姓名查找\n");

	scanf("%d", &findWay);
	switch (findWay)
	{
	case 1:
		findNode = findInfoByID();
		break;
	case 2:
		/* code */
		findNode = findInfoByName();
		break;
	default:
		break;
	}
	if (findNode == NULL)
	{
		printf("\t\t没有找到该信息。\n");
		return NULL;
	}
	else
	{
		printfNodeInfo(findNode);
		return findNode;
	}
}

/* 	printf("\t\tID：%d\n",ndoe->id);
	printf("\t\t姓名：%s\n",ndoe->name);
	printf("\t\t性别:%s\n",ndoe->sexy);
	printf("\t\t身高(cm):%.1f\n",ndoe->height);
	printf("\t\t体重(kg):%.1f\n",ndoe->weight);
	printf("\t\t收入(yuan):%d\n", ndoe->wages); */
//写入txt文件
void write_inTxt()
{
	char fileName[20];
	person *listen; //监听是否读完链表
	FILE *output = NULL;
	printf("\t\t您正在执行文件导出操作。\n");
	printf("\t\t请输入需要导出的文件名（如果文件不存在，则创建新的文件）：\n");
	scanf("%s", fileName);
	output = fopen(fileName, "a");
	for (listen = head->next; listen != tail; listen = listen->next)
	{
		printf("写入中------------%d", listen->id);
		fprintf(output, "\nID: %d\n姓名： %s\n性别: %s\n身高(cm): %.1f\n体重(kg): %.1f\n收入(yuan): %d\n",
				listen->id, listen->name, listen->sexy, listen->height, listen->weight, listen->wages);
		printf("\nID: %d\n姓名： %s\n性别: %s\n身高(cm): %.1f\n体重(kg): %.1f\n收入(yuan): %d\n",
				listen->id, listen->name, listen->sexy, listen->height, listen->weight, listen->wages);
	}
	fclose(output);
	printf("\t\t写入完毕!\n");
}
//修改信息
void changeInfo()
{
	person *findNode;
	printf("\t\t下面查找需要修改信息的用户:\n");
	findNode = findInfo();
	printf("\t\t您可以修改如下信息：\n");
	printf("\t\t请输入需要修改姓名：\n");
	scanf("%s", findNode->name);
	printf("\t\t请输入修改性别:\n");
	scanf("%s", findNode->sexy);
	printf("\t\t请输入需要修改身高(cm):\n");
	scanf("%f", &(findNode->height));
	printf("\t\t请输入需要修改体重(kg):\n");
	scanf("%f", &(findNode->weight));
	printf("\t\t请输入需要修改收入(yuan):\n");
	scanf("%d", &(findNode->wages));
}

//删除信息
void deleteInfo()
{
	int op;
	person *findNode;
	printf("\t\t下面查找需要删除的用户:\n");
	findNode = findInfo();
	printf("\t\t确认删除请按1,其他数字为取消操作:\n");	
	scanf("%d",&op);
	switch (op)
	{
	case 1:
		findNode->prev->next = findNode->next;
		findNode->next->prev = findNode->prev;
		free(findNode);
		break;
	
	default:
		printf("\t\t操作已取消！\n");
		break;
	}
}
//读取txt文件
void read_inTxt()
{
	char format[20];
	char fileName[20];
	FILE *input = NULL;
	printf("\t\t您正在进行从TXT导入操作。\n");
	printf("\t\t请输入需要导入的文件名（请确定文件存在）：\n");
	scanf("%s", fileName);
	input = fopen(fileName, "r");
	if (!input)
	{
		printf("\t\t输入的文件有误！！！\n");
	}
	else
	{
		while (!feof(input))
		{
			person *insertLoc;
			person *node;
			insertLoc = tail->prev;
			node = (person *)malloc(sizeof(person));
			fscanf(input, "%s %d\n%s %s\n%s %s\n%s %f\n%s %f\n%s %d\n",
				   format, &(node->id), format,(node->name), format,(node->sexy), 
				   format,&(node->height), format,&(node->weight),format, &(node->wages));
			tail->prev = node;
			node->next = tail;
			node->prev = insertLoc;
			insertLoc->next = node;
		}
		fclose(input);
	}
}

int main()
{
	int choose;
	printTitle();
	initPersonTable();
	printOpTip();
	while (1)
	{
		choose = chooseOp();

		switch (choose)
		{
		case 1:
			tipsInputUserNameAndPassword();
			printf("\t\t您的操作已完成，查看菜单请输入9！\n");
			break;
		case 2:
			adjustIsManager();
			if (isManeger == 0)
			{
				break;
			}
			else
			{
				insertPerson();
			}
			printf("\t\t您的操作已完成，查看菜单请输入9！\n");
			break;

		case 3:
			findInfo();
			printf("\t\t您的操作已完成，查看菜单请输入9！\n");
			break;
		case 4:
			/* code */
			changeInfo();
			printf("\t\t您的操作已完成，查看菜单请输入9！\n");
			break;
		case 5:
			exitManeger();
			printf("\t\t您的操作已完成，查看菜单请输入9！\n");
			break;
		case 6:
			showAllPerson();
			printf("\t\t您的操作已完成，查看菜单请输入9！\n");
			break;
		case 7:
			write_inTxt();
			printf("\t\t您的操作已完成，查看菜单请输入9！\n");
			break;
		case 8:
			read_inTxt();
			printf("\t\t您的操作已完成，查看菜单请输入9！\n");
			break;
		case 9:
			printOpTip();
			printf("\t\t您的操作已完成，查看菜单请输入9！\n");
			break;
		case 10:
			exit(0);
			printf("\t\t您的操作已完成，查看菜单请输入9！\n");
			break;
		case 11:
			printTitle();
			printf("\t\t\t\t\t@stupid0121\n");
			break;
		case 12:
			deleteInfo();
			printf("\t\t您的操作已完成，查看菜单请输入9！\n");
			break;
		default:
			break;
		}
	}

	return 0;
}
