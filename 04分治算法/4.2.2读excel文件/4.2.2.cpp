#include<fstream>
#include<sstream>
#include<string>
#include<iostream>
#include<streambuf>
#include<iostream>
#include<map>
#include<vector>
using namespace std;
map<string,float>dataArr;
vector<float>dataArray;
/*�ؼ���:���ļ�����UTF-8���룬��CSV�ļ���׺*/
bool ReadFromExcel(const char *ad) {
	//�����ļ������
	ifstream re;
	
	//��Ҫ������ļ�
	//re.open("TRD_Dalyr.xlsx");
	  re.open(ad);
	if (re.bad()) {//������ļ���ʧ��
		return false;
	}
	string tem1,tem2;
	//��Ҫ������ļ� 
	while (re.peek()!= EOF) {
		re >> tem1;//ÿ�ζ�ȡһ�У���������ʽ�ָ���
	//	cout << tem1 << endl;
		//�Զ���Ϊ�ֽ���
		stringstream ss(tem1);
		string token1,token2;//token1������,token2�浱��۸�
		std::getline(ss, token1, ',');
		std::getline(ss, token2, ',');
		//��token2��ȡΪ������
		float priceOfone = std::atof(token2.c_str());
		dataArr[token1] = priceOfone;//��map�����ݵĻ�˳�����
		dataArray.push_back(priceOfone);//���ڶ�дԭ��dataArray�����һ�ж��һ�Σ������ڴ����������ʱ���ס�����һ���޳����ɡ�
	}
	cout << dataArr.size()<< endl;
	cout << dataArray.size() << endl;
	return true;
}

int main() {
	ReadFromExcel("data.csv");
}
