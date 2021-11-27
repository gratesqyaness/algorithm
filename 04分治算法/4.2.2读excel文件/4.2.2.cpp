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
/*关键点:将文件采用UTF-8编码，用CSV文件后缀*/
bool ReadFromExcel(const char *ad) {
	//定义文件输出流
	ifstream re;
	
	//打开要输出的文件
	//re.open("TRD_Dalyr.xlsx");
	  re.open(ad);
	if (re.bad()) {//如果打开文件夹失败
		return false;
	}
	string tem1,tem2;
	//打开要输出的文件 
	while (re.peek()!= EOF) {
		re >> tem1;//每次读取一行，按逗号形式分隔开
	//	cout << tem1 << endl;
		//以逗号为分界点拆开
		stringstream ss(tem1);
		string token1,token2;//token1存日期,token2存当天价格
		std::getline(ss, token1, ',');
		std::getline(ss, token2, ',');
		//将token2提取为浮点型
		float priceOfone = std::atof(token2.c_str());
		dataArr[token1] = priceOfone;//用map存数据的话顺序会乱
		dataArray.push_back(priceOfone);//由于读写原因，dataArray将最后一行多读一次，我们在处理子数组的时候记住将最后一行剔除即可。
	}
	cout << dataArr.size()<< endl;
	cout << dataArray.size() << endl;
	return true;
}

int main() {
	ReadFromExcel("data.csv");
}
