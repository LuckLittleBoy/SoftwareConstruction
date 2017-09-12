#include<iostream>
#include "stdio.h"
#include "malloc.h"
#include "conio.h"
using namespace std;

//ջ˵����base�Ƿ��ս��ջ��h���ս��ջ��topָ��ջ��Ԫ�أ�temp,p�൱���м�ָ��
struct tagLchar{
	char char_ch;
	struct tagLchar *next;
}Lchar, *p, *h, *temp, *top, *base;

char curchar; //�ս��
char curtocmp;//���ս��
int right1;

//Ԥ�������1�����ķ�ʽ 0�����ķ�ʽ��
int table[5][8] = { { 1, 0, 0, 1, 0, 0 },
{ 0, 1, 0, 0, 1, 1 },
{ 1, 0, 0, 1, 0, 0 },
{ 0, 1, 1, 0, 1, 1 },
{ 1, 0, 0, 1, 0, 0 } };
int i, j; // i����Ԥ��������з��ս����λ�ã�j����Ԥ����������ս����λ��
//changchartoint()�������ڽ����ս�����ս��ת��Ϊ��Ԥ�����������Ӧ��λ��

//��ջ
void push(char pchar)
{
	temp = (struct tagLchar*)malloc(sizeof(tagLchar));
	temp->char_ch = pchar;
	temp->next = top;
	top = temp;
}

//��ջ
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

//���ڽ����ս�����ս��ת��Ϊ��Ԥ�����������Ӧ��λ��
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

//������ı��ʽ���з���
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
	cout << "������������Ҫ�����Ĵ�(#�Ž���)��" << endl;

	right1 = 1;

	//���ս��ջ��ʼ��
	base = (struct tagLchar*)malloc(sizeof(tagLchar));
	base->next = NULL;
	base->char_ch = '#';
	temp = (struct tagLchar*)malloc(sizeof(tagLchar));
	temp->next = base;
	temp->char_ch = 'E';
	top = temp;

	//�ս��ջ��ʼ��
	h = (struct tagLchar*)malloc(sizeof(tagLchar));
	h->next = NULL;
	p = h;

	do{

		ch = getchar(); //�����ַ�
		putchar(ch);    //�����ַ�

		//�ж������ַ��Ƿ����Ҫ��

		//����Ҫ����ս��ջ
		if (ch == 'i' || ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '(' || ch == ')' || ch == '#')
		{
			
			temp = (struct tagLchar*)malloc(sizeof(tagLchar));
			temp->next = NULL;

			//ch��ջ
			temp->char_ch = ch;
			h->next = temp;
			h = h->next;
		}
		//������Ҫ����������
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
		printf("\n�ɹ�!\n");
	else
		printf("\n����!\n");
	getchar();
}
