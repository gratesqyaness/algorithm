#include<iostream>
#include<vector>
using namespace  std;
/*利用分治法求逆序对的个数，基于分治动点小手脚*/
void merger(vector<int>& nums, int left, int mid, int right);
void findreversePairs(vector<int>& nums, int left, int right);
int numOfParis = 0;
int reversePairs(vector<int>& nums) {
	if (nums.size() <= 1)
		return 0;
	findreversePairs(nums, 0, nums.size() - 1);
	return numOfParis;
}

void findreversePairs(vector<int>& nums, int left, int right) {
	if (left - right == 0) {//当递归到只剩下一个元素的时候，我们返回
		return;
	}
	/*否则我们将数组分成两部分进行递归*/
	int mid = (left + right) / 2;
	findreversePairs(nums, left, mid);
	findreversePairs(nums, mid + 1, right);
	merger(nums, left, mid, right);
	/*递归之后我们进行合并，这里思路可以参考归并排序，在归并的时候找逆序对的个数*/
}

void merger(vector<int>& nums, int left, int mid, int right) {
	vector<int>temp;//创建一个数组用来合并
	int i = left, j = mid + 1;
	while (i <= mid && j <= right) {
		if (nums[i] <= nums[j]) {//此时没有逆序对
			temp.push_back(nums[i++]);
		}
		else {//出现了前面大于后面的情况，那么说明后面子数组这点及之前的所有元素都是逆序对
			temp.push_back(nums[j++]);
			numOfParis += (mid - i + 1);//这里划重点！！！为啥要这么干捏 mid-i+1相当于我此时左半边数组的元素个数，每次将右边归并时候，逆序对的个数=原有个数+左边所有元素个数 逆向思维啊我去
		}

	}

	/*如果i>mid说明前一个数组中的元素已经全部放到temp中了，那么后面的没有逆序对*/
	if (i > mid) {
		while (j <= right) {
			temp.push_back(nums[j++]);
		}
	}
	else {
		while (i <= mid) {/*如果是后面先结束，那么逆序对个个数为前面元素个数*后面数组长度*/
			temp.push_back(nums[i++]);
		}

	}
	//将temp里面的内容复制到nums中去，保护现场
	for (i = left, j = 0; i <= right; i++, j++) {
		nums[i] = temp[j];
	}

}

void main() {
	vector<int>nums = {1,3,2,3,1};
	reversePairs(nums);
	cout << numOfParis << endl;
	for (int i = 0; i < nums.size(); i++) {
		cout << nums[i] <<"	";
	}
}