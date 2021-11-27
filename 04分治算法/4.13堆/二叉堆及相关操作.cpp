#include<iostream>
#include<vector>
using namespace std;
/*最大堆*/
class heap {
	/*用数组来存储*/
	vector<int>heapArr;
public:
	heap(vector<int>& arr);
	void increase(int i, int x);//增加index=i元素的值为x
	void PrintTree();//以树的形式输出数组
	void insert(int x);//插入新的元素
	void heapify(int index);//堆化，修正以index为根的的子树（除index以外其余的部分以及满足堆的properities)相当于做一个decrease
	void decrease(int index, int x);//减少index的值为x，进行heapify即可。
	int delete_max();//删除根节点并返回
	void init();//新建一个堆
	void heapSort();//堆排序
};

heap::heap(vector<int>&arr) {
	heapArr = arr;
	init();//将其构建为堆
}

void heap::increase(int i, int x) {//增加index=i元素的值为x
	heapArr[i] = x;//我们只用和其向上的父亲和祖先进行比较即可
	int indexOfFather=i;
	do {
		if (i == 0) {//到根节点了，该退出了
			break;
		}
		else if (i % 2 == 0) {
			indexOfFather = indexOfFather / 2 - 1;
		}
		else {
			indexOfFather = indexOfFather / 2;
		}
		if (heapArr[indexOfFather] < x) {
			swap(heapArr[indexOfFather], heapArr[i]);//如果其大于父亲结点，向上移动
			i = indexOfFather;
		}
		else {
			break;
		}
	} while (true);
}

void heap::insert(int x) {
	heapArr.push_back(x);//先将其放到末尾
	increase(heapArr.size() - 1, x);//再做一次increase即可
	
}

void heap::heapify(int index) {//大堆化以i为根节点，除i以外满足堆properties的堆
	//只需于自己的孩子相比较，如果小于：和较大的孩子进行交换。
	int indexLength = heapArr.size()-1;
	int indexOflChild;
	int indexOfRChild;
	int swapIndex;
	do {
		indexOflChild = 2 * index + 1;
		indexOfRChild = 2 * index + 2;
		if (indexOflChild > indexLength) {//左子结点已经越界啦，说明此时arr[index]一定是叶子结点，我们退出即可
			break;
		}
		else if (indexOfRChild > indexLength) {//不存在右节点,但我左边的数据仍然可能比arr[index]大
			swapIndex = indexOflChild;
		}
		else {
			swapIndex = heapArr[indexOflChild] > heapArr[indexOfRChild] ? indexOflChild : indexOfRChild;//决定谁发生交换
		}
		if (heapArr[swapIndex] > heapArr[index]) {
			swap(heapArr[swapIndex], heapArr[index]);
			index = swapIndex;
		}
		else {//否则，说明此时arr[index]已经移动到正确的位置了
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

void heap::init() {//构建堆
	for (int i = heapArr.size() / 2; i >= 0; i--) {
		heapify(i);
	}
}

int heap::delete_max() {
	int temp = heapArr[0];
	//1.先将根节点和堆尾元素进行交换，然后直接去除最后一个元素
	swap(heapArr[0], heapArr[heapArr.size() - 1]);
	heapArr.pop_back();
	//2.对根节点进行堆化即可
	heapify(0);
	return temp;
}

void heap::heapSort() {//堆排序，实际上是我在最大堆上做了delete_max操作，得出的删除序列，就是一个堆
	int length = heapArr.size();//将长度存起来，因为我在不断的删元素,heapAr.size()是变化的
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

