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
* @return true on success
*         false on failure
*/


void print_location(){
	struct location *print = locations_list;
	
	printf("Locations = ");
	while(print!=NULL){
		printf(" %d ",print->lid);
		print=print->next;
	}

	printf("\nDONE\n");
	
}

int add_location(int lid) {
struct location *q=locations_list,*pq=NULL;
struct location *temp;

while(q!=NULL && q->lid<lid){
	pq=q;
	q=q->next;
}

if(q!=NULL && q->lid == lid) return 0;

	temp=(struct location*)malloc(sizeof(struct location));
	temp->lid=lid;
	temp->poi_list=NULL;
	temp->next=q;
	if(pq==NULL) locations_list = temp;
	else pq->next = temp;
	
	printf("L <%d> \n",lid);
	print_location();
     	return 1;
}

/**
* @brief Add point-of-interest (POI) to a location
* 
* @param pid POI's id
* @param type The type of the POI
* @param distance The distance of POI from the locations reference point
* @param lid The location of the POI
*
* @return true on success
*         false on failure
*/
void print_poi(){
	
struct location *print = locations_list;
struct poi *temp;
	
	
	while(print!=NULL){
	temp=print->poi_list;
	while(temp!=NULL){
	
	printf(" <%d:%d:%d> ",temp->distance,temp->pid,temp->type);
	
		temp=temp->next;
	}
	print=print->next;
		
}
printf("\nDONE\n");
}

int add_poi_to_location(int pid, int type, int distance, int lid) {
	struct location *q=locations_list;
	int i=0;
	struct poi *R,*k,*Q;
	
	printf("P <%d> <%d> <%d> \nLocation = ",pid,type,distance);
	while(q!=NULL){
		if(q->lid==lid){
			
		struct poi *temp = (struct poi*)malloc(sizeof(struct poi));
		temp->distance=distance;
		temp->pid=pid;
		temp->type=type;
		temp->prev=NULL;
		temp->next=NULL;
	
		
	if(q->poi_list == NULL){
		q->poi_list = temp;
		
	}else{
	k = q->poi_list;
	Q = q->poi_list;
	if(k->distance > temp->distance){
		
	temp->next=q->poi_list;
	q->poi_list->prev = temp;
	q->poi_list = temp;
	
	while(Q!=NULL){
		if(Q==k){
			Q=Q->next; /*den theloume na prosthesoume sto prwto komvo*/
		}
		Q->distance=Q->distance+k->distance;
		Q=Q->next;
	}
	
	}else{
		R=q->poi_list;
		while(R->next!=NULL){
			i+=R->distance;
			if(temp->distance<i){
			break;
			}
			R=R->next;
		}
		
		
		
		temp->next=R->next;
		temp->prev=R;
		temp->distance=temp->distance-R->distance;
		
		if(R->next != NULL){
			R->next->prev = temp;
		}
		
		R->next = temp;	
	
}
}
		
		}
	
		q=q->next;
	}
	print_poi();
	
	return 1;
}

/**
* @brief A POI is unavailable to vistors
*
* @param pid The POI's id
* @param lid The location's id
* 
* @return true on success
*         false on failure
*/
int unavailable_poi(int pid, int lid) {
	struct location *q=locations_list;
	struct poi *k,*temp=NULL;
	printf("A <%d> <%d> \nLocation = ",pid,lid);
	while(q!=NULL){
		if(q->lid==lid){
			k=q->poi_list;
			while(k!=NULL){
				temp=k;
				if(k->pid==pid){
					if(k->prev==NULL){/*an einai 1o stixio*/
						temp=temp->next;
						temp->distance=temp->distance+k->distance;
						q->poi_list=temp;
					}else 
					if(k->next==NULL){/*an einai teleuteo stixio*/
						temp->prev->next=NULL;
					}else
					if(k->prev!=NULL&&k->next!=NULL){/*an einai sth mesh*/
					k->next->distance=k->next->distance+k->distance;
						temp->prev->next=temp->next;
						temp->next->prev=temp->prev;
					}
				}
				
				k=k->next;
			}
		}
		q=q->next;
	}
	
	print_poi();
	return 1;
}

