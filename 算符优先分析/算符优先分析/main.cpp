#include<iostream>
#include<string.h>
#include<stdlib.h>
#include <ctype.h>

using namespace std;
const int maxsize = 100; //Ϊ����str[]��in[]��������洢�ռ�
const  int length = 100;//Ϊ����array[]��������洢�ռ�
class  stack
{
private:
	int size;//sizeΪ��ǰ����array[]�Ĵ�С
	char  array[length];//���ڴ洢������ַ�
public:
	stack()
	{
		size = 0;//����array[]�ĳ�ʼ����Ϊ0
	}
	void push(char ch)
	{
		if (size<length)//�������δ������ѹ��
		{
			array[size] = ch;
			size++;
		}
		else//�����������������������Ϣ
			cout << "overflow!" << endl;
	}
	int  pop(char  ch[], int len)//�����ַ�׼����Լ
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
			cout << "��������!" << endl;
			return 0;
		}
	}
	char saomiao(int pos)//�жϴ�С�Ƿ�Ϸ�
	{
		if (pos >= 0 && pos<size)
			return array[pos];
		return '\0';
	}
	void saomiaosuoyou()//�����ǰ�����е��ַ�
	{
		for (int i = 0; i<getsize(); i++)
			cout << saomiao(i);
		cout << endl;
	}
	int getsize()//���ص�ǰ�����С
	{
		return size;
	}
};
char  guiyue(char ch[])//��ԼΪ'M'
{
	return 'M';
}
int isnumch(char ch)//�ж�ch�ǲ������ֻ�Сд��ĸ
{
	return (ch >= '0'&&ch <= '9' || ch >= 'a'&&ch <= 'z');
}
int getrank(char ch1, char ch2)//����������ȷ����������ö������ȴ���
{                             //0��ʾ���ڣ�1��ʾ���ڣ�-1��ʾС�ڣ�2��ʾû�����ȹ�ϵ
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
int isvt(char ch)//����μӹ�Լ���ʸ�
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
/****************������**************/
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
	cout << "******���ķ���������Ⱦ���������ʾ*******" << endl;
	for (int i = 0; i <= 8; i++)            //���������Ⱦ���
	{
		for (int j = 0; j <= 8; j++)
		{
			cout << juzhen[i][j] << "     ";
		}
		cout << endl;
	}
	char  in[maxsize]; //���ڽ��������ļ���
	char  str[maxsize];
	FILE *fin; //����ָ�������ļ���ָ��
	cout << "������Դ�����ļ���(����test.txt)��";
	cin >> in;
	if ((fin = fopen(in, "r")) == NULL) //�ж������ļ����Ƿ���ȷ
	{
		cout << endl << "�򿪴ʷ����������ļ�����!" << endl;

	}

	int m = 0;
	char ch1 = 'a';
	while (ch1 != '#')//���ļ��ж���һ���ַ�
	{
		ch1 = getc(fin);
		str[m++] = ch1;
	}
	str[m] = '#';//��'#'�����ַ���β
	stack  s;//����stack��ı���s
	int  len;
	len = int(strlen(str));//ȡ�������ַ����ĳ��� 
	s.push('#');//�Ȱ�'#'ѹ������array[]
	int k = s.getsize() - 1, t = 0, j;//kΪ��ǰ����array[]�����Ѷ����ַ���λ�ñ�ʶ,
	//tΪ�����ַ�������str[]�����������ַ�λ�ñ�ʶ,
	//j���ڼ�¼��ǰ����array[]�е����һ�����ս����λ��
	char a = str[0];//a���ڴ��ݼ���������ַ�
	while (a != '#')//���a������'#',���������������Լ����
	{
		a = str[t];
		if (isvt(s.saomiao(k)))
			j = k;
		else
			j = k - 1;
		while (isvt(a) && getrank(s.saomiao(j), a) == 1)//�ж��Ƿ������Լ������
		{
			int h = j, low = j - 1;//h��¼Ҫ��Լ��λ�ã�low��¼��Լ������array[]�е����һ�����ս����λ��
			if (!isvt(s.saomiao(low)))
				low--;
			while (getrank(s.saomiao(low), s.saomiao(h)) != -1)//Ѱ�����һ�����ս����λ����low��¼
			{
				h = low;
				low--;
				if (!isvt(s.saomiao(low)))
					low--;
			}
			h = s.getsize() - 1;
			low++;
			int len = h - low + 1;    //len��¼Ҫ��Լ�ĳ���
			char  ch[10];
			for (int p = 0; p<10; p++)
				ch[p] = '\0';
			s.pop(ch, len);//����Ҫ��Լ���ַ����ַ���ch�洢
			char c = guiyue(ch);//��ch��ԼΪM
			s.push(c);//�ٽ���Լ���Mѹ��������
			cout << ch << " ��ԼΪ " << guiyue(ch) << endl;
			s.saomiaosuoyou();//��Լ�������ǰ����array[]�е��ַ�
			j = s.getsize() - 1;
			if (!isvt(s.saomiao(j)))
				j--;
		}
		if (!(a >= 'A'&&a <= 'Z') && getrank(s.saomiao(j), a) == 2)//���������ַ����Ǵ�д��ĸ����ǰһ��
		{                                            //���ս�������ȹ�ϵ����ʾ����������ʾ
			cout << "��������д���!" << endl;
			cout << "����Ϊ�� " << t + 1 << "���ַ� :" << str[t] << endl;
			exit(0);
		}
		else
		{
			cout << "�ƽ� :" << a << endl;
			s.push(a);//��aѹ������array[]
			s.saomiaosuoyou();//����������ǰ����array[]�е��ַ�
			t++;
			k = s.getsize() - 1;
		}
	}
	char temp[10];
	s.pop(temp, 3);
	if (s.getsize() == 0)//����������array[]�ĳ���size��ֵΪ0��������ɹ�
		cout << "�ɹ�!" << endl;
	else//���򣬷���ʧ��
		cout << "ʧ��!" << endl;
	fclose(fin);//�ر������ļ�

}