//深度优先遍历无向图
#include<iostream>
using namespace std;
#include<stack>
typedef char Elemtype;

typedef struct headnode { //顶点；
	Elemtype data;
}headnode;

typedef struct Graph {     //无向图的邻接矩阵；
	headnode* vertics;  //顶点表；
	int verticsnum;        //顶点数
	int arcnum;          //边数
	int** graph;           //邻接矩阵
}Graph;

bool* vertics;      //访问数组，用来存放顶点是否访问过的；

void Select(Graph& G, Elemtype data1, Elemtype data2, int& head1, int& head2) { //查找下标；
	for (int i = 0; i < G.verticsnum; i++) {
		if (data1 == G.vertics[i].data)  head1 = i;
		if (data2 == G.vertics[i].data)  head2 = i;
	}
}
void Select(Graph& G, Elemtype data, int& head) {
	for (int i = 0; i < G.verticsnum; i++) {
		if (data == G.vertics[i].data) head = i;
	}
}
void creatGraph(Graph &G,int n,int m) {           //构建邻接矩阵；
	if (n < 1) return;
	G.verticsnum = n;
	vertics = new bool[n];
	G.arcnum = m;
	G.vertics = new headnode[G.verticsnum];
	G.graph = new int* [G.verticsnum];
	for (int i = 0; i < G.verticsnum; i++) {
		cout << "请输入第" << i + 1 << "个顶点的名称：" << endl;
		cin >> G.vertics[i].data;
		vertics[i] = false;
		
	}
	for (int i = 0; i < G.verticsnum; i++) {
		G.graph[i] = new int[n];
		for (int j = 0; j < G.verticsnum; j++) {
			G.graph[i][j] = 0;
		}
	}
	for (int i = 0; i < G.arcnum; i++) {
		cout << "请输入第" << i + 1 << "条边的两个顶点和权值：" << endl;
		Elemtype data1, data2;
		int weight;
		int head1, head2;
		cin >> data1 >> data2 >> weight;
		Select(G, data1, data2, head1, head2);
		G.graph[head1][head2] = weight;
		G.graph[head2][head1] = G.graph[head1][head2];
	}
}

void display(Graph& G) {    //打印邻接矩阵；
	for (int i = 0; i < G.verticsnum; i++) {
		for (int j = 0; j < G.verticsnum; j++) {
			cout << G.graph[i][j] << " ";
		}
		cout << endl;
	}
	
}

void DFS(Graph& G,Elemtype e) {   //深度优先遍历算法；非递归；
	int head;
	Select(G, e, head);
	stack<int> s;
	s.push(head);
	vertics[head] = 1;
	cout << G.vertics[head].data;
	int i;
	while (!s.empty()){ //栈不为空
		for (i = 0; i < G.verticsnum; i++) {     
			if (G.graph[head][i] != 0 && vertics[i] != true) {       //找到当前顶点的下一个相邻顶点；
				s.push(i);
				cout << G.vertics[i].data;
				head = i;
				vertics[i] = true;
				break;

			}
		}
		if (i == G.verticsnum) {  //如果遍历了当前顶点的所有顶点发现都遍历过了，就要出栈回溯；
			head = s.top();
			s.pop();
		}

	}
}
void DFS(Graph& G, int v) {     //深度优先递归算法；
	vertics[v] = 1;
	cout << G.vertics[v].data;
	for (int i = 0; i < G.verticsnum; i++) {
		if (G.graph[v][i] != 0 && vertics[i] != 1) {
			DFS(G, i);
		}
	}
}

int main() {
	Graph G;
	creatGraph(G, 4, 5);
	display(G);
	Elemtype e;
	cout << "请输入深度遍历开始节点：" << endl;
	cin >> e;
	//DFS(G, 0);
	DFS(G, e);

	return 0;
}