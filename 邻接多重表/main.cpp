//�����ڽӱ�洢����ͼʱ����e���ߵĻ����ͻ���2e���߽ڵ㡣ÿһ���߶���洢���Σ��˷ѿռ䡣���Բ����ڽӶ��ر����洢����ͼ��
#include<iostream>
using namespace std;
typedef char Elemtype;

typedef struct sidenode {
	int head1, head2;     //�ߵ����������±ꣻ
	struct sidenode* head1next, * head2next;//�ߵ������������һ����ָ�룻
	int weight;  //Ȩֵ��
}sidenode;

typedef struct headnode {
	Elemtype data;
	sidenode* sidefirst;//ָ���һ���ߣ�
	sidenode real;
}headnode;

typedef struct multilist {    //�ڽӶ��ر�
	headnode* vertics; //�����
	int verticsnum;
	int arcnum;
}multilist;

void Select(multilist& L, int& head1, int& head2,Elemtype data1,Elemtype data2) { //�����±ꣻ
	for (int i = 0; i < L.verticsnum; i++) {
		if (data1 == L.vertics[i].data)   head1 = i;
		if (data2 == L.vertics[i].data)   head2 = i;
	}
}

void creatmultilist(multilist &L,int n,int m) {      //�����ڽӶ��ر�
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
		cout << "�������" << i + 1 << "����������ƣ�" << endl;
		cin >> L.vertics[i].data;
	}
	for (int i = 0; i < L.arcnum; i++) {
		cout << "�������" << i + 1 << "���ߵ����������Ȩֵ��" << endl;
		Elemtype data1, data2;
		int head1, head2;
		int weight;
		cin >> data1 >> data2 >> weight;
		sidenode* p = new sidenode;
		Select(L, head1, head2, data1, data2);
		p->head1 = head1;
		p->head2 = head2;
		p->weight = weight;
		p->head1next = L.vertics[head1].sidefirst;     //ͷ�巨��
		L.vertics[head1].sidefirst = p;
		p->head2next = L.vertics[head2].sidefirst;
		L.vertics[head2].sidefirst = p;




	}


}

void display(multilist& L) {       //��ӡ�����
	for (int i = 0; i < L.verticsnum; i++) {
		cout << "�����±꣺" << i << "�������ƣ�" << L.vertics[i].data << endl;
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