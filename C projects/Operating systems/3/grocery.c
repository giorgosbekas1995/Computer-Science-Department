/**
 * grocery store problem
 * Giorgos Bekas
 * hy345 homework 2
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <time.h>
#include <pthread.h> 
#include <semaphore.h>
	
void* grocer_function(void *idp);
void* customer_function(void *idp);
void  service_customer(void);

int chairs, clients, pwlhtes;
float average       = 0;
int busy            = 0; /* times 0, 1, 2 */
int efugan          = 0;
int kathontai       = 0;
int current_clients = 0;
int served_clients  = 0;
int Index           = 0;
int cnt 			= 0;
int* buffer_help    = NULL;
int* buffer         = NULL;
int size = 1000;

pthread_mutex_t clients_lock, pwlhtes_lock, new_lock;
pthread_cond_t 	clients_cond, pwlhtes_cond;
sem_t clients_sem, pwlhtes_sem, empty, full, mutex, mutex2;

int main(int argc, char** argv)
{
	/* dilwseis metavlitwn */
	int i, j; 
	time_t t; /* ashmanto xrhsimopoietai mono sthn srand((unsigned) time(&t)) */
	pthread_t* threadspwlhtwn;
	pthread_t* threadsclients;
	
	if (argc != 3) {
		fprintf(stderr, "wrong arguments\nWe need chairs and clients\n");
		return (EXIT_FAILURE);
	}
	
	srand((unsigned) time(&t)); /* arxikopoihsh gia na pairnw random times, to googlara gia na vrw pws douleuei */
	
	/* arxikopoihseis */
	chairs         = atoi(argv[1]);
	clients        = atoi(argv[2]);
	j              = clients;
	pwlhtes        = 2;
	threadsclients = malloc(clients * sizeof(pthread_t) * size);
	threadspwlhtwn = malloc(pwlhtes * sizeof(pthread_t) * size);
	buffer         = calloc(clients * size, sizeof(int));
	buffer_help    = calloc(clients * size, sizeof(int));
	
	pthread_mutex_init(&clients_lock, NULL);
    pthread_mutex_init(&pwlhtes_lock, NULL);
	pthread_mutex_init(&new_lock, NULL);

    pthread_cond_init(&clients_cond, NULL);
    pthread_cond_init(&pwlhtes_cond, NULL);
	
	sem_init(&mutex, 0, 1);
	sem_init(&mutex2, 0, 1);
	sem_init(&full, 0, 2);
	sem_init(&empty, 0, chairs);
	/* telos arxikopoihsewn */
	
	printf("O arithmos twn chairs  einai: %d\n", chairs);
	printf("To plithwn twn clients einai: %d\n", clients);
	printf("O arithmos twn pwlhtwn einai: %d\n", pwlhtes);
	
	/* dhmiourgia 2 threads pwlhtwn */
	for(i = 0; i < pwlhtes; i++)
		pthread_create(&threadspwlhtwn[i], NULL, &grocer_function, NULL);
	
	/* dhmiourgia threads clients kathe delay ms*/
	for (i = 0; i < clients; i++) {
		usleep(100 * 1000);
		pthread_create(&threadsclients[i], NULL, &customer_function, NULL);
	}
	
	/* termatismos threads clients */
	for(j = 0; j < clients; j++)
		pthread_join(threadsclients[j], NULL);	
	
	/* termatismos threads pwlthwn */
	for(i = 0; i < pwlhtes; i++)
		pthread_join(threadspwlhtwn[i], NULL);

	
	/* ektupwsh twn zhtoumenwn tis askisis diladi:
	 * enan metrhth twn poswn efugan kai to meso oro tou pinaka buffer */
	for(i = 0; i < Index; i++) {
		if (buffer_help[i] != 0) {
			cnt++;
			efugan = clients * 0.2;
			average = average + buffer_help[i];
		}
	}
	if (clients - efugan > 0 && cnt != 0) /* mia sto ekatomurio pou o xrhsths dwsei 0 clients */
		average = average / cnt;
	else /* edw tha mpei mono an o xrhsths dwsei 0 clients sthn ektelesi */
		average = 0;
	
	printf("O arithmos twn clients pou efugan htan %d\n", efugan);
	printf("O Mesos Oros anamonis htan %f\n", average);
	
	/* osa malloc ekana - kanw alla tosa free :D */
	free(buffer);
	free(buffer_help);
	free(threadsclients);
	free(threadspwlhtwn);
	
	pthread_mutex_destroy(&clients_lock);
    pthread_mutex_destroy(&pwlhtes_lock);

    pthread_cond_destroy(&clients_cond);
    pthread_cond_destroy(&pwlhtes_cond);
	
	sem_destroy(&mutex);
	sem_destroy(&mutex2);
	sem_destroy(&full);
	sem_destroy(&empty);
	
	return (EXIT_SUCCESS);
}

/* thn zhthse h ekfwnshsh */
void* grocer_function(void *idp)
{
	while (1)
	{
		while ( current_clients == 0)
		{
			//pthread_cond_wait(&clients_cond, &clients_lock);
			usleep(100 * 1000);
		}
		pthread_mutex_lock(&new_lock);
		if (current_clients >= clients)
		{
	
			pthread_mutex_unlock(&new_lock);
			busy = 0;
			break;
		}
		
		sem_wait(&mutex);
		service_customer();
		busy--;
		kathontai--;
		if(kathontai < 0) kathontai = 0;
		if (busy < 0) busy = 0;
		pthread_cond_signal(&pwlhtes_cond);
		sem_post(&mutex);
		pthread_mutex_unlock(&new_lock);
	}
	return idp;
}

/* thn zhthse h ekfwnshsh */
void* customer_function(void* idp)
{
	while (1) 
	{		
		pthread_mutex_lock(&new_lock);
		if (current_clients >= clients)
		{
			pthread_mutex_unlock(&new_lock);
			break;
		}
		while(busy >= 2) {
			usleep(100 * 1000);
			busy = 0;
		} 
		current_clients++;
		if (kathontai >= chairs)
		{
			efugan++;
			pthread_mutex_unlock(&new_lock);
			break;
		}
		else
		{
			served_clients++;
			kathontai++;
			usleep(buffer[Index] * 1000);
		}
		
		busy++;
		if (busy > 2) busy = 2;
		pthread_mutex_unlock(&new_lock);
	}
	return idp;
}

/* thn zhthse h ekfwnshsh */
void service_customer(void)
{
	useconds_t delay = rand() % 400 + 1;
	buffer[Index] = delay;
	buffer_help[Index] = buffer_help[Index] + delay;
	Index++;
	//usleep(delay * 1000); // douleuei kai xwris auto, an xreiastei to vgazw!
}