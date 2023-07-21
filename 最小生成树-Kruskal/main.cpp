//Kruskal�㷨������С��������ʼ״ֻ̬��n��������ޱߣ�Ȼ����ȥ�Ҹ�������֮����С��Ȩֵ�ı߼��뵽��С�������У�����ҵ��ı߻ᵼ����С�������γɻ�·����Ѱ�������ıߡ�
//����̶�������С�ıߣ����������ϡ��ͼ��
#include<iostream>
using namespace std;
#include<stack>
typedef char Elemtype;
#define max 20

typedef struct sidenode {  //�߽ڵ㣻
	int weight;            //��Ȩֵ��
	int head1, head2;       //�ߵĵ�һ������͵ڶ��������±ꣻ
	struct sidenode* head1next, * head2next;    //�ߵĵ�һ���������һ���ߣ��ߵĵڶ����������һ���ߣ�
	bool visited;          //�ж��Ƿ�߱����ʹ���

}sidenode;

typedef struct headnode { //ͷ�ڵ㣻
	Elemtype headdata;
	sidenode* firstside;
}headnode;

typedef struct multilist {   //�ڽӶ��ر�
	headnode* vertics;   //�����
	int vernum;
	int arcnum;
}multilist;

typedef struct Kruskaltree { //�����С������
	int head1, head2;
	int length;
}Kruskaltree;

void Select(multilist& L, Elemtype headdata1, Elemtype headdata2, int& head1, int& head2) {
	for (int i = 0; i < L.vernum; i++) {
		if (headdata1 == L.vertics[i].headdata)  head1 = i;
		if (headdata2 == L.vertics[i].headdata)  head2 = i;
	}
}

void creatmultilist(multilist &L,int m,int n) {   //�������ر�
	if (m < 1 || n < 0) return;
	L.vertics = new headnode[m];
	L.vernum = m;
	L.arcnum = n;
	for (int i = 0; i < m; i++) {
		L.vertics[i].headdata = '0';
		L.vertics[i].firstside = NULL;
	}
	for (int i = 0; i < m; i++) {
		cout << "�������" << i + 1 << "����������ƣ�" << endl;
		cin >> L.vertics[i].headdata;
	}
	for (int i = 0; i < n; i++) {
		cout << "�������" << i + 1 << "���ߵ����������Ȩֵ��" << endl;
		Elemtype headdata1, headdata2;
		int weight;
		int head1, head2;
		cin >> headdata1 >> headdata2 >> weight;
		Select(L, headdata1, headdata2, head1, head2);
		sidenode* p = new sidenode;
		p->weight = weight;      
		p->head1 = head1;
		p->head2 = head2;
		p->visited = 0;    //û�з��ʹ���
		p->head1next = L.vertics[head1].firstside;     //ͷ�巨��
		p->head2next = L.vertics[head2].firstside;
		L.vertics[head1].firstside = p;
		L.vertics[head2].firstside = p;
	}

}
void display(multilist &L) {    //��ӡ���ر�
	for (int i = 0; i < L.vernum; i++) {
		cout << "�±꣺" << i << "���㣺" << L.vertics[i].headdata;
		sidenode* p = L.vertics[i].firstside;
		while (p) {
			if (i == p->head1) {
				cout << "->" << p->head2;
				p = p->head1next;

			}
			else {
				cout << "->" << p->head1;
				p = p->head2next;
			}
			
		}
		cout << endl;
	}

}

bool compare(int head1,int head2,Kruskaltree *kru) {  //�ж��¼���������߻᲻��ɻ���
	stack<int> s;
	bool visited[20] = { 0 };
	s.push(head1);      //��Ҫ�жϵıߵ�һ��������ջ��
	visited[head1] = 1; 
	while (!(s.empty())) {  //ջ��Ϊ�գ�
		int cur = s.top();
		s.pop();
		if (cur == head2) return 1; //���������ջ��Ԫ����Ҫ�жϵıߵ���һ�����㣬��ô�ͻ�ɻ���

			for (int i = 0; i < kru->length; i++) {   //���������С�����������бߵĶ���    
				if (cur == kru[i].head1 && visited[kru[i].head2] == 0) {     //���ջ��Ԫ������С������������һ���ߵ�һ�����㲢����һ������û�з���
					s.push(kru[i].head2);             //�Ͱ���һ��������ջ
					visited[kru[i].head2] = 1;
				}
				if (cur == kru[i].head2 && visited[kru[i].head1] == 0) {
					s.push(kru[i].head1);
					visited[kru[i].head1] = 1;
				}
			}
		}

	return 0;

}

void Kruskal(multilist &L,Kruskaltree *kru){ //��³˹�����㷨
	kru->length = 0;
	while (kru->length < L.vernum-1) {          //n�����㣬��ô��С����������n-1���ߣ��±���㿪ʼ��
		int min = max;
		int head1 = -1;
		int head2 = -1;
		for (int i = 0; i < L.vernum; i++) {        //�������ж���ı�
			sidenode* p = L.vertics[i].firstside;
			while (p) {
				if (p->weight < min && compare(p->head1, p->head2, kru) == 0 && p->visited == 0) {   //�ҵ����ж����Ȩֵ��С�ı�,������������û�б�������С��������Ҳ����û�б����ʣ�
					min = p->weight;  //�޸����±ߵ�Ȩֵ���������㣻
					head1 = p->head1;
					head2 = p->head2;

				}
				if (i == p->head1) {
					p = p->head1next;
				}
				else {
					p = p->head2next;
				}

			}
		}
		for (int i = 0; i < L.vernum; i++) {        
			sidenode* q = L.vertics[i].firstside;
			while (q) {
				if (q->head1 == head1 && q->head2 == head2) q->visited = 1;    //���ҵ�����С�ı��޸�Ϊ�Ѿ����ʹ���
				if (i == q->head1) {
					q= q->head1next;
				}
				else {
					q = q->head2next;
				}

			}
		}

		kru[kru->length].head1 = head1;       //���ҵ������ж�����Ȩֵ��С�ıߵ������������ż��룻Ҳ���ǰ������߼�����С�������У�
		kru[kru->length].head2 = head2;
		kru->length++;



	}

}

void displayKruskal(multilist &L,Kruskaltree *kru) {   //��ӡ��С�������������Ե���ʽ��
	for (int i = 0; i < kru->length ; i++) {
		cout << "(" << L.vertics[kru[i].head1].headdata << "," << L.vertics[kru[i].head2].headdata<< ")" << endl;
	}

}
int main() {
	multilist L;
	creatmultilist(L, 4, 5);
	display(L);
	Kruskaltree kru[max] = {0};
	Kruskal(L, kru);
	cout << "��С��������" << endl;
	displayKruskal(L, kru);



	return 0;
}

