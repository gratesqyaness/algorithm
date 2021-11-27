#include<iostream>
#include<vector>
#include<algorithm>
/*from https://www.cnblogs.com/bigsai/p/13396391.html
   https://zh.wikipedia.org/wiki/%E6%A1%B6%E6%8E%92%E5%BA%8F*/
using namespace std;

//void BucketSort(vector<int>&arr) {
//	//1.设置一个定量的数组当作空桶子。我们这里拍小数据，设定为桶大小为5
//	vector<vector<int>>bucket(5);
//
//	//2.寻访序列，并且把项目一个一个放到对应的桶子去。
//	for (int i = 0; i < arr.size(); i++) {
//		int index = arr[i] / 10;//max(arr[i])=46，我们将全部数据/10恰好能与桶号上限对应
//		bucket[index].push_back(arr[i]);//将arr[i]放到对应的桶中
//	}
//	//3.对每个不是空的桶子进行排序。
//	for (int i = 0; i < bucket.size(); i++) {//对桶内数据进行快排
//		if (bucket[i].size() != 0) {
//			sort(bucket[i].begin(), bucket[i].end());
//		}
//	}
//	//4.从不是空的桶子里把项目再放回原来的序列中。
//	for (int i = 0,j=0; i < bucket.size(); i++) {
//		int NumOfRow = bucket[i].size();//用来指示改行所剩的元素个数
//		while (NumOfRow>0) {
//			arr[j++] = bucket[i][bucket[i].size() - NumOfRow];
//			NumOfRow--;
//		}
//	}
//}


/*桶排序时一个桶装多少元素(gap)，桶的个数该怎么确定 https://blog.csdn.net/wusecaiyun/article/details/48048901
  这非常重要，不然的话很有可能比快排还差，因为要重新新开很多临时数组*/
void BucketSort(vector<int>& arr) {
	//假如对数组nums进行桶排序，nums的长度为L，最小元素为A，最大元素为B。则gap为(B - A) / L + 1
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
	//桶的个数为
	int numOfBucket = (maxOfarr - minOfarr) / gap + 1;
	
	//1.设置一个定量的数组当作空桶子。我们这里拍小数据，设定为桶大小为5
	vector<vector<int>>bucket(numOfBucket);

	//2.寻访序列，并且把项目一个一个放到对应的桶子去。
	for (int i = 0; i < arr.size(); i++) {
		int index = (arr[i]-minOfarr) / (gap);//max(arr[i])=46，我们将全部数据/10恰好能与桶号上限对应
		bucket[index].push_back(arr[i]);//将arr[i]放到对应的桶中
	}
	//3.对每个不是空的桶子进行排序。
	for (int i = 0; i < bucket.size(); i++) {//对桶内数据进行快排
		if (bucket[i].size() != 0) {
			sort(bucket[i].begin(), bucket[i].end());
		}
	}
	
	//4.从不是空的桶子里把项目再放回原来的序列中。
	for (int i = 0, j = 0; i < bucket.size(); i++) {
		int NumOfRow = bucket[i].size();//用来指示改行所剩的元素个数
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