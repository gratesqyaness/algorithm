#include<iostream>
#include<vector>
using namespace std;
//bool flag = false;
/*������һ���Ƚ���ֵ����⣬Ϊʲô�ҵ��жϵ��ڲ��ܷ������һ��else*/
int binarySearch(vector<int>& benchArr,int left,int right, int target) {
	//���ֲ��ң��鵽���˷����±꣬û���ҵ�����-1
	//if (left > right)//�ݹ��յ����ֹ��֮ǰ
	//	return -1;
	int mid = (left + right) / 2;
	if (benchArr[mid] == target) {
		flag = true;
		return mid;//���ʱ�����Ƿ������±�
	}
	else if (benchArr[mid] < target) {//�м��ֵС��target,��Ӧ��ȥ�ұ�ȥ����
		binarySearch(benchArr, mid + 1, right, target);
	}
	else {//�м�ֵ����target����Ӧ��ȥ���ȥ����
		binarySearch(benchArr, left, mid - 1, target);
	}
	/*if (!flag)//������ôд����Ϊ��ʱ�ݹ鲢û�н���
		return -1;*/
}
int main() {
	vector<int>beachArr = { 1,3,5,7,9,10,11,22,33,45 };
	int target;
	cin >> target;
	cout << "���ղ��ҵ����±���" << binarySearch(beachArr, 0,beachArr.size()-1,target)<<endl;
}