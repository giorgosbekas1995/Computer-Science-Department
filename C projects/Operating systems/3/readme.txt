/**
 * grocery store problem
 * Giorgos Bekas
 * hy345 homework 2
 */
compile: gcc grocery.c -lrt -lpthread
run: ./a.out CHAIRS CLIENTS gia paradeigma ./a.out 100 1000
Ftiaxnw 2 threads pwlitwn
Ftiaxnw N threads clients
exw enan pinaka poy apoteleitai apo oses chairs edwse o xrhsths sthn ekfwnhsh

1. an den yparxoun pelates oi pwlhtes koimountai
2. an erhtei pelaths alla oi karekles einai piasmenes COUNTER++
3. an erhtei pelaths alla oi pwlhtes eina busy kathete se mia karekla
4. an erhtei pelaths alla oi pwlhtes koimountai, ksupnaei enan

Typwnw twn aritmo twn pelatwn pou efugan (einai apla enas counter)
Typwnw ton meso oro tou pinaka pou antistoixei ston xrono anamonis

gia na ftiaksw ta threads xrhsimopoihsa tis:
pthread_create(&threadspwlhtwn[i], NULL, &grocer_function, NULL);
pthread_create(&threadsclients[i], NULL, &customer_function, NULL);

gia na termatisw ta threads xrhsimopoihsa tis:
pthread_join(threadsclients[i], NULL);
pthread_join(threadspwlhtwn[i], NULL);

gia tis anamones xrhsimopoihsa thn:
usleep(delay); pou perimenei delay milliseconds