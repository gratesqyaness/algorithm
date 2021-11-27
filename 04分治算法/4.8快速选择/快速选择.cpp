#include<iostream>
#include<vector>
using namespace std;
/*leetcode中有类似的题https://leetcode-cn.com/problems/xx4gT2/solution/*/
/*快速选择，返回数组中第i大的元素
 C(n)best=n-1
 C(n)worst=n(n-1)/2
 C(n)average是线性的啦。英文课本159*/
int LomutoPartition(vector<int>& arr,int left,int right) {
	int pivot = arr[left];//选择子数组的第一个数组作为选择中轴
	int s = left;
	int i;
	for (i = left + 1; i <= right; i++) {
		/*s指向已经看过的小于privot的最后一个元素。i指向没有看过的第一个元素*/
		if (arr[i] < pivot) {//小于pivot我们就与s+1进行交换
			swap(arr[i], arr[++s]);
		}
	}
	
	swap(arr[left], arr[s]);//将pivot放到分割线
	return s;//最后将s的位置返回
}

int quickSelect(vector<int>&arr,int left,int right,int k) {//寻找第k小的值
	if (left >= right) {//如果剩下一个元素了，此时的值便是我们想要的值。
		return arr[left];
	}
	int s = LomutoPartition(arr, left, right);
	if (s == k - 1) {//如果此时的s恰好为k-1(下标),说明我们找到了
		return arr[s];
	}
	if (s >k - 1) {//s的位置大于我们需要寻找的位置，说明我们要找的还是左边，往左边继续递归即可
		quickSelect(arr, left,  s - 1,k);
	}
	else {//s的位置小于我们需要寻找的位置，说明我们要找的在右边，往右边继续递归即可
		quickSelect(arr, s + 1, right, k);
	}
}
void swap(int &a,int &b) {//交换数组中的两个元素
	int temp = a;
	a = b;
	b = temp;
}

void main() {
	vector<int>arr = { 3,2,1,5,6,4 };
	cout << quickSelect(arr, 0, arr.size() - 1, 5);
}