#include<iostream>
#include<vector>/*碰到负数无法排序*/
using namespace std;
int maxbit(vector<int>& arr) {//辅助函数，求最大位数
	int maxOfArr = -1e7;
	for (int i = 0; i < arr.size(); i++) {
		if (arr[i] > maxOfArr) {
			maxOfArr = arr[i];
		}
	}
	int numOfBit = 0;
	while (maxOfArr > 0) {
		maxOfArr /= 10;
		numOfBit++;
	}
	return numOfBit;
}

void RadixSort(vector<int>& arr) {
	int bit = maxbit(arr);//找出需要整体排序的次数
	
	int radix = 1;//用来指示现在排哪个位置，我们从低位向高位排。其实就是利用稳定性

	vector<int>count(10,0);//每个位的范围位0-9,所以我们需要一个10个大小为1的桶进行计数
	for (int i = 0; i <bit; i++) {//进行bit次排序
		for (int j = 0; j < 10; j++) {//每次要清空计数器
			count[j] = 0;
		}
		for (int j = 0; j < arr.size(); j++) {
			int index = (arr[j] / radix) % 10;
			count[index]++;
		}
		//这里类似与计数排序，count[i]表示有多少个元素小于i(对应位)
		for (int j = 1; j < 10; j++) {
			count[j] += count[j - 1];
		}
		//4.反向填充目标数组：将每个元素放在新数组的第C[i]项，每放一个元素就将 C[i]减去1
		vector<int>targetArr(arr.size());
		for (int j = arr.size()-1; j >=0; j--) {
			int index = (arr[j] / radix) % 10;//index表示某一位数上的值 
			targetArr[--count[index]] = arr[j];//count[index]表示有多少数字（包括自己)小于等于index
		}
		//将targetArr里的数据导回到原数组
		for (int j= 0; j < arr.size(); j++) {
			arr[j] = targetArr[j];
		}
		radix *= 10;
	}

}
int main() {
	vector<int>arr = { 3,-1 };
	RadixSort(arr);
	for (int i : arr) {
		cout << i << " "  ;
	}
}