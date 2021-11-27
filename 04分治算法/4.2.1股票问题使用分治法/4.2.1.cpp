#include<iostream>
#include<vector>
#include<math.h>
#include<algorithm>
//按序寻找最大差值
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
	return max(findTheMaxProfit(0, pricesGap.size() - 1, pricesGap), 0);//如果结果<=0输出0
}

int findTheMaxProfit(int left, int right, vector<int>& pricesGap) {
	if (left >= right) {//发现只剩下一个元素了，递归结束
		return pricesGap[left];
	}
	//如果最大收益出现在左右两边数组，我们就递归去左右两边数组去寻找
	int mid = (right + left) / 2;
	int sumOfLeft = findTheMaxProfit(left, mid, pricesGap);
	int sumOfRight = findTheMaxProfit(mid + 1, right, pricesGap);
	/*如果我的最大收益横跨了我分离的左右数组，那么我就这两个左右数组合并,去找最大值。这里要注意，此时一定会跨两端*/
	int Cross = CrossArray(left, mid, right, pricesGap);

	return max(sumOfLeft, max(sumOfRight, Cross));
}

int  CrossArray(int left, int mid, int right, vector<int>& pricesGap) {
	int sumOfLeft = 0;
	int SumOfRight = 0;//用来记录我左右的所找的结点总值
	int maxOfLeft = 0xffffffff;
	int maxOfRight = 0xffffffff;
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
	/*我们要先将数组进行处理，让每一项的前一个该项，得到新的一个数组*/
	vector<int>intial = {1,544,3,4,656,7};
	cout << maxProfit(intial) << endl;;
}