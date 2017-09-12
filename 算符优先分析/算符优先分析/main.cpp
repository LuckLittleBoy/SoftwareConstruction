#include<iostream>
#include<string.h>
#include<stdlib.h>
#include <ctype.h>

using namespace std;
const int maxsize = 100; //为数组str[]、in[]分配的最大存储空间
const  int length = 100;//为数组array[]分配的最大存储空间
class  stack
{
private:
	int size;//size为当前数组array[]的大小
	char  array[length];//用于存储读入的字符
public:
	stack()
	{
		size = 0;//数组array[]的初始长度为0
	}
	void push(char ch)
	{
		if (size<length)//如果数组未满，则压入
		{
			array[size] = ch;
			size++;
		}
		else//若数组已满，则给出出错信息
			cout << "overflow!" << endl;
	}
	int  pop(char  ch[], int len)//弹出字符准备规约
	{
		if (size - len >= 0)
		{
			for (int i = 0; i<len; i++)
				ch[i] = array[size - len + i];
			size -= len;
			return len;
		}
		else
		{
			cout << "参数错误!" << endl;
			return 0;
		}
	}
	char saomiao(int pos)//判断大小是否合法
	{
		if (pos >= 0 && pos<size)
			return array[pos];
		return '\0';
	}
	void saomiaosuoyou()//输出当前数组中的字符
	{
		for (int i = 0; i<getsize(); i++)
			cout << saomiao(i);
		cout << endl;
	}
	int getsize()//返回当前数组大小
	{
		return size;
	}
};
char  guiyue(char ch[])//规约为'M'
{
	return 'M';
}
int isnumch(char ch)//判断ch是不是数字或小写字母
{
	return (ch >= '0'&&ch <= '9' || ch >= 'a'&&ch <= 'z');
}
int getrank(char ch1, char ch2)//根据算符优先分析矩阵设置读入优先次序
{                             //0表示等于，1表示大于，-1表示小于，2表示没有优先关系
	if (isnumch(ch1))
		ch1 = 'i';

	if (isnumch(ch2))
		ch2 = 'i';

	if (ch1 == '+' || ch1 == '-')
	{
		if (ch2 == '+' || ch2 == '#' || ch2 == ')' || ch2 == '-')
			return 1;
		else
			return -1;
	}

	if (ch1 == '*' || ch1 == '/')
	{
		if (ch2 == '(' || ch2 == 'i')
			return -1;
		else
			return 1;
	}

	if (ch1 == '(')
	{
		if (ch2 == ')')
			return 0;
		else if (ch2 == '#')
			return 2;
		else
			return -1;
	}

	if (ch1 == 'i' || ch1 == ')')
	{
		if (ch2 == 'i' || ch2 == '(')
			return 2;
		else
			return 1;
	}

	if (ch1 == '#')
	{
		if (ch2 == '#')
			return 0;
		else
		if (ch2 == ')')
			return 2;
		else
			return -1;
	}
	return 2;

}
int isvt(char ch)//区别参加规约的资格
{
	if (ch >= 'a'&&ch <= 'z')
		return 1;
	if (ch >= '('&&ch <= '+')
		return 1;
	if (ch == '#')
		return 1;
	if (ch == '/')
		return 1;
	if (ch == '-')
		return 1;
	if (ch >= '0'&&ch <= '9')
		return 1;
	return 0;

}
/****************主函数**************/
void main()
{
	char juzhen[9][9] = { ' ', '+', '-', '*', '/', '(', ')', 'i', '#',
		'+', '>', '>', '<', '<', '<', '>', '<', '>',
		'-', '>', '>', '<', '<', '<', '>', '<', '>',
		'*', '>', '>', '>', '>', '<', '>', '<', '>',
		'/', '>', '>', '>', '>', '<', '>', '<', '>',
		'(', '<', '<', '<', '<', '<', '=', '<', ' ',
		')', '>', '>', '>', '>', ' ', '>', ' ', '>',
		'i', '>', '>', '>', '>', ' ', '>', ' ', '>',
		'#', '<', '<', '<', '<', '<', ' ', '<', '=', };
	cout << "******此文法的算符优先矩阵如下所示*******" << endl;
	for (int i = 0; i <= 8; i++)            //输出算符优先矩阵
	{
		for (int j = 0; j <= 8; j++)
		{
			cout << juzhen[i][j] << "     ";
		}
		cout << endl;
	}
	char  in[maxsize]; //用于接收输入文件名
	char  str[maxsize];
	FILE *fin; //用于指向输入文件的指针
	cout << "请输入源程序文件名(例如test.txt)：";
	cin >> in;
	if ((fin = fopen(in, "r")) == NULL) //判断输入文件名是否正确
	{
		cout << endl << "打开词法分析输入文件出错!" << endl;

	}

	int m = 0;
	char ch1 = 'a';
	while (ch1 != '#')//从文件中读入一串字符
	{
		ch1 = getc(fin);
		str[m++] = ch1;
	}
	str[m] = '#';//将'#'赋给字符串尾
	stack  s;//定义stack类的变量s
	int  len;
	len = int(strlen(str));//取出输入字符串的长度 
	s.push('#');//先把'#'压入数组array[]
	int k = s.getsize() - 1, t = 0, j;//k为当前数组array[]读入已读入字符的位置标识,
	//t为输入字符串数组str[]即将被读的字符位置标识,
	//j用于记录当前数组array[]中的最后一个非终结符的位置
	char a = str[0];//a用于传递即将读入的字符
	while (a != '#')//如果a不等于'#',则继续读入操作或规约操作
	{
		a = str[t];
		if (isvt(s.saomiao(k)))
			j = k;
		else
			j = k - 1;
		while (isvt(a) && getrank(s.saomiao(j), a) == 1)//判断是否满足规约的条件
		{
			int h = j, low = j - 1;//h记录要规约的位置，low记录规约后数组array[]中的最后一个非终结符的位置
			if (!isvt(s.saomiao(low)))
				low--;
			while (getrank(s.saomiao(low), s.saomiao(h)) != -1)//寻找最后一个非终结符的位置用low记录
			{
				h = low;
				low--;
				if (!isvt(s.saomiao(low)))
					low--;
			}
			h = s.getsize() - 1;
			low++;
			int len = h - low + 1;    //len记录要规约的长度
			char  ch[10];
			for (int p = 0; p<10; p++)
				ch[p] = '\0';
			s.pop(ch, len);//弹出要规约的字符用字符串ch存储
			char c = guiyue(ch);//将ch规约为M
			s.push(c);//再将规约后的M压入数组中
			cout << ch << " 规约为 " << guiyue(ch) << endl;
			s.saomiaosuoyou();//规约后输出当前数组array[]中的字符
			j = s.getsize() - 1;
			if (!isvt(s.saomiao(j)))
				j--;
		}
		if (!(a >= 'A'&&a <= 'Z') && getrank(s.saomiao(j), a) == 2)//当待输入字符不是大写字母且与前一个
		{                                            //非终结符无优先关系则提示出错并给出提示
			cout << "你的输入有错误!" << endl;
			cout << "错误为第 " << t + 1 << "个字符 :" << str[t] << endl;
			exit(0);
		}
		else
		{
			cout << "移近 :" << a << endl;
			s.push(a);//将a压入数组array[]
			s.saomiaosuoyou();//读入后输出当前数组array[]中的字符
			t++;
			k = s.getsize() - 1;
		}
	}
	char temp[10];
	s.pop(temp, 3);
	if (s.getsize() == 0)//如果最后数组array[]的长度size的值为0，则分析成功
		cout << "成功!" << endl;
	else//否则，分析失败
		cout << "失败!" << endl;
	fclose(fin);//关闭输入文件

}