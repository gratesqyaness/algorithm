#include<iostream>
#include<vector>/*���������޷�����*/
using namespace std;
int maxbit(vector<int>& arr) {//���������������λ��
	int maxOfArr = -1e7;
	for (int i = 0; i < arr.size(); i++) {
		if (arr[i] > maxOfArr) {
			maxOfArr = arr[i];
		}
	}
	int numOfBit = 0;
	while (maxOfArr > 0) {
		maxOfArr /= 10;
		numOfBit++;
	}
	return numOfBit;
}

void RadixSort(vector<int>& arr) {
	int bit = maxbit(arr);//�ҳ���Ҫ��������Ĵ���
	
	int radix = 1;//����ָʾ�������ĸ�λ�ã����Ǵӵ�λ���λ�š���ʵ���������ȶ���

	vector<int>count(10,0);//ÿ��λ�ķ�Χλ0-9,����������Ҫһ��10����СΪ1��Ͱ���м���
	for (int i = 0; i <bit; i++) {//����bit������
		for (int j = 0; j < 10; j++) {//ÿ��Ҫ��ռ�����
			count[j] = 0;
		}
		for (int j = 0; j < arr.size(); j++) {
			int index = (arr[j] / radix) % 10;
			count[index]++;
		}
		//�����������������count[i]��ʾ�ж��ٸ�Ԫ��С��i(��Ӧλ)
		for (int j = 1; j < 10; j++) {
			count[j] += count[j - 1];
		}
		//4.�������Ŀ�����飺��ÿ��Ԫ�ط���������ĵ�C[i]�ÿ��һ��Ԫ�ؾͽ� C[i]��ȥ1
		vector<int>targetArr(arr.size());
		for (int j = arr.size()-1; j >=0; j--) {
			int index = (arr[j] / radix) % 10;//index��ʾĳһλ���ϵ�ֵ 
			targetArr[--count[index]] = arr[j];//count[index]��ʾ�ж������֣������Լ�)С�ڵ���index
		}
		//��targetArr������ݵ��ص�ԭ����
		for (int j= 0; j < arr.size(); j++) {
			arr[j] = targetArr[j];
		}
		radix *= 10;
	}

}
int main() {
	vector<int>arr = { 3,-1 };
	RadixSort(arr);
	for (int i : arr) {
		cout << i << " "  ;
	}
}