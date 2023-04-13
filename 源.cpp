#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<vector>
#include<algorithm>
#include<cstring>
#include <stdlib.h>
#include<stdio.h>
#include <cstdio>
#include <stack>
#include <fstream>
#include<iomanip>
using namespace std;
typedef pair<int,pair<string, string>> PSS;//�洢����Token 
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
bool is_delimiter(char ch) {
	char word[] = { '+','-','*','/','(',')',';','[',']','=','<' };
	for (auto x : word) {
		if (x == ch)return true;
	}
	return false;
}
bool judge(char ch) {
	char word[] = { '+','-','*','/','(',')',';','[',']','=','<',':','{','.',',',' ','\n','\t'};
	for (auto x : word) {
		if (x == ch)return true;
	}
	return false;
}
void printToken(PSS& token1) {
	int line = token1.first;
	auto item = token1.second;
	//cout << setw(15) <<"����" << setw(15) << "" << setw(15) << "" << endl;
	cout <<setw(15)<<line <<setw(15) << item.first <<setw(15)<<item.second<< endl;

}//��ʾһ������ 
bool  reservedLookup(string s) {
	string Keyword[] = { "program","procedure","type","var","then","else","fi","do",
"endwh","array","of","record","write","return","integer","char","if","EOF","read","while","end","begin"};
	for (auto x : Keyword) {
		if (x == s)return true;
	}
	return false;
};//���ұ�����
bool getTokenlist(FILE* fp,vector<PSS> &token)//ȡ�õ�ǰ�����е�token����
{	
	char cp = fgetc(fp);
	int line = 1;
	while (cp!=EOF){
		while (cp == ' ' || cp == '\t' || cp == '\n')
		{
			if (cp == '\n')line++;
			cp = fgetc(fp);
		}//ȥ�����еĿո��Ʊ�������з�
		if (!is_letter(cp) && !is_num(cp) && !judge(cp)&&cp!=EOF) {
			cout<< line << ":�����޷���'"<<cp<<"'�ַ���ͷ����淶����" <<"\n"<< endl;

			return false;
		}
		if (is_num(cp)) {//����
			string val;
			//val.push_back(cp);
			while (is_num(cp)) {
				val.push_back(cp);
				cp = fgetc(fp);

			}
			ungetc(cp, fp);
			cp = val.back();
			PSS ans = { line,{ "�޷�������",val } };
			//printToken(ans);
			token.push_back(ans);
		}
		if (is_letter(cp)) {//��ĸ
			string val;
			while (is_letter(cp) || is_num(cp)) {
				val.push_back(cp);
				cp = fgetc(fp);
			}
			ungetc(cp, fp);
			PSS ans;
			if (reservedLookup(val)) {
				ans = { line,{ "������",val } };
			}
			else {
				ans = { line,{ "��ʶ��",val } };
			}
			
			//printToken(ans);
			token.push_back(ans);
			cp = val.back();
		}
			if (is_delimiter(cp)) {//�ֽ��
				string tmp;
				tmp += cp;
				PSS a_token = { line,{ "���ֽ��",tmp } };
				//printToken(a_token);
				token.push_back(a_token);
			}
			if (cp == ':') {//:=˫�ֽ��
				string tmp;
				tmp += cp;
				cp = fgetc(fp);
				if (cp == '=') {
					tmp += cp;
					PSS to = { line,{ "˫�ֽ��",tmp } };
					//printToken(to);
					token.push_back(to);
				}
				else {
					ungetc(cp, fp);
					cp = ':';
					cout << line <<":����,���ǲ�����д�˸��Ⱥ�ѽ���ֵ�"<< endl;
					return false;
				}
			}
			if (cp == '{') {//ע��
				cp = fgetc(fp);
				while (cp != '}') {
					if (cp == '\n')line++;
					cp = fgetc(fp);
					
				}
				if (cp != '}')return false;
				PSS to = { line,{ "ע��","{}"} };
				//printToken(to);
				token.push_back(to);
			}
			if (cp == '.')//�����±�
			{
				cp = fgetc(fp);
				if (cp == '.') {
					PSS to = { line,{ "�����±�",".." } };
					//printToken(to);
					token.push_back(to);
				}
				else {
					PSS to = { line,{ "���������־","."} };
					if (cp != ' '&&cp!='\n'&&cp!=EOF) {
						cout << line << ":�����ֵܣ��������±��ǲ�������һ����ѽ" << endl;
						return false;
					}
					else {
						ungetc(cp, fp);
						cp = '.';
						//printToken(to);
						token.push_back(to);
					}
				}
			}
			if (cp == ',') {//�ַ���־״̬
				cp = fgetc(fp);
				if (is_num(cp) || is_letter(cp)) {
					ungetc(cp, fp);
					cp = ',';
					PSS to = { line,{ "�ַ���־״̬","," } };
					//printToken(to);
					token.push_back(to);
				}
				else {
					ungetc(cp, fp);
					cp = ',';
					cout << line <<":����','���ַ���־״̬������Ӧ������ĸ������"<< endl;
					return false;
				}
			}
			
			cp = fgetc(fp);
		}
	return true;
}
void printTokenlist(vector<PSS>& to) {
	cout << setw(15) << "����" << setw(15) << "�ʷ���Ϣ" << setw(15) << "������Ϣ" << endl;
	for (auto a = to.begin(); a != to.end(); a++) {
		printToken(*a);
	}
}//��ʾ�ʷ������Ľ��
int main() {
	vector<PSS> token;
	FILE* fp;
	if ((fp=fopen("input.txt", "r")) == NULL)
	{
		printf("�ļ���ʧ��\n");
		exit(1);
	}
	bool flag = getTokenlist(fp,token);
	fclose(fp);
	if(flag==false){
		cout << "�ʷ�����ʧ�ܣ������д�д��������±��" << endl;
	}
	else {
		printTokenlist(token);
	}
	return 0;
}