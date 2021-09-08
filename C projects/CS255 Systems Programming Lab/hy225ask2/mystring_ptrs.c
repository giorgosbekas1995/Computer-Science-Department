
/*Georgios Bekas
  askisi 2
  mystring_ptrs.c
  */

#include "mystring.h"

/*return the lenght of a C string */
size_t ms_length(const char *pcStr)
{
  const char *pcStrEnd = pcStr;
  assert(pcStr!=NULL); 
  while (*pcStrEnd!='\0') 
    pcStrEnd++;
  return pcStrEnd-pcStr;
} 

/*Copy a c string*/
char *ms_copy(char *s,const char *p){
	char *a=s;
	assert(p!=NULL);
	while(*p!='\0'){
	*s++=*p++;
}
	return a;
}


/*Copy first k characters of the string*/
char *ms_ncopy(char *s, const char *p,size_t k){
    char *a=s;
	assert(p!=NULL);
	while(*p != '\0'&& k>0){
	*s++=*p++;
	k--;
	}
	return a;
}

/*attach 2nd string to 1st*/
char *ms_concat(char *s,const char *p){
	char *a=s;
	assert(p!=NULL);
	while(*s!='\0'){
		s++;
	}
	while(*p!='\0'){
			*s++=*p++;
	}
	
	return a;
}

/*attach first n characters of 2nd string to 1st*/
char *ms_nconcat(char *s,const char *p,size_t n){
	char *a=s;
	assert(p!=NULL);
	
	while(*s!='\0'){
		s++;
	}
	while(n>0 && *p!='\0'){
	
			*s++=*p++;
			n--;
	}
	
	return a;
}

/*Checks who is the biger string*/
int ms_compare(const char *s,const char *p){
	
	while(*s!='\0' && *p!='\0' && *s==*p){
		s++;
		p++;
	}
	

	if(*(unsigned char *)s<*(unsigned char *)p) return -1;
	else 
	if(*(unsigned char *)s>*(unsigned char *)p) return 1;
	else return 0;
	
}
/*checks of the first n characters of the 2 strings who is biger*/ 
int ms_ncompare(const char *s,const char *p,size_t n){
	
	while(*s!='\0' && *p!='\0' && *s==*p && n>0){
		s++;
		p++;
		n--;
	}
	

	if(*(unsigned char *)s<*(unsigned char *)p) return -1;
	else 
	if(*(unsigned char *)s>*(unsigned char *)p) return 1;
	else return 0;
	
}

