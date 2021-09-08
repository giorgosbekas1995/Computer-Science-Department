/**********************************************************************
 * @file   santa_claus.c                                              *
 * @author Papaioannou Antonis <papaioan@csd.uoc.gr>				  *
 *                                                                    *
 * @brief  Main file for the needs of the Data Structures (HY-240a)   *
 * project (Fall 2015)                                                *
 * version 20151213 (13-Dec-2015)									  *
 * Computer Science Department, University of Crete, Greece           *
**********************************************************************/

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "santa_claus.h"

#define LEN(x) (sizeof(x) / sizeof(*(x)))

char *tokens[128];
int asint[LEN(tokens)];

struct child *Age_categories[N];
/* global variable pointing to the root of stock tree */
struct present *stock_R;
/*global variable pointinh to the sentinel node of stock tree */
struct present *stock_S;

int cnt1=0,cnt2=0,cnt3=0,cnt4=0;
int cnt5=0,cnt6=0,cnt7=0,cnt8=0;
struct district *head;
struct present_assign *head2;

struct present* Insert(struct present* root, int pid,int stock){
  if(root == NULL)
  {
     root = (struct present*)malloc(sizeof(struct present));
    root->stock_cnt=stock;
    root->request_cnt=0;
    root->parent=root;
    root->pid = pid;
    root->lc = stock_S;
 	root ->rc = stock_S;

  }
  else
  {
    if(pid <= root->pid)
    { 
      root->lc = Insert(root->lc, pid,stock);
    }
    else
    {
      root->rc = Insert(root->rc, pid,stock);
    }
   
  }
  return root;
}
void preOrderPrint(struct present *p){
 struct present *q=p;
 if(q==stock_S) return;
 
 printf(" <%d:%d> ",q->pid,q->stock_cnt);
 preOrderPrint(q->lc);
 preOrderPrint(q->rc);
 
 
 
}

void preOrderSearchPresent(struct present *p,int pid1,int pid2,int pid3){
 struct present *q=p;
 if(q==stock_S) return;
 
 if(q->pid==pid1){
 	cnt1=1;
	q->request_cnt++;
 }
 if(q->pid==pid2){
 	cnt2=1;
	q->request_cnt++;
 }
 if(q->pid==pid3){
 	cnt3=1;
	q->request_cnt++;
 }
 preOrderSearchPresent(q->lc,pid1,pid2,pid3);
 preOrderSearchPresent(q->rc,pid1,pid2,pid3);
 
 
}


void preOrderPrintChild(struct child *p){
int i;	

struct child* q=p;
 if(q==NULL) return;
 
 printf("%d ",q->cid);
 preOrderPrintChild(q->lc);
 preOrderPrintChild(q->rc);
 

}


void preOrderGivePresent(struct present *p,struct child *k){
 struct present *q=p;
 if(q==stock_S) return;
 
 if(q->pid==k->present_choices[0]){
 	cnt5=q->stock_cnt;
 }else
 if(q->pid==k->present_choices[1]){
 	cnt6=q->stock_cnt;
 }else
 if(q->pid==k->present_choices[2]){
 	cnt7=q->stock_cnt;	
 }else{
 	cnt8=4;
 }
 preOrderGivePresent(q->lc,k);
 preOrderGivePresent(q->rc,k);
 
 
 
}





struct child* InsertChild(struct child* root,int cid, int age,int did, int pid1, int pid2, int pid3){
  if(root == NULL)
  {
    root = (struct child*)malloc(sizeof(struct child));
    root->cid=cid;
    root->age=age;
    root->did=did;
   	root->present_choices[0]=pid1;
   	root->present_choices[1]=pid2;
   	root->present_choices[2]=pid3;
    root->lc = NULL;
 	root ->rc = NULL;

  }
  else
  
  {
    if(cid <= root->cid)
    { 
      root->rc = InsertChild(root->rc,cid,age,did,pid1,pid2,pid3);
    }
    else 
    {
      root->lc = InsertChild(root->lc,cid,age,did,pid1,pid2,pid3);
    }
   
  }
  return root;
}



