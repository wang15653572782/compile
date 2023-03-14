#include<iostream>
#include<vector>
#include<algorithm>
#include<cstring>
#include <cstdio>
#include <stack>
#include <fstream>
using namespace std;
typedef pair<int, pair<string, string>> PSS;//存储单个Token 
vector<PSS> token;
string Keyword[] = { "program","procedure","type","var","then","else","fi","do",
"endwh","array","of","record","write","return","integer","char","if","read","while","end","begin" };
string operate[] = { "+","-",">","<","=" };

void getNextChar();//取得下一个非空字符 
void ungetNextChar();//回退字符
bool  reservedLookup(string s) {
	for (auto x : Keyword) {
		if (x == s)return true;
	}
	return false;
};//查找保留字
void getTokenlist();//取得所有单词
void printToken(PSS& token1) {
	int line = token1.first;
	auto item = token1.second;
	string key = item.first;
	string val = item.second;
	cout << line << "  " << key << " " << val << endl;


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
	ifstream fin("input.txt");
	if (!fin.is_open()) {
		cout << "error while opening the file\n";
		exit(0);
	}
	int lin = 1;
	while (!fin.eof()) {
		char ch[50];
		fin.getline(ch, 50);//逐行扫描


	}

	//cout << ch << endl;

	return 0;

}