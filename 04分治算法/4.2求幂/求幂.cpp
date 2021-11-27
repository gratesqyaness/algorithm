#include<iostream>
#include<vector>
using namespace std;
int result = 1;
int binaryPow(int &n, int &e) {//用一个引用
	if (e == 1) {
		return n;
	}
	if (e % 2 == 0) {//如果e为偶数
		e = e / 2;
		int temp=binaryPow(n, e);//注意，此处不能写作binaryPow(n,e)*binaryPow(n,e) 
								//根据主定理可知log2/log2=1>d=0。此时的算法复杂度仍然为n(log2/log2)次方
								//向我这么写,log1/log2 =d=0。此时算法复杂度为log2n
		return temp * temp;
	}
	else {//e为奇数
		e = (e - 1) / 2;
		int temp =  binaryPow(n, e);
		return n*temp * temp;
	}
}

int main() {
	int n = 3;
	int e = 5;
	cout<<binaryPow(n,e);
}