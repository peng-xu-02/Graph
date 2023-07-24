//��������Ӧ���������޻�ͼ��AOV����һ������ͼ��ʾһ�����̣����ж����ʾ����߻��߻���ʾ�֮����Ⱥ���Լ��ϵ����������֮ΪAOV����
#include<iostream>
using namespace std;
typedef char Elemtype;
#define max 20

typedef struct sidenode {      //�߽ڵ㣻
	int weight;
	int headadjex, tailadjex;
	struct sidenode* indegreenext, * outdegreenext;
}sidenode;

typedef struct headnode {     //ͷ�ڵ㣻
	Elemtype data;
	sidenode* indegreefirst, * outdegreefirst;
	bool visited;
}headnode;

typedef struct Orthoanilist {      //ʮ������
	headnode* vertics;
	int vernum, arcnum;
}Orthoanilist;

Elemtype list[max];    //�洢�������е����飻
int length = 0;     //�������еĳ��ȣ�

void Select(Orthoanilist& L, Elemtype data1, Elemtype data2, int& head, int& tail) {
	for (int i = 0; i < L.vernum; i++) {
		if (data1 == L.vertics[i].data)  head = i;
		if (data2 == L.vertics[i].data)  tail = i;
	}
}

void creatlist(Orthoanilist &L,int m,int n){    //����ʮ������
	if (m < 1 || n < 0) return;
	L.vertics = new headnode[m];
	L.vernum = m;
	L.arcnum = n;
	for (int i = 0; i < m; i++) {
		cout << "�������" << i + 1 << "����������ݣ�" << endl;
		cin >> L.vertics[i].data;
		L.vertics[i].visited = false;
		L.vertics[i].indegreefirst = NULL;
		L.vertics[i].outdegreefirst = NULL;
	}
	for (int i = 0; i < n; i++) {
		cout << "�������" << i + 1 << "���ߵı��ף���β�ͱ�Ȩֵ��" << endl;
		Elemtype data1, data2;
		int weight;
		int head, tail;
		cin >> data1 >> data2 >> weight;
		Select(L, data1, data2, head, tail);
		sidenode* p = new sidenode;
		p->headadjex = head;
		p->tailadjex = tail;
		p->weight = weight;
		//β�巨����ڵ㣻
		if (L.vertics[head].outdegreefirst == NULL) {  //���ͷ�ڵ�ĳ��ȱ�Ϊ�գ���ôֱ�ӽ����ȱ߲��룻
			L.vertics[head].outdegreefirst = p;
			p->outdegreenext = NULL;
		}else {
			sidenode* q = L.vertics[head].outdegreefirst;       //�ҵ����һ���ڵ㣬���߲��뵽��֮��
			while (q->outdegreenext) {
				q = q->outdegreenext;
			}
			q->outdegreenext= p;
			p->outdegreenext = NULL;
			
		}
		if (L.vertics[tail].indegreefirst == NULL) {
			L.vertics[tail].indegreefirst = p;
			p->indegreenext = NULL;
		}
		else {
			sidenode* q = L.vertics[tail].indegreefirst;
			while (q->indegreenext) {
				q = q->indegreenext;
			}
			q->indegreenext = p;
			p->indegreenext = NULL;
		}
	
	}

}


void pop(Orthoanilist& L, Elemtype data) {  //ɾ���ڵ�����бߣ�
	int adjex = -1;
	for (int i = 0; i < L.vernum; i++) {
		if (data == L.vertics[i].data)  adjex = i;    //�ҵ�Ҫɾ���ߵĶ����±ꣻ
	}
	sidenode* p = L.vertics[adjex].outdegreefirst;    //��iΪ���׵ı�
	sidenode* p1= L.vertics[adjex].indegreefirst;     //��iΪ��β�ı�
	while (p) {
		sidenode* q = p;       //����һ��ָ���pָ��ͬһ��λ�ã�����֮��ɾ��p����Ϊ���ʹ��p����ı߽ڵ��Ҳ�����
		L.vertics[adjex].outdegreefirst = p->outdegreenext;    //ͷ�ڵ�ָ��Ҫɾ����p����һ����;
		sidenode* m = L.vertics[p->tailadjex].indegreefirst;   //�ҵ���Ҫɾ���Ľڵ�Ϊ���׵ıߣ��ҵ���β��
		while (m) {
			if (m->headadjex == adjex)  break;    //�ҵ���β�ڵ���Ӧ��Ҫɾ���Ľڵ�֮��ıߣ�
			m = m->indegreenext;

		}
		if (m == L.vertics[p->tailadjex].indegreefirst) {   //����ҵ��ı��ǵ�һ���߽ڵ㣬��ֱ���޸�ͷ�ڵ��ָ��
			L.vertics[p->tailadjex].indegreefirst = m->indegreenext;
		}
		else {
			sidenode *n= L.vertics[p->tailadjex].indegreefirst;      //�ҵ�Ҫɾ���ıߵ�ǰһ���߽ڵ�
			while (n->indegreenext!=m) {
				n = n->indegreenext;
			}
			n->indegreenext = m->indegreenext;            //�޸�ǰһ���߽ڵ����һ����ָ��
		}
		p = p->outdegreenext;
		delete q;      //ɾ�������ߣ�ע��һ��Ҫ�Ƚ�pָ����һ���ڵ����ɾ������ڵ㣻

	}
	while (p1) {
		sidenode* q = p1;
		L.vertics[adjex].indegreefirst = p1->indegreenext;
		sidenode* m = L.vertics[p1->headadjex].outdegreefirst; // �ҵ�ͷ���ĳ��ȱ�ĵ�һ�����
		while (m) {
			if (m->tailadjex== adjex)  break;
			m = m->outdegreenext;

		}
		if (m == L.vertics[p1->headadjex].outdegreefirst) {
			L.vertics[p1->headadjex].outdegreefirst = m->outdegreenext;
		}
		else {
			sidenode* n = L.vertics[p1->headadjex].outdegreefirst;
			while (n->outdegreenext!=m) {
				n = n->outdegreenext;
			}
			n->outdegreenext = m->outdegreenext;
		}


		p1 = p1->indegreenext;
		delete q;

	}
}

void tuopusort(Orthoanilist &L) {    //���������㷨
	memset(list, -1, sizeof(list));
	bool flag = true;    //һ������Ƿ������ݱ仯�ı�־��
	while (flag) { 
		flag = false;
		for (int i = 0; i < L.vernum; i++) {
			if (L.vertics[i].indegreefirst == NULL && L.vertics[i].visited==false) {
				list[length] = L.vertics[i].data;
				L.vertics[i].visited = true;
				pop(L, L.vertics[i].data);
				length++;
				flag = true;

			}

		}

	}
}

void display(Orthoanilist& L) { //��ӡʮ������
	for (int i = 0; i < L.vernum; i++) {
		cout << "�±꣺" << i << "���㣺" << L.vertics[i].data<<endl;
		cout << "��" << L.vertics[i].data << "Ϊ���׵ıߣ�";
		sidenode* p = L.vertics[i].outdegreefirst;
		while (p) {
			cout << "(" << L.vertics[p->headadjex].data << "->" << L.vertics[p->tailadjex].data << ")"<<" ";
			p = p->outdegreenext;
		}
		cout << endl;
	}
}

void displaytuopu(Orthoanilist &L) {   //��ӡ��������
	for (int i = 0; i < length; i++) {
		cout << list[i] << "->";
	}
	cout << endl;
	if (length < L.vernum)  cout << "��ͼ���ڻ���";

}

int main() {
	Orthoanilist L;
	int m, n;
	cout << "�������ܶ��������ܱ�����" << endl;
	cin >> m >> n;
	creatlist(L, m, n);
	display(L);
	tuopusort(L);
	cout << "��������Ϊ��" << endl;
	displaytuopu(L);


	return 0;
}