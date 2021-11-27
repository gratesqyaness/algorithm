#include<iostream>
#include<vector>
using namespace std;
void merger(vector<int>& arr, int left, int mid, int right);
void mergerSort(vector<int>&arr,int left,int right) {
	/*归并排序,对于一个需要排序的数组A[0,n-1],归并排序把它一分为二，A[0,(n/2-1)]和A[n/2,n-1],并对每个子数组递归排序*/
	
	if (left >= right) { return; }//终止条件
	   int mid = (left+right) / 2;
		mergerSort(arr, left, mid);
		mergerSort(arr, mid + 1, right);
		//这里要记住合并
		merger(arr, left,mid,right);//合并啦
}
void merger(vector<int>&arr,int left,int mid,int right) {//将B的left和right部分进行排序
	//将两个有序数组合并成一个有序数组
	vector<int>temp;//我们使用一个length=right-left+1的数组，这样能使得合并比较的次数为n。
	 int i = left, j = mid+1;//i用来看数组arr[left:mid]是否比较完毕，J用来看数组arr[mid+1:right]是否比较完毕
	 while (i <= mid && j <=right) {//任意一个数组比较完毕我们都应该退出循环
		 if (arr[i] < arr[j]) {//将较小的插到前面去
			 temp.push_back(arr[i]);
			 i++;
		 }
		 else
		 {
			 temp.push_back(arr[j]);
			 j++;
		 }
	 }
	 if (i <=mid) {//如果哪边先结束了，那么另外一半剩余的元素肯定是最大的，直接插到数组末尾即可
		 while (i <= mid) {
			 temp.push_back(arr[i++]);
		 }
	 }
	 else {
		 while (j <= right) {
			 temp.push_back(arr[j++]);
		 }
	 }
		/*我们再将排序好的temp返回到arr,这样不让排好序的信息丢失*/
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