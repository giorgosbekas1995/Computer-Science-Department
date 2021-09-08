/* 
 * apo thn paragwgh sthn katanalwsh
 * by Giorgos Bekas
 * Operating Systems - hy345
 */

#define _BSD_SOURCE    // petage error to useconds_t
#define _XOPEN_SOURCE 500 // petage error to useconds_t
#include <unistd.h> 
#include "defines.h"
#include <time.h>  // to vala giati to xreiazetai h srand
#include <pthread.h>   // ta system calls gia ta threads

int* array;
int element=0;
int avail=0;
long int finish=1;
int* dedomena;
__thread int  until = 0;
__thread int values = 0;
pthread_mutex_t paragwgos_lock;
pthread_mutex_t katanalwths_lock;
pthread_cond_t sinthiki = PTHREAD_COND_INITIALIZER;

// prepei na dinontai ws parametroi
int arithmos_par;
int arithmos_kat;

void* paragwgos(void *arg)
{
	useconds_t delay;
	int val;
	// o paragwgos tha dimiourghsei sunolika 10000 dedomena gia na einai
	// pio grigoro to debuging gia megala noumera px ./consumers 1000 30
	// evala to TOTAL na einai ena mikrotero noumero -> 1000
	while (until < TOTAL)
	{
		// perimenei prwta: delay microseconds kai meta epixeirei na parei to lock
		delay = rand() % 10 + 1;
		//delay = delay / 1000;
		//sleep(delay);
		usleep(delay);
		
		// PROSOXH critical section
		pthread_mutex_lock(&paragwgos_lock);
		
		until++;
		val = rand() % 100 + 1;
		array[element] = val;
		element++;
		avail++;		
		
		pthread_mutex_lock(&katanalwths_lock);
		pthread_cond_signal(&sinthiki);
		pthread_mutex_unlock(&katanalwths_lock);
		pthread_mutex_unlock(&paragwgos_lock);
		// PROSOXH TELOS critical section
	}
	return NULL;
}

// oi katanalwtes den exoun kathisteriseis kai katanalwnoun oso pio grigora mporoun
void* katanalwths(void* arg)
{
	pthread_t tid;
	while (true)
	{
		// PROSOXH critical section
		pthread_mutex_lock(&katanalwths_lock);
		if (finish >= (TOTAL * arithmos_par) ){
			pthread_mutex_unlock(&katanalwths_lock);
			break;
		}
		
		while (avail == true) // oso den exei dedomena koimatai kai perimenei tous paragwgous na ton ksypnhsoun
		{
			pthread_cond_wait(&sinthiki, &katanalwths_lock);
		}
		
		if (element != 0) // eixan diafora sthn auksisi kata 1
		{
			values = values + array[element-1];
		}
		else
		{
			values = values + array[element];
		}
		finish++;
		avail--;
		tid = pthread_self();
		dedomena[tid % arithmos_kat] = values;
		pthread_mutex_unlock(&katanalwths_lock);
		// PROSOXH TELOS critical section
	}
	return NULL;
}

int main(int argc, char* argv[])
{
	int err;
	int i,j,k,l,o; // den exei shmasia kai mono to i na eixa, aplws sto debuging to vala
	time_t t; // xreiastike stin srand
	pthread_t* threadsKatanalwtwn; // ta threads ton paragwgwn
	pthread_t* threadsParagwgwn; // ta threads twn katanalwtwn
	//pthread_t tid = pthread_self();
	// parsing parametrwn apo strings se int
	arithmos_par = atoi(argv[1]);
	arithmos_kat = atoi(argv[2]);
	
	//arxikopoihsh random generator
	// thn xrhsimopoihsa giati alliws h RAND evgaze to idioo !!!!!!!
	srand((unsigned) time(&t));
	
	// edw ta krataw ta id's twn threads gia na ta kanw join meta
	// genika einai xrisimi texniki na kratas ena pool apo threads, auto eida
	// psaxnontas online
	threadsParagwgwn = malloc(sizeof(pthread_t) * arithmos_par);
	threadsKatanalwtwn = malloc(sizeof(pthread_t) * arithmos_kat);
	
	array=malloc(sizeof(int) * TOTAL * arithmos_par);
	
	// arxikopoihsh twn lock
	pthread_mutex_init(&paragwgos_lock, NULL);
	pthread_mutex_init(&katanalwths_lock, NULL);
	
	dedomena = calloc(arithmos_kat, sizeof(int));

	
	printf("arithmos_par=%d, arithmos_kat=%d ara dimiourgw:\n",arithmos_par, arithmos_kat);
	printf("%d paragwgous kai %d katanalwtes\n", arithmos_par, arithmos_kat);
	
	// to kserw oti den exei poly shmasia pws legontai oi counters alla
	// gia logous debug kai na mai 1000 sigouros tous allaska
	for ( i = 0; i < arithmos_par; i++) {
		err = pthread_create(&threadsParagwgwn[i], NULL, &paragwgos, NULL);
		if (err){
			printf("Error: %s, %d,\n threads=%d",
			       strerror(err), err, i);
			break;
		}		
	}	
	
	for (j = 0; j < arithmos_kat; j++) {
		err = pthread_create(&threadsKatanalwtwn[j], NULL, &katanalwths, NULL);
		if (err){
			printf("Error: %s, %d,\n threads=%d",
			       strerror(err), err, i);
			break;
		}		
	}
	
	
	for (k = 0; k < arithmos_par; k++) {
		err = pthread_join(threadsParagwgwn[k], NULL);
		if (err) {
			printf("Error: %s, %d,\n threads=%d\n",
			       strerror(err), err, i);
		}

	}
	
	for (l = 0; l > arithmos_kat; l++) {
		err = pthread_join(threadsKatanalwtwn[l], NULL);
		if (err) {
			printf("Error: %s, %d,\n threads=%d\n", strerror(err), err, i);
		}
	} 
	printf("h diadikasia paragwghs katanalwshs teleiwse\n");
	for (o = 0; o < arithmos_kat; o++) {
		printf("katanalwths%d:%d\n", o, dedomena[o]);
	}
	
	pthread_mutex_destroy(&katanalwths_lock);
	pthread_mutex_destroy(&paragwgos_lock);
	free(array);
	free(dedomena);
	free(threadsParagwgwn);
	free(threadsKatanalwtwn);
	return (EXIT_SUCCESS);
}


