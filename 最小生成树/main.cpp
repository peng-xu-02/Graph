//构建最小生成树，找到从一个顶点遍历其他顶点最小的开销，每个顶点只访问一次。生成树中不存在环和回路。
#include<iostream>
using namespace std;
typedef char Elemtype;

typedef struct Graph {         //邻接矩阵；
	Elemtype* vertics;//顶点表；
	int vernum, arcnum;
	int** graph;   //指针数组，动态分配内存；
}Graph;

typedef struct primearry {        //最小生成树；
	int data;        //加入最小生成树的顶点下标；
	int pv;           //加入最小生成树的顶点的前驱下标；
}primearry;

typedef struct visited {      //存放最小生成树数组；
	primearry *data;  //定义一个数组结构；
	int length;     //数组当前长度；
}visited;
visited T;


void Select(Graph& G, Elemtype data1, Elemtype data2, int& head1, int& head2) { 
	for (int i = 0; i < G.vernum; i++) {
		if (data1 == G.vertics[i]) head1 = i;
		if (data2 == G.vertics[i]) head2 = i;
	}
}

void creatGraph(Graph &G,int m,int n){  //构建无向网；
	if (m < 1 || n < 0) return;
	G.vernum = m;
	G.arcnum = n;
	G.vertics = new Elemtype[G.vernum];
	T.data = new primearry[n];
	T.length = 0;
	G.graph = new int* [G.vernum];
	for (int i = 0; i < G.vernum; i++) {       //初始化；
		G.vertics[i] = '0';
		G.graph[i] = new int[G.vernum];
		for (int j = 0; j < G.vernum; j++) {
			G.graph[i][j] = 0;
		}

	}
	for (int i = 0; i < G.vernum; i++) {
		cout << "请输入第" << i + 1 << "个顶点的名称："<< endl;
		cin >> G.vertics[i];
	}
	for (int j = 0; j < G.arcnum; j++) {
		cout << "请输入第" << j + 1 << "条边的两个顶点和权值：" << endl;
		Elemtype data1, data2;
		int weight;
		int head1, head2;
		cin >> data1 >> data2 >> weight;
		Select(G, data1, data2, head1, head2);
		G.graph[head1][head2] = weight;
		G.graph[head2][head1] = G.graph[head1][head2];
	}
}

void display(Graph& G) {
	for (int i = 0; i < G.vernum; i++) {
		cout <<" "<< G.vertics[i];
	}
	cout << endl;
	for (int i = 0; i < G.vernum; i++) {
		cout << G.vertics[i];
		for (int j = 0; j < G.vernum; j++) {
			cout << G.graph[i][j] << " ";
		}
		cout << endl;
	}
}
int compre(int adiex, int adjex) {           //判断这条边是否已经被加入了
	for (int i = 0; i < T.length; i++) {
		for (int j = 0; j < T.length; j++) {
			if (adiex == T.data[i].data && adjex == T.data[j].data) {
				return 1;
			}
		}
	}
	return 0;
}

void primetree(Graph &G,Elemtype data) {     //普利姆算法；
	int head=0;
	for (int i = 0; i < G.vernum; i++) {
		if (data == G.vertics[i]) head = i;
	}
	T.data[T.length].data = head;
	T.length++;
	int adjex = -1,adiex=-1;
	while (T.length != G.vernum) {
		int min = 20; //让min为一个较大值；
		for (int i = 0; i < T.length; i++) {
			for (int j = 0; j < G.vernum; j++) {
				if (G.graph[T.data[i].data][j] != 0 && G.graph[T.data[i].data][j] < min && compre(T.data[i].data, j) == 0) {
					min = G.graph[T.data[i].data][j];
					adiex = T.data[i].data; 
					adjex = j;
				}
			}
		}
		T.data[T.length].data = adjex;  //顶点下标加入最小生成树；
		T.data[T.length].pv = adiex;    //顶点的前驱；
		T.length++;
	}
}

void displayprime(Graph &G) {    //打印最小生成树；
	for (int i = 1; i < T.length; i++) {
		cout <<"("<<G.vertics[T.data[i].pv]<<","<< G.vertics[T.data[i].data]<<")" << endl;
	}
}




int main() {
	Graph G;
	creatGraph(G, 4, 4);
	display(G);
	Elemtype e;
	cout << "请输入开始顶点：" << endl;
	cin >> e;
	primetree(G, e);
	cout <<"最小生成树：" << endl;
	displayprime(G);


	return 0;
}