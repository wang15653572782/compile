#include<iostream>
#include<vector>
#include<algorithm>
#include<cstring>
#include <cstdio>
#include <stack>
#include <fstream>
using namespace std;
typedef pair<int, pair<string, string>> PSS;//�洢����Token 
vector<PSS> token;
string Keyword[] = { "program","procedure","type","var","then","else","fi","do",
"endwh","array","of","record","write","return","integer","char","if","read","while","end","begin" };
string operate[] = { "+","-",">","<","=" };

void getNextChar();//ȡ����һ���ǿ��ַ� 
void ungetNextChar();//�����ַ�
bool  reservedLookup(string s) {
	for (auto x : Keyword) {
		if (x == s)return true;
	}
	return false;
};//���ұ�����
void getTokenlist();//ȡ�����е���
void printToken(PSS& token1) {
	int line = token1.first;
	auto item = token1.second;
	string key = item.first;
	string val = item.second;
	cout << line << "  " << key << " " << val << endl;


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
	ifstream fin("input.txt");
	if (!fin.is_open()) {
		cout << "error while opening the file\n";
		exit(0);
	}
	int lin = 1;
	while (!fin.eof()) {
		char ch[50];
		fin.getline(ch, 50);//����ɨ��


	}

	//cout << ch << endl;

	return 0;

}