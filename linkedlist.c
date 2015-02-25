#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <limits.h>

#define type int

typedef struct Node Node;
typedef struct List List;

struct Node {
	type value;
	Node *prev,*next;
};

struct List{
	int size;
	Node *head,*tail;
};

Node * Make_Node(type value){
	Node *res=(Node*) malloc(sizeof(Node));
	res->value=value;
	res->next=NULL;
	res->prev=NULL;
	return res;
}

Node *Concat_Node(Node *x, Node *y){
	x->next=y;
	y->prev=x;
	return x;
}

List *Make_List(){
	List *res=(List*) malloc(sizeof(List));
	res->head=NULL;
	res->tail=NULL;
	res->size=0;
	return res;
}

Node * List_PushBack(List *lst, type value){
	Node *tmp=Make_Node(value);
	if(lst->size==0){
		lst->head=lst->tail=tmp;
	}else {
		Concat_Node(lst->tail,tmp);
		lst->tail=tmp;
	}
	lst->size++;
	return tmp;
}


Node * List_PushFront(List *lst, type value){
	Node *tmp=Make_Node(value);
	if(lst->size==0){
		lst->head=lst->tail=tmp;
	}else {
		Concat_Node(tmp,lst->head);
		lst->head=tmp;
	}
	lst->size++;
	return tmp;
}

void List_PopBack(List *lst){
	if(lst->size>1){
		Node *tmp=lst->tail->prev;
		free(lst->tail);
		tmp->next=NULL;
		lst->tail=tmp;
		lst->size--;
	}else if(lst->size==1){
		free(lst->tail);
		lst->head=NULL;
		lst->tail=NULL;
		lst->size--;
	}
}

void List_PopFront(List *lst){
	if(lst->size>1){
		Node *tmp=lst->head->next;
		free(lst->head);
		tmp->prev=NULL;
		lst->head=tmp;
		lst->size--;
	}else if(lst->size==1){
		free(lst->tail);
		lst->head=NULL;
		lst->tail=NULL;
		lst->size--;
	}
}


int main() {
	
	List *lst=Make_List();
	
	List_PushBack(lst,1);
	List_PushBack(lst,2);
	List_PopBack(lst);
	List_PushFront(lst,3);
	List_PushFront(lst,4);
	
	List_PopBack(lst);
	
	Node *t=lst->head;
	while(t){
		printf("%d\n",t->value);
		t=t->next;
	}
	return 0;
}
