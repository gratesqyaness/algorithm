/*ԭ��:https://blog.csdn.net/weixin_44176696/article/details/105821366
* https://nkwangpeng.github.io/2020/04/14/Closet-Point/#%E4%BB%A3%E7%A0%81%E6%B8%85%E5%8D%95
  */
#include<iostream>
#include<vector>
#include<math.h>
#include<algorithm>
using namespace std;
struct point {
	float x;
	float y;
};

/*�ڰ���n����ļ����У��ҳ����������������*/
float distance(point a,point b) {
	return sqrt(pow(a.x - b.x, 2)+pow(a.y-b.y,2));
}
bool equalOfPoint(point a, point b) {//�ж�a��b�Ƿ�Ϊͬһ����
	if (a.x == b.x && a.y == b.y)
		return true;
	else
		return false;
}
bool compX(point a, point b) {// �ȴ�С���� STL ���� sort ������ 3 ������ (start,end,compare ������)
	return a.x < b.x;//����x�����С��������
}
bool compY(point a, point b) {
	return a.y < b.y;//����y�����С��������
}


float nearestPair(int left, int right, vector<point>& node) {
	/*�֣������Ǽ������Ժ�����Ϊ��׼���洢�ģ�������input �Ժ���Ϊ��׼ƽ���ֳ���������1-n/2 n/2+1-n*/
	if (left >= right) {//�ݹ��յ�
		return INFINITY;//���ֻ��һ�����ˣ���ô����Ϊ���
	}
	if (right - left == 1) {//���ֻ��������Ļ������Ǿͷ������ǵľ���
		return distance(node[left], node[right]);
	}
	/*��:�ݹ�Ľ��a=2��n/2��ģ�����⣨�ֱ�������������ֵ��������룬��Ϊd1��d2 ��d=min(d1,d2)*/
	int mid = (left + right) / 2;
	float d1 = nearestPair(left, mid, node);
	float d2 = nearestPair(mid + 1, right, node);
	float d = min(d1, d2);//��¼���Ҳ��ֵ��������
	float mind=d;//����ÿ�εݹ��ȫ����С����
	/*��:��С���Խ�յ��ʱ�����Ǻ���Ȼֻ���غ�����x=�ָ���+-d�����Χ�ڿ��ǡ�
	  ����ȡ��ߵ�һ��ΪP����֤�����ұߵ�������������6����(������һ��ΪP')��ʹ��PP'<d*/
	  /*���ۣ�������߾��������ÿһ��p��Ҫ�����ұ������ҵ�һ��p��ʹ�� pp������<=d�������ĵ�p���ض������ڡ���p��y����Ϊ���ģ�������չd�γɵ�d*2d���Ӿ����С�*/

	  /*�����ҵ�����������е㰴��y�����������ҷֿ����򣬲��ǻ����һ�𣩣�
	  ��ָ��i���������ߵ����е��ʱ������ָ��h���ұߵĵ��������ң�
	  �ҵ���һ��������i��y����d�߶ȵĵ�h����h��i��߶Ȳ�С��d������h������6���㼴��*/
	/*������X=����+-d������ֱ�������temporary����װ����*/
	vector<point>tempL, tempR;
	for(int i=mid;i>=left&&fabs(node[i].x- node[mid].x)<=d;i--){//
		tempL.push_back(node[i]);
	}
	for (int i = mid; i <= right && fabs(node[i].x - node[mid].x) <= d; i++) {
		tempR.push_back(node[i]);
	}
	/*����y�������������������������Ļ����ҵ��Ҳ�ָ��h�Ͳ��������ܣ���������ʵ��O(n)�ĸ��Ӷȣ�����ע��Ļ�������ĸ��Ӷ�Ϊnlogn*/
	sort(tempL.begin(), tempL.end(), compY);
	sort(tempR.begin(), tempR.end(), compY);//��left-right��Χ�ĵĵ�ֱ���X��Y��������
	int h = 0;//�����ұߵ�ָ��
	for (int i = 0; i < tempL.size(); i++) {
		//���������ο���ÿһ���㣬���Ҵ�ʱ�Ҳ���������6���㼴��
		while (h < tempR.size() && d<tempL[i].y- tempR[h].y) {//�ٽ��������������ҪС��d,�����Ҳ�ĵ�Ҫλ���������
			h++;//�ҵ��ٽ��h����h��������6���㼴��
		}
		h = min(h,(int)tempR.size());//�����ĸ�С�����Խ����
		for (int j = h; j < min(h + 6, (int)tempR.size()); j++) {
			if (!equalOfPoint(tempL[i], tempR[j]) ){//��������㲻��ͬһ����Ļ������Ǿͼ������ǵľ���
				mind = min(mind, distance(tempL[i], tempR[j]));
			}
		}
	}
	return mind;
}


float Brutal(vector<point>& node) {
	float mind = INFINITY;
	for (int i = 0; i < node.size()-1; i++) {
		for (int j = i + 1; j < node.size(); j++) {
			mind = min(mind, distance(node[i], node[j]));
		}
	}
	return mind;
}

//����һ�����������������
vector<point>createRandom(int size) {
	vector<point>randomArr;
	randomArr.resize(size);
	srand(time(0));//����������ӣ���ֹÿ�����ɵ��������ͬ
	for (int i = 0; i < size; i++) {
			randomArr[i].x=rand();
	}
	for (int i = 0; i < size; i++) {
		randomArr[i].y = rand();
	}
	return randomArr;
}
int main() {
	/*������Ҫ�����������飬һ���Ǹ���x���������һ���Ǹ���y���������*/
	vector<point>data =createRandom(1000);
	//vector<point>data = { {1,1},{1.5,1.5},{2,2},{2.8,2},{1.1,1.1}, {3,3} };
	sort(data.begin(), data.end(), compX);//��Ҫ�Ը����ĵ������Ÿ���
	cout << nearestPair(0, data.size() - 1, data) << endl;;
	cout << Brutal(data) << endl;
	

}

