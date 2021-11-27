#include<iostream>
#include<vector>
#include<algorithm>
/*from https://www.cnblogs.com/bigsai/p/13396391.html
   https://zh.wikipedia.org/wiki/%E6%A1%B6%E6%8E%92%E5%BA%8F*/
using namespace std;

//void BucketSort(vector<int>&arr) {
//	//1.����һ�����������鵱����Ͱ�ӡ�����������С���ݣ��趨ΪͰ��СΪ5
//	vector<vector<int>>bucket(5);
//
//	//2.Ѱ�����У����Ұ���Ŀһ��һ���ŵ���Ӧ��Ͱ��ȥ��
//	for (int i = 0; i < arr.size(); i++) {
//		int index = arr[i] / 10;//max(arr[i])=46�����ǽ�ȫ������/10ǡ������Ͱ�����޶�Ӧ
//		bucket[index].push_back(arr[i]);//��arr[i]�ŵ���Ӧ��Ͱ��
//	}
//	//3.��ÿ�����ǿյ�Ͱ�ӽ�������
//	for (int i = 0; i < bucket.size(); i++) {//��Ͱ�����ݽ��п���
//		if (bucket[i].size() != 0) {
//			sort(bucket[i].begin(), bucket[i].end());
//		}
//	}
//	//4.�Ӳ��ǿյ�Ͱ�������Ŀ�ٷŻ�ԭ���������С�
//	for (int i = 0,j=0; i < bucket.size(); i++) {
//		int NumOfRow = bucket[i].size();//����ָʾ������ʣ��Ԫ�ظ���
//		while (NumOfRow>0) {
//			arr[j++] = bucket[i][bucket[i].size() - NumOfRow];
//			NumOfRow--;
//		}
//	}
//}


/*Ͱ����ʱһ��Ͱװ����Ԫ��(gap)��Ͱ�ĸ�������ôȷ�� https://blog.csdn.net/wusecaiyun/article/details/48048901
  ��ǳ���Ҫ����Ȼ�Ļ����п��ܱȿ��Ż����ΪҪ�����¿��ܶ���ʱ����*/
void BucketSort(vector<int>& arr) {
	//���������nums����Ͱ����nums�ĳ���ΪL����СԪ��ΪA�����Ԫ��ΪB����gapΪ(B - A) / L + 1
	int maxOfarr = -1e7, minOfarr = 1e7;
	for (int i = 0; i < arr.size(); i++) {
		if (arr[i] > maxOfarr) {
			maxOfarr = arr[i];
		}
		if (arr[i] < minOfarr) {
			minOfarr = arr[i];
		}
	}
	int gap = (maxOfarr - minOfarr) / arr.size() + 1;
	//Ͱ�ĸ���Ϊ
	int numOfBucket = (maxOfarr - minOfarr) / gap + 1;
	
	//1.����һ�����������鵱����Ͱ�ӡ�����������С���ݣ��趨ΪͰ��СΪ5
	vector<vector<int>>bucket(numOfBucket);

	//2.Ѱ�����У����Ұ���Ŀһ��һ���ŵ���Ӧ��Ͱ��ȥ��
	for (int i = 0; i < arr.size(); i++) {
		int index = (arr[i]-minOfarr) / (gap);//max(arr[i])=46�����ǽ�ȫ������/10ǡ������Ͱ�����޶�Ӧ
		bucket[index].push_back(arr[i]);//��arr[i]�ŵ���Ӧ��Ͱ��
	}
	//3.��ÿ�����ǿյ�Ͱ�ӽ�������
	for (int i = 0; i < bucket.size(); i++) {//��Ͱ�����ݽ��п���
		if (bucket[i].size() != 0) {
			sort(bucket[i].begin(), bucket[i].end());
		}
	}
	
	//4.�Ӳ��ǿյ�Ͱ�������Ŀ�ٷŻ�ԭ���������С�
	for (int i = 0, j = 0; i < bucket.size(); i++) {
		int NumOfRow = bucket[i].size();//����ָʾ������ʣ��Ԫ�ظ���
		while (NumOfRow > 0) {
			arr[j++] = bucket[i][bucket[i].size() - NumOfRow];
			NumOfRow--;
		}
	}
}

void main() {
	vector<int>arr = { 5,1,1,2,0,0 };
	BucketSort(arr);
	for (int i : arr) {
		cout << i << " ";
	}
}