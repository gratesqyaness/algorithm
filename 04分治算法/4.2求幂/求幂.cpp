#include<iostream>
#include<vector>
using namespace std;
int result = 1;
int binaryPow(int &n, int &e) {//��һ������
	if (e == 1) {
		return n;
	}
	if (e % 2 == 0) {//���eΪż��
		e = e / 2;
		int temp=binaryPow(n, e);//ע�⣬�˴�����д��binaryPow(n,e)*binaryPow(n,e) 
								//�����������֪log2/log2=1>d=0����ʱ���㷨���Ӷ���ȻΪn(log2/log2)�η�
								//������ôд,log1/log2 =d=0����ʱ�㷨���Ӷ�Ϊlog2n
		return temp * temp;
	}
	else {//eΪ����
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