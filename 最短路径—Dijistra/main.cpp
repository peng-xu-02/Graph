//单源节点到其他节点的寻找最短路径算法-Dijistra算法
#include<iostream>
#include<stdlib.h>
using namespace std;
typedef char Elemtype;
#define max 10
#define maxsize 100

typedef struct sidenode {        //边节点；
	int weight; //权值
	int head, tail;   //边首和边尾下标
	struct sidenode* indegreenext, * outdegreenext;  //下一条入度边，下一条出度边
}sidenode;

typedef struct headnode {       //头节点；
	Elemtype data; 
	sidenode* indegreefirst, * outdegreefirst;


}headnode;

typedef struct Orthogonallist {      //十字链表；
	headnode* vertics;
	int vernum, arcnum;

}Orthogonallist;


void Initlst(Orthogonallist& L,int m) {    //初始化十字链表；
	L.vertics = new headnode[m];
	L.vernum = m;
	for (int i = 0; i < m; i++) {
		L.vertics[i].data = 0;
		L.vertics[i].indegreefirst= NULL;
		L.vertics[i].outdegreefirst = NULL;
	}

}

void Select(Orthogonallist& L, Elemtype data1, Elemtype data2, int& head, int& tail) {
	for (int i = 0; i < L.vernum; i++) {
		if (data1 == L.vertics[i].data)  head = i;
		if (data2 == L.vertics[i].data)  tail = i;
	}
}
void creatlist(Orthogonallist& L, int m) {     //建立十字链表；
	L.arcnum = m;
	for (int i = 0; i < L.vernum; i++) {
		cout << "请输入第" << i + 1 << "个顶点的名称：" << endl;
		cin >> L.vertics[i].data;
	}
	for (int i = 0; i < m; i++) {
		cout << "请输入第" << i + 1 << "条边的边首、边尾和边的权值：" << endl;
		int head, tail;
		int weight;
		Elemtype data1, data2;
		cin >> data1 >> data2 >> weight;
		Select(L, data1, data2, head, tail);
		sidenode* p = new sidenode;
		p->head = head;
		p->tail = tail;
		p->weight = weight;
		p->indegreenext = L.vertics[tail].indegreefirst;      //头插法，找到边的边首和边尾，分别插到边首节点的出度边和边尾节点的入度边
		p->outdegreenext = L.vertics[head].outdegreefirst;
		L.vertics[head].outdegreefirst = p;
		L.vertics[tail].indegreefirst = p;

	}
}

void display(Orthogonallist& L) {  //打印十字链表
	for (int i = 0; i < L.vernum; i++) {
		cout << "下标：" << i << "顶点：" << L.vertics[i].data<<endl;
		cout << "以" << L.vertics[i].data << "为边首的边：";
		sidenode* p = L.vertics[i].outdegreefirst;
		while (p) {
			cout << "("<<p->head<<"->" << p->tail<<")";
			p = p->outdegreenext;
		}
		cout << "以" << L.vertics[i].data << "为边尾的边：";
		sidenode* q = L.vertics[i].indegreefirst;
		while (q) {
			cout <<"("<< q->head<<"->"<<q->tail<<")";
			q = q->indegreenext;
		}
		cout << endl;
	}
	
}

int dv[max];      //用来存储到达某一顶点的最短路径长度；
int pre[max];    //用来存储到达第i个顶点的先序节点的下标；
Elemtype arry[max][max];  //存储到达第i个节点的最短路径
int length[max];          //存储第i个节点的最短路径的元素个数；

void Dijistra(Orthogonallist& L,Elemtype e) {
	memset(dv, maxsize, sizeof(dv));
	memset(pre, -1, sizeof(pre));    //初始化都为-1,表示没有先序节点；
	int head = 0;
	for (int i = 0; i < L.vernum; i++) {
		if (e == L.vertics[i].data)  head = i;
	}
	dv[head] = 0;
	int cout1[max]; //记录已经找到最短路径的顶点；
	memset(cout1, -1, sizeof(cout1));
	int length = 0;
	cout1[length] = head; //记录已经访问过的顶点
	length++;
	sidenode* p = L.vertics[head].outdegreefirst; //从出度表开始遍历
	while (p) {
		dv[p->tail] = p->weight; //记录从开始顶点到其他顶点的距离
		pre[p->tail] = p->head;   //修改其先序节点；
		p = p->outdegreenext; //指向下一个出度边
	}
	while (length < L.vernum) { //当访问过的顶点数小于总顶点数时
		int min = maxsize; //初始化最小距离为无穷大
		int k = -1; //初始化最小距离的顶点下标为-1
		for (int i = 0; i < L.vernum; i++) { //遍历所有顶点
			if (dv[i] < min && cout1[i] == -1) { //如果当前顶点的距离小于最小距离，并且没有被访问过
				min = dv[i]; //更新最小距离
				k = i; //更新最小距离的顶点下标
			}
		}
		if (k == -1) break; //如果没有找到合适的顶点，说明图不连通，退出循环
		cout1[k] = 1; //标记当前顶点已经访问过
		cout1[length] = k; //记录当前顶点到访问过的顶点数组中
		length++; //增加访问过的顶点数
		p = L.vertics[k].outdegreefirst; //从当前顶点的出度表开始遍历
		while (p) { //当出度边存在时
			if (dv[p->tail] > dv[k] + p->weight) { //如果从当前顶点到其他顶点的距离大于从开始顶点经过当前顶点到其他顶点的距离
				dv[p->tail] = dv[k] + p->weight; //更新最短距离
				pre[p->tail] = p->head;          //修改其先序节点为k;
			}
			p = p->outdegreenext; //指向下一个出度边
		}
	}

}

void displayshort(Orthogonallist& L,Elemtype e) {
	memset(arry, -1, sizeof(arry));
	memset(length, 0, sizeof(length));
	for (int i = 0; i < L.vernum; i++) {
		int k = pre[i]; //找到到达第i个节点的先序节点下标；
		while (k!=-1) {   //先序节点不为空
			arry[i][length[i]] = L.vertics[k].data;    //先序节点加入最短路径中
			length[i]++;
			k = pre[k];    //先序节点修改为先序节点的先序节点；
		}
	}
	for (int i = 0; i < L.vernum; i++) {
		cout << "从" << e << "到" << L.vertics[i].data << "的最短路径为：";
		for (int j = length[i] - 1; j >= 0; j--) {
			cout << "->" << arry[i][j];
		}
		cout << "->" << L.vertics[i].data;
		cout << " 开销为：" << dv[i];
		cout << endl;
	}
}

int main() {
	Orthogonallist L;
	Initlst(L, 5);
	creatlist(L, 7);
	display(L);
	Elemtype e;
	cin >> e;
	Dijistra(L, e);
	displayshort(L, e);

	return 0;
}