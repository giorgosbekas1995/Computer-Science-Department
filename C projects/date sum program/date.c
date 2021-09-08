#include <stdio.h>

int main(){
int year1,month1,day1;
int year2,month2,day2;
int f_year,f_month,f_day;
f_year = 0;
f_month = 0;
f_day = 0;

printf("Give date1 and date2\n");
scanf("%d %d %d %d %d %d",&year1,&month1,&day1,&year2,&month2,&day2);

f_day = day1 + day2;
f_month = month1 + month2;

if(f_month > 12){
f_month -= 12;
f_year += 1;
}

if(f_month%2 == 1 && f_day > 31){
f_month++;
f_day -= 31;
}

else if(f_month%2 == 0 && f_day >30){
f_month++;
f_day -= 30;
}

else if(f_month == 2 && f_day>29){
f_month++;
f_day -= 29;
}

f_year = f_year + year1 + year2;

printf("New date is %d/%d/%d ", f_year, f_month, f_day);

} 
