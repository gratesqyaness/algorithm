#include<iostream>
#include<vector>
#include<Windows.h>
using namespace std;
vector<int>arr;
void PrintArr(vector<int>arr) {
	for (int i = 0; i < arr.size(); i++) {
		cout << arr[i] << "	";
	}
	cout << endl;
}
void CobblerSort(int left,int right,vector<int>&arr) {
	if (left==right) {//即只有一个数据
		return;
	}
	else if(right-left==1) {//如果有两个元素
		if (arr[left] > arr[right]) {
			int temp = arr[left];
			arr[left] = arr[right];
			arr[right] = temp;
			//PrintArr(arr);
		}
		
		return;
	}
	else {
		//它首先递归的对数组的前2n⁄3个元素进行排序
		int bench =  (right-left+1) / 3;//数组大小为right-left+1
		//CobblerSort(left,left+bench*2-1,arr);
		CobblerSort(left, right - bench, arr);
		for (int i = 0; i < arr.size(); i++) {
			cout << arr[i] << "  ";
		}
		cout << endl;
		//接着对数组的后2n/3个元素进行排序
		CobblerSort(left+bench,right,arr);
		//再对数组的前2n/3元素进行排序
		//CobblerSort(left,left+bench*2-1,arr);
		CobblerSort(left, right - bench, arr);
	}
}


int main() {
	int arrSize = 12;
	arr.resize(arrSize);
	for (int i = arrSize; i > 0; i--)
		arr[arrSize - i] = i;
	for (int i = 0; i < arr.size(); i++) {
		cout << arr[i] << "  ";
	}
	cout << endl;
	clock_t t2 = clock();// 使用clock()构造clock_t对象(实际上是long类型的变量)
	CobblerSort(0, arr.size() - 1, arr);
	cout << "t2所用时间为" << (clock() - t2) * 1.0 / CLOCKS_PER_SEC * 1000 << "ms" << endl;
	
}