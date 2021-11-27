#include<iostream>
#include<vector>
using namespace std;
/*����*/
class heap {
	/*���������洢*/
	vector<int>heapArr;
public:
	heap(vector<int>& arr);
	void increase(int i, int x);//����index=iԪ�ص�ֵΪx
	void PrintTree();//��������ʽ�������
	void insert(int x);//�����µ�Ԫ��
	void heapify(int index);//�ѻ���������indexΪ���ĵ���������index��������Ĳ����Լ�����ѵ�properities)�൱����һ��decrease
	void decrease(int index, int x);//����index��ֵΪx������heapify���ɡ�
	int delete_max();//ɾ�����ڵ㲢����
	void init();//�½�һ����
	void heapSort();//������
};

heap::heap(vector<int>&arr) {
	heapArr = arr;
	init();//���乹��Ϊ��
}

void heap::increase(int i, int x) {//����index=iԪ�ص�ֵΪx
	heapArr[i] = x;//����ֻ�ú������ϵĸ��׺����Ƚ��бȽϼ���
	int indexOfFather=i;
	do {
		if (i == 0) {//�����ڵ��ˣ����˳���
			break;
		}
		else if (i % 2 == 0) {
			indexOfFather = indexOfFather / 2 - 1;
		}
		else {
			indexOfFather = indexOfFather / 2;
		}
		if (heapArr[indexOfFather] < x) {
			swap(heapArr[indexOfFather], heapArr[i]);//�������ڸ��׽�㣬�����ƶ�
			i = indexOfFather;
		}
		else {
			break;
		}
	} while (true);
}

void heap::insert(int x) {
	heapArr.push_back(x);//�Ƚ���ŵ�ĩβ
	increase(heapArr.size() - 1, x);//����һ��increase����
	
}

void heap::heapify(int index) {//��ѻ���iΪ���ڵ㣬��i���������properties�Ķ�
	//ֻ�����Լ��ĺ�����Ƚϣ����С�ڣ��ͽϴ�ĺ��ӽ��н�����
	int indexLength = heapArr.size()-1;
	int indexOflChild;
	int indexOfRChild;
	int swapIndex;
	do {
		indexOflChild = 2 * index + 1;
		indexOfRChild = 2 * index + 2;
		if (indexOflChild > indexLength) {//���ӽ���Ѿ�Խ������˵����ʱarr[index]һ����Ҷ�ӽ�㣬�����˳�����
			break;
		}
		else if (indexOfRChild > indexLength) {//�������ҽڵ�,������ߵ�������Ȼ���ܱ�arr[index]��
			swapIndex = indexOflChild;
		}
		else {
			swapIndex = heapArr[indexOflChild] > heapArr[indexOfRChild] ? indexOflChild : indexOfRChild;//����˭��������
		}
		if (heapArr[swapIndex] > heapArr[index]) {
			swap(heapArr[swapIndex], heapArr[index]);
			index = swapIndex;
		}
		else {//����˵����ʱarr[index]�Ѿ��ƶ�����ȷ��λ����
			break;
		}
	} while (true);
}

void heap::decrease(int index, int x) {
	heapArr[index] = x;
	heapify(index);
}

void heap::PrintTree(){
	for (int i = 0,layer=1; i < heapArr.size(); i++) {
		if (i == pow(2, layer) - 1) {
			layer++;
			cout << endl;
		}
		cout << heapArr[i] << "	" ;
	}
	cout << endl;
}

void heap::init() {//������
	for (int i = heapArr.size() / 2; i >= 0; i--) {
		heapify(i);
	}
}

int heap::delete_max() {
	int temp = heapArr[0];
	//1.�Ƚ����ڵ�Ͷ�βԪ�ؽ��н�����Ȼ��ֱ��ȥ�����һ��Ԫ��
	swap(heapArr[0], heapArr[heapArr.size() - 1]);
	heapArr.pop_back();
	//2.�Ը��ڵ���жѻ�����
	heapify(0);
	return temp;
}

void heap::heapSort() {//������ʵ��������������������delete_max�������ó���ɾ�����У�����һ����
	int length = heapArr.size();//�����ȴ���������Ϊ���ڲ��ϵ�ɾԪ��,heapAr.size()�Ǳ仯��
	for (int i = 0; i < length; i++) {
		cout<<delete_max()<<" ";
	}
}
int main() {
	//vector<int>arr = { 9,8,7,2,1,4,5 };
	vector<int>arr = { 1,2,3,4,5,6,7 };
	heap test(arr);
	test.PrintTree();
	test.heapSort();
	//test.PrintTree();
}

