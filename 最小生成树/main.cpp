//������С���������ҵ���һ�������������������С�Ŀ�����ÿ������ֻ����һ�Ρ��������в����ڻ��ͻ�·��
#include<iostream>
using namespace std;
typedef char Elemtype;

typedef struct Graph {         //�ڽӾ���
	Elemtype* vertics;//�����
	int vernum, arcnum;
	int** graph;   //ָ�����飬��̬�����ڴ棻
}Graph;

typedef struct primearry {        //��С��������
	int data;        //������С�������Ķ����±ꣻ
	int pv;           //������С�������Ķ����ǰ���±ꣻ
}primearry;

typedef struct visited {      //�����С���������飻
	primearry *data;  //����һ������ṹ��
	int length;     //���鵱ǰ���ȣ�
}visited;
visited T;


void Select(Graph& G, Elemtype data1, Elemtype data2, int& head1, int& head2) { 
	for (int i = 0; i < G.vernum; i++) {
		if (data1 == G.vertics[i]) head1 = i;
		if (data2 == G.vertics[i]) head2 = i;
	}
}

void creatGraph(Graph &G,int m,int n){  //������������
	if (m < 1 || n < 0) return;
	G.vernum = m;
	G.arcnum = n;
	G.vertics = new Elemtype[G.vernum];
	T.data = new primearry[n];
	T.length = 0;
	G.graph = new int* [G.vernum];
	for (int i = 0; i < G.vernum; i++) {       //��ʼ����
		G.vertics[i] = '0';
		G.graph[i] = new int[G.vernum];
		for (int j = 0; j < G.vernum; j++) {
			G.graph[i][j] = 0;
		}

	}
	for (int i = 0; i < G.vernum; i++) {
		cout << "�������" << i + 1 << "����������ƣ�"<< endl;
		cin >> G.vertics[i];
	}
	for (int j = 0; j < G.arcnum; j++) {
		cout << "�������" << j + 1 << "���ߵ����������Ȩֵ��" << endl;
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
int compre(int adiex, int adjex) {           //�ж��������Ƿ��Ѿ���������
	for (int i = 0; i < T.length; i++) {
		for (int j = 0; j < T.length; j++) {
			if (adiex == T.data[i].data && adjex == T.data[j].data) {
				return 1;
			}
		}
	}
	return 0;
}

void primetree(Graph &G,Elemtype data) {     //����ķ�㷨��
	int head=0;
	for (int i = 0; i < G.vernum; i++) {
		if (data == G.vertics[i]) head = i;
	}
	T.data[T.length].data = head;
	T.length++;
	int adjex = -1,adiex=-1;
	while (T.length != G.vernum) {
		int min = 20; //��minΪһ���ϴ�ֵ��
		for (int i = 0; i < T.length; i++) {
			for (int j = 0; j < G.vernum; j++) {
				if (G.graph[T.data[i].data][j] != 0 && G.graph[T.data[i].data][j] < min && compre(T.data[i].data, j) == 0) {
					min = G.graph[T.data[i].data][j];
					adiex = T.data[i].data; 
					adjex = j;
				}
			}
		}
		T.data[T.length].data = adjex;  //�����±������С��������
		T.data[T.length].pv = adiex;    //�����ǰ����
		T.length++;
	}
}

void displayprime(Graph &G) {    //��ӡ��С��������
	for (int i = 1; i < T.length; i++) {
		cout <<"("<<G.vertics[T.data[i].pv]<<","<< G.vertics[T.data[i].data]<<")" << endl;
	}
}




int main() {
	Graph G;
	creatGraph(G, 4, 4);
	display(G);
	Elemtype e;
	cout << "�����뿪ʼ���㣺" << endl;
	cin >> e;
	primetree(G, e);
	cout <<"��С��������" << endl;
	displayprime(G);


	return 0;
}