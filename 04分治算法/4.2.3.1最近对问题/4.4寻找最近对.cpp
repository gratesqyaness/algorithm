/*原理:https://blog.csdn.net/weixin_44176696/article/details/105821366
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

/*在包含n个点的集合中，找出距离最近的两个点*/
float distance(point a,point b) {
	return sqrt(pow(a.x - b.x, 2)+pow(a.y-b.y,2));
}
bool equalOfPoint(point a, point b) {//判断a，b是否为同一个点
	if (a.x == b.x && a.y == b.y)
		return true;
	else
		return false;
}
bool compX(point a, point b) {// 比大小函数 STL 库中 sort 函数有 3 个参数 (start,end,compare 函数名)
	return a.x < b.x;//按照x横轴大小进行排序
}
bool compY(point a, point b) {
	return a.y < b.y;//按照y纵轴大小进行排序
}


float nearestPair(int left, int right, vector<point>& node) {
	/*分：（我们假设是以横坐标为基准来存储的），我们input 以横轴为基准平均分成两个部分1-n/2 n/2+1-n*/
	if (left >= right) {//递归终点
		return INFINITY;//如果只有一个点了，那么距离为无穷啊
	}
	if (right - left == 1) {//如果只有两个点的话，我们就返回他们的距离
		return distance(node[left], node[right]);
	}
	/*治:递归的解决a=2个n/2规模的问题（分别求出左右两部分的最近点距离，记为d1和d2 记d=min(d1,d2)*/
	int mid = (left + right) / 2;
	float d1 = nearestPair(left, mid, node);
	float d2 = nearestPair(mid + 1, right, node);
	float d = min(d1, d2);//记录左右部分的最近距离
	float mind=d;//保存每次递归的全局最小距离
	/*合:最小点跨越终点的时候，我们很显然只需沿横轴在x=分割线+-d这个范围内考虑。
	  我们取左边的一点为P经过证明，右边的区域中最多存在6个点(设任意一点为P')能使得PP'<d*/
	  /*结论：对于左边矩形区域的每一点p，要想在右边区域找到一点p’使得 pp’距离<=d，这样的点p’必定存在于【以p的y坐标为中心，上下延展d形成的d*2d的子矩形中】*/

	  /*对左右的子区域的所有点按照y升序排序（左右分开排序，不是混合在一起），
	  在指针i升序遍历左边的所有点的时候，设置指针h在右边的点中向后查找，
	  找到第一个不矮于i点y坐标d高度的点h（即h和i点高度差小于d），从h往后找6个点即可*/
	/*将左右X=中线+-d的数组分别用两个temporary数组装起来*/
	vector<point>tempL, tempR;
	for(int i=mid;i>=left&&fabs(node[i].x- node[mid].x)<=d;i--){//
		tempL.push_back(node[i]);
	}
	for (int i = mid; i <= right && fabs(node[i].x - node[mid].x) <= d; i++) {
		tempR.push_back(node[i]);
	}
	/*按照y轴给这两个数组进行排序，这样的话，我的右侧指针h就不用往回跑，这样就能实现O(n)的复杂度，这里注意的话，排序的复杂度为nlogn*/
	sort(tempL.begin(), tempL.end(), compY);
	sort(tempR.begin(), tempR.end(), compY);//将left-right范围的的点分别按照X和Y进行排序
	int h = 0;//矩形右边的指针
	for (int i = 0; i < tempL.size(); i++) {
		//对于左侧矩形框框的每一个点，查找此时右侧矩形区域的6个点即可
		while (h < tempR.size() && d<tempL[i].y- tempR[h].y) {//临界点两点纵轴坐标要小于d,并且右侧的点要位于左侧下面
			h++;//找到临界点h，沿h向上再找6个点即可
		}
		h = min(h,(int)tempR.size());//看看哪个小，面对越界了
		for (int j = h; j < min(h + 6, (int)tempR.size()); j++) {
			if (!equalOfPoint(tempL[i], tempR[j]) ){//如果这两点不是同一个点的话，我们就计算他们的距离
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

//构建一个函数来生成随机数
vector<point>createRandom(int size) {
	vector<point>randomArr;
	randomArr.resize(size);
	srand(time(0));//设置随机种子，防止每次生成的随机数相同
	for (int i = 0; i < size; i++) {
			randomArr[i].x=rand();
	}
	for (int i = 0; i < size; i++) {
		randomArr[i].y = rand();
	}
	return randomArr;
}
int main() {
	/*我们需要传递两个数组，一个是根据x轴进行排序，一个是根据y轴进行排序*/
	vector<point>data =createRandom(1000);
	//vector<point>data = { {1,1},{1.5,1.5},{2,2},{2.8,2},{1.1,1.1}, {3,3} };
	sort(data.begin(), data.end(), compX);//先要对给出的点坐标排个序
	cout << nearestPair(0, data.size() - 1, data) << endl;;
	cout << Brutal(data) << endl;
	

}

