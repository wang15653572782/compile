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
typedef pair<string, string> PSS;//存储单个Token 
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
};//查找保留字

bool getTokenlist(FILE* fp)//取得当前行所有的token序列
{
	int state = 0;//初态
	//int point = 0;
	//vector<char> to;
	
	char cp = fgetc(fp);
	
	while (cp!=EOF){
		while (cp == ' ' || cp == '\t' || cp == '\n')
		{

			cp = fgetc(fp);
		}//去掉所有的空格，制表符，换行符
		
		if (is_letter(cp) || is_num(cp)) {//是字母或是数字

			//int init = p;
			int state = 0;//初态

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
					ans = { "保留字",val };
				}
				else ans = { "标识符",val };

				token.push_back(ans);
			}
		}
			if (cp == '+' || cp == '-' || cp == '*' || cp == '/' || cp == '(' ||
				cp == ')' || cp == ';' || cp == '[' || cp == ']' || cp == '=' || cp == '<') {
				string tmp;
				tmp += cp;
				PSS a_token = { "单分界符",tmp };
				token.push_back(a_token);
			}
			if (cp == ':') {//:=
				string tmp;
				tmp += cp;
				cp = fgetc(fp);
				if (cp == '=') {
					tmp += cp;
					PSS to = { "双分界符",tmp };
					token.push_back(to);
				}
				else {
					ungetc(cp, fp);
					return false;
				}


			}
			if (cp == '{') {//注释
				cp = fgetc(fp);
				while (cp != '}') {
					cp = fgetc(fp);

				}
				if (cp != '}')return false;
				PSS to = { "注释","{}" };
				token.push_back(to);
			}
			if (cp == '.')//数组下标
			{
				cp = fgetc(fp);
				if (cp == '.') {
					PSS to = { "数组下标",".." };
					token.push_back(to);
				}
				else {
					PSS to = { "程序结束标志","."};
					token.push_back(to);
				}
			}
			if (cp == ',') {//字符标志状态
				cp = fgetc(fp);
				if (is_num(cp) || is_letter(cp)) {
					ungetc(cp, fp);
					PSS to = { "字符标志状态","," };

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

}//显示一个单词 
void printTokenlist(vector<PSS>& to) {
	for (auto a = to.begin(); a != to.end(); a++) {
		printToken(*a);
	}
}//显示词法分析的结果
void ChainToFile(vector<PSS>& Chainhead);//将链表中的Token存入文件 
//enum state { 0, 1, 2, 3, 4, 5 };//dfa的所有状态 
//enum letter { 'a'..'Z' };//字母 
//enum digit { '0'..'9' };//数字
//enum outkind {
// id, num, error, start
//}; //输出单词的类别
//int T[6][]

int main() {
	FILE* fp;
	if ((fopen_s(&fp,"/input.txt", "r")) == NULL)
	{
		printf("文件打开失败\n");
		exit(1);
	}
	bool flag = getTokenlist(fp);
	fclose(fp);
	if(flag==false){
		cout << "词法分析失败，程序编写有错误" << endl;
	}
	else {
		printTokenlist(token);
	}

	
	

	return 0;

}