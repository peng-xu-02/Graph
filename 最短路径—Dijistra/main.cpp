//单源节点到其他节点的寻找最短路径算法-Dijistra算法
#include<iostream>
#include<stdlib.h>
using namespace std;
typedef char Elemtype;
#define max 10
#define maxsize 100

typedef struct sidenode {
	int weight;
	int head, tail;
	struct sidenode* indegreenext, * outdegreenext;
}sidenode;

typedef struct headnode {
	Elemtype data;
	sidenode* indegreefirst, * outdegreefirst;


}headnode;

typedef struct Orthogonallist {
	headnode* vertics;
	int vernum, arcnum;

}Orthogonallist;

typedef struct Dijistra {
	int arr[max][max] = {0};
	int length[max] = {0};

}Dijistraarry;

void Initlst(Orthogonallist& L,int m) {
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
void creatlist(Orthogonallist& L, int m) {
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
		p->indegreenext = L.vertics[tail].indegreefirst;
		p->outdegreenext = L.vertics[head].outdegreefirst;
		L.vertics[head].outdegreefirst = p;
		L.vertics[tail].indegreefirst = p;

	}
}

void display(Orthogonallist& L) {
	for (int i = 0; i < L.vernum; i++) {
		cout << "下标：" << i << "顶点：" << L.vertics[i].data<<endl;
		cout << "以" << L.vertics[i].data << "为边首的边：";
		sidenode* p = L.vertics[i].outdegreefirst;
		while (p) {
			cout << "->" << p->tail;
			p = p->outdegreenext;
		}
		cout << "以" << L.vertics[i].data << "为边尾的边：";
		sidenode* q = L.vertics[i].indegreefirst;
		while (q) {
			cout << "->" << q->head;
			q = q->indegreenext;
		}
		cout << endl;
	}
	
}

int dv[max];


void Dijistra(Orthogonallist& L) {
	memset(dv, maxsize, sizeof(dv));
	cout << "请输入开始顶点：" << endl;
	Elemtype e;
	cin >> e;
	int head = 0;
	for (int i = 0; i < L.vernum; i++) {
		if (e == L.vertics[i].data)  head = i;
	}
	int cout1[max];
	memset(cout1, -1, sizeof(cout1));
	int length = 0;
	cout1[length] = head; //记录已经访问过的顶点
	length++;
	sidenode* p = L.vertics[head].outdegreefirst; //从出度表开始遍历
	while (p) {
		dv[p->tail] = p->weight; //记录从开始顶点到其他顶点的距离
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
			}
			p = p->outdegreenext; //指向下一个出度边
		}
	}
	for (int i = 1; i < L.vernum; i++) { //输出结果
		cout << "从" << e << "到" << L.vertics[i].data << "的最短距离为：" << dv[i] << endl;
	}

}

int main() {
	Orthogonallist L;
	Initlst(L, 4);
	creatlist(L, 3);
	display(L);
	Dijistra(L);

	return 0;
}