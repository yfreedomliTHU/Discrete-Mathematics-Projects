// �沨�����ʽ 
#include<iostream>
#include<stack>
#include<string>
using namespace std;
int getPriority(char t);
string Input, Output;
bool check()//�����ʽ��ʽ�ĺϷ���
{
	int leftcount = 0, rightcount = 0; 
	for (int i = 0; i < Input.length(); i++)
	{
		if (Input[i]<'A'&&Input[i]!='&'&&Input[i]!='!'&&Input[i]!='>'&&Input[i]!='<'&&Input[i]!='|'&&Input[i]!='('&&Input[i]!=')')    return 0;
		else if(Input[i]>'Z'&&Input[i]!='&'&&Input[i]!='!'&&Input[i]!='>'&&Input[i]!='<'&&Input[i]!='|'&&Input[i]!='('&&Input[i]!=')')     return 0;
		if(!Input[i]) return 0;
		else if (Input[i] == '(')  leftcount++;
		else if (Input[i] == ')')  rightcount++;
		if (i == 0)
		{
			if ((getPriority(Input[i]) >= 3 && getPriority(Input[i]) <= 6) || Input[i] == ')')  return 0;
		}
		if (i < Input.length())
		{
			if (Input[i] >= 'A' && Input[i] <= 'Z')
			{
				if (Input[i+1] == '!' || Input[i+1] == '(' || (Input[i+1] >= 'A' && Input[i+ 1] <= 'Z'))                return 0;
				else if(Input[i+1]=='&'&&(Input[i+2]<'A'||Input[i+2]>'Z')&&Input[i+2]!='!') return 0;
			}
			else if (Input[i] == '(')
			{
				if (getPriority(Input[i + 1]) >= 3 && getPriority(Input[i + 1]) <= 6)   return 0;
			}
			else if (Input[i] == ')')
			{
				if ((Input[i + 1] >= 'A' && Input[i + 1] <= 'Z') || Input[i + 1] == '(' || Input[i + 1] == '!')return 1;
			}
			else
			{
				if ((getPriority(Input[i + 1]) >= 3 && getPriority(Input[i + 1]) <= 6) || Input[i + 1] == ')')return 0;
			}
		}
	}
	if (leftcount - rightcount != 0)   return 0;
	return 1;
}
int main()
{
	    stack<char>sta;
	    cout<<"�밴��ע����������:������ǣ�>�����̺���<����˫�̺���| ������ȡ��& �����ȡ"<<endl;
		cout<<"�������ʽ��ʽ��";
		cin >> Input;
		if (check() == 0)
			{
				cout << "���빫ʽ��ʽ����" << endl;
				exit(1);
			}//�жϹ�ʽ�Ƿ���ȷ
		Input.append(1, '@');
		sta.push('@');//����ʼ���ѹ��ջ
		for (int i=0;sta.empty() == 0;i++)   //ɨ������Ĺ�ʽ
		{
			if (Input[i] >= 'A'&&Input[i] <= 'Z')
			{
				Output.append(1, Input[i]);
			}
			else
			{
				if (Input[i]== '(')   sta.push(Input[i]);
				else if (Input[i] == ')')
				{
					char temp = sta.top();
					sta.pop();
					while (temp != '(')
					{
						Output.append(1, temp);
						temp = sta.top();
						sta.pop();
					}
				}
				else
				{
					while (!sta.empty() && getPriority(sta.top()) >= getPriority(Input[i]) && sta.top()!='@')
					{
						Output.append(1, sta.top());
						sta.pop();
					}
					sta.push(Input[i]);
				}
			}
			if (Input[i] == '@')
			{
				break;//ɨ�赽ĩβ��ǣ�����ѭ��
			}
		}
		cout <<"�沨�����ʽΪ��"<< Output<<endl;
	    return 0;
}
int getPriority(char t)
{
	switch (t)
	{
	      case '@': return 1;break;
		  case '(': return 2;break;
		  case '<': return 3;break;
		  case '>': return 4;break;
		  case '|': return 5;break;
		  case '&': return 6;break;
		  case '!': return 7;break;
		  case ')': return 8;break;
	     default:return 0;//�ж����ȼ�
	}
}
