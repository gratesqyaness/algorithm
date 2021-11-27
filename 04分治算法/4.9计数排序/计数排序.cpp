/*from https://zh.wikipedia.org/wiki/%E8%AE%A1%E6%95%B0%E6%8E%92%E5%BA%8F*/
#include<iostream>
#include<vector>
using namespace std;
/*���Ӷ�O(n+k)*/
void countingSort(vector<int>&arr) {
	//1.�ҳ��������������������С��Ԫ��
	int maxElement = -10e7, minElement = 10e7;
	for (int i = 0; i < arr.size(); i++) {
		if (arr[i] > maxElement) {
			maxElement = arr[i];
		}
		if (arr[i] < minElement) {
			minElement = arr[i];
		}
	}
	//2.ͳ��������ÿ��ֵΪi��Ԫ�س��ֵĴ�������������C�ĵ�i��
	vector<int>countArr;
	
	countArr.resize(maxElement - minElement +1);//maxElement - minElement +1Ϊ��Ԫ��ֵ����
	for (int i = 0; i < countArr.size(); i++) {//��countArr���������0����
		countArr[i] = 0;
	}
	for (int i = 0; i < arr.size(); i++) {//����Ҫע����С��aee.size������Ϊ��ʱ��Ҫ��arr�����countArr��ӦO(n)
		countArr[arr[i] - minElement]++;
	}
	//3.�����еļ����ۼӣ��� C �еĵ�һ��Ԫ�ؿ�ʼ��ÿһ���ǰһ����ӣ�
	for (int i = 1; i < countArr.size(); i++) {//O(k)
		countArr[i] += countArr[i - 1];//��ʱcountArr[i]��ζ�ű�iС�������ж��ٸ�
	}
	//4.�������Ŀ�����飺��ÿ��Ԫ�ط���������ĵ�C[i]�ÿ��һ��Ԫ�ؾͽ� C[i]��ȥ1
	vector<int>targetArr;
	targetArr.resize(arr.size());
	for (int i = arr.size()-1; i>=0; i--) {//��ʱҲ��Ҫע����arr����
	//arr[i]-minElement��Դ�С,countArr[i]�д����С��iԪ�صĸ�����
	//ͨ�׵���⣬������10�����䲻ͬ���ˣ�ͳ�Ƴ���8���˵������AС����A����������ڵ�9λ��������������Եõ�����ÿ���˵�λ�ã�Ҳ���ź�����
		targetArr[--countArr[arr[i] - minElement]] = arr[i];//����Ҫ��--��why����ΪcountArr[arr[i] - minElement]��ʾ��arr[i]С�ڵ��ڵĸ���ʵ����Ҳ�������Լ����������Ǵ�0-length-1�ģ�Ҫ��Ӧ����������
		
	}
	for (int i : targetArr) {
		cout << i<<" ";
	}
	//������������ԭ����
	for (int i = 0; i < arr.size(); i++) {
		arr[i] = targetArr[i];
	}
}

void main() {
	vector<int>arr = {5,2,3,1};
	countingSort(arr);
	
}