//��Դ�ڵ㵽�����ڵ��Ѱ�����·���㷨-Dijistra�㷨
#include<iostream>
#include<stdlib.h>
using namespace std;
typedef char Elemtype;
#define max 10
#define maxsize 100

typedef struct sidenode {
	int weight;
	int head, tail;
	struct sidenode* indegreenext, * outdegreenext;
}sidenode;

typedef struct headnode {
	Elemtype data;
	sidenode* indegreefirst, * outdegreefirst;


}headnode;

typedef struct Orthogonallist {
	headnode* vertics;
	int vernum, arcnum;

}Orthogonallist;

typedef struct Dijistra {
	int arr[max][max] = {0};
	int length[max] = {0};

}Dijistraarry;

void Initlst(Orthogonallist& L,int m) {
	L.vertics = new headnode[m];
	L.vernum = m;
	for (int i = 0; i < m; i++) {
		L.vertics[i].data = 0;
		L.vertics[i].indegreefirst= NULL;
		L.vertics[i].outdegreefirst = NULL;
	}

}

void Select(Orthogonallist& L, Elemtype data1, Elemtype data2, int& head, int& tail) {
	for (int i = 0; i < L.vernum; i++) {
		if (data1 == L.vertics[i].data)  head = i;
		if (data2 == L.vertics[i].data)  tail = i;
	}
}
void creatlist(Orthogonallist& L, int m) {
	L.arcnum = m;
	for (int i = 0; i < L.vernum; i++) {
		cout << "�������" << i + 1 << "����������ƣ�" << endl;
		cin >> L.vertics[i].data;
	}
	for (int i = 0; i < m; i++) {
		cout << "�������" << i + 1 << "���ߵı��ס���β�ͱߵ�Ȩֵ��" << endl;
		int head, tail;
		int weight;
		Elemtype data1, data2;
		cin >> data1 >> data2 >> weight;
		Select(L, data1, data2, head, tail);
		sidenode* p = new sidenode;
		p->head = head;
		p->tail = tail;
		p->weight = weight;
		p->indegreenext = L.vertics[tail].indegreefirst;
		p->outdegreenext = L.vertics[head].outdegreefirst;
		L.vertics[head].outdegreefirst = p;
		L.vertics[tail].indegreefirst = p;

	}
}

void display(Orthogonallist& L) {
	for (int i = 0; i < L.vernum; i++) {
		cout << "�±꣺" << i << "���㣺" << L.vertics[i].data<<endl;
		cout << "��" << L.vertics[i].data << "Ϊ���׵ıߣ�";
		sidenode* p = L.vertics[i].outdegreefirst;
		while (p) {
			cout << "->" << p->tail;
			p = p->outdegreenext;
		}
		cout << "��" << L.vertics[i].data << "Ϊ��β�ıߣ�";
		sidenode* q = L.vertics[i].indegreefirst;
		while (q) {
			cout << "->" << q->head;
			q = q->indegreenext;
		}
		cout << endl;
	}
	
}

int dv[max];


void Dijistra(Orthogonallist& L) {
	memset(dv, maxsize, sizeof(dv));
	cout << "�����뿪ʼ���㣺" << endl;
	Elemtype e;
	cin >> e;
	int head = 0;
	for (int i = 0; i < L.vernum; i++) {
		if (e == L.vertics[i].data)  head = i;
	}
	int cout1[max];
	memset(cout1, -1, sizeof(cout1));
	int length = 0;
	cout1[length] = head; //��¼�Ѿ����ʹ��Ķ���
	length++;
	sidenode* p = L.vertics[head].outdegreefirst; //�ӳ��ȱ�ʼ����
	while (p) {
		dv[p->tail] = p->weight; //��¼�ӿ�ʼ���㵽��������ľ���
		p = p->outdegreenext; //ָ����һ�����ȱ�
	}
	while (length < L.vernum) { //�����ʹ��Ķ�����С���ܶ�����ʱ
		int min = maxsize; //��ʼ����С����Ϊ�����
		int k = -1; //��ʼ����С����Ķ����±�Ϊ-1
		for (int i = 0; i < L.vernum; i++) { //�������ж���
			if (dv[i] < min && cout1[i] == -1) { //�����ǰ����ľ���С����С���룬����û�б����ʹ�
				min = dv[i]; //������С����
				k = i; //������С����Ķ����±�
			}
		}
		if (k == -1) break; //���û���ҵ����ʵĶ��㣬˵��ͼ����ͨ���˳�ѭ��
		cout1[k] = 1; //��ǵ�ǰ�����Ѿ����ʹ�
		cout1[length] = k; //��¼��ǰ���㵽���ʹ��Ķ���������
		length++; //���ӷ��ʹ��Ķ�����
		p = L.vertics[k].outdegreefirst; //�ӵ�ǰ����ĳ��ȱ�ʼ����
		while (p) { //�����ȱߴ���ʱ
			if (dv[p->tail] > dv[k] + p->weight) { //����ӵ�ǰ���㵽��������ľ�����ڴӿ�ʼ���㾭����ǰ���㵽��������ľ���
				dv[p->tail] = dv[k] + p->weight; //������̾���
			}
			p = p->outdegreenext; //ָ����һ�����ȱ�
		}
	}
	for (int i = 1; i < L.vernum; i++) { //������
		cout << "��" << e << "��" << L.vertics[i].data << "����̾���Ϊ��" << dv[i] << endl;
	}

}

int main() {
	Orthogonallist L;
	Initlst(L, 4);
	creatlist(L, 3);
	display(L);
	Dijistra(L);

	return 0;
}