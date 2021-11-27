#include<iostream>
#include<vector>
using namespace std;
/*leetcode�������Ƶ���https://leetcode-cn.com/problems/xx4gT2/solution/*/
/*����ѡ�񣬷��������е�i���Ԫ��
 C(n)best=n-1
 C(n)worst=n(n-1)/2
 C(n)average�����Ե�����Ӣ�Ŀα�159*/
int LomutoPartition(vector<int>& arr,int left,int right) {
	int pivot = arr[left];//ѡ��������ĵ�һ��������Ϊѡ������
	int s = left;
	int i;
	for (i = left + 1; i <= right; i++) {
		/*sָ���Ѿ�������С��privot�����һ��Ԫ�ء�iָ��û�п����ĵ�һ��Ԫ��*/
		if (arr[i] < pivot) {//С��pivot���Ǿ���s+1���н���
			swap(arr[i], arr[++s]);
		}
	}
	
	swap(arr[left], arr[s]);//��pivot�ŵ��ָ���
	return s;//���s��λ�÷���
}

int quickSelect(vector<int>&arr,int left,int right,int k) {//Ѱ�ҵ�kС��ֵ
	if (left >= right) {//���ʣ��һ��Ԫ���ˣ���ʱ��ֵ����������Ҫ��ֵ��
		return arr[left];
	}
	int s = LomutoPartition(arr, left, right);
	if (s == k - 1) {//�����ʱ��sǡ��Ϊk-1(�±�),˵�������ҵ���
		return arr[s];
	}
	if (s >k - 1) {//s��λ�ô���������ҪѰ�ҵ�λ�ã�˵������Ҫ�ҵĻ�����ߣ�����߼����ݹ鼴��
		quickSelect(arr, left,  s - 1,k);
	}
	else {//s��λ��С��������ҪѰ�ҵ�λ�ã�˵������Ҫ�ҵ����ұߣ����ұ߼����ݹ鼴��
		quickSelect(arr, s + 1, right, k);
	}
}
void swap(int &a,int &b) {//���������е�����Ԫ��
	int temp = a;
	a = b;
	b = temp;
}

void main() {
	vector<int>arr = { 3,2,1,5,6,4 };
	cout << quickSelect(arr, 0, arr.size() - 1, 5);
}