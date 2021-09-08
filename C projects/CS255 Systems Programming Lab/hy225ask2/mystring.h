#include <stdio.h>
#include <assert.h>
#include <stddef.h>
#include <string.h>

/*Γεώργιος Μπέκας
  ’σκηση 2
  mystring_ptrs.h
  */

/* return the lenght of a C string */ 
size_t ms_length(const char *pcStr);

/*Copy a c string*/
char *ms_copy(char *s,const char *p);

/*Copy first k characters of the string*/
char *ms_ncopy(char *s, const char *p,size_t k);

/*attach 2nd string to 1st*/
char *ms_concat(char *s,const char *p);

/*attach first n characters of 2nd string to 1st*/
char *ms_nconcat(char *s,const char *p,size_t n);


/*Checks who is the biger string*/
int ms_compare(const char *s,const char *p);


/*checks of the first n characters of the 2 strings who is biger*/ 
int ms_ncompare(const char *s,const char *p,size_t n);
