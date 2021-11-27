#include<iostream>
#include<vector>
using namespace std;
void merger(vector<int>& arr, int left, int mid, int right);
void mergerSort(vector<int>&arr,int left,int right) {
	/*�鲢����,����һ����Ҫ���������A[0,n-1],�鲢�������һ��Ϊ����A[0,(n/2-1)]��A[n/2,n-1],����ÿ��������ݹ�����*/
	
	if (left >= right) { return; }//��ֹ����
	   int mid = (left+right) / 2;
		mergerSort(arr, left, mid);
		mergerSort(arr, mid + 1, right);
		//����Ҫ��ס�ϲ�
		merger(arr, left,mid,right);//�ϲ���
}
void merger(vector<int>&arr,int left,int mid,int right) {//��B��left��right���ֽ�������
	//��������������ϲ���һ����������
	vector<int>temp;//����ʹ��һ��length=right-left+1�����飬������ʹ�úϲ��ȽϵĴ���Ϊn��
	 int i = left, j = mid+1;//i����������arr[left:mid]�Ƿ�Ƚ���ϣ�J����������arr[mid+1:right]�Ƿ�Ƚ����
	 while (i <= mid && j <=right) {//����һ������Ƚ�������Ƕ�Ӧ���˳�ѭ��
		 if (arr[i] < arr[j]) {//����С�Ĳ嵽ǰ��ȥ
			 temp.push_back(arr[i]);
			 i++;
		 }
		 else
		 {
			 temp.push_back(arr[j]);
			 j++;
		 }
	 }
	 if (i <=mid) {//����ı��Ƚ����ˣ���ô����һ��ʣ���Ԫ�ؿ϶������ģ�ֱ�Ӳ嵽����ĩβ����
		 while (i <= mid) {
			 temp.push_back(arr[i++]);
		 }
	 }
	 else {
		 while (j <= right) {
			 temp.push_back(arr[j++]);
		 }
	 }
		/*�����ٽ�����õ�temp���ص�arr,���������ź������Ϣ��ʧ*/
	 for (int i = left,j=0; i <= right; i++,j++) {
		 arr[i] = temp[j];
	 }
}

 int main() {
	 vector<int>arr = { 6,5,4,3,2,1 };
	 mergerSort(arr, 0, arr.size()-1);
	 for (auto i : arr)
		 cout << i << " ";
}