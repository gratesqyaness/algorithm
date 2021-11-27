#include<iostream>
#include<vector>
using namespace std;
//bool flag = false;
/*这里有一个比较奇怪的问题，为什么我的判断等于不能放在最后一个else*/
int binarySearch(vector<int>& benchArr,int left,int right, int target) {
	//二分查找，查到到了返回下标，没查找到返回-1
	//if (left > right)//递归终点需防止在之前
	//	return -1;
	int mid = (left + right) / 2;
	if (benchArr[mid] == target) {
		flag = true;
		return mid;//相等时，我们返回其下标
	}
	else if (benchArr[mid] < target) {//中间的值小于target,我应该去右边去找他
		binarySearch(benchArr, mid + 1, right, target);
	}
	else {//中间值大于target，我应该去左边去找它
		binarySearch(benchArr, left, mid - 1, target);
	}
	/*if (!flag)//不能这么写，因为此时递归并没有结束
		return -1;*/
}
int main() {
	vector<int>beachArr = { 1,3,5,7,9,10,11,22,33,45 };
	int target;
	cin >> target;
	cout << "最终查找到的下标是" << binarySearch(beachArr, 0,beachArr.size()-1,target)<<endl;
}