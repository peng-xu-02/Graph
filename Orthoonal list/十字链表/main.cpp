//����ͼ���ڽӱ��ʾ����Ҫͬʱ�ҵ�����ĳ��Ⱥ���Ⱥ��ѣ����Բ���ʮ����������ʾ��
#include<iostream>
using namespace std;
typedef char Elemtype;

typedef struct sidenode {        //����߽ڵ㣻
	int sidehead;        //�����ߵ���ʼ�������ף�
	int sidetail;        //�����ߵı�β����
	int weight;          //��Ȩֵ��
	struct sidenode *indegree;    //���ָ�룻
	struct sidenode *outdegree;   //����ָ�룻
}sidenode;


typedef struct headnode {    //����ͷ�ڵ㣻
	Elemtype data;     //�ڵ����ƣ�
	sidenode* indegreefirst;      //ָ���һ����ȱߣ�
	sidenode* outdegreefirst;     //ָ���һ�����ȱߣ�
}headnode;

typedef struct Orthoonallist {  //����ʮ������
	headnode* vertics; //����һ�������
	int verticsnum;     //��������
	int archnum;        //������
}Orthoonallist;
 
void Select(Orthoonallist& T, Elemtype head, Elemtype tail, int& id1, int& id2) {   //�������ݵ��±ꣻ
	for (int i = 0; i < T.verticsnum; i++) {
		if (head == T.vertics[i].data) id1 = i;
		if (tail == T.vertics[i].data) id2 = i;
	}
}

void creatOrthoonallist(int m,int n,Orthoonallist &T) { //����ʮ������
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
		cout << "�������" << i + 1 << "����������ƣ�" << endl;
		cin >> T.vertics[i].data;
	}
	for (int i = 0; i < T.archnum; i++) {
		Elemtype head, tail;
		int id1, id2;
		int weight;
		cout << "�������"<<i+1<<"���ߵı��ס���β����Ȩֵ��" << endl;
		cin >> head >> tail >> weight;
		sidenode* p = new sidenode;
		Select(T, head, tail, id1, id2);
		p->sidehead = id1;
		p->sidetail = id2;
		p->weight = weight;
		p->indegree = T.vertics[id2].indegreefirst;        //ͷ�巨���룻
		p->outdegree = T.vertics[id1].outdegreefirst;
		T.vertics[id1].outdegreefirst = p;
		T.vertics[id2].indegreefirst = p;
	}
}

void display(Orthoonallist &T) {     //��ӡ�����
	for (int i = 0; i < T.verticsnum; i++) {
		cout << "�±꣺" << i << "�������ƣ�" << T.vertics[i].data << endl;
		sidenode* p = T.vertics[i].outdegreefirst;
		cout << "���ȱߣ�";
		while (p) {
			cout << p->sidetail << " ";
			p = p->outdegree;
		}
		sidenode* q = T.vertics[i].indegreefirst;
		cout << endl;
		cout << "��ȱߣ�";
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