#include<iostream>
#include<math.h>
#include<vector>
#include<algorithm>
using namespace std;

typedef struct p
{
	int x, y;
	p() {}
	p(int X, int Y) :x(X), y(Y) {}
}p;

/*
������С��������ֹĬ��min��int�βνض�
*/
double lfmin(double a, double b)
{
	return (a < b) ? (a) : (b);
}

/*
�ȽϺ����������ã�x����x��ͬ��y����
param p1 : ��һ����
param p2 : �ڶ�����
return   : p1 ǰ�� p2 ?
*/
bool cmpx(const p& p1, const p& p2)
{
	if (p1.x == p2.x) return p1.y < p2.y;
	return p1.x < p2.x;
}

/*
�ȽϺ����������ã���y���򣬹鲢��
param p1 : ��һ����
param p2 : �ڶ�����
return   : p1 ǰ�� p2 ?
*/
bool cmpy(const p& p1, const p& p2)
{
	return p1.y < p2.y;
}

/*
�������ŷ�Ͼ���
param p1 : ��һ����
param p2 : �ڶ�����
return   : ���룬������
*/
double dis(const p& p1, const p& p2)
{
	return sqrt((double)(p1.x - p2.x) * (p1.x - p2.x) + (double)(p1.y - p2.y) * (p1.y - p2.y));
}

/*
������ˮƽ����
param p1 : ��һ����
param p2 : �ڶ�����
return   : ˮƽ���룬������
*/
double disX(const p& p1, const p& p2)
{
	double ans = (double)p1.x - (double)p2.x;
	if (ans < 0) return ans * -1;
	return ans;
}

/*
�������������
param points : �������
return       : �����Ծ���
*/
//double cp(vector<p>& points)
//{
//	double ans = (double)INT_MAX;
//	for (int i = 0; i < points.size(); i++)
//		for (int j = i + 1; j < points.size(); j++)
//			ans = lfmin(ans, dis(points[i], points[j]));
//	return ans;
//}

/*
������������ԣ����Ӷ�O(nlog(n)log(n))
param points : �������
param l      : ��������˵�
param r      : �������Ҷ˵�
return       : �����Ծ���
explain      : ����[l, r]����ұ�
*/
bool eqfunc(p a,p b ) {
	if (a.x == b.x && a.y == b.y) {
		return true;
	}
	else {
		return false;
	}
}
double cp(vector<p>& points, int l, int r)
{
	if (l >= r) return (double)INT_MAX;
	if (l + 1 == r) return dis(points[l], points[r]);
	int mid = (l + r) / 2, le = mid, ri = mid, h = 0;
	double d = lfmin(cp(points, l, mid), cp(points, mid + 1, r)), ans=d;
	vector<p> ll, rr;
	while (le >= l && disX(points[mid], points[le]) <= d) ll.push_back(points[le]), le--;
	while (ri <= r && disX(points[mid], points[ri]) <= d) rr.push_back(points[ri]), ri++;
	sort(ll.begin(), ll.end(), cmpy), sort(rr.begin(), rr.end(), cmpy);
	for (int i = 0; i < ll.size(); i++)
	{
		while (h < rr.size() && rr[h].y + d < ll[i].y) h++; h = min((int)rr.size(), h);
		for (int j = h; j < min((int)rr.size(), h + 6); j++)
			if (!eqfunc(ll[i], rr[j])) ans = lfmin(ans, dis(ll[i], rr[j]));
	}
	return ans;
}

/*
����+�鲢��������ԣ����Ӷ�O(nlog(n))
param points : �������
param l      : ��������˵�
param r      : �������Ҷ˵�
return       : �����Ծ���
explain      : ����[l, r]����ұ�
*/
double cpm(vector<p>& points, int l, int r)
{
	if (l >= r) return (double)INT_MAX;
	if (l + 1 == r)
	{
		if (cmpy(points[r], points[l])) swap(points[l], points[r]);
		return dis(points[l], points[r]);
	}
	int mid = (l + r) / 2, le = mid, ri = mid, h = 0;
	p midp = points[mid];
	double d = lfmin(cpm(points, l, mid), cpm(points, mid + 1, r)), ans = d;
	inplace_merge(points.begin() + l, points.begin() + mid + 1, points.begin() + r + 1, cmpy);
	vector<p> ll, rr;
	for (int i = l; i <= r; i++)
	{
		if (midp.x >= points[i].x && disX(midp, points[i]) <= d) ll.push_back(points[i]);
		if (midp.x <= points[i].x && disX(midp, points[i]) <= d) rr.push_back(points[i]);
	}
	for (int i = 0; i < ll.size(); i++)
	{
		while (h < rr.size() && rr[h].y + d < ll[i].y) h++; h = min((int)rr.size(), h);
		for (int j = h; j < min((int)rr.size(), h + 6); j++)
			if (!eqfunc(ll[i], rr[j])) ans = lfmin(ans, dis(ll[i], rr[j]));
	}
	return lfmin(ans, d);
}

float Brutal(vector<p>& node) {
	double mind = INFINITY;
	for (int i = 0; i < node.size() - 1; i++) {
		for (int j = i + 1; j < node.size(); j++) {
			mind = min(mind, dis(node[i], node[j]));
		}
	}
	return mind;
}

//����һ�����������������
vector<p>createRandom(int size) {
	vector<p>randomArr;
	randomArr.resize(size);
	srand(time(0));//����������ӣ���ֹÿ�����ɵ��������ͬ
	for (int i = 0; i < size; i++) {
		randomArr[i].x = rand();
	}
	for (int i = 0; i < size; i++) {
		randomArr[i].y = rand();
	}
	return randomArr;
}

int main() {
	vector<p>data =createRandom(1000);
	sort(data.begin(), data.end(), cmpx);//����ҪX�ᱣ֤������
	cout << cp(data, 0, data.size() - 1) << endl;
	cout << Brutal(data);
}
