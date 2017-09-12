#include<stdio.h>
#include<stdlib.h>

int Action[12][6] =
{
	105, 0, 0, 104, 0, 0,
	0, 106, 0, 0, 0, -1,
	0, 52, 107, 0, 52, 52,
	0, 54, 54, 0, 54, 54,
	105, 0, 0, 104, 0, 0,
	0, 56, 56, 0, 56, 56,
	105, 0, 0, 104, 0, 0,
	105, 0, 0, 104, 0, 0,
	0, 106, 0, 0, 111, 0,
	0, 51, 107, 0, 51, 51,
	0, 53, 53, 0, 53, 53,
	0, 55, 55, 0, 55, 55 };
int Goto[12][3] =
{
	1, 2, 3,
	0, 0, 0,
	0, 0, 0,
	0, 0, 0,
	8, 2, 3,
	0, 0, 0,
	0, 9, 3,
	0, 0, 10,
	0, 0, 0,
	0, 0, 0,
	0, 0, 0,
	0, 0, 0
};
char Grammar[20][10] = { '\0' };
char VT[10], VN[10];
char AVT[6] = { 'i', '+', '*', '(', ')', '#' };
char GVN[3] = { 'E', 'T', 'F' };
int vnNum, vtNum, stateNum = 12;
int VNum[10];
int grammarNum;

typedef struct{
	char *base;
	char *top;
}SymbolStack;

typedef struct{
	int *base;
	int *top;
}StateStack;


StateStack state;
SymbolStack symbol;

int ScanGrammar()
{
	FILE *fp = fopen("F:\\大三\\软件构造_刘丹\\实验六\\SLR(1)文法\\test.txt", "r");
	FILE *tp;
	char singleChar, nextChar;
	int i = 0, j = 0, k, count;
	while (!feof(fp))
	{
		fscanf(fp, "%c", &singleChar);
		if (singleChar == '?')
		{
			Grammar[i][j] = '\0';
			break;
		}
		if (singleChar == '\n')
		{
			Grammar[i][j] = '\0';
			i++;
			j = 0;
			continue;
		}
		if (singleChar == '-')
		{
			tp = fp;
			fscanf(tp, "%c", &nextChar);
			if (nextChar == '>')
			{
				fp = tp;
				continue;
			}
		}
		if (singleChar == '|')
		{
			Grammar[i + 1][0] = Grammar[i][0];
			Grammar[i][j] = '\0';
			i++;
			j = 1;
			continue;
		}
		Grammar[i][j] = singleChar;
		if (singleChar >= 'A'&&singleChar <= 'Z')
		{
			count = 0;
			while (VN[count] != singleChar&&VN[count] != '\0')
			{
				count++;
			}
			if (VN[count] == '\0')
			{
				vnNum = count + 1;
				if (singleChar == 'S')
				{
					j++;
					continue;
				}
				VN[count] = singleChar;
				vnNum = count + 1;
			}
		}
		else
		{
			count = 0;
			while (VT[count] != singleChar&&VT[count] != '\0')
			{
				count++;
			}
			if (VT[count] == '\0')
			{
				VT[count] = singleChar;
				vtNum = count + 1;
			}
		}
		j++;
	}
	printf("输入的文法：\n");
	for (k = 0; k <= i; k++)
	{
		j = 0;
		while (Grammar[k][j] != '\0')
		{
			if (j == 1)
			{
				printf("->");
			}
			printf("%c", Grammar[k][j]);
			j++;
		}
		printf("\n");
	}
	count = 0;
	printf("VT:");
	while (VT[count] != '\0')
	{
		printf("%3c", VT[count]);
		count++;
	}
	VT[count] = '#';
	vtNum = count + 1;
	printf("%3c", VT[count]);
	printf("\nVN:");
	count = 0;
	while (VN[count] != '\0')
	{
		printf("%3c", VN[count]);
		count++;
	}
	printf("\n");
	//	printf("\n%d %d\n",vtNum,vnNum);
	fclose(fp);
	grammarNum = i + 1;
	return i;
}

int vNumCount()
{
	int i, j;
	for (i = 0; i<grammarNum; i++)
	{
		j = 1;
		while (Grammar[i][j] != '\0')
		{
			j++;
		}
		VNum[i] = j;
		//		printf("%3d",VNum[i]);
	}
	printf("\n");
	return 0;
}

void InitStack()
{
	state.base = (int *)malloc(100 * sizeof(int));
	if (!state.base)exit(1);
	state.top = state.base;
	*state.top = 0;
	symbol.base = (char *)malloc(100 * sizeof(char));
	if (!symbol.base)exit(1);
	symbol.top = symbol.base;
	*symbol.top = '#';
}

int Judge(int stateTop, char inputChar)
{
	int i, j;
	for (i = 0; i<stateNum; i++)
	{
		if (stateTop == i)break;
	}
	for (j = 0; j<vtNum; j++)
	{
		if (inputChar == AVT[j])break;
	}
	return Action[i][j];
}
int GetGoto(int stateTop, char inputChar)
{
	int i, j;
	for (i = 0; i<stateNum; i++)
	{
		if (stateTop == i)break;
	}
	for (j = 0; j<vnNum; j++)
	{
		if (inputChar == GVN[j])break;
	}
	return Goto[i][j];
}

int print(int count, int i, char Input[], int action, int gt, int sign)
{

	int *p = state.base, stateNum;
	int j, jj;
	char *q = symbol.base, symbolNum;
	printf("%d\t", count);
	while (p != state.top + 1)
	{
		stateNum = *p;
		printf("%d", stateNum);
		p++;
	}
	printf("\t");

	while (q != symbol.top + 1)
	{
		symbolNum = *q;
		printf("%c", symbolNum);
		q++;
	}
	printf("\t");
	j = i;
	jj = 0;
	while (jj<j)
	{
		printf(" ");
		jj++;
	}
	while (Input[j] != '\0')
	{
		printf("%c", Input[j]);
		j++;
	}
	printf("\t");
	if (sign == 1)
	{
		printf("\tS%d\t%d\n", action, gt);
	}
	if (sign == 2)
	{
		printf("\tr%d\t%d\n", action, gt);
	}
	if (sign == 3)
	{
		printf("\tacc\t%d\n", gt);
	}
	if (sign == 0)printf("\t0\t0\n");
	return 0;
}

int Pop(int action)
{
	int *p, stateNum, ssValue, i;
	state.top--;
	p = state.top;
	stateNum = *p;
	i = VNum[action] - 1;
	while (i != 0)
	{
		symbol.top--;
		i--;
	}
	symbol.top++;
	*symbol.top = Grammar[action][0];
	ssValue = GetGoto(stateNum, Grammar[action][0]);
	if (ssValue == 0)return ssValue;
	state.top++;
	*state.top = ssValue;
	return ssValue;
}
int Reduction()
{
	char Input[20];
	int i = 0, count = 1;
	int ssValue, action;
	int stateTop, gt;
	int sign = -1;//移进1，规约2，接受3
	scanf("%s", &Input);
	while (Input[i] != '\0')
	{
		if (Input[i] >= 'A'&&Input[i] <= 'Z')
		{
			printf("输入的不是有效的表达式！");
			return 0;
		}
		i++;
	}
	i = 0;
	printf("步骤\t状态栈\t符号栈\t输入串\t\tACTION\tGOTO\n");
	while (Input[i] != '\0')
	{

		if (count == 1)
		{
			print(count, i, Input, 0, 0, 0);
			count++;
		}
		stateTop = *state.top;
		ssValue = Judge(stateTop, Input[i]);
		if (ssValue == 0)
		{
			state.top--;
			if (*symbol.top == '#')
			{
				printf("规约出错！");
				return 0;
			}
			continue;
		}
		if (ssValue == -1)
		{
			sign = 3;
			print(count, i, Input, ssValue, 0, sign);
			count++;
			return 1;
		}
		if (ssValue >= 100)
		{
			sign = 1;
			action = ssValue - 100;
			state.top++;
			*state.top = action;
			symbol.top++;
			*symbol.top = Input[i];
			i++;
			print(count, i, Input, action, 0, sign);
			count++;
		}
		if (ssValue >= 50 && ssValue<100)
		{
			sign = 2;
			action = ssValue - 50;
			gt = Pop(action);
			print(count, i, Input, action, gt, sign);
			count++;
		}
	}
	return 0;
}

int main()
{
	ScanGrammar();
	vNumCount();
	InitStack();
	Reduction();
	return 0;
}
