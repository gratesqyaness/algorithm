#include<iostream>
#include<vector>
#include<math.h>
#include<algorithm>
//����Ѱ������ֵ
using namespace std;
int findTheMaxProfit(int left, int right, vector<int>& pricesGap);
int  CrossArray(int left, int mid, int right, vector<int>& pricesGap);
int maxProfit(vector<int>& prices) {
	if (prices.size() <= 1) {
		return 0;
	}
	vector<int>pricesGap;
	for (int i = 0; i < prices.size() - 1; i++) {
		pricesGap.push_back(prices[i + 1] - prices[i]);
	}
	return max(findTheMaxProfit(0, pricesGap.size() - 1, pricesGap), 0);//������<=0���0
}

int findTheMaxProfit(int left, int right, vector<int>& pricesGap) {
	if (left >= right) {//����ֻʣ��һ��Ԫ���ˣ��ݹ����
		return pricesGap[left];
	}
	//��������������������������飬���Ǿ͵ݹ�ȥ������������ȥѰ��
	int mid = (right + left) / 2;
	int sumOfLeft = findTheMaxProfit(left, mid, pricesGap);
	int sumOfRight = findTheMaxProfit(mid + 1, right, pricesGap);
	/*����ҵ�������������ҷ�����������飬��ô�Ҿ���������������ϲ�,ȥ�����ֵ������Ҫע�⣬��ʱһ���������*/
	int Cross = CrossArray(left, mid, right, pricesGap);

	return max(sumOfLeft, max(sumOfRight, Cross));
}

int  CrossArray(int left, int mid, int right, vector<int>& pricesGap) {
	int sumOfLeft = 0;
	int SumOfRight = 0;//������¼�����ҵ����ҵĽ����ֵ
	int maxOfLeft = 0xffffffff;
	int maxOfRight = 0xffffffff;
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
	/*����Ҫ�Ƚ�������д�����ÿһ���ǰһ������õ��µ�һ������*/
	vector<int>intial = {1,544,3,4,656,7};
	cout << maxProfit(intial) << endl;;
}