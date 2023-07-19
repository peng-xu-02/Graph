//鉴于图的邻接表表示法想要同时找到顶点的出度和入度很难，所以采用十字链表来表示；
#include<iostream>
using namespace std;
typedef char Elemtype;

typedef struct sidenode {        //定义边节点；
	int sidehead;        //这条边的起始，即边首；
	int sidetail;        //这条边的边尾部；
	int weight;          //边权值；
	struct sidenode *indegree;    //入度指针；
	struct sidenode *outdegree;   //出度指针；
}sidenode;


typedef struct headnode {    //定义头节点；
	Elemtype data;     //节点名称；
	sidenode* indegreefirst;      //指向第一条入度边；
	sidenode* outdegreefirst;     //指向第一条出度边；
}headnode;

typedef struct Orthoonallist {  //定义十字链表；
	headnode* vertics; //定义一个顶点表；
	int verticsnum;     //顶点数；
	int archnum;        //边数；
}Orthoonallist;
 
void Select(Orthoonallist& T, Elemtype head, Elemtype tail, int& id1, int& id2) {   //查找数据的下标；
	for (int i = 0; i < T.verticsnum; i++) {
		if (head == T.vertics[i].data) id1 = i;
		if (tail == T.vertics[i].data) id2 = i;
	}
}

void creatOrthoonallist(int m,int n,Orthoonallist &T) { //创建十字链表
	if (m < 1 && n<0) return;
	T.vertics = new headnode[m];
	T.verticsnum = m;
	T.archnum = n;
	for (int i = 0; i < T.verticsnum; i++) {
		T.vertics[i].data = 0;
		T.vertics[i].indegreefirst = NULL;
		T.vertics[i].outdegreefirst = NULL;
	}
	for (int i = 0; i < T.verticsnum; i++) {
		cout << "请输入第" << i + 1 << "个顶点的名称：" << endl;
		cin >> T.vertics[i].data;
	}
	for (int i = 0; i < T.archnum; i++) {
		Elemtype head, tail;
		int id1, id2;
		int weight;
		cout << "请输入第"<<i+1<<"条边的边首、边尾、边权值：" << endl;
		cin >> head >> tail >> weight;
		sidenode* p = new sidenode;
		Select(T, head, tail, id1, id2);
		p->sidehead = id1;
		p->sidetail = id2;
		p->weight = weight;
		p->indegree = T.vertics[id2].indegreefirst;        //头插法插入；
		p->outdegree = T.vertics[id1].outdegreefirst;
		T.vertics[id1].outdegreefirst = p;
		T.vertics[id2].indegreefirst = p;
	}
}

void display(Orthoonallist &T) {     //打印结果；
	for (int i = 0; i < T.verticsnum; i++) {
		cout << "下标：" << i << "顶点名称：" << T.vertics[i].data << endl;
		sidenode* p = T.vertics[i].outdegreefirst;
		cout << "出度边：";
		while (p) {
			cout << p->sidetail << " ";
			p = p->outdegree;
		}
		sidenode* q = T.vertics[i].indegreefirst;
		cout << endl;
		cout << "入度边：";
		while (q) {
			cout << q->sidehead << " ";
			q = q->indegree;
		}
		cout << endl;
	}

}



int main() {
	Orthoonallist T;
	creatOrthoonallist(5, 9, T);
	display(T);


	return 0;
}