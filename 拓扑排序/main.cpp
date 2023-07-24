//拓扑排序：应用于有向无环图。AOV网：一个有向图表示一个工程，其中顶点表示活动，边或者弧表示活动之间的先后制约关系，这种网称之为AOV网。
#include<iostream>
using namespace std;
typedef char Elemtype;
#define max 20

typedef struct sidenode {      //边节点；
	int weight;
	int headadjex, tailadjex;
	struct sidenode* indegreenext, * outdegreenext;
}sidenode;

typedef struct headnode {     //头节点；
	Elemtype data;
	sidenode* indegreefirst, * outdegreefirst;
	bool visited;
}headnode;

typedef struct Orthoanilist {      //十字链表；
	headnode* vertics;
	int vernum, arcnum;
}Orthoanilist;

Elemtype list[max];    //存储拓扑序列的数组；
int length = 0;     //拓扑序列的长度；

void Select(Orthoanilist& L, Elemtype data1, Elemtype data2, int& head, int& tail) {
	for (int i = 0; i < L.vernum; i++) {
		if (data1 == L.vertics[i].data)  head = i;
		if (data2 == L.vertics[i].data)  tail = i;
	}
}

void creatlist(Orthoanilist &L,int m,int n){    //建立十字链表；
	if (m < 1 || n < 0) return;
	L.vertics = new headnode[m];
	L.vernum = m;
	L.arcnum = n;
	for (int i = 0; i < m; i++) {
		cout << "请输入第" << i + 1 << "个顶点的数据：" << endl;
		cin >> L.vertics[i].data;
		L.vertics[i].visited = false;
		L.vertics[i].indegreefirst = NULL;
		L.vertics[i].outdegreefirst = NULL;
	}
	for (int i = 0; i < n; i++) {
		cout << "请输入第" << i + 1 << "条边的边首，边尾和边权值：" << endl;
		Elemtype data1, data2;
		int weight;
		int head, tail;
		cin >> data1 >> data2 >> weight;
		Select(L, data1, data2, head, tail);
		sidenode* p = new sidenode;
		p->headadjex = head;
		p->tailadjex = tail;
		p->weight = weight;
		//尾插法插入节点；
		if (L.vertics[head].outdegreefirst == NULL) {  //如果头节点的出度边为空，那么直接将出度边插入；
			L.vertics[head].outdegreefirst = p;
			p->outdegreenext = NULL;
		}else {
			sidenode* q = L.vertics[head].outdegreefirst;       //找到最后一个节点，将边插入到它之后
			while (q->outdegreenext) {
				q = q->outdegreenext;
			}
			q->outdegreenext= p;
			p->outdegreenext = NULL;
			
		}
		if (L.vertics[tail].indegreefirst == NULL) {
			L.vertics[tail].indegreefirst = p;
			p->indegreenext = NULL;
		}
		else {
			sidenode* q = L.vertics[tail].indegreefirst;
			while (q->indegreenext) {
				q = q->indegreenext;
			}
			q->indegreenext = p;
			p->indegreenext = NULL;
		}
	
	}

}


void pop(Orthoanilist& L, Elemtype data) {  //删除节点的所有边；
	int adjex = -1;
	for (int i = 0; i < L.vernum; i++) {
		if (data == L.vertics[i].data)  adjex = i;    //找到要删除边的顶点下标；
	}
	sidenode* p = L.vertics[adjex].outdegreefirst;    //以i为边首的边
	sidenode* p1= L.vertics[adjex].indegreefirst;     //以i为边尾的边
	while (p) {
		sidenode* q = p;       //先令一个指针和p指向同一块位置，不能之间删除p，因为这会使得p后面的边节点找不到；
		L.vertics[adjex].outdegreefirst = p->outdegreenext;    //头节点指向要删除的p的下一条边;
		sidenode* m = L.vertics[p->tailadjex].indegreefirst;   //找到以要删除的节点为边首的边，找到边尾。
		while (m) {
			if (m->headadjex == adjex)  break;    //找到边尾节点相应和要删除的节点之间的边；
			m = m->indegreenext;

		}
		if (m == L.vertics[p->tailadjex].indegreefirst) {   //如果找到的边是第一个边节点，就直接修改头节点的指向；
			L.vertics[p->tailadjex].indegreefirst = m->indegreenext;
		}
		else {
			sidenode *n= L.vertics[p->tailadjex].indegreefirst;      //找到要删除的边的前一个边节点
			while (n->indegreenext!=m) {
				n = n->indegreenext;
			}
			n->indegreenext = m->indegreenext;            //修改前一个边节点的下一条边指向；
		}
		p = p->outdegreenext;
		delete q;      //删除这条边，注意一定要先将p指向下一个节点后再删除这个节点；

	}
	while (p1) {
		sidenode* q = p1;
		L.vertics[adjex].indegreefirst = p1->indegreenext;
		sidenode* m = L.vertics[p1->headadjex].outdegreefirst; // 找到头结点的出度表的第一个结点
		while (m) {
			if (m->tailadjex== adjex)  break;
			m = m->outdegreenext;

		}
		if (m == L.vertics[p1->headadjex].outdegreefirst) {
			L.vertics[p1->headadjex].outdegreefirst = m->outdegreenext;
		}
		else {
			sidenode* n = L.vertics[p1->headadjex].outdegreefirst;
			while (n->outdegreenext!=m) {
				n = n->outdegreenext;
			}
			n->outdegreenext = m->outdegreenext;
		}


		p1 = p1->indegreenext;
		delete q;

	}
}

void tuopusort(Orthoanilist &L) {    //拓扑排序算法
	memset(list, -1, sizeof(list));
	bool flag = true;    //一个检测是否还有数据变化的标志；
	while (flag) { 
		flag = false;
		for (int i = 0; i < L.vernum; i++) {
			if (L.vertics[i].indegreefirst == NULL && L.vertics[i].visited==false) {
				list[length] = L.vertics[i].data;
				L.vertics[i].visited = true;
				pop(L, L.vertics[i].data);
				length++;
				flag = true;

			}

		}

	}
}

void display(Orthoanilist& L) { //打印十字链表；
	for (int i = 0; i < L.vernum; i++) {
		cout << "下标：" << i << "顶点：" << L.vertics[i].data<<endl;
		cout << "以" << L.vertics[i].data << "为边首的边：";
		sidenode* p = L.vertics[i].outdegreefirst;
		while (p) {
			cout << "(" << L.vertics[p->headadjex].data << "->" << L.vertics[p->tailadjex].data << ")"<<" ";
			p = p->outdegreenext;
		}
		cout << endl;
	}
}

void displaytuopu(Orthoanilist &L) {   //打印拓扑序列
	for (int i = 0; i < length; i++) {
		cout << list[i] << "->";
	}
	cout << endl;
	if (length < L.vernum)  cout << "该图存在环！";

}

int main() {
	Orthoanilist L;
	int m, n;
	cout << "请输入总顶点数和总边数：" << endl;
	cin >> m >> n;
	creatlist(L, m, n);
	display(L);
	tuopusort(L);
	cout << "拓扑序列为：" << endl;
	displaytuopu(L);


	return 0;
}