#include "symtablehash.h"

#define HASH_MULTIPLIER 65599


static unsigned int SymTable_hash(const char *pcKey)
{
  size_t ui;
  unsigned int uiHash = 0U;
  for (ui = 0U; pcKey[ui] != '\0'; ui++)
    uiHash = uiHash * HASH_MULTIPLIER + pcKey[ui];
  return uiHash;
} 


SymTable_T   SymTable_new(void){
	Node Newnode;
	SymTable_T	head;
	int i;
	
	Newnode=(struct node*)malloc(sizeof(struct node));
	if(Newnode == NULL){
		printf("allocation failed");
		return 0;
	}
	
	head=(struct SymTable*)malloc(sizeof(struct SymTable));
	
	if(head == NULL){
		printf("allocation failed");
		return 0;
	}
	
	Newnode->key=NULL;
	Newnode->value=NULL;
	Newnode->next=NULL;
	for(i=0;i<509;i++){
		head->symbuckets[i] = Newnode;
	}
	
	return head;
}


void  SymTable_free(SymTable_T oSymTable){
	SymTable_T temp=NULL;
	int i=0;
	if(oSymTable==NULL){
		return;
	}

	while(oSymTable->symbuckets[i]!=NULL){
		if(oSymTable->symbuckets[i]->next==NULL){
			return;
		}
		temp->symbuckets[i]=oSymTable->symbuckets[i];
		oSymTable->symbuckets[i]=oSymTable->symbuckets[i]->next;
		free(temp);
		i++;
	}
	free(oSymTable);

}

unsigned int SymTable_getLength(SymTable_T oSymTable){
	assert(oSymTable != NULL);
	return oSymTable->lenght;
}

int SymTable_contains(SymTable_T oSymTable, const char *pcKey){
	int k=0;
	SymTable_T temp;
	assert(oSymTable!=NULL);
	assert(pcKey!=NULL);
	temp=oSymTable;
	while(temp->symbuckets[k]!=NULL){
		if(temp->symbuckets[k]->key!=NULL){
		if(strcmp(temp->symbuckets[k]->key,pcKey)==0)
			return 1;
		}
		k++;
	
	}
	return 0;
}


int SymTable_put(SymTable_T oSymTable, const char *pcKey,const void *pvValue){
	unsigned int symhash;
	Node temp;
 	assert(oSymTable!=NULL);
 	assert(pcKey!=NULL);
	symhash=SymTable_hash(pcKey);
	
	
	
	if(SymTable_contains(oSymTable,pcKey)){
		return 0;
	}
	temp=(struct node*)malloc(sizeof(struct node));
	
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
	temp->next=oSymTable->symbuckets[symhash];
	oSymTable->symbuckets[symhash]=temp;
	oSymTable->lenght++;

	return 1;
}

void* SymTable_get(SymTable_T oSymTable, const char *pcKey){
	int k=0;
	SymTable_T temp;
	unsigned int symhash;
	assert(oSymTable!=NULL);
	assert(pcKey!=NULL);
	temp=oSymTable;
	symhash=SymTable_hash(pcKey);
		while(temp->symbuckets[k]!=NULL){
		if(temp->symbuckets[k]->key!=NULL){
		if(strcmp(temp->symbuckets[k]->key,pcKey)==0)
			return temp->symbuckets[symhash]->value;
		}
		k++;
	
	}
	return 0;
	
}





























