//鉴于邻接表存储无向图时，有e条边的话，就会有2e个边节点。每一条边都会存储两次，浪费空间。所以采用邻接多重表来存储无向图。
#include<iostream>
using namespace std;
typedef char Elemtype;

typedef struct sidenode {
	int head1, head2;     //边的两个顶点下标；
	struct sidenode* head1next, * head2next;//边的两个顶点的下一条边指针；
	int weight;  //权值；
}sidenode;

typedef struct headnode {
	Elemtype data;
	sidenode* sidefirst;//指向第一条边；
	sidenode real;
}headnode;

typedef struct multilist {    //邻接多重表；
	headnode* vertics; //顶点表；
	int verticsnum;
	int arcnum;
}multilist;

void Select(multilist& L, int& head1, int& head2,Elemtype data1,Elemtype data2) { //查找下标；
	for (int i = 0; i < L.verticsnum; i++) {
		if (data1 == L.vertics[i].data)   head1 = i;
		if (data2 == L.vertics[i].data)   head2 = i;
	}
}

void creatmultilist(multilist &L,int n,int m) {      //创建邻接多重表；
	if (n < 1) return;
	else if (m < 0) return;
	L.vertics = new headnode[n];
	L.verticsnum = n;
	L.arcnum = m;
	for (int i = 0; i < L.verticsnum; i++) {
		L.vertics[i].data = 0;
		L.vertics[i].sidefirst = NULL;

	}
	for (int i = 0; i < L.verticsnum; i++) {
		cout << "请输入第" << i + 1 << "个顶点的名称：" << endl;
		cin >> L.vertics[i].data;
	}
	for (int i = 0; i < L.arcnum; i++) {
		cout << "请输入第" << i + 1 << "条边的两个顶点和权值：" << endl;
		Elemtype data1, data2;
		int head1, head2;
		int weight;
		cin >> data1 >> data2 >> weight;
		sidenode* p = new sidenode;
		Select(L, head1, head2, data1, data2);
		p->head1 = head1;
		p->head2 = head2;
		p->weight = weight;
		p->head1next = L.vertics[head1].sidefirst;     //头插法；
		L.vertics[head1].sidefirst = p;
		p->head2next = L.vertics[head2].sidefirst;
		L.vertics[head2].sidefirst = p;




	}


}

void display(multilist& L) {       //打印结果；
	for (int i = 0; i < L.verticsnum; i++) {
		cout << "顶点下标：" << i << "顶点名称：" << L.vertics[i].data << endl;
		sidenode* p = L.vertics[i].sidefirst;
		while (p) {
			cout << p->head1 << " " << p->head2 << endl;
			if (p->head1 == i)
				p = p->head1next;
			else
				p = p->head2next;
		}
	}
}

int main() {
	multilist L;
	creatmultilist(L, 4, 5);
	display(L);

	return 0;
}