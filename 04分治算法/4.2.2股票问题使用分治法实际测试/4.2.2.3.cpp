#include<fstream>
#include<sstream>
#include<iostream>
#include<vector>
#include<math.h>
#include<algorithm>
using namespace std;
vector<float>dataArray;//用来存我从excel中读到的所有数据
bool ReadData(const char* ad) {//ad 为文件名
	//定义文件输出流
	ifstream re;

	//打开要输出的文件
	re.open(ad);
	if (re.bad()) {//如果打开文件失败
		return false;
	}
	string tem1;//用来存我们此读出的一行字符串
	/*每次读取一行，按逗号形式分割开*/
	while (re.peek() != EOF) {
		re >> tem1;//每次读取一行
		stringstream ss(tem1);
		string token1, token2;//token1存日期，token2存当天价格
		std::getline(ss, token1, ',');
	std:getline(ss, token2, ',');//以逗号的形式分隔开
	//将token2由字符串型提取为浮点型
		float priceOfDay = std::atof(token2.c_str());
		dataArray.push_back(priceOfDay);//由于读写原因，dataArray将最后一行多读一次，我们在处理子数组的时候记住将最后一行剔除即可。
	}
	return true;
}


float findTheMaxProfit(int left, int right, vector<float>& pricesGap);
float  CrossArray(int left, int mid, int right, vector<float>& pricesGap);
float maxProfit(vector<float>& prices) {
	if (prices.size() <= 1) {
		return 0;
	}
	vector<float>pricesGap;
	for (int i = 0; i < prices.size() - 1; i++) {
		pricesGap.push_back(prices[i + 1] - prices[i]);
	}
	/*return max(findTheMaxProfit(0, pricesGap.size() - 1, pricesGap), 0);*///如果结果<=0输出0
	return findTheMaxProfit(0, pricesGap.size() - 1, pricesGap);
}

float findTheMaxProfit(int left, int right, vector<float>& pricesGap) {
	if (left >= right) {//发现只剩下一个元素了，递归结束
		return pricesGap[left];
	}
	//如果最大收益出现在左右两边数组，我们就递归去左右两边数组去寻找
	int mid = (right + left) / 2;
	float sumOfLeft = findTheMaxProfit(left, mid, pricesGap);
	float sumOfRight = findTheMaxProfit(mid + 1, right, pricesGap);
	/*如果我的最大收益横跨了我分离的左右数组，那么我就这两个左右数组合并,去找最大值。这里要注意，此时一定会跨两端*/
	float Cross = CrossArray(left, mid, right, pricesGap);

	return max(sumOfLeft, max(sumOfRight, Cross));
}

float  CrossArray(int left, int mid, int right, vector<float>& pricesGap) {
	float sumOfLeft = 0;
	float SumOfRight = 0;//用来记录我左右的所找的结点总值
	float maxOfLeft = -1e10;
	float maxOfRight = -1e10;//将初始设置为极小值
	for (int i = mid; i >= left; i--) {//要从两端开始找
		sumOfLeft += pricesGap[i];//计算左数组最大值
		if (sumOfLeft > maxOfLeft) {
			maxOfLeft = sumOfLeft;//如果出现了比max大的值，说明此时出现了比之前更好的情况。
		}
	}


	for (int i = mid + 1; i <= right; i++) {
		SumOfRight += pricesGap[i];
		if (SumOfRight > maxOfRight) {
			maxOfRight = SumOfRight;
		}
	}

	return  maxOfLeft + maxOfRight;//返回本次过程找到的最大max
}

void main() {
	ReadData("data.csv");
	cout<<maxProfit(dataArray);
	///*
//1.从data.scv中读取所有数据，放到dataArray中
//2.新生成dataArray[i]-dataArray[i-1]数组subArray*/
//ReadData("data.csv");
//createSubArray();
///*之后，相当于是求最大连续子数组问题*/
//cout << "最大收益为" << BestBenificeOfStock(0, subArray.size() - 1, subArray) << endl;

////由于indexOfRight是转换后数组的下标，所以对应与远数组下标要么是indexOfRight,要么是indexOfRight+1
//float rightResult = subArray[indexOfRight] > subArray[indexOfRight + 1] ? indexOfRight : indexOfRight + 1;
////然后找到这个右结点之前的最小值即可
//float leftResult = distance(subArray.begin(), min_element(subArray.begin(), subArray.begin() + rightResult));
//cout << "下标为" << leftResult << "->" << rightResult << endl;
}