void print_user(){
	struct user *print=users_list;
	while(print!=users_sentinel){
		printf("<%d>",print->uid);
		print=print->next;
	}
	printf("\nDONE\n");
}
        
/**
* @brief Register user
*
* @param uid The user's id
* 
* @return true on success
*         false on failure
*/
int register_user(int uid) {
	printf("R <%d> \nUsers = ",uid);
	if(users_list==NULL){
	struct user *q =(struct user*)malloc(sizeof(struct user));
	struct user *sentinel =(struct user*)malloc(sizeof(struct user));
	sentinel->uid=-1;
	sentinel->next=NULL;
	sentinel->interesting_poi=NULL;
	users_sentinel=sentinel;
	users_sentinel->next=users_list;
	users_list=users_sentinel;
	
	q->uid=uid;
	q->interesting_poi=NULL;
	q->next=users_list;
	users_list=q;
   }else{
   	struct user *q =(struct user*)malloc(sizeof(struct user));
   	q->uid=uid;
	q->interesting_poi=NULL;
	q->next=users_list;
	users_list=q;
   }
	print_user();
	return 1;
}

void print_userpoi(){
	struct user *q=users_list;
	struct user_poi *print;
	
	printf("Users = ");
	while(q!=users_sentinel){
		print=q->interesting_poi;
	while(print!=NULL){
		printf(" <%d> ",print->upid);
		print=print->next;
	}
		q=q->next;
	}
	printf("\nDONE\n");
}
       
/**
* @brief User is interested in POI
* 
* @param uid The user's id
* @param pid The POI's id
*
* @return true on success
*         false on failure
*/
int interesting_poi(int uid, int upid) {
	struct user *k=users_list;
	struct user_poi *q,*pq=NULL,*temp;
	printf("I <%d> <%d> \nPOI = ",uid,upid);
	while(k!=users_sentinel){
		if(k->uid==uid){
			q=k->interesting_poi;
		while(q!=NULL && q->upid<upid){
	pq=q;
	q=q->next;
}

if(q!=NULL && q->upid == upid) return 0;

	temp=(struct user_poi*)malloc(sizeof(struct user_poi));
	temp->upid=upid;
	temp->next=q;
	if(pq==NULL) k->interesting_poi = temp;
	else pq->next = temp;
		}
		k=k->next;
	}
	print_userpoi();
	return 1;
}
 
 void print_group(int uid1, int uid2, int uid3){
	struct user *q=users_list;
	struct user_poi *print;
	
	
	while(q!=users_sentinel){
		if(q->uid==uid1||q->uid==uid2||q->uid==uid3){
		printf("User%d = ",q->uid);
		print=q->interesting_poi;
	while(print!=NULL){
		printf(" <%d> ",print->upid);
		print=print->next;
	}
		q=q->next;
	}
	printf("\n");
}

	
}
       
/**
* @brief Group users
* 
* @param uid1 The id of the 1st user
* @param uid2 The id of the 2nd user
* @param uid3 The id of the 3rd user
*
* @return true on success
*         false on failure
*/
int group_users(int uid1, int uid2, int uid3) {
	struct user *k=users_list;
	struct user_poi *u1,*u2,*u3;
	printf("G <%d> <%d> <%d> \n",uid1,uid2,uid3);
	print_group(uid1,uid2,uid3);
	while(k!=users_sentinel){
		if(k->uid==uid1){
			u1=k->interesting_poi;
		}
		if(k->uid==uid2){
			u2=k->interesting_poi;
		}
		if(k->uid==uid3){
			u3=k->interesting_poi;
		}
		k=k->next;
	}
	
	while(u1!=NULL&&u2!=NULL&&u3!=NULL){
		if(u1->upid==u2->upid && u2->upid==u3->upid){
			printf("Common = %d",u1->upid);
			u1=u1->next;
			u2=u2->next;
			u3=u3->next;
		}else
		if(u1->upid<=u2->upid&&u1->upid<=u3->upid){
			
			u1=u1->next;
		}else
		if(u2->upid<=u1->upid&&u2->upid<=u3->upid){
		
			u2=u2->next;
		}else{
		
			u3=u3->next;
		}
		
		
	}
	printf("\nDONE\n");
	return 1;
}
        
