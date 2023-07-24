//���·�����������㷨�������ж���֮������·����
#include<iostream>
using namespace std;
#define maxsize 10   //�������������
typedef char Elemtype;
#define max 100       //���������룻

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

void creatGraph(Graph& G, int m, int n) { //�����ڽӾ���
	if (m < 1 || n < 0)  return;
	memset(G.vertics, -1, sizeof(G.vertics));     //��ʼ�������
	G.vernum = m;
	G.arcnum = n;
	for (int i = 0; i < G.vernum; i++) {
		for (int j = 0; j < G.vernum; j++) {   //��ʼ������
			if (i == j) G.graph[i][j] = 0;
			else {
				G.graph[i][j] = max;

			}
			
		}
	}
	for (int i = 0; i < m; i++) {
		cout << "�������" << i + 1 << "�������ֵ��" << endl;
		cin >> G.vertics[i].data;
	}
	for (int j = 0; j < n; j++) {
		cout << "�������" << j+ 1 << "���ߵı��ף���β�ͱ�Ȩֵ��" << endl;
		Elemtype data1, data2;
		int weight;
		int head, tail;
		cin >> data1 >> data2 >> weight;
		Select(G, data1, data2, head, tail);
		G.graph[head][tail] = weight;
	}
}
int dv[maxsize][maxsize];        //�洢����i������j�����·��������
int pre[maxsize][maxsize];       //�洢����i������j�����·��������ڵ��±ꣻ

void Floydshortway(Graph& G) {
	for (int i = 0; i < G.vernum; i++) {
		for (int j = 0; j < G.vernum; j++) {
			dv[i][j] = G.graph[i][j];       //��ʼ����̾��뿪��Ϊ��������֮��ľ��룻
			pre[i][j] = -1;                 //����ڵ�Ϊ��
			if (G.graph[i][j] != max &&i!=j) {     
				pre[i][j] = i;           //������ڶ���i��j�Ļ������޸�i��j������ڵ�Ϊi��
			}
		}
	}
	bool flag = true;    //һ���ж��Ƿ������ݱ仯�ı�־��
	while (flag) {
		flag = false;
		for (int i = 0; i < G.vernum; i++) {
			for (int j = 0; j < G.vernum; j++) {
				int pre1 = pre[i][j];      //����ڵ㣻
				for (int k = 0; k < G.vernum; k++) {
					if (dv[i][j] > dv[i][k] + G.graph[k][j] && G.graph[k][j] != max && dv[i][k] != max) {
						dv[i][j] = dv[i][k] + G.graph[k][j];
						pre1 = k;
						flag = true;       
						//����ҵ�����·��ʹ�ÿ�����С����ô���޸���̿���������i��j������ڵ����Ϊk;
					}
				}
				pre[i][j] = pre1;
			}
		}

	}
	
}

void  display(Graph& G) { //��ӡ����
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
void displayshort(Graph& G) {      //��ӡ��̿�������
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

void displayFloyd(Graph &G) {      //��ӡ���·����Ϣ��
	for (int i = 0; i < G.vernum; i++) {
		cout << "��" << G.vertics[i].data << "��ʼ��������������·����" << endl;
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
				cout << "��" << G.vertics[i].data << "��" << G.vertics[j].data << "�����·����";
				for (int k = length - 1; k >= 0; k--) {
					cout << arry[k] << "->";
				}
				cout << G.vertics[j].data;
				cout << "\t����Ϊ��" << dv[i][j];

			}
			else {
				cout << "��" << G.vertics[i].data << "��" << G.vertics[j].data << "�����·��������";
			}
			cout << endl;
		}
	}

}


int main() {
	Graph G;
	int m, n;
	cout << "�����붥�����ͱ�����" << endl;
	cin >> m >> n;
	creatGraph(G, m, n);
	cout << "ͼ���ڽӾ���" << endl;
	display(G);
	Floydshortway(G);
	cout << "ͼ�����·����������" << endl;
	displayshort(G);
	displayFloyd(G);


	return 0;
}