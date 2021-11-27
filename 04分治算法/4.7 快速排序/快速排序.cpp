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
/*普通选取pivot*/
int HoarePartition(vector<int>& arr, int left, int right) {//采用在位的合二划分
	// pivot (Element to be placed at right position)
	int pivot = arr[left];//我们可以简单的选取第一个元素的pivot
	int i = left+1, j = right;//i、j分别用来指明未处理的元素中出现的第一个比pivot大、小的元素
	while (true) {//到终点了，结束 
		while (i<=right&&arr[i] < pivot) {//找到第一个大于等于pivot,包括=是为了分的均匀。这里i有溢出的风险，如果pivot为全局最大值,那么i就会溢出
			i++;
		}
		while (j>left&&arr[j] > pivot) {//j并不会溢出，因为总归会访问到pivot，会停止
			j--;
		}
		if (i>=j)
			break;
		swap(arr[i],arr[j]);
		i++;
		j--;
	}	
	swap(arr[left],arr[j]);//将pivot与index j交换
	return j;
}

/*如果碰到很大的顺序或则逆序数据，普通的选取pivot很有可能会stack overflow，所以我们需要改变一下选取pivot的方式*/
//随机选取pivot
int RandomHoarePartition(vector<int>& arr, int left, int right) {
	srand(time(0));//设置一个随机种子
	int pivotIndex = rand() % (right - left + 1)+left;//生成从left-(right-left+1)的随机数字
	//将随机种子选中的index交换到left
	swap(arr[left], arr[pivotIndex]);
	int pivot = arr[left];//将随机pivotIndex所对应的值赋给pivot
	int i = left + 1, j = right;
	while (true) {
		while (i <= right&&arr[i] < pivot) {//记住此时i不超过right就可以
			i++;
		}
		while (j > left && arr[j] > pivot) {//此时的j不能达到left也就是pivot所在的位置，不然有可能将pivot换走
			j--;
		}
		if (j <= i) {
			break;
		}
		swap(arr[i], arr[j]);//交换
		i++;
		j--;//这里记住i和j均需要向前走一格，不然可能会死循环
	}
	swap(arr[left], arr[j]);//将pivot移到合适的地方
	return j;
}

//使用median of three选取pivot

//找左右中三个数的中位数,并将其放在数组的最左侧
void findMedianOfThree(vector<int>&arr, int &left,int &right) {//不能返回局部对象和函数的指针或则应用原因见:https://blog.csdn.net/qq_33266987/article/details/53516977
	int mid = (left + right)/2;
	//我们将left ,mid ,right三个位置的中位数移到最左边
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

//medianOfThreeHoarePartition 找left mid right中的中位数作为pivot
int medianOfThreeHoarePartition(vector<int>&arr, int left, int right) {
	findMedianOfThree(arr, left, right);//将left mid right中的中位数移到最左侧并作为pivot
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
	swap(arr[left], arr[j]);//最后将pivot放置在合适的位置
	return j;//此时arr[j]已经排到了合适的位置
}



void QuickSort(vector<int>& arr, int left, int right) {
	if (left >= right) {
		return;
	}
	/*快排，先比较，再分*/
	//int s = HoarePartition(arr, left, right);
	 int s=RandomHoarePartition(arr,left,right);
	//int s = medianOfThreeHoarePartition(arr, left, right);
	/*用s所在的位置将原问题大小分为l-s-1,s+1-r两个子问题，此时s已经安置好了，所以显然我们此时无需安置*/
	QuickSort(arr,left,s-1);
	QuickSort(arr, s + 1, right);
}

vector<int> CreateRandom( int size) {//用来生成随机数的函数
	vector<int>randomArr;
	randomArr.resize(size);
	srand(time(0));//设置随机种子
	for (int i = 0; i < size; i++) {
		randomArr[i] = rand();
	}
	return randomArr;
}

void printArr(vector<int>&arr) {//用来打印数组
	for (int i : arr) {
		cout << i << "  ";
	}
	cout << endl;
}

int main() {
	//vector<int>arr= CreateRandom(1000);
	vector<int>arr = {5,3,2,1};
	

	clock_t t2 = clock();// 使用clock()构造clock_t对象(实际上是long类型的变量)
	QuickSort(arr, 0, arr.size() - 1);
	cout << "t2所用时间为" << (clock() - t2) * 1.0 / CLOCKS_PER_SEC * 1000 << "ms" << endl;
	printArr(arr);

}