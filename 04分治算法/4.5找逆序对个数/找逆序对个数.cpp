#include<iostream>
#include<vector>
using namespace  std;
/*���÷��η�������Եĸ��������ڷ��ζ���С�ֽ�*/
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
	if (left - right == 0) {//���ݹ鵽ֻʣ��һ��Ԫ�ص�ʱ�����Ƿ���
		return;
	}
	/*�������ǽ�����ֳ������ֽ��еݹ�*/
	int mid = (left + right) / 2;
	findreversePairs(nums, left, mid);
	findreversePairs(nums, mid + 1, right);
	merger(nums, left, mid, right);
	/*�ݹ�֮�����ǽ��кϲ�������˼·���Բο��鲢�����ڹ鲢��ʱ��������Եĸ���*/
}

void merger(vector<int>& nums, int left, int mid, int right) {
	vector<int>temp;//����һ�����������ϲ�
	int i = left, j = mid + 1;
	while (i <= mid && j <= right) {
		if (nums[i] <= nums[j]) {//��ʱû�������
			temp.push_back(nums[i++]);
		}
		else {//������ǰ����ں�����������ô˵��������������㼰֮ǰ������Ԫ�ض��������
			temp.push_back(nums[j++]);
			numOfParis += (mid - i + 1);//���ﻮ�ص㣡����ΪɶҪ��ô���� mid-i+1�൱���Ҵ�ʱ���������Ԫ�ظ�����ÿ�ν��ұ߹鲢ʱ������Եĸ���=ԭ�и���+�������Ԫ�ظ��� ����˼ά����ȥ
		}

	}

	/*���i>mid˵��ǰһ�������е�Ԫ���Ѿ�ȫ���ŵ�temp���ˣ���ô�����û�������*/
	if (i > mid) {
		while (j <= right) {
			temp.push_back(nums[j++]);
		}
	}
	else {
		while (i <= mid) {/*����Ǻ����Ƚ�������ô����Ը�����Ϊǰ��Ԫ�ظ���*�������鳤��*/
			temp.push_back(nums[i++]);
		}

	}
	//��temp��������ݸ��Ƶ�nums��ȥ�������ֳ�
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