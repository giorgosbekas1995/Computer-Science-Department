
/*Georgios Bekas
  askisi  2
  mystring_ars.c
  */

#include "mystring.h"

/*return the lenght of a C string */
size_t ms_length(const char pcStr[])
{
  size_t i=0;
  assert(pcStr!=NULL); 
  while (pcStr[i]!='\0') 
    i++;
  return i;
} 

/*Copy a c string*/
char *ms_copy(char s[],const char p[]){
	size_t i;
	char *a=s;
	assert(p!=NULL);
for( i=0; i<ms_length(p);i++){
	
	s[i]=p[i];
}
	return a;
}


/*Copy first k characters of the string*/
char *ms_ncopy(char *s, const char *p,size_t k){
	size_t i;
        char *a=s;
	assert(p!=NULL);
	for(i=0; k>0&&i<ms_length(p);i++,k--){
	s[i]=p[i];
}
	return a;
}

/*attach 2nd string to 1st*/
char *ms_concat(char *s,const char *p){
	size_t i,j;
	char *a=s;
	assert(p!=NULL);
	 j = ms_length(s);
	for(i=0;i<ms_length(p);i++){
		s[j++]=p[i];
	}
	
	return a;
}

/*attach first n characters of 2nd string to 1st*/
char *ms_nconcat(char *s,const char *p,size_t n){
	size_t i,j;
	char *a=s;
	assert(p!=NULL);
	 j=ms_length(s);
	for(i=0;n>0&&i<ms_length(p);n--,i++){
		s[j++]=p[i];
	}
	
	return a;
}

/*Checks who is the biger string*/
int ms_compare(const char *s,const char *p){
	
	size_t i=0;
	
	while(s[i]!='\0' && p[i]!='\0' && s[i]==p[i]){
		i++;
	}
	
	
	if((unsigned char )s[i]<(unsigned char )p[i]) return -1;
	else 
	if((unsigned char )s[i]>(unsigned char )p[i]) return 1;
	else return 0;
	
}
/*checks of the first n characters of the 2 strings who is biger*/ 
int ms_ncompare(const char *s,const char *p,size_t n){

	size_t i=0;

	while(s[i]!='\0' && p[i]!='\0' && s[i]==p[i] && n>0){

		i++;
		n--;
	}


	if((unsigned char )s[i]<(unsigned char )p[i]) return -1;
	else
	if((unsigned char )s[i]>(unsigned char )p[i]) return 1;
	else return 0;

}



/*int main(){
	const char *x="abc";
	char p[]="abc";
	char d[]="abcc";

	printf("%d\n",ms_length(x));

	printf("%s\n",ms_copy(s,x));
	printf("%s\n",ms_ncopy(s,x,2));
	printf("%s",ms_concat(d,x));
	printf("%d",ms_ncompare(p,d,3));

	return 0;


}*/

