//������ȱ�������ͼ
#include<iostream>
using namespace std;
#include<stack>
typedef char Elemtype;

typedef struct headnode { //���㣻
	Elemtype data;
}headnode;

typedef struct Graph {     //����ͼ���ڽӾ���
	headnode* vertics;  //�����
	int verticsnum;        //������
	int arcnum;          //����
	int** graph;           //�ڽӾ���
}Graph;

bool* vertics;      //�������飬������Ŷ����Ƿ���ʹ��ģ�

void Select(Graph& G, Elemtype data1, Elemtype data2, int& head1, int& head2) { //�����±ꣻ
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
void creatGraph(Graph &G,int n,int m) {           //�����ڽӾ���
	if (n < 1) return;
	G.verticsnum = n;
	vertics = new bool[n];
	G.arcnum = m;
	G.vertics = new headnode[G.verticsnum];
	G.graph = new int* [G.verticsnum];
	for (int i = 0; i < G.verticsnum; i++) {
		cout << "�������" << i + 1 << "����������ƣ�" << endl;
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
		cout << "�������" << i + 1 << "���ߵ����������Ȩֵ��" << endl;
		Elemtype data1, data2;
		int weight;
		int head1, head2;
		cin >> data1 >> data2 >> weight;
		Select(G, data1, data2, head1, head2);
		G.graph[head1][head2] = weight;
		G.graph[head2][head1] = G.graph[head1][head2];
	}
}

void display(Graph& G) {    //��ӡ�ڽӾ���
	for (int i = 0; i < G.verticsnum; i++) {
		for (int j = 0; j < G.verticsnum; j++) {
			cout << G.graph[i][j] << " ";
		}
		cout << endl;
	}
	
}

void DFS(Graph& G,Elemtype e) {   //������ȱ����㷨���ǵݹ飻
	int head;
	Select(G, e, head);
	stack<int> s;
	s.push(head);
	vertics[head] = 1;
	cout << G.vertics[head].data;
	int i;
	while (!s.empty()){ //ջ��Ϊ��
		for (i = 0; i < G.verticsnum; i++) {     
			if (G.graph[head][i] != 0 && vertics[i] != true) {       //�ҵ���ǰ�������һ�����ڶ��㣻
				s.push(i);
				cout << G.vertics[i].data;
				head = i;
				vertics[i] = true;
				break;

			}
		}
		if (i == G.verticsnum) {  //��������˵�ǰ��������ж��㷢�ֶ��������ˣ���Ҫ��ջ���ݣ�
			head = s.top();
			s.pop();
		}

	}
}
void DFS(Graph& G, int v) {     //������ȵݹ��㷨��
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
	cout << "��������ȱ�����ʼ�ڵ㣺" << endl;
	cin >> e;
	//DFS(G, 0);
	DFS(G, e);

	return 0;
}