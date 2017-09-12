#include <iostream> 
#include<string> 
#include <fstream> 
using namespace std;


/*  定义如下文法： E->TE' E'->+TE' T->FT' T'->*FT' F->i|(E)|^ 

E->TE’  
E’->+TE’|−TE’|ε 
T->FT’   
T’->*FT’| /FT’|ε 
F->(E) | i
*/
//单词的二元组描述 
typedef struct 
{  
	char *str;   
	int code;//种别码  
}Word;

//关键字描述
Word  key[9] = { { "main", 1 }, { "int", 2 }, { "if", 3 }, { "for", 4 }, { "while", 5 }, { "do", 6 }, { "return", 7 }, { "break", 8 }, { "continue", 9 } };

//运算符描述 
Word  optr[11]={{"+",41},{"-",42},{"*",43},{"/",44},{"=",45},{">",46},{"<",47},{">=",48},{"<=",49},{"==",50},{"!=",51}};

//分界符描述 
Word  separator[6]={{",",61},{";",62},{"{",63},{"}",64},{"(",65},{")",66}};

char ch;

//判断是否为保留字
int IsKey(string ss) 
{ 
	int i;   
	for (i = 0; i<9; i++)  
	{ 
		if (!strcmp(key[i].str, ss.c_str()))      
			return (key[i].code); 
	}  

	return 0; 
}

//判断是否为字母
int IsLetter(char c)
{
	if (((c >= 'a') && (c <= 'z')) || ((c >= 'A') && (c <= 'Z')))
		return 1;
	else
		return 0;
}

//判断是否为数字 
int IsDigit(char c) 
{  
	if(c>='0'&&c<='9')    
		return 1;   
	else    
		return 0;  
}

//判断是否为运算符 
int IsOptr(string ss)
{
	int i;
	for (i = 0; i < 11; i++)
	{
		if (!strcmp(optr[i].str, ss.c_str()))
			return (optr[i].code);
	}

	return 0;
}

// 判断是否为分界符 
int IsSeparator(string ss) 
{ 
	int i;   
	for (i = 0; i<6; i++)  
	{ 
		if (!strcmp(separator[i].str, ss.c_str()))     
			return (separator[i].code); 
	} 

	return 0; 
}

//词法分析函数
void analyse(ifstream &in)  {
	string st = "";   //char ch;    
	while ((ch = in.get()) != EOF)
	{
		st = "";
		if ((ch == ' ') || (ch == '\t') || (ch == '\n'))//空格，tab健，换行，处 理    
		{
		}
		else if (IsLetter(ch))    //保留字、标识符的处理     
		{
			while (IsLetter(ch) || IsDigit(ch))
			{
				st += ch;
				ch = in.get();
			}

			in.seekg(-1, ios::cur);//文件指针（光标）后退一个字节     
			if (IsKey(st))  //为保留字        
				cout << "(" << IsKey(st) << "," << 0 << ")" << endl;
			else     //为标识符         
				cout << "(" << 20 << "," << '\"'<< st << '\"' << ")" << endl;
		}

		else if (IsDigit(ch))  //无符号整数处理     
		{
			while (IsDigit(ch))
			{
				st += ch;
				ch = in.get();
			}
			in.seekg(-1, ios::cur);
			cout << "(" << 30 << "," << st << ")" << endl;
		}

		else
		{
			st += ch;
			if (IsOptr(st))   //运算符处理     
			{
				ch = in.get();
				if (ch == '=')//对可能是“>=,<=,==,!=”的情况（1）的处理
				{
					string sr(st);
					sr += ch;
					if (IsOptr(sr))//是情况（1）        
						cout << "(" << IsOptr(sr) << "," << 0 << ")" << endl;
					else//不是情况（1）
					{
						cout << "(" << IsOptr(st) << "," << 0 << ")" << endl;
						in.seekg(-1, ios::cur);
					}
				}
				else//对"+,-,*,/,=,>,<"的处理      
				{
					cout << "(" << IsOptr(st) << "," << 0 << ")" << endl;
					in.seekg(-1, ios::cur);
				}
			}

			else if (IsSeparator(st))//分隔符处理     
			{
				cout << "(" << IsSeparator(st) << "," << 0 << ")" << endl;
			}
		}
	}
}
void main()
{
	ifstream in;
	in.open("test.txt", ios_base::in);
	if (in.is_open())  
	{ 
		analyse(in);    
	}
	else    
		cout << "文件操作出错" << endl;
	in.close();
}