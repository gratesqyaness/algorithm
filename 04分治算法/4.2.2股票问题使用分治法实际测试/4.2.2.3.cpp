#include<fstream>
#include<sstream>
#include<iostream>
#include<vector>
#include<math.h>
#include<algorithm>
using namespace std;
vector<float>dataArray;//�������Ҵ�excel�ж�������������
bool ReadData(const char* ad) {//ad Ϊ�ļ���
	//�����ļ������
	ifstream re;

	//��Ҫ������ļ�
	re.open(ad);
	if (re.bad()) {//������ļ�ʧ��
		return false;
	}
	string tem1;//���������Ǵ˶�����һ���ַ���
	/*ÿ�ζ�ȡһ�У���������ʽ�ָ*/
	while (re.peek() != EOF) {
		re >> tem1;//ÿ�ζ�ȡһ��
		stringstream ss(tem1);
		string token1, token2;//token1�����ڣ�token2�浱��۸�
		std::getline(ss, token1, ',');
	std:getline(ss, token2, ',');//�Զ��ŵ���ʽ�ָ���
	//��token2���ַ�������ȡΪ������
		float priceOfDay = std::atof(token2.c_str());
		dataArray.push_back(priceOfDay);//���ڶ�дԭ��dataArray�����һ�ж��һ�Σ������ڴ����������ʱ���ס�����һ���޳����ɡ�
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
	/*return max(findTheMaxProfit(0, pricesGap.size() - 1, pricesGap), 0);*///������<=0���0
	return findTheMaxProfit(0, pricesGap.size() - 1, pricesGap);
}

float findTheMaxProfit(int left, int right, vector<float>& pricesGap) {
	if (left >= right) {//����ֻʣ��һ��Ԫ���ˣ��ݹ����
		return pricesGap[left];
	}
	//��������������������������飬���Ǿ͵ݹ�ȥ������������ȥѰ��
	int mid = (right + left) / 2;
	float sumOfLeft = findTheMaxProfit(left, mid, pricesGap);
	float sumOfRight = findTheMaxProfit(mid + 1, right, pricesGap);
	/*����ҵ�������������ҷ�����������飬��ô�Ҿ���������������ϲ�,ȥ�����ֵ������Ҫע�⣬��ʱһ���������*/
	float Cross = CrossArray(left, mid, right, pricesGap);

	return max(sumOfLeft, max(sumOfRight, Cross));
}

float  CrossArray(int left, int mid, int right, vector<float>& pricesGap) {
	float sumOfLeft = 0;
	float SumOfRight = 0;//������¼�����ҵ����ҵĽ����ֵ
	float maxOfLeft = -1e10;
	float maxOfRight = -1e10;//����ʼ����Ϊ��Сֵ
	for (int i = mid; i >= left; i--) {//Ҫ�����˿�ʼ��
		sumOfLeft += pricesGap[i];//�������������ֵ
		if (sumOfLeft > maxOfLeft) {
			maxOfLeft = sumOfLeft;//��������˱�max���ֵ��˵����ʱ�����˱�֮ǰ���õ������
		}
	}


	for (int i = mid + 1; i <= right; i++) {
		SumOfRight += pricesGap[i];
		if (SumOfRight > maxOfRight) {
			maxOfRight = SumOfRight;
		}
	}

	return  maxOfLeft + maxOfRight;//���ر��ι����ҵ������max
}

void main() {
	ReadData("data.csv");
	cout<<maxProfit(dataArray);
	///*
//1.��data.scv�ж�ȡ�������ݣ��ŵ�dataArray��
//2.������dataArray[i]-dataArray[i-1]����subArray*/
//ReadData("data.csv");
//createSubArray();
///*֮���൱�����������������������*/
//cout << "�������Ϊ" << BestBenificeOfStock(0, subArray.size() - 1, subArray) << endl;

////����indexOfRight��ת����������±꣬���Զ�Ӧ��Զ�����±�Ҫô��indexOfRight,Ҫô��indexOfRight+1
//float rightResult = subArray[indexOfRight] > subArray[indexOfRight + 1] ? indexOfRight : indexOfRight + 1;
////Ȼ���ҵ�����ҽ��֮ǰ����Сֵ����
//float leftResult = distance(subArray.begin(), min_element(subArray.begin(), subArray.begin() + rightResult));
//cout << "�±�Ϊ" << leftResult << "->" << rightResult << endl;
}


