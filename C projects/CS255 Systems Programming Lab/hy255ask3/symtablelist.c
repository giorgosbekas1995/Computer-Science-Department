#include "symtablelist.h"





SymTable_T   SymTable_new(void){
	SymTable_T Newnode;
	SymTable_T	head;
	
	Newnode=(struct SymTable*)malloc(sizeof(struct SymTable));
	if(Newnode == NULL){
		printf("allocation failed");
		return 0;
	}
	
	Newnode->key=NULL;
	Newnode->value=NULL;
	Newnode->lenght=0;
	Newnode->next=NULL;
	head=Newnode;
	
	return head;
}

void  SymTable_free(SymTable_T oSymTable){
	SymTable_T temp=NULL;

	if(oSymTable==NULL){
		return;
	}

	while(oSymTable!=NULL){
		temp=oSymTable;
		oSymTable=oSymTable->next;
		free(temp);
	}
	free(oSymTable);

}

unsigned int SymTable_getLength(SymTable_T oSymTable){
	assert(oSymTable != NULL);
	return oSymTable->lenght;
}






 int SymTable_put(SymTable_T oSymTable, const char *pcKey,const void *pvValue){
	SymTable_T temp;
 	assert(oSymTable!=NULL);
 	assert(pcKey!=NULL);
	

	if(SymTable_contains(oSymTable,pcKey)){
		return 0;
	}
	temp=(struct SymTable*)malloc(sizeof(struct SymTable));
	
	if(temp==NULL){
		printf("allocation failed");
		return 0;
	}
	temp->key=(char*)malloc(strlen(pcKey)+1);
	if(temp->key==NULL){
		printf("allocation failed");
		return 0;
	}
	
	temp->key=(char*)pcKey;
	temp->value=(void*)pvValue;
	temp->next=oSymTable->next;
	oSymTable->next=temp;
	oSymTable->lenght++;

	return 1;
}

int SymTable_contains(SymTable_T oSymTable, const char *pcKey){
	SymTable_T temp;
	assert(oSymTable!=NULL);
	assert(pcKey!=NULL);
	temp=oSymTable;
	while(temp!=NULL){
		if(temp->key!=NULL){
		if(strcmp(temp->key,pcKey)==0)
			return 1;
		}
		temp=temp->next;
	
	}
	return 0;
}

int SymTable_remove(SymTable_T oSymTable, const char *pcKey){
	SymTable_T temp,temp2;
	assert(oSymTable!=NULL);
	assert(pcKey!=NULL);
	temp=oSymTable;
	if(strcmp(temp->next->key,pcKey)==0){ /* delete mono gia to 1o node!! */
			temp2=temp;
			temp=temp->next;
			temp2->next=temp->next;
			free(temp);
			oSymTable->lenght--;
			return 1;

	}else
	while(temp!=NULL){
 	 if(temp->key!=NULL && strcmp(temp->next->key,pcKey)==0){ /*delete apo to 2o node kai meta */
			temp2=temp;
			temp=temp->next;
			temp2->next=temp->next;
			free(temp);
			oSymTable->lenght--;
			return 1;
		}
		temp=temp->next;
	}
	
	return 0;
	
}

void* SymTable_get(SymTable_T oSymTable, const char *pcKey){
	SymTable_T temp;
	assert(oSymTable!=NULL);
	assert(pcKey!=NULL);
	temp=oSymTable;
	while(temp!=NULL){
		if(temp->key!=NULL && strcmp(temp->key,pcKey)==0){
			return temp->value;	
		}
		temp=temp->next;
	}
	
	return 0;
	
}

void  SymTable_map(SymTable_T oSymTable,void (*pfApply)(const char *pcKey, void *pvValue,void *pvExtra),const void *pvExtra){
SymTable_T temp;
assert(oSymTable!=NULL);
assert(pfApply!=NULL);


temp=oSymTable;
while(temp!=NULL){
	if(temp->key!=NULL){
		pfApply(temp->key,temp->value,(void *) pvExtra);
		temp=temp->next;
	}
}


}