void preOrderSearchChild(struct child *p){
int i;	
struct district *temp=head;
struct child* q=p;
 if(q==NULL) return;


preOrderGivePresent(stock_R,q);


while(temp!=NULL){
	if(q->did==temp->did){
		printf("<%d>\n",temp->did);
	if(cnt5>0){
		temp->assignHT = (struct present_assign*)malloc(sizeof(struct present_assign));
		temp->assignHT->pid=q->present_choices[0];
		temp->assignHT->cid=q->cid;
		temp->assignHT->next=head2;
		head2=temp->assignHT;
		printf("Assigment: <%d , %d>\n",temp->assignHT->cid,temp->assignHT->pid);
	cnt5--;
	break;
	}
	if(cnt6>0){
		temp->assignHT = (struct present_assign*)malloc(sizeof(struct present_assign));
		temp->assignHT->pid=q->present_choices[1];
		temp->assignHT->cid=q->cid;
		temp->assignHT->next=head2;
		head2=temp->assignHT;
		printf("Assigment: <%d , %d>\n",temp->assignHT->cid,temp->assignHT->pid);
	cnt6--;
	break;
	}
	if(cnt7>0){
		temp->assignHT = (struct present_assign*)malloc(sizeof(struct present_assign));
		temp->assignHT->pid=q->present_choices[2];
		temp->assignHT->cid=q->cid;
		temp->assignHT->next=head2;
		head2=temp->assignHT;
		printf("Assigment: <%d , %d>\n",temp->assignHT->cid,temp->assignHT->pid);
	cnt7--;
	break;
	}
	if(cnt8=4){
		temp->assignHT = (struct present_assign*)malloc(sizeof(struct present_assign));
		temp->assignHT->pid=-2;
		temp->assignHT->cid=q->cid;
		temp->assignHT->next=head2;
		head2=temp->assignHT;
		printf("Assigment: <%d , %d>\n",temp->assignHT->cid,temp->assignHT->pid);
	break;
	}
		}
	temp=temp->next;
}

 preOrderSearchChild(q->lc);
 preOrderSearchChild(q->rc);
}

void preOrderDegreeChild(struct child *p,int cid,int did,int degree){
int i;	
struct district *temp=head;
struct child* q=p;
 if(q==NULL) return;

if(q->did==did){
while(temp!=NULL){
	if(temp->did==did&&temp->assignHT->cid==cid){
if(temp->assignHT->pid=q->present_choices[0]){
	temp->assignHT->s_degree=5;
	printf("F <%d> <%d> <%d>\n\nDONE\n\n",temp->assignHT->cid,temp->assignHT->s_degree,temp->assignHT->pid);
	break;
}
if(temp->assignHT->pid=q->present_choices[1]){
	temp->assignHT->s_degree=4;
	printf("F <%d> <%d> <%d>\n\nDONE\n\n",temp->assignHT->cid,temp->assignHT->s_degree,temp->assignHT->pid);
	break;
}
if(temp->assignHT->pid=q->present_choices[2]){
	temp->assignHT->s_degree=3;
	printf("F <%d> <%d> <%d>\n\nDONE\n\n",temp->assignHT->cid,temp->assignHT->s_degree,temp->assignHT->pid);
	break;
}
if(temp->assignHT->pid=-2){
	temp->assignHT->s_degree=1;
	printf("F <%d> <%d> <%d>\n\nDONE\n\n",temp->assignHT->cid,temp->assignHT->s_degree,temp->assignHT->pid);
	break;
}
	}
		temp=temp->next;
		}

}

 preOrderDegreeChild(q->lc,cid,did,degree);
 preOrderDegreeChild(q->rc,cid,did,degree);
}

int buy_present(int pid, int stock_cnt) {
printf("B <%d> <%d> \n\n Presents=",pid,stock_cnt);
stock_R=Insert(stock_R,pid,stock_cnt);
preOrderPrint(stock_R);
printf("\n\nDONE\n\n");
return 1;
}


int letter_received(int cid, int age, int did, int pid1, int pid2, int pid3) {
	if(age>0&&age<=3){
		Age_categories[0]=InsertChild(Age_categories[0],cid,age,did,pid1,pid2,pid3);
	}else
	if(age>3&&age<=7){
		Age_categories[1]=InsertChild(Age_categories[1],cid,age,did,pid1,pid2,pid3);
	}else
	if(age>7&&age<=11){
		Age_categories[2]=InsertChild(Age_categories[2],cid,age,did,pid1,pid2,pid3);
	}else
	if(age>11&&age<=15){
		Age_categories[3]=InsertChild(Age_categories[3],cid,age,did,pid1,pid2,pid3);
	}
	
	preOrderSearchPresent(stock_R,pid1,pid2,pid3);
	if(cnt1==0){
		buy_present(pid1,10);
	}
	if(cnt2==0){
		buy_present(pid2,10);
	}
	if(cnt3==0){
		buy_present(pid3,10);
	}
	

	
		
		struct district *temp=(struct district*)malloc(sizeof(struct district));
		temp->did = did;
		temp->next=head;
		head = temp;
		
		
		struct district *temp1=head;
		while(temp1!=NULL){
		if(temp1->did==did){
			cnt4=1;
			temp1->children_cnt++;
		}

		temp1=temp1->next;
}



	
	printf("L <%d>, <%d>, <%d>, <%d>, <%d>, <%d>\nDONE\n",cid,age,did,pid1,pid2,pid3);
	return 1;
}

