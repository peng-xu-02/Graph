//最短路径弗洛伊德算法，求所有顶点之间的最短路径；
#include<iostream>
using namespace std;
#define maxsize 10   //定义最大容量；
typedef char Elemtype;
#define max 100       //定义最大距离；

typedef struct headnode {
	Elemtype data;
}headnode;

typedef struct Graph {
	headnode vertics[maxsize];
	int graph[maxsize][maxsize];
	int vernum, arcnum;
}Graph;

void Select(Graph& G, Elemtype data1, Elemtype data2, int& head, int& tail) {
	for (int i = 0; i < G.vernum; i++) {
		if (data1 == G.vertics[i].data)  head = i;
		if (data2 == G.vertics[i].data)  tail = i;
	}
}

void creatGraph(Graph& G, int m, int n) { //建立邻接矩阵；
	if (m < 1 || n < 0)  return;
	memset(G.vertics, -1, sizeof(G.vertics));     //初始化顶点表；
	G.vernum = m;
	G.arcnum = n;
	for (int i = 0; i < G.vernum; i++) {
		for (int j = 0; j < G.vernum; j++) {   //初始化矩阵；
			if (i == j) G.graph[i][j] = 0;
			else {
				G.graph[i][j] = max;

			}
			
		}
	}
	for (int i = 0; i < m; i++) {
		cout << "请输入第" << i + 1 << "个顶点的值：" << endl;
		cin >> G.vertics[i].data;
	}
	for (int j = 0; j < n; j++) {
		cout << "请输入第" << j+ 1 << "条边的边首，边尾和边权值：" << endl;
		Elemtype data1, data2;
		int weight;
		int head, tail;
		cin >> data1 >> data2 >> weight;
		Select(G, data1, data2, head, tail);
		G.graph[head][tail] = weight;
	}
}
int dv[maxsize][maxsize];        //存储顶点i到顶点j的最短路径开销；
int pre[maxsize][maxsize];       //存储顶点i到顶点j的最短路径的先序节点下标；

void Floydshortway(Graph& G) {
	for (int i = 0; i < G.vernum; i++) {
		for (int j = 0; j < G.vernum; j++) {
			dv[i][j] = G.graph[i][j];       //初始化最短距离开销为两个顶点之间的距离；
			pre[i][j] = -1;                 //先序节点为空
			if (G.graph[i][j] != max &&i!=j) {     
				pre[i][j] = i;           //如果存在顶点i到j的弧，则修改i到j的先序节点为i；
			}
		}
	}
	bool flag = true;    //一个判断是否还有数据变化的标志；
	while (flag) {
		flag = false;
		for (int i = 0; i < G.vernum; i++) {
			for (int j = 0; j < G.vernum; j++) {
				int pre1 = pre[i][j];      //先序节点；
				for (int k = 0; k < G.vernum; k++) {
					if (dv[i][j] > dv[i][k] + G.graph[k][j] && G.graph[k][j] != max && dv[i][k] != max) {
						dv[i][j] = dv[i][k] + G.graph[k][j];
						pre1 = k;
						flag = true;       
						//如果找到其他路径使得开销变小，那么就修改最短开销，并且i到j的先序节点更改为k;
					}
				}
				pre[i][j] = pre1;
			}
		}

	}
	
}

void  display(Graph& G) { //打印矩阵；
	cout << " ";
	for (int i = 0; i < G.vernum; i++) {
		cout << G.vertics[i].data<<"\t";
	}
	cout << endl;
	for (int i = 0; i < G.vernum; i++) {
		cout << G.vertics[i].data;
		for (int j = 0; j < G.vernum; j++) {
			cout << G.graph[i][j]<<"\t";
		}
		cout << endl;
	}
}
void displayshort(Graph& G) {      //打印最短开销矩阵；
	cout << " ";
	for (int i = 0; i < G.vernum; i++) {
		cout << G.vertics[i].data << "\t";
	}
	cout << endl;
	for (int i = 0; i < G.vernum; i++) {
		cout << G.vertics[i].data;
		for (int j = 0; j < G.vernum; j++) {
			cout << dv[i][j] << "\t";
		}
		cout << endl;
	}
}

void displayFloyd(Graph &G) {      //打印最短路径信息；
	for (int i = 0; i < G.vernum; i++) {
		cout << "从" << G.vertics[i].data << "开始到其他顶点的最短路径：" << endl;
		for (int j = 0; j < G.vernum; j++) {
			Elemtype arry[maxsize];
			int length = 0;
			memset(arry, 0, sizeof(arry));
			int k = pre[i][j];
			while (k != -1) {
				arry[length] = G.vertics[k].data;
				length++;
				k = pre[i][k];
			}
			if (dv[i][j] != max) {
				cout << "从" << G.vertics[i].data << "到" << G.vertics[j].data << "的最短路径：";
				for (int k = length - 1; k >= 0; k--) {
					cout << arry[k] << "->";
				}
				cout << G.vertics[j].data;
				cout << "\t开销为：" << dv[i][j];

			}
			else {
				cout << "从" << G.vertics[i].data << "到" << G.vertics[j].data << "的最短路径不存在";
			}
			cout << endl;
		}
	}

}


int main() {
	Graph G;
	int m, n;
	cout << "请输入顶点数和边数：" << endl;
	cin >> m >> n;
	creatGraph(G, m, n);
	cout << "图的邻接矩阵：" << endl;
	display(G);
	Floydshortway(G);
	cout << "图的最短路径开销矩阵：" << endl;
	displayshort(G);
	displayFloyd(G);


	return 0;
}