
								/*This PROGRAM is perfect for INSERTION BALANCING */

#include<iostream>
#include<stdlib.h>
#include<math.h>
using namespace std;

struct Node
{
	int data;
	Node* left;
	Node* right;
};

struct Node2
{	
	Node* data;
	Node2* next;
};
Node2* root=NULL;

class c1
{
	public:
	int data,Cleft,Cright;
	Node* head;
	Node* pNode;
	bool b1;	
};

Node* HEAD=NULL;
int Insert(int d);
int Print(Node* head);
int Balancing(c1 cc);
int orientation(Node* p, int t );
c1 check(c1 cc);
int max(int t1 , int t2);
int left_left(Node* p);
int left_right(Node* p);
int right_left(Node* p);
int right_right(Node* p);
bool treverse(Node* p,Node* head,Node* temp);
void enque(Node* temp);
Node* deque();
void SPrint();
int power=0;
int main()
{
	int t=0;
	for(;;)
	{
		cout<<"\n	Enter INPUT :- ";
		cin>>t;cout<<"\n";
		Insert(t);
		cout<<"\n\n";	enque(HEAD);power=0;
			SPrint();	cout<<"\n\n";
		c1 cc;
		cc.b1=false;cc.Cleft=0;cc.Cright=0;cc.data=t;cc.head=HEAD;cc.pNode=NULL;
		cc=check(cc);
		cc.Cleft=0;cc.Cright=0;cc.head=HEAD;
		if(cc.b1)
		{
			cc.b1=false;
			cout<<"\n		UnBALANCED!!!!!! ="<<cc.pNode->data<<"\n";
			Balancing(cc);
			enque(HEAD);power=0;
			SPrint();
			//SPrint();
			cc.pNode=NULL;
			cc.head=HEAD;
			cc=check(cc);
			if(!cc.b1)cout<<"\n\n			Balancing done!!!!!\n\n";
			else cout<<"\n\n 	Not Balanced Yet	!!!	\n";	
		}
		
	}
	return 0;
}

int Insert(int d)
{
	Node* temp1;
	temp1=(Node*)malloc(sizeof(Node));
	temp1->left=NULL;
	temp1->right=NULL;
	temp1->data=d;
		
	Node* temp=HEAD;
	
	if(HEAD==NULL)
	{
		HEAD=temp1;
		return 0;
	}
	
	for(;;)
	{
		if(temp->data<d){if(temp->right==NULL){temp->right=temp1;return 0;}temp=temp->right;}
		else if(temp->data>d){if(temp->left==NULL){temp->left=temp1;return 0;}temp=temp->left;}
		else if(temp->data=d){cout<<"\n		Already Exists this val :-!!!! ";return 0;}
	}
}

int Print(Node* head)
{
	//cout<<"ll";
	if(head->left==NULL && head->right==NULL)
	{
		cout<<head->data<<"	";
		return 0;
	}
	if(head->left!=NULL)Print(head->left);
	if(head->right!=NULL)Print(head->right);
	cout<<head->data<<"	";
	return 0;
}

c1 check(c1 cc)
{
	c1 m=cc;
	if((cc.head->left==NULL&&cc.head->right==NULL) || cc.b1==true)return cc;

	if(cc.head->left!=NULL)
	{
		m.head=m.head->left;
		m=check(m);
		cc.b1=m.b1;
		cc.pNode=m.pNode;
		if(cc.b1)return cc;
		cc.Cleft=max(m.Cleft,m.Cright)+1;		
	}
	
	m=cc;
	m.Cleft=0;
	
	if(cc.head->right!=NULL)
	{
		m.head=m.head->right;
		m=check(m);
		cc.b1=m.b1;
		cc.pNode=m.pNode;
		if(cc.b1)return cc;
		cc.Cright=max(m.Cleft,m.Cright)+1;		
	}
	if((cc.Cleft-cc.Cright>1 || cc.Cright-cc.Cleft>1 )&& !cc.b1)
	{
		cc.b1=true;
		cc.pNode=cc.head;
	}
	return cc;
}


int max(int t1 , int t2)
{
	if(t1>t2)return t1;
	return t2;
}

int Balancing(c1 cc)
{	
	int tt= orientation(cc.pNode , cc.data);
	switch(tt)
	{
		case 11: cout<<"\n\n			LEFT_LEFT\n\n";left_left(cc.pNode);break;
		case 12: cout<<"\n\n			LEFT_RIGHT\n\n";left_right(cc.pNode);break;
		case 21: cout<<"\n\n			RIGHT_LEFT\n\n";right_left(cc.pNode);break;
		case 22: cout<<"\n\n			RIGHT_RIGHT\n\n";right_right(cc.pNode);break;
	} 
	return tt;
}

int orientation(Node* p , int t)
{
	int tt=0;
	if(p->data>t)	{p=p->left; tt=tt+10; }
	else if(p->data<t)	{p=p->right; tt=tt+20; }
	if(p->data>t)	{p=p->left; tt=tt+1; }
	else if(p->data<t)	{p=p->right; tt=tt+2; }
	return tt;	
}

int right_right(Node* p)
{
	Node* temp=p->right;
	p->right=p->right->left;
	temp->left=p;
	if(p==HEAD)HEAD=temp;
	else{treverse(p,HEAD,temp);}
	return 1;	
}

int left_right(Node* p)
{
	right_right(p->left);
	left_left(p);
	return 1;	
}

int right_left(Node* p)
{
	left_left(p->right);
	right_right(p);
	return 1;	
}

int left_left(Node* p)
{
	Node* temp=p->left;
	p->left=p->left->right;
	temp->right=p;
	if(p==HEAD)HEAD=temp;
	else{treverse(p,HEAD,temp);}
	return 1;
}
	
bool treverse(Node* p, Node* head,Node* temp)
{
	if(head->left==p){head->left=temp;return true;}
	else if(head->right==p){head->right=temp;return true;}
	if(head->left!=NULL)if(treverse(p,head->left,temp))return true;
	if(head->right!=NULL)if(treverse(p,head->right,temp))return true;
	return false;
}

void enque(Node* temp)
{
	
	Node2* tt=new Node2;
	tt->data=temp;
	tt->next=NULL;
	Node2* t1=root;
	if(root ==NULL)root=tt;
	else
	{
		while(t1->next!=NULL)t1=t1->next;
		t1->next=tt;
	}
}

Node* deque()
{
	if(root==NULL)return NULL;
	Node2* temp2=root;
	Node* temp=root->data;
	root=root->next;
	delete temp2;
	return temp;
}

void SPrint()
{
	int gap=61/(int)(pow(2,power)+1);		
	cout<<"\n\n";
	if(root==NULL)return;
	for(int t=0;t<pow(2,power);t++)
	{
		for(int t1=0;t1<gap;t1++)cout<<" ";
		Node* head=deque();
		if(head==NULL){cout<<" ";
		continue;}
		cout<<head->data;
		enque(head->left);
		enque(head->right);
	}
	power++;
	SPrint();
}