int prepare_presents(void) {
	int i;
	printf("P\n\nDistricts: \n\n");
	for(i=0;i<N;i++){
	preOrderSearchChild(Age_categories[i]);
}

printf("\nDONE\n\n");
	
	
	return 1;
}

int give_feedback(int cid, int did, int s_degree) {
	int i;
	for(i=0;i<N;i++){
	preOrderDegreeChild(Age_categories[i],cid,did,s_degree);
}
	return 1;
}

int analytics(int k) {
	return 1;
}

int new_season(void) {
	return 1;
}

int clear_list_of_children(void) {
	return 1;
}

void SearchPresent(struct present *p,int pid){
 struct present *q=p;
 if(q==stock_S) return;
 
 if(q->pid==pid){
 	
	printf("\n\nS<%d>\n\n<%d> , <%d>\n\nDONE\n\n",q->pid,q->stock_cnt,q->request_cnt);
 }
 
 SearchPresent(q->lc,pid);
 SearchPresent(q->rc,pid);
 
 
}
int search_present(int pid) {
	SearchPresent(stock_R,pid);
	return 1;
}

void PrintChild(struct child *p){
int i;	

struct child* q=p;
 if(q==NULL) return;
 
 printf("<%d:{%d, %d, %d}> ",q->cid,q->present_choices[0],q->present_choices[1],q->present_choices[2]);

 PrintChild(q->lc);
 PrintChild(q->rc);
}

int print_child(void) {
	printf("H\n\n");
	int i;
	for(i=0;i<N;i++){
		if(i==0){
			printf("0-3:  ");
		}
		if(i==1){
			printf("4-7:  ");
		}
		if(i==2){
			printf("8-11:  ");
		}
		if(i==3){
			printf("12-15:  ");
		}
		PrintChild(Age_categories[i]);
		printf("\n");
	}
	printf("\n\nDONE\n\n");
	return 1;
}

int print_district(void) {
	printf("I\n");
 
 struct district *ptr=head;
 struct present_assign *temp=head2;
 printf("DISTRICTS:  \n");
 while(ptr!=NULL&&temp!=NULL){
  printf("<%d>\n",ptr->did);
 printf("ASSIGNMENT:<%d:%d:%d>\n", temp->cid,temp->pid,temp->s_degree);
  
 ptr=ptr->next;
 temp=temp->next;
 }
 printf("\n");
 printf("DONE\n\n");
	return 1;
}

void PrintStock(struct present *p){
 struct present *q=p;
 if(q==stock_S) return;
 
 printf(" <%d:%d> ",q->pid,q->stock_cnt);
 
 PrintStock(q->lc);
 PrintStock(q->rc);
 
 
}

int print_stock(void) {
	printf("T\n\nStock = ");
	PrintStock(stock_R);
	printf("\n\nDONE\n\n");
	return 1;
}

void tokenize(char *s) { /*tokenization of input arguments*/
	char *p, *last;
	int i = 0;
	for ((p = strtok_r(s, " ", &last)); p;
	    (p = strtok_r(NULL, " ", &last))) {
		if (i < LEN(tokens) - 1) {
			tokens[i] = p;
			asint[i] = atoi(p);
			i++;
		}
	}
	tokens[i] = NULL;
}

int main(int argc, char *argv[]) { /*main function*/
	char *prog = argv[0];
	char *file = argv[1];
	char buf[1024];
	FILE *fp;
	int ret;
	char ev;


	if (file == NULL) {
		fprintf(stderr, "Usage: %s file\n", prog);
		return 1;
	}

	fp = fopen(file, "r");
	if (fp == NULL) {
		fprintf(stderr, "fopen %s: %s\n", file, strerror(errno));
		return 1;
	}

	while (fgets(buf, sizeof(buf), fp) != NULL) {
		buf[strcspn(buf, "\n")] = '\0';
		tokenize(buf);
		ev = *tokens[0];

		switch (ev) {
		case 'B':
			ret = buy_present(asint[1], asint[2]);
			break;
		case 'L':
			ret = letter_received(asint[1], asint[2], asint[3], asint[4], asint[5], asint[6]);
			break;
		case 'P':
			ret = prepare_presents();
			break;
		case 'F':
			ret = give_feedback(asint[1], asint[2], asint[3]);
			break;
		case 'A':
			ret = analytics(asint[1]);
			break;
		case 'N':
			ret = new_season();
			break;
		case 'C':
			ret = clear_list_of_children();
			break;
		case 'S':
			ret = search_present(asint[1]);
			break;
		case 'H':
			ret = print_child();
			break;
		case 'I':
			ret = print_district();
			break;
		case 'T':
			ret = print_stock();
			break;
		default:
			fprintf(stderr, "Invalid event");
			return 1;
		}
		fprintf(stderr, "Event '%c' %s\n", ev, ret ? "passed" : "failed");
	}
	return 1;
}

