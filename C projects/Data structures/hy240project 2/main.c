/****************************************************************
 * @file   main.c                                      	        *
 * @author Nikolaos <batsaras@csd.uoc.gr>                       *
 *                                                              *
 * @brief Header function for the needs of cs-240b project 2017 *
 ****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "geo.h"

#define BUFFER_SIZE 1024  /**< Maximum length of a line in input file */

/* Uncomment the following line to enable debugging prints 
 * or comment to disable it */
#define DEBUG

#ifdef DEBUG
#define DPRINT(...) fprintf(stderr, __VA_ARGS__);
#else  /* DEBUG */
#define DPRINT(...)
#endif /* DEBUG */


/**
* @brief Add a new location to the system
*
* @param lid The location's id
*
* @return 1 on success
*         0 on failure
*/
void print_loc(){
	int i=0;
	printf("Locations = ");
for(i=0;i<1000;i++){
	if(locations_array[i] == NULL){
		break;
	}
	printf(" <%d> ",locations_array[i]->lid);
}

}

int add_location(int lid)
{
struct location *temp;
int i=0,k;
printf("L<%d>\n",lid);
for(i=0;i<1000;i++){
	if(locations_array[i] == NULL ){
		locations_array[i]=(struct location*)malloc(sizeof(struct location));
		locations_array[i]->lid=lid;
		locations_array[i]->poi_sentinel=NULL;
		locations_array[i]->poi_tree=NULL;
		break;
	}
}
for(i=0;i<1000;i++){
for(k=i+1;k<1000;k++){
	if(locations_array[k]!=NULL){
	if(locations_array[i]->lid>locations_array[k]->lid){
		temp=locations_array[i];
		locations_array[i]=locations_array[k];
		locations_array[k]=temp;
	}
}

}	
}
print_loc();
printf("\nDONE\n\n");
  return 1;
}


struct poi *add_poi(struct poi* root, int pid, int distance, int type){
  if(root == NULL)
  {
     root = (struct poi*)malloc(sizeof(struct poi));
    root->distance=distance;
    root->pid=pid;
    root->type=type;
    root->p=NULL;
    root->lc = NULL;
 	root->rc = NULL;

  }
  else
  {
    if(pid <= root->pid)
    { 
      root->lc = add_poi(root->lc,pid,distance,type);
    
    }
    else
    {
      root->rc = add_poi(root->rc,pid,distance,type);
    
    }
   
  }
  return root;
}

void Print_poitree(struct poi *p){
 struct poi *q=p;
 if(q==NULL) return;
 
 printf(" <%d:%d:%d> ",q->pid,q->type,q->distance);
 Print_poitree(q->lc);
 Print_poitree(q->rc);
 
 
 
}

void print_poi(){
	int i=0;
	struct poi *temp;
	printf("Location = ");
for(i=0;i<1000;i++){
	if(locations_array[i] != NULL){
	if(locations_array[i]->poi_tree!=NULL){
	temp=locations_array[i]->poi_tree;
	Print_poitree(temp);
}
}
}
}

/**
* @brief Add point-of-interest (POI) to a location
* 
* @param pid      POI's id
* @param type     The type of the POI
* @param distance The distance of POI from the locations reference point
* @param lid      The location of the POI
*
* @return 1 on success
*         0 on failure
*/

int add_poi_to_location(int pid, int type, int distance, int lid)
{
int i=0;
printf("P<%d><%d><%d><%d>\n",pid,type,distance,lid);
for(i=0;i<1000;i++){
	if(locations_array[i] != NULL){
	if(locations_array[i]->lid==lid){
		locations_array[i]->poi_tree = add_poi(locations_array[i]->poi_tree,pid,distance,type);
		
	}
	}
  
}
print_poi();
printf("\nDONE\n\n");
return 1;
}



/**
* @brief A POI is unavailable to visitors
*
* @param pid The POI's id
* @param lid The location's id
* 
* @return 1 on success
*         0 on failure
*/
int unavailable_poi(int pid, int lid)
{
  return 1;
}


void print_user(){
	int i=0;
	printf("Users= ");
for(i=0;i<1000;i++){
	if(users_hashtable[i] == NULL){
		break;
	}
	printf(" <%d> ",users_hashtable[i]->uid);
}

}
/**
* @brief Register user
*
* @param uid The user's id
* 
* @return 1 on success
*         0 on failure
*/
int register_user(int uid)
{
struct user *temp;
int i=0,k;
printf("R<%d>\n",uid);
for(i=0;i<1000;i++){
	if(users_hashtable[i] == NULL ){
		users_hashtable[i]=(struct user*)malloc(sizeof(struct user));
		users_hashtable[i]->uid=uid;
		users_hashtable[i]->upoi_count=0;
		users_hashtable[i]->interesting_poi=NULL;
		break;
	}
}
print_user();
printf("\nDONE\n\n");
  return 1;
}

struct user_poi *add_userpoi(struct user_poi* root, int upid){
  if(root == NULL)
  {
     root = (struct user_poi*)malloc(sizeof(struct user_poi));
    root->upid=upid;
    root->lc = NULL;
 	root->rc = NULL;

  }
  else
  {
    if(upid <= root->upid)
    { 
      root->lc = add_userpoi(root->lc,upid);
    
    }
    else
    {
      root->rc = add_userpoi(root->rc,upid);
    
    }
   
  }
  return root;
}

void Print_userpoitree(struct user_poi *p){
 struct user_poi *q=p;
 if(q==NULL) return;
 
 printf(" <%d> ",q->upid);
 Print_userpoitree(q->lc);
 Print_userpoitree(q->rc);
 
 
 
}

void print_userpoi(){
	int i=0;
	struct user_poi *temp;
	printf("Users POI = ");
for(i=0;i<1000;i++){
	if(users_hashtable[i] != NULL){
	if(users_hashtable[i]->interesting_poi!=NULL){
	temp=users_hashtable[i]->interesting_poi;
	Print_userpoitree(temp);
}
}
}
}

/**
* @brief User is interested in POI
* 
* @param uid The user's id
* @param pid The POI's id
*
* @return 1 on success
*         0 on failure
*/
int interesting_poi(int uid, int upid)
{
int i=0;
printf("I<%d><%d>\n",uid,upid);
for(i=0;i<1000;i++){
	if(users_hashtable[i] != NULL){
	if(users_hashtable[i]->uid==uid){
	
		users_hashtable[i]->interesting_poi = add_userpoi(users_hashtable[i]->interesting_poi,upid);
		
	}
	}	
  
}
print_userpoi();
printf("\nDONE\n\n");
return 1;
}

/**
* @brief Group users
* 
* @param uid1 The id of the 1st user
* @param uid2 The id of the 2nd user
*
* @return 1 on success
*         0 on failure
*/
int group_users(int uid1, int uid2)
{
  return 1;
}

/**
* @brief Find the inorder successors from one pid the other
* 
* @param lid  The location's id
* @param pid1 A point of interest
* @param pid2 A point of interest
*
* @return 1 on success
*         0 on failure
*/
int inorder_successors(int lid, int pid1, int pid2)
{
  return 1;
}

/**
* @brief Print all locations
*
* @return 1 on success
*         0 on failure
*/
int print_locations()
{   
	int i=0;
	printf("\nX\nLOCATIONS:\n");
for(i=0;i<1000;i++){
	if(locations_array[i] != NULL){
	printf(" Location%d ",locations_array[i]->lid);
	Print_poitree(locations_array[i]->poi_tree);
	
}
}
printf("\nDONE\n\n");
  return 1;
}

/**
* @brief Print all users
*
* @return 1 on success
*         0 on failure
*/
int print_users()
{
	int i=0;
	printf("\nY\nUsers:\n");
for(i=0;i<1000;i++){
	if(users_hashtable[i] != NULL){
	printf(" User%d ",users_hashtable[i]->uid);
	Print_userpoitree(users_hashtable[i]->interesting_poi);

}
}
printf("\nDONE\n\n");
  return 1;
}

/**
* @brief Search for user
* 
* @param uid The id of the user we are looking for
*
* @return 1 on success
*         0 on failure
*/
int search_user(int uid)
{
	int i=0;
	printf("\nY\nIntresting_poi:\n");
for(i=0;i<1000;i++){
	if(users_hashtable[i] != NULL){
	if(users_hashtable[i]->uid==uid){
	Print_userpoitree(users_hashtable[i]->interesting_poi);
}
}
}
printf("\nDONE\n\n");
  return 1;
}

/**
* @brief Cleanup resources
* 
* @return 1 on success
*         0 on failure
*/
int free_world()
{
  return 1;
}


/**
 * @brief The main function
 *
 * @param argc Number of arguments
 * @param argv Argument vector
 *
 * @return 0 on success
 *         1 on failure
 */
int main(){
	add_location(1);
	add_location(2);
	add_location(5);
	add_location(4);
	add_poi_to_location(5, 4, 30, 2);
	add_poi_to_location(6, 3, 30, 2);
	add_poi_to_location(4, 1, 30, 4);
	register_user(5);
	register_user(4);
	register_user(6);
	interesting_poi(4,7);
	interesting_poi(4,8);
	interesting_poi(5,6);
	print_locations();
	print_users();
	search_user(4);

}
