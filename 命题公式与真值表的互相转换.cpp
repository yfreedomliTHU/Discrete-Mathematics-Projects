#include <iostream>
#include <string>
#include <stack>
#include <memory.h>
using namespace std;
bool calc(char x, bool n1, bool n2);
bool check();
void creat();
void truth_table();
void Paradigm();
int getPriority(char t);
string result, D, C;
string input,R;//����
int sum;// ԭ��������Ŀ
int a[50]; char b[20];
bool list[1 << 10][11];
int main()
{
	    cout<<"�밴��ע����������,������ǣ�>�����̺���<����˫�̺���| ������ȡ��& �����ȡ"<<endl;
		cout<<endl;
		cout << "��ѡ�������" ;
		cout <<	"1�����⹫ʽ��д��ֵ��ͷ�ʽ  2����ֵ����д���⹫ʽ" <<endl;
		int choice;
		cin >> choice;
		if (choice == 1)
		{
			cout << "���������⹫ʽ" << endl;
			cin >> input;
			R=input;
			if (check() == 0)
			{
				cout << "���빫ʽ��ʽ����" << endl;
				exit(1);
			}//�жϹ�ʽ�Ƿ���ȷ
			creat();
			truth_table();
			Paradigm();
		}
		else if (choice == 2)
		{
			 cout << "������ԭ���������Ŀ" << endl;
	         cin >> sum;
	         cout << "��������ֵ��" << endl;
	         for (int i = 0; i < (1 << sum); i++)
	         {
		         for (int j = 0; j <= sum; j++)
			      cin >> list[i][j];
	         }
	         for (int i = 0; i < sum; i++)
		       b[i] = 'A' + i;
			   Paradigm();
		}
		else
		{
			cout << "����Ĳ���ģʽ���󣡣���" << endl;
		}
	return 0;
}
bool calc(char x, bool n1=0, bool n2=0)
{
	switch(x)
	{
	    case '!':return !n1;       break;
	    case '&':return n1&n2;     break;
	    case '|':return n1 | n2;   break;
	    case '>':return (!n1) | n2;break;
	    case '<':return (n1 == n2);break;
		default: break;
	}
}
bool check()//�����ʽ��ʽ�ĺϷ���
{
	int leftcount = 0, rightcount = 0; 
	for (int i = 0; i < input.length(); i++)
	{
		if (input[i]<'A'&&input[i]!='&'&&input[i]!='!'&&input[i]!='>'&&input[i]!='<'&&input[i]!='|'&&input[i]!='('&&input[i]!=')')    return 0;
		else if(input[i]>'Z'&&input[i]!='&'&&input[i]!='!'&&input[i]!='>'&&input[i]!='<'&&input[i]!='|'&&input[i]!='('&&input[i]!=')')     return 0;
		if(!input[i]) return 0;
		else if (input[i] == '(')  leftcount++;
		else if (input[i] == ')')  rightcount++;
		if (i == 0)
		{
			if ((getPriority(input[i]) >= 3 && getPriority(input[i]) <= 6) || input[i] == ')')  return 0;
		}
		if (i < input.length())
		{
			if (input[i] >= 'A' && input[i] <= 'Z')
			{
				if (input[i+1] == '!' || input[i+1] == '(' ||(input[i+1] >= 'A' && input[i+ 1] <= 'Z'))                return 0;
				else if(input[i+1]=='&'&&(input[i+2]<'A'||input[i+2]>'Z')&&input[i+2]!='!') return 0;
			}
			else if (input[i] == '(')
			{
				if (getPriority(input[i + 1]) >= 3 && getPriority(input[i + 1]) <= 6)   return 0;
			}
			else if (input[i] == ')')
			{
				if ((input[i + 1] >= 'A' && input[i + 1] <= 'Z') || input[i + 1] == '(' || input[i + 1] == '!')return 1;
			}
			else
			{
				if ((getPriority(input[i + 1]) >= 3 && getPriority(input[i + 1]) <= 6) || input[i + 1] == ')')return 0;
			}
		}
	}
	if (leftcount - rightcount != 0)   return 0;
    return 1;
}
void creat()
{
	int count = 0;
	for (int i = 0; i < input.length(); i++)
	{
		if (input[i] >= 'A' && input[i] <= 'Z')
		{
			if (a[input[i] - 'A'] == 0)
			{
				count++;
				a[input[i] - 'A'] = count;
				b[count - 1] = input[i];
			}
		}
	}
	sum = count;
	
		stack<char>sta;
		input.append(1, '@');
		sta.push('@');
		for (int i=0;sta.empty() == 0;i++)
		{
			if (input[i] >= 'A'&&input[i] <= 'Z')
			{
				result.append(1, input[i]);
			}
			else
			{
				if (input[i] == '(')    sta.push(input[i]);
				else if (input[i] == ')')
				{
					char temp = sta.top();
					sta.pop();
					while (temp != '(')
					{
						result.append(1, temp);
						temp = sta.top();
						sta.pop();
					}
				}
				else
				{
					while (!sta.empty() && getPriority(sta.top()) >= getPriority(input[i]) && sta.top() != '@')
					{
						result.append(1, sta.top());
						sta.pop();
					}
					sta.push(input[i]);
				}
			}
			if (input[i] == '@')
			{
				break;
			}
		}
}

void Paradigm()
{
	for (int i = 0; i < (1 << sum); i++)
	{
		if (list[i][sum])
		{
			D.append(1, '(');
			for (int j = 0; j < sum; j++)
			{
				if (list[i][j] == 0)D.append(1, '!');
				D.append(1, b[j]);
				if (j < sum - 1)D.append(1, '&');
			}
			D.append(1, ')');
			D.append(1, '|');
		}
		else
		{
			C.append(1, '(');
			for (int j = 0; j < sum; j++)
			{
				if (list[i][j])C.append(1, '!');
				C.append(1, b[j]);
				if (j < sum - 1)C.append(1, '|');
			}
			C.append(1, ')');
			C.append(1, '&');
		}
	}
	C = C.substr(0, C.length() - 1);
	D = D.substr(0, D.length() - 1);
	cout << "����ȡ��ʽ : " << D << endl;
	cout << "����ȡ��ʽ : " << C << endl;
}
void truth_table()
{
	for (int i = 0; i < 1 << (sum); i++)
	{
		for (int j = 0; j < sum; j++)
			list[i][j] = (i & (1 << (sum - 1 - j)));
		stack<bool>temp;
		for (int j = 0; j < result.length(); j++)
		{
			if (result[j] >= 'A' && result[j] <= 'Z')
			{
				temp.push(list[i][a[result[j] - 'A'] - 1]);
			}
			else
			{
				if (result[j] == '!')
				{
					bool n1 = temp.top();     
					temp.pop();
					temp.push(calc('!' , n1));
				}
				else
				{
					bool n1 = temp.top();  temp.pop();
					bool n2 = temp.top();  temp.pop();
					temp.push(calc(result[j], n2, n1));
				}
			}
			list[i][sum] = temp.top();
		}
	}
	for (int j = 0; j < sum; j++)
	{
		cout << b[j] << ' ';
	}
	cout << R << endl;
	for (int i = 0; i < 1 << sum; i++)//��1����sumλ
	{
		for (int j = 0; j <= sum; j++)
			cout << list[i][j] << ' ';
		cout << endl;
	}
}
int getPriority(char t)
{
	switch(t)
		{
	      case '@': return 1;break;
		  case '(': return 2;break;
		  case '<': return 3;break;
		  case '>': return 4;break;
		  case '|': return 5;break;
		  case '&': return 6;break;
		  case '!': return 7;break;
		  case ')': return 8;break;
		  default:  return 0;break;
	    }
	}
