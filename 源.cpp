#include<iostream>
#include<vector>
#include<algorithm>
#include<cstring>
#include <stdlib.h>
#include<stdio.h>
#include <cstdio>
#include <stack>
#include <fstream>
using namespace std;
typedef pair<string, string> PSS;//�洢����Token 
vector<PSS> token;

//string operate[] = { "+","-",">","<","=" };
int T[6][3] = {
1,3,5,1,1,2,0,0,0,4,3,4,0,0,0,0,0,0
};
bool is_num(char ch) {
	if (ch >= '0' && ch <= '9')return true;
	return false;
}
bool is_letter(char ch) {
	if (ch >= 'a' && ch <= 'z')return true;
	if (ch >= 'A' && ch <= 'Z')return true;
	return false;
}
bool is_other(char ch) {
	if (is_num(ch) || is_letter(ch))return false;
	return true;
}

bool  reservedLookup(string s) {
	string Keyword[] = { "program","procedure","type","var","then","else","fi","do",
"endwh","array","of","record","write","return","integer","char","if","EOF","read","while","end","begin"};
	for (auto x : Keyword) {
		if (x == s)return true;
	}
	return false;
};//���ұ�����

bool getTokenlist(FILE* fp)//ȡ�õ�ǰ�����е�token����
{
	int state = 0;//��̬
	//int point = 0;
	//vector<char> to;
	
	char cp = fgetc(fp);
	
	while (cp!=EOF){
		while (cp == ' ' || cp == '\t' || cp == '\n')
		{

			cp = fgetc(fp);
		}//ȥ�����еĿո��Ʊ�������з�
		
		if (is_letter(cp) || is_num(cp)) {//����ĸ��������

			//int init = p;
			int state = 0;//��̬

			int k = 2;
			if (is_letter(cp))k = 0;
			if (is_num(cp))k = 1;
			string val;

			while (T[state][k] && cp != '.') {
				state = T[state][k];
				val.push_back(cp);
				cp = fgetc(fp);
			}
			ungetc(cp, fp);
			PSS ans;
			if (state == 2) {
				if (reservedLookup(val)) {
					ans = { "������",val };
				}
				else ans = { "��ʶ��",val };

				token.push_back(ans);
			}
		}
			if (cp == '+' || cp == '-' || cp == '*' || cp == '/' || cp == '(' ||
				cp == ')' || cp == ';' || cp == '[' || cp == ']' || cp == '=' || cp == '<') {
				string tmp;
				tmp += cp;
				PSS a_token = { "���ֽ��",tmp };
				token.push_back(a_token);
			}
			if (cp == ':') {//:=
				string tmp;
				tmp += cp;
				cp = fgetc(fp);
				if (cp == '=') {
					tmp += cp;
					PSS to = { "˫�ֽ��",tmp };
					token.push_back(to);
				}
				else {
					ungetc(cp, fp);
					return false;
				}


			}
			if (cp == '{') {//ע��
				cp = fgetc(fp);
				while (cp != '}') {
					cp = fgetc(fp);

				}
				if (cp != '}')return false;
				PSS to = { "ע��","{}" };
				token.push_back(to);
			}
			if (cp == '.')//�����±�
			{
				cp = fgetc(fp);
				if (cp == '.') {
					PSS to = { "�����±�",".." };
					token.push_back(to);
				}
				else {
					PSS to = { "���������־","."};
					token.push_back(to);
				}
			}
			if (cp == ',') {//�ַ���־״̬
				cp = fgetc(fp);
				if (is_num(cp) || is_letter(cp)) {
					ungetc(cp, fp);
					PSS to = { "�ַ���־״̬","," };

				}
				else {
					ungetc(cp, fp);
					return false;
				}
			}
			else return false;
			cp = fgetc(fp);
		}
	return true;
}
void printToken(PSS& token1) {
	
	string key = token1.first;
	string val = token1.second;
	cout << key << " " << val << endl;

}//��ʾһ������ 
void printTokenlist(vector<PSS>& to) {
	for (auto a = to.begin(); a != to.end(); a++) {
		printToken(*a);
	}
}//��ʾ�ʷ������Ľ��
void ChainToFile(vector<PSS>& Chainhead);//�������е�Token�����ļ� 
//enum state { 0, 1, 2, 3, 4, 5 };//dfa������״̬ 
//enum letter { 'a'..'Z' };//��ĸ 
//enum digit { '0'..'9' };//����
//enum outkind {
// id, num, error, start
//}; //������ʵ����
//int T[6][]

int main() {
	FILE* fp;
	if ((fopen_s(&fp,"/input.txt", "r")) == NULL)
	{
		printf("�ļ���ʧ��\n");
		exit(1);
	}
	bool flag = getTokenlist(fp);
	fclose(fp);
	if(flag==false){
		cout << "�ʷ�����ʧ�ܣ������д�д���" << endl;
	}
	else {
		printTokenlist(token);
	}

	
	

	return 0;

}