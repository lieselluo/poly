#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>

typedef struct PolyNode_ {
	int coef;
	int expn;
	struct PolyNode_ *next;
} PolyNode, *LinkList, Link;

LinkList L[10];

void jianli(int i)//LinkList A)
{
	LinkList p, head, rear, record,A;
	char c;
	A = head = rear = (LinkList)malloc(sizeof(struct PolyNode_));
	record = A;//记录头结点
	A->coef = 0;
	A->expn = 0;
	head->next = NULL;
	rear->next = NULL;
	int count = 0;//位数
	int k = 1;//正负
	printf("请输入多项式：\n");
	c = getchar();
	c = getchar();
	while (c != '\n') {
		if (c == 'x' || c == '*') {
			c = getchar();
			continue;
		}
		if (c == '+' || c == '-' || A->next == NULL) {
			p = (LinkList)malloc(sizeof(struct PolyNode_));
			p->coef = 0;
			p->expn = 0;
			p->next = NULL;
			rear->next = p;
			rear = p;
			rear->coef = 0;
			rear->expn = 0;

			if (c == '-') {
				k = -1;
				c = getchar();
				count = 0;
				continue;
			}
			if (c != '+'&&c != '-') {
				int temp = c - '0';
				rear->coef = rear->coef + temp * pow(10, count)*k;
			}
			c = getchar();
		}
		else if (c == '^') {//不考虑指数为负
			count = 0;
			c = getchar();
			while (c > '0'&&c <= '9') {
				int temp = c - '0';
				rear->expn = rear->expn + temp * pow(10, count);
				count++;
				c = getchar();//多扫了一个怎么办啊？
			}
			count = 0;
			continue;
		}
		else if (c > '0'&&c <= '9') {//add
			int temp = c - '0';
			rear->coef = rear->coef + temp * pow(10, count)*k;
			count++;
			c = getchar();
			continue;
		}

		//-222*x^2+1*x+3
	}
	rear->next = NULL;
	A = record;
	L[i] = A;
	printf("建立完成\n");
}

void xiaohui(LinkList A) {
	LinkList p, h;
	p = h = A;
	while (p) {
		p = p->next;
		free(h);
		h = p;
	}
}
void qingkong(LinkList A) {
	LinkList p, h;
	p = h = A->next;
	while (p) {
		p = p->next;
		free(h);
		h = p;
	}
}

void xianshi(LinkList A) {
	LinkList p;
	printf("start:\n");
	p = A->next;
	while (p != NULL) {
		printf("+%dx^%d", p->coef, p->expn);
		p = p->next;
	}
	printf("\n");
}

void jiafa(LinkList A, LinkList B) {
	LinkList p, q, a, b, t;
	int s;
	p = A->next;
	q = B->next;
	a = A;
	free(B);
	while (p&&q) {
		if (p->expn>q->expn) {
			a = p;
			p = p->next;
		}
		else if (p->expn == q->expn) {
			s = p->coef + q->coef;
			if (s != 0) {
				p->coef = s;
				b = q;
				a = p;
				p = p->next;
				q = q->next;
				free(b);
			}
			else {
				t = p;
				p = p->next;
				a->next = p;
				free(t);
				b = q;
				q = q->next;
				free(b);
			}
		}
		else {
			b = q;
			q = q->next;
			b->next = p;
			a->next = b;
			a = a->next;
		}
	}
	if (q != NULL)
		a->next = q;
}

void jianfa(LinkList A, LinkList B) {
	LinkList p, q, a, b, t;
	int s;
	p = A->next;
	q = B->next;
	a = A;
	free(B);
	while (p&&q) {
		if (p->expn>q->expn) {
			a = p;
			p = p->next;
		}
		else if (p->expn == q->expn) {
			s = p->coef - q->coef;
			if (s != 0) {
				p->coef = s;
				b = q;
				a = p;
				p = p->next;
				q = q->next;
				free(b);
			}
			else {
				t = p;
				p = p->next;
				a->next = p;
				free(t);
				b = q;
				q = q->next;
				free(b);
			}
		}
		else {
			b = q;
			q = q->next;
			b->next = p;
			a->next = b;
			a = a->next;
		}
	}
	if (q != NULL)
		a->next = q;
}

void chengfa(LinkList &A, LinkList &B, LinkList &head) {
	LinkList C, b, p, t, x, h0, h;
	head = C = (LinkList)malloc(sizeof(struct PolyNode_));
	h0 = h = (LinkList)malloc(sizeof(struct PolyNode_));
	p = A->next;
	b = B->next;
	while (p) {
		C->next = t = (LinkList)malloc(sizeof(struct PolyNode_));
		t->coef = p->coef*b->coef;
		t->expn = p->expn + b->expn;
		p = p->next;
		C = C->next;
	}
	C->next = NULL;
	//printf("1\n");
	//shuchu(head);
	for (b = b->next;b;b = b->next) {
		h = h0;
		p = A->next;
		//printf("循环\n");
		while (p) {
			h->next = x = (LinkList)malloc(sizeof(struct PolyNode_));
			x->coef = p->coef*b->coef;
			x->expn = p->expn + b->expn;
			p = p->next;
			h = h->next;
		}
		h->next = NULL;
		jiafa(head, h0);
	}
	//printf("2\n");
	//shuchu(head);
}

void qiudao1(LinkList A) {
	LinkList p, h;
	p = A->next;
	h = A;
	while (p) {
		p->coef = p->coef*p->expn;
		p->expn = p->expn - 1;
		if (p->expn<0) {
			h->next = NULL;
			break;
		}
		p = p->next;
		h = h->next;
	}
}

void qiudao(LinkList A, int n) {
	while (n) {
		n = n - 1;
		qiudao1(A);
	}
}

int qiuzhi(LinkList A, int x) {
	LinkList p;
	int y = 0, z = 1;
	p = A->next;
	while (p) {
		while (p->expn) {
			z = z*x;
			p->expn = (p->expn - 1);
		}
		z = z*(p->coef);
		y = (y + z);
		p = p->next;
	}
	return(y);
}
void charu(LinkList A, int m, int n) {
	LinkList p, q;
	int k = 1;
	p = A->next;
	q = (LinkList)malloc(sizeof(struct PolyNode_));
	if (m<0) {
		k = -1;
	}
	if (n>0 && n <= 9) {
		q->coef = m*k;
	}
	q->expn = n;
	q->next = p->next;
	p->next = q;
}
void shanchu(LinkList A, int i)
{
	LinkList p, q;
	int j = 0;
	p = A;
	while (p->next&&j<i - 1)
	{
		p = p->next;++j;
	}
	if (!(p->next) || j>i - 1)
		return;
	q = p->next;p->next = q->next;
	free(q);
	return;
}
void xiugai(LinkList A, int k, int m, int n)
{
	LinkList p;
	int j = 0;
	p = A;
	while (p->next&&j<k - 1)
	{
		p = p->next;++j;
	}
	if (!(p->next) || j>k - 1)
		return;
	p->coef = m;
	p->expn = n;
	return;
}
void fz(LinkList A, LinkList &B) {
	LinkList p, q, h, z;
	p = A->next;
	B = (LinkList)malloc(sizeof(struct PolyNode_));
	q = (LinkList)malloc(sizeof(struct PolyNode_));
	B->next = q;
	z = B;
	while (p) {
		q->coef = p->coef;
		q->expn = p->expn;
		p = p->next;
		h = (LinkList)malloc(sizeof(struct PolyNode_));
		q->next = h;
		q = q->next;
		z = z->next;
	}
	free(q);
	z->next = NULL;
	printf("复制完成\n");
}


int main() {
	for (int i = 0;i < 10;i++)
		L[i] = NULL;
	int c = 1, i, j, k, n, x, y, m;
	while (c != 0) {
		printf("输入要进行的操作\n");
		printf("0.结束\n1.创建多项式\n2.显示多项式\n3.复制多项式\n4.求和\n5.求差\n6.求值\n7.销毁\n8.清空\n91.插入\n92.删除\n93.修改\n10.乘法\n11.求导\n");
		scanf("%d", &c);
		switch (c) {
		case 0:
			return(0);
		case 1:   //Input A
			printf("输入i的位置，将在L[i]位置创建多项式:\n");
			scanf("%d", &i);
			jianli(i);
			break;
		case 2:
			printf("输入显示的多项式L[i]\n");
			scanf("%d", &i);
			xianshi(L[i]);
			break;
		case 3:
			printf("输入多项式名称，以空格隔开\n");
			scanf("%d %d", &i, &j);
			if (i >= 0 && i <= 9 && j >= 0 && j <= 9) {
				fz(L[i], L[j]);
				xianshi(L[i]);
				xianshi(L[j]);
			}
			break;
		case 4:
			printf("输入要进行加法的多项式名称\n");
			scanf("%d %d", &i, &j);
			jiafa(L[i], L[j]);
			xianshi(L[i]);
			break;

		case 5:
			printf("输入要进行减法的多项式名称\n");
			scanf("%d %d", &i, &j);
			jianfa(L[i], L[j]);
			xianshi(L[i]);
			break;
		case 6:
			printf("输入多项式L[i]\n");
			scanf("%d", &i);
			printf("输入x的值\n");
			scanf("%d", &x);
			y = qiuzhi(L[i], x);
			printf("y=%d", y);
			break;

		case 7:
			printf("输入要销毁的多项式名称\n");
			scanf("%d", &i);
			xiaohui(L[i]);
			xianshi(L[i]);
			break;

		case 8:
			printf("输入要清空的多项式名称\n");
			scanf("%d", &i);
			qingkong(L[i]);
			break;

		case 91:
			printf("输入要插入的多项式名称\n");
			scanf("%d", &i);
			printf("输入插入项的系数和指数\n");
			scanf("%d %d", &m, &n);
			charu(L[i], m, n);
			break;
		case 92:
			printf("输入要删除的多项式名称\n");
			scanf("%d", &i);
			printf("输入要删除第几项\n");
			scanf("%d", &n);
			shanchu(L[i], n);
		case 93:
			printf("输入要修改的多项式名称\n");
			scanf("%d", &i);
			printf("输入要修改第几项\n");
			scanf("%d", &k);
			printf("输入修改项的系数和指数\n");
			scanf("%d %d", &m, &n);
			xiugai(L[i], k, m, n);
			break;
		case 10:
			printf("输入要进行乘法的多项式名称\n");
			scanf("%d %d %d", &i, &j, &k);
			chengfa(L[i], L[j], L[k]);
			xianshi(L[k]);
			break;
		case 11:
			printf("输入要求导的多项式名称\n");
			scanf("%d", &i);
			printf("输入n的值\n");
			scanf("%d", &n);
			qiudao(L[i], n);
			break;
		default:
			return(0);
		}
	}
	return(0);
}

