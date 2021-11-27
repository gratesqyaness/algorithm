#include<iostream>
#include<vector>
using namespace std;
int MAX(vector<int>&arr,int left,int right) {
	if (left == right) {//如果只剩下一个元素，直接返回
		return arr[left];
	}
	else if (right - left == 1) {//如果剩下两个元素，返回较大的
		return max(arr[left], arr[right]);
	}
	else {//否则我就继续递归啊
		int mid = (left + right) / 2;
		return max(MAX(arr, left, mid), MAX(arr, mid + 1, right));
	}
}

void main() {
	vector<int>arr = { 1,2,34,5,6,7,8 ,1,1,1,111,111,112};
	cout << MAX(arr, 0, arr.size() - 1);
}