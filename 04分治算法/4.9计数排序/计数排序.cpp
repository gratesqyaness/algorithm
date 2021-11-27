/*from https://zh.wikipedia.org/wiki/%E8%AE%A1%E6%95%B0%E6%8E%92%E5%BA%8F*/
#include<iostream>
#include<vector>
using namespace std;
/*复杂度O(n+k)*/
void countingSort(vector<int>&arr) {
	//1.找出待排序的数组中最大和最小的元素
	int maxElement = -10e7, minElement = 10e7;
	for (int i = 0; i < arr.size(); i++) {
		if (arr[i] > maxElement) {
			maxElement = arr[i];
		}
		if (arr[i] < minElement) {
			minElement = arr[i];
		}
	}
	//2.统计数组中每个值为i的元素出现的次数，存入数组C的第i项
	vector<int>countArr;
	
	countArr.resize(maxElement - minElement +1);//maxElement - minElement +1为该元素值域跨度
	for (int i = 0; i < countArr.size(); i++) {//将countArr数组进行清0操作
		countArr[i] = 0;
	}
	for (int i = 0; i < arr.size(); i++) {//这里要注意是小于aee.size。是因为此时需要将arr数组和countArr对应O(n)
		countArr[arr[i] - minElement]++;
	}
	//3.对所有的计数累加（从 C 中的第一个元素开始，每一项和前一项相加）
	for (int i = 1; i < countArr.size(); i++) {//O(k)
		countArr[i] += countArr[i - 1];//此时countArr[i]意味着比i小的数据有多少个
	}
	//4.反向填充目标数组：将每个元素放在新数组的第C[i]项，每放一个元素就将 C[i]减去1
	vector<int>targetArr;
	targetArr.resize(arr.size());
	for (int i = arr.size()-1; i>=0; i--) {//此时也需要注意是arr数组
	//arr[i]-minElement相对大小,countArr[i]中存的是小于i元素的个数。
	//通俗地理解，例如有10个年龄不同的人，统计出有8个人的年龄比A小，那A的年龄就排在第9位，用这个方法可以得到其他每个人的位置，也就排好了序。
		targetArr[--countArr[arr[i] - minElement]] = arr[i];//这里要先--。why？因为countArr[arr[i] - minElement]表示比arr[i]小于等于的个数实际上也包括了自己。但数组是从0-length-1的，要对应。否则会溢出
		
	}
	for (int i : targetArr) {
		cout << i<<" ";
	}
	//将排序结果导入原数组
	for (int i = 0; i < arr.size(); i++) {
		arr[i] = targetArr[i];
	}
}

void main() {
	vector<int>arr = {5,2,3,1};
	countingSort(arr);
	
}