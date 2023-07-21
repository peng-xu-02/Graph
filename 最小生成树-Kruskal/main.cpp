//Kruskal算法，令最小生成树初始状态只有n个顶点而无边，然后再去找各个顶点之间最小的权值的边加入到最小生成树中，如果找到的边会导致最小生成树形成回路，就寻找其他的边。
//顶点固定，找最小的边，因此适用于稀疏图；
#include<iostream>
using namespace std;
#include<stack>
typedef char Elemtype;
#define max 20

typedef struct sidenode {  //边节点；
	int weight;            //边权值；
	int head1, head2;       //边的第一个顶点和第二个顶点下标；
	struct sidenode* head1next, * head2next;    //边的第一个顶点的下一条边；边的第二个顶点的下一条边；
	bool visited;          //判断是否边被访问过；

}sidenode;

typedef struct headnode { //头节点；
	Elemtype headdata;
	sidenode* firstside;
}headnode;

typedef struct multilist {   //邻接多重表；
	headnode* vertics;   //顶点表；
	int vernum;
	int arcnum;
}multilist;

typedef struct Kruskaltree { //存放最小生成树
	int head1, head2;
	int length;
}Kruskaltree;

void Select(multilist& L, Elemtype headdata1, Elemtype headdata2, int& head1, int& head2) {
	for (int i = 0; i < L.vernum; i++) {
		if (headdata1 == L.vertics[i].headdata)  head1 = i;
		if (headdata2 == L.vertics[i].headdata)  head2 = i;
	}
}

void creatmultilist(multilist &L,int m,int n) {   //创建多重表；
	if (m < 1 || n < 0) return;
	L.vertics = new headnode[m];
	L.vernum = m;
	L.arcnum = n;
	for (int i = 0; i < m; i++) {
		L.vertics[i].headdata = '0';
		L.vertics[i].firstside = NULL;
	}
	for (int i = 0; i < m; i++) {
		cout << "请输入第" << i + 1 << "个顶点的名称：" << endl;
		cin >> L.vertics[i].headdata;
	}
	for (int i = 0; i < n; i++) {
		cout << "请输入第" << i + 1 << "条边的两个顶点和权值：" << endl;
		Elemtype headdata1, headdata2;
		int weight;
		int head1, head2;
		cin >> headdata1 >> headdata2 >> weight;
		Select(L, headdata1, headdata2, head1, head2);
		sidenode* p = new sidenode;
		p->weight = weight;      
		p->head1 = head1;
		p->head2 = head2;
		p->visited = 0;    //没有访问过；
		p->head1next = L.vertics[head1].firstside;     //头插法；
		p->head2next = L.vertics[head2].firstside;
		L.vertics[head1].firstside = p;
		L.vertics[head2].firstside = p;
	}

}
void display(multilist &L) {    //打印多重表；
	for (int i = 0; i < L.vernum; i++) {
		cout << "下标：" << i << "顶点：" << L.vertics[i].headdata;
		sidenode* p = L.vertics[i].firstside;
		while (p) {
			if (i == p->head1) {
				cout << "->" << p->head2;
				p = p->head1next;

			}
			else {
				cout << "->" << p->head1;
				p = p->head2next;
			}
			
		}
		cout << endl;
	}

}

bool compare(int head1,int head2,Kruskaltree *kru) {  //判断新加入的这条边会不会成环；
	stack<int> s;
	bool visited[20] = { 0 };
	s.push(head1);      //将要判断的边的一个顶点入栈；
	visited[head1] = 1; 
	while (!(s.empty())) {  //栈不为空；
		int cur = s.top();
		s.pop();
		if (cur == head2) return 1; //如果弹出的栈顶元素是要判断的边的另一个顶点，那么就会成环；

			for (int i = 0; i < kru->length; i++) {   //否则遍历最小生成树的所有边的顶点    
				if (cur == kru[i].head1 && visited[kru[i].head2] == 0) {     //如果栈顶元素是最小生成树的其中一条边的一个顶点并且另一个顶点没有访问
					s.push(kru[i].head2);             //就把另一个顶点入栈
					visited[kru[i].head2] = 1;
				}
				if (cur == kru[i].head2 && visited[kru[i].head1] == 0) {
					s.push(kru[i].head1);
					visited[kru[i].head1] = 1;
				}
			}
		}

	return 0;

}

void Kruskal(multilist &L,Kruskaltree *kru){ //克鲁斯卡尔算法
	kru->length = 0;
	while (kru->length < L.vernum-1) {          //n个顶点，那么最小生成树就有n-1条边，下标从零开始；
		int min = max;
		int head1 = -1;
		int head2 = -1;
		for (int i = 0; i < L.vernum; i++) {        //遍历所有顶点的边
			sidenode* p = L.vertics[i].firstside;
			while (p) {
				if (p->weight < min && compare(p->head1, p->head2, kru) == 0 && p->visited == 0) {   //找到所有顶点的权值最小的边,并且这条边是没有被加入最小生成树的也就是没有被访问；
					min = p->weight;  //修改最下边的权值和两个顶点；
					head1 = p->head1;
					head2 = p->head2;

				}
				if (i == p->head1) {
					p = p->head1next;
				}
				else {
					p = p->head2next;
				}

			}
		}
		for (int i = 0; i < L.vernum; i++) {        
			sidenode* q = L.vertics[i].firstside;
			while (q) {
				if (q->head1 == head1 && q->head2 == head2) q->visited = 1;    //将找到的最小的边修改为已经访问过；
				if (i == q->head1) {
					q= q->head1next;
				}
				else {
					q = q->head2next;
				}

			}
		}

		kru[kru->length].head1 = head1;       //把找到的所有顶点中权值最小的边的两个顶点的序号加入；也就是把这条边加入最小生成树中；
		kru[kru->length].head2 = head2;
		kru->length++;



	}

}

void displayKruskal(multilist &L,Kruskaltree *kru) {   //打印最小生成树，以数对的形式；
	for (int i = 0; i < kru->length ; i++) {
		cout << "(" << L.vertics[kru[i].head1].headdata << "," << L.vertics[kru[i].head2].headdata<< ")" << endl;
	}

}
int main() {
	multilist L;
	creatmultilist(L, 4, 5);
	display(L);
	Kruskaltree kru[max] = {0};
	Kruskal(L, kru);
	cout << "最小生成树：" << endl;
	displayKruskal(L, kru);



	return 0;
}

