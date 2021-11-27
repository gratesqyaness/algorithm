/*from https://www.geeksforgeeks.org/quick-sort/*/
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
void swap(int &a,int &b) {//to swap index a  b two element in arr
	int temp = a;
	a=b;
	b = temp;
}
/* This function takes last element as pivot, places
   the pivot element at its correct position in sorted
	array, and places all smaller (smaller than pivot)
   to left of pivot and all greater elements to right
   of pivot */
/*��ͨѡȡpivot*/
int HoarePartition(vector<int>& arr, int left, int right) {//������λ�ĺ϶�����
	// pivot (Element to be placed at right position)
	int pivot = arr[left];//���ǿ��Լ򵥵�ѡȡ��һ��Ԫ�ص�pivot
	int i = left+1, j = right;//i��j�ֱ�����ָ��δ�����Ԫ���г��ֵĵ�һ����pivot��С��Ԫ��
	while (true) {//���յ��ˣ����� 
		while (i<=right&&arr[i] < pivot) {//�ҵ���һ�����ڵ���pivot,����=��Ϊ�˷ֵľ��ȡ�����i������ķ��գ����pivotΪȫ�����ֵ,��ôi�ͻ����
			i++;
		}
		while (j>left&&arr[j] > pivot) {//j�������������Ϊ�ܹ����ʵ�pivot����ֹͣ
			j--;
		}
		if (i>=j)
			break;
		swap(arr[i],arr[j]);
		i++;
		j--;
	}	
	swap(arr[left],arr[j]);//��pivot��index j����
	return j;
}

/*��������ܴ��˳������������ݣ���ͨ��ѡȡpivot���п��ܻ�stack overflow������������Ҫ�ı�һ��ѡȡpivot�ķ�ʽ*/
//���ѡȡpivot
int RandomHoarePartition(vector<int>& arr, int left, int right) {
	srand(time(0));//����һ���������
	int pivotIndex = rand() % (right - left + 1)+left;//���ɴ�left-(right-left+1)���������
	//���������ѡ�е�index������left
	swap(arr[left], arr[pivotIndex]);
	int pivot = arr[left];//�����pivotIndex����Ӧ��ֵ����pivot
	int i = left + 1, j = right;
	while (true) {
		while (i <= right&&arr[i] < pivot) {//��ס��ʱi������right�Ϳ���
			i++;
		}
		while (j > left && arr[j] > pivot) {//��ʱ��j���ܴﵽleftҲ����pivot���ڵ�λ�ã���Ȼ�п��ܽ�pivot����
			j--;
		}
		if (j <= i) {
			break;
		}
		swap(arr[i], arr[j]);//����
		i++;
		j--;//�����סi��j����Ҫ��ǰ��һ�񣬲�Ȼ���ܻ���ѭ��
	}
	swap(arr[left], arr[j]);//��pivot�Ƶ����ʵĵط�
	return j;
}

//ʹ��median of threeѡȡpivot

//������������������λ��,�������������������
void findMedianOfThree(vector<int>&arr, int &left,int &right) {//���ܷ��ؾֲ�����ͺ�����ָ�����Ӧ��ԭ���:https://blog.csdn.net/qq_33266987/article/details/53516977
	int mid = (left + right)/2;
	//���ǽ�left ,mid ,right����λ�õ���λ���Ƶ������
	if (arr[left] > arr[right]) {
		swap(arr[left], arr[right]);
	}
	if (arr[mid] > arr[right]) {
		swap(arr[mid], arr[right]);
	}
	if (arr[mid] > arr[left]) {
		swap(arr[left], arr[mid]);
	}
	
}

//medianOfThreeHoarePartition ��left mid right�е���λ����Ϊpivot
int medianOfThreeHoarePartition(vector<int>&arr, int left, int right) {
	findMedianOfThree(arr, left, right);//��left mid right�е���λ���Ƶ�����ಢ��Ϊpivot
	int pivot = arr[left];
	int i = left + 1, j = right;
	while (true) {
		while (i <= right&&arr[i] < pivot) {
			i++;
		}
		while (j > left&&arr[j] > pivot) {
			j--;
		}
		if (j <= i) {
			break;
		}
		swap(arr[i], arr[j]);
		i++;
		j--;
	}
	swap(arr[left], arr[j]);//���pivot�����ں��ʵ�λ��
	return j;//��ʱarr[j]�Ѿ��ŵ��˺��ʵ�λ��
}



void QuickSort(vector<int>& arr, int left, int right) {
	if (left >= right) {
		return;
	}
	/*���ţ��ȱȽϣ��ٷ�*/
	//int s = HoarePartition(arr, left, right);
	 int s=RandomHoarePartition(arr,left,right);
	//int s = medianOfThreeHoarePartition(arr, left, right);
	/*��s���ڵ�λ�ý�ԭ�����С��Ϊl-s-1,s+1-r���������⣬��ʱs�Ѿ����ú��ˣ�������Ȼ���Ǵ�ʱ���谲��*/
	QuickSort(arr,left,s-1);
	QuickSort(arr, s + 1, right);
}

vector<int> CreateRandom( int size) {//��������������ĺ���
	vector<int>randomArr;
	randomArr.resize(size);
	srand(time(0));//�����������
	for (int i = 0; i < size; i++) {
		randomArr[i] = rand();
	}
	return randomArr;
}

void printArr(vector<int>&arr) {//������ӡ����
	for (int i : arr) {
		cout << i << "  ";
	}
	cout << endl;
}

int main() {
	//vector<int>arr= CreateRandom(1000);
	vector<int>arr = {5,3,2,1};
	

	clock_t t2 = clock();// ʹ��clock()����clock_t����(ʵ������long���͵ı���)
	QuickSort(arr, 0, arr.size() - 1);
	cout << "t2����ʱ��Ϊ" << (clock() - t2) * 1.0 / CLOCKS_PER_SEC * 1000 << "ms" << endl;
	printArr(arr);

}