/**
* @brief Calculate the distance between locations
* 
* @param lid The location's id
* @param pid1 The id of the 1st POI
* @param pid1 The id of the 2nd POI
* @param pid1 The id of the 3rd POI
*
* @return true on success
*         false on failure
*/
int sightseeing_distance(int lid, int pid1, int pid2, int pid3) {
	return 1;
}
        
/**
* @brief Print all locations
*
* @return true on success
*         false on failure
*/
int print_locations() {
struct location *print = locations_list;
struct poi *temp;
	
	printf("LOCATIONS:\n");
	while(print!=NULL){
	temp=print->poi_list;
	if(temp!=NULL){
	printf("Location%d = ",print->lid);
}
	while(temp!=NULL){
	
	printf(" <%d:%d:%d> ",temp->distance,temp->pid,temp->type);
	
		temp=temp->next;
	}
	printf("\n");
	print=print->next;
		
}
printf("\nDONE\n");
	return 1;
}
        
/**
* @brief Print all users
*
* @return true on success
*         false on failure
*/
int print_users() {
	struct user *q=users_list;
	struct user_poi *print;
	
	printf("Y\n");
	while(q!=users_sentinel){
		printf("User%d = ",q->uid);
		print=q->interesting_poi;
	while(print!=NULL){
		printf(" <%d> ",print->upid);
		print=print->next;
	}
		q=q->next;
		
	printf("\n");
}
	printf("\nDONE\n");
	return 1;
}
        
/**
* @brief Search for user
* 
* @param uid The id of the user we are looking for
*
* @return true on success
*         false on failure
*/
int search_user(int uid) {
	struct user *q=users_list;
	struct user_poi *print;
	
	printf("Z <%d>\n\nInteresting_poi : ",uid);
	while(q!=users_sentinel){
		if(q->uid==uid){
		print=q->interesting_poi;
	while(print!=NULL){
		printf(" <%d> ",print->upid);
		print=print->next;
	}
		
	}
	q=q->next;
}
	printf("\nDONE\n");
	return 1;
}

