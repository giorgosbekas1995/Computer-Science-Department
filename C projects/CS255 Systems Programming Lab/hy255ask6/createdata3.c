#include <stdio.h>

int main(){
	int i;
	FILE *data3;

	data3=fopen("data3.txt","w+");
	for(i=0;i<100;i++){
	fputs("2",data3);
	}
	fclose(data3);
        return 0;
}
