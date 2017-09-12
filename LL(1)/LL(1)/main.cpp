#include<iostream>
#include "stdio.h"
#include "malloc.h"
#include "conio.h"
using namespace std;

//栈说明：base是非终结符栈，h是终结符栈，top指向栈顶元素，temp,p相当于中间指针
struct tagLchar{
	char char_ch;
	struct tagLchar *next;
}Lchar, *p, *h, *temp, *top, *base;

char curchar; //终结符
char curtocmp;//非终结符
int right1;

//预测分析表（1：有文法式 0：无文法式）
int table[5][8] = { { 1, 0, 0, 1, 0, 0 },
{ 0, 1, 0, 0, 1, 1 },
{ 1, 0, 0, 1, 0, 0 },
{ 0, 1, 1, 0, 1, 1 },
{ 1, 0, 0, 1, 0, 0 } };
int i, j; // i代表预测分析表中非终结符的位置，j代表预测分析表中终结符的位置
//changchartoint()方法用于将非终结符，终结符转化为在预测分析表中相应的位置

//入栈
void push(char pchar)
{
	temp = (struct tagLchar*)malloc(sizeof(tagLchar));
	temp->char_ch = pchar;
	temp->next = top;
	top = temp;
}

//出栈
void pop(void)
{
	curtocmp = top->char_ch;
	if (top->char_ch != '#')
		top = top->next;
}


void doforpush(int t)
{
	switch (t)
	{
	case 0:push('A'); push('T'); break;
	case 5:push('A'); push('T'); break;
	case 11:push('A'); push('T'); push('+'); break;

	case 20:push('B'); push('F'); break;
	case 23:push('B'); push('F'); break;
	case 32:push('B'); push('F'); push('*'); break;

	case 40:push('i'); break;
	case 43:push(')'); push('E'); push('(');
	}
}

//用于将非终结符，终结符转化为在预测分析表中相应的位置
void changchartoint()
{
	switch (curtocmp)
	{
	case 'A':i = 1; break;
	case 'B':i = 3; break;
	case 'E':i = 0; break;
	case 'T':i = 2; break;
	case 'F':i = 4;
	}
	switch (curchar)
	{
	case 'i':j = 0; break;
	case '+':j = 1; break;

	case '*':j = 2; break;

	case '(':j = 3; break;
	case ')':j = 4; break;
	case '#':j = 5;
	}
}

//对输入的表达式进行分析
void dosome(void)
{
	int t;
	for (;;)
	{
		pop();
		curchar = h->char_ch;
		printf("\n%c\t%c", curchar, curtocmp);
		if (curtocmp == '#' && curchar == '#')
			break;
		if (curtocmp == 'A' || curtocmp == 'B' || curtocmp == 'E' || curtocmp == 'T' || curtocmp == 'F')
		{
			if (curtocmp != '#')
			{
				changchartoint();
				if (table[i][j])
				{
					t = 10 * i + j;
					doforpush(t);
					continue;
				}
				else
				{
					right1 = 0;
					break;
				}
			}
			else
			if (curtocmp != curchar)
			{
				right1 = 0;
				break;
			}
			else
				break;
		}
		else
		if (curtocmp != curchar)
		{
			right1 = 0;
			break;
		}
		else
		{
			h = h->next;
			continue;
		}
	}
}

void main(void)
{
	char ch;
	cout << "请在下行输入要分析的串(#号结束)：" << endl;

	right1 = 1;

	//非终结符栈初始化
	base = (struct tagLchar*)malloc(sizeof(tagLchar));
	base->next = NULL;
	base->char_ch = '#';
	temp = (struct tagLchar*)malloc(sizeof(tagLchar));
	temp->next = base;
	temp->char_ch = 'E';
	top = temp;

	//终结符栈初始化
	h = (struct tagLchar*)malloc(sizeof(tagLchar));
	h->next = NULL;
	p = h;

	do{

		ch = getchar(); //输入字符
		putchar(ch);    //储存字符

		//判断输入字符是否符合要求

		//符合要求进终结符栈
		if (ch == 'i' || ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '(' || ch == ')' || ch == '#')
		{
			
			temp = (struct tagLchar*)malloc(sizeof(tagLchar));
			temp->next = NULL;

			//ch入栈
			temp->char_ch = ch;
			h->next = temp;
			h = h->next;
		}
		//不符合要求重新输入
		else
		{
			temp = p->next;
			printf("\nInput a wrong char!Input again:\n");
			for (;;)
			{
				if (temp != NULL)
					printf("%c", temp->char_ch);
				else
					break;
				temp = temp->next;
			}
		}
	} 
	while (ch != '#');

	p = p->next;
	h = p;

	dosome();

	if (right1)
		printf("\n成功!\n");
	else
		printf("\n错误!\n");
	getchar();
}