int free_world() {
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
int main(int argc, char** argv)
{
	FILE *fin = NULL;
	char buff[BUFFER_SIZE], event;


	/* Check command buff arguments */
	if ( argc != 2 ) {
		fprintf(stderr, "Usage: %s <input_file> \n", argv[0]);
		return EXIT_FAILURE;
	}

	/* Open input file */
	if (( fin = fopen(argv[1], "r") ) == NULL ) {
		fprintf(stderr, "\n Could not open file: %s\n", argv[1]);
		perror("Opening test file\n");
		return EXIT_FAILURE;
	}

	/* Read input file buff-by-buff and handle the events */
	while ( fgets(buff, BUFFER_SIZE, fin) ) {

		DPRINT("\n>>> Event: %s", buff);

		switch(buff[0]) {

		/* Comment */
		case '#':
			break;

		/* Add location
		 * L <lid> */
		case 'L':
		{
			int lid;
			sscanf(buff, "%c %d", &event, &lid);
			DPRINT("%c %d\n", event, lid);


			if ( add_location(lid) ) {
				DPRINT("L %d succeeded\n", lid);
			} else {
				fprintf(stderr, "L %d failed\n", lid);
			}

			break;
		}

		/* Add POI to location
		 * P <pid> <type> <distance> <lid> */
		case 'P':
		{
			int pid, type, distance, lid;

			sscanf(buff, "%c %d %d %d %d", &event, &pid, &type, &distance, &lid);
			DPRINT("%c\n", event);

			if ( add_poi_to_location(pid, type, distance, lid) ) {
				DPRINT("%c %d %d %d %d succeeded\n", event, pid, type, distance, lid);
			} else {
				fprintf(stderr, "%c %d %d %d %d failed\n", event, pid, type, distance, lid);
			}

			break;
		}

		/* POI is not available
		 * A <pid> <lid> */
		case 'A':
		{
			int pid;
			int lid;
			sscanf(buff, "%c %d %d", &event, &pid, &lid);
			DPRINT("%c %d %d\n", event, pid, lid);

			if ( unavailable_poi(pid, lid) ) {
				DPRINT("%c %d %d succeeded\n", event, pid, lid);
			} else {
				fprintf(stderr, "%c %d %d failed\n", event, pid, lid);
			}

			break;
		}

		/* Register user
		 * R <uid> <hotel-id> */
		case 'R':
		{
			int uid;
			sscanf(buff, "%c %d", &event, &uid);
			DPRINT("%c %d\n", event, uid);

			if ( register_user(uid) ) {
				DPRINT("%c %d succeeded\n", event, uid);
			} else {
				fprintf(stderr, "%c %d failed\n", event, uid);
			}

			break;
		}

		/* User interested in poi
		 * I <uid> <pid> */
		case 'I':
		{
			int uid, upid;
			sscanf(buff, "%c %d %d", &event, &uid, &upid);
			DPRINT("%c %d %d\n", event, uid, upid);

			if ( interesting_poi(uid, upid) ) {
				DPRINT("%c %d %d succeeded\n", event, uid, upid);
			} else {
				fprintf(stderr, "%c %d %d failed\n", event, uid, upid);
			}

			break;
		}

		/* Group users
		 * G <uid1> <uid2> <uid3> */
		case 'G':
		{
			int uid1, uid2, uid3;
			sscanf(buff, "%c %d %d %d", &event, &uid1, &uid2, &uid3);
			DPRINT("%c %d %d %d\n", event, uid1, uid2, uid3);

			if ( group_users(uid1, uid2, uid3) ) {
				DPRINT("%c %d %d %d succeeded\n", event, uid1, uid2, uid3);
			} else {
				fprintf(stderr, "%c %d %d %dfailed\n", event, uid1, uid2, uid3);
			}

			break;
		}

		/* Sightseeing distance
		 * B <lid> <pid1> <pid2> <pid3> */
		case 'B':
		{
			int lid;
			int pid1, pid2, pid3;
			sscanf(buff, "%c %d %d %d %d\n", &event, &lid, &pid1, &pid2, &pid3);
			DPRINT("%c %d %d %d %d\n", event, lid, pid1, pid2, pid3);

			if ( sightseeing_distance(lid, pid1, pid2, pid3) ) {
				DPRINT("%c %d %d %d %d succeeded\n", event, lid, pid1, pid2, pid3);
			} else {
				fprintf(stderr, "%c %d %d %d %d failed\n", event, lid, pid1, pid2, pid3);
			}

			break;
		}

		/* Print locations
         * X */
		case 'X':
		{
			sscanf(buff, "%c", &event);
			DPRINT("%c\n", event);

			if ( print_locations() ) {
				DPRINT("%c succeeded\n", event);
			} else {
				fprintf(stderr, "%c failed\n", event);
			}

			break;
		}

		/* Print users
		 * Y */
		case 'Y':
		{
			sscanf(buff, "%c", &event);
			DPRINT("%c\n", event);

			if ( print_users() ) {
				DPRINT("%c succeeded\n", event);
			} else {
				fprintf(stderr, "%c failed\n", event);
			}

			break;
		}

		/* Search user
		 * Z */
		case 'Z':
		{
			int uid;
			sscanf(buff, "%c %d", &event, &uid);
			DPRINT("%c\n", event);

			if ( search_user(uid) ) {
				DPRINT("%c %d succeeded\n", event, uid);
			} else {
				fprintf(stderr, "%c %d failed\n", event, uid);
			}

			break;
		}


		/* Empty line */
		case '\n':
			break;

		/* Ignore everything else */
		default:
			DPRINT("Ignoring buff: %s \n", buff);

			break;
		}
	}

	free_world();
	return (EXIT_SUCCESS);
}
