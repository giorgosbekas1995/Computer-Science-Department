#include <stdio.h>

	char a[3][3] ={ {' ',' ',' '},
	                {' ',' ',' '},  /*arxikopoihsh kenou pinaka to kanoume eksw apo th main gia na min xriazete na ton dhlwnoume se oles tis sinartiseis*/
				    {' ',' ',' '}
			};


int main()
{
	

	
	
	
	
int x,y;
int player =0,choice;
char mark;

	

for(;;)
{
board();  /*tipwnei ton adeio pinaka*/	
player=player%2 + 1;/*o paixths tha einai panta 1 h 2 diladi oi pextes tha pezoun enalaks*/
player == 1 ? printf("Player X: ") : printf("Player O: ");/*an o pexths einai 1 tipwnete oti einai i sira tou 'X' aliws tou 'O'*/
mark=(player == 1) ? 'X' : 'O';/*an o paixths einai 1 tipwnete 'X' sto kouti pou theloume aliws 'O'*/
scanf("%d",&choice);/*dialegoume to kouti pou theloume na peksoume*/

if (choice == 1 && a[0][0] == ' ')
a[0][0] = mark;
else if (choice == 2 && a[0][1] == ' ')
a[0][1] = mark;
else if (choice == 3 && a[0][2]== ' ')  /*arxikopoioume to kathe kouti me thn antistoixh epilogh pou tha kanoume*/
a[0][2] = mark;                         /*kai vazoume kai th sinthiki oti prepi na einai kena gia na grapsoume*/
else if (choice == 4 && a[1][0]== ' ')  /*wste na min ginete na ksanagrapsoume se auta ta koutia otan exoume hdh*/
a[1][0] = mark;                         /*grapsi kai mono oi arithmoi apo to 1-9 tha ginoun dektoi*/
else if (choice == 5 && a[1][1]== ' ')
a[1][1] = mark;
else if (choice == 6 && a[1][2]== ' ')
a[1][2] = mark;
else if (choice == 7 && a[2][0]== ' ')
a[2][0] = mark;
else if (choice == 8 && a[2][1]== ' ')
a[2][1] = mark;
else if (choice == 9 && a[2][2]== ' ')
a[2][2] = mark;
else
{
printf("Lathos kinisi prospathise pali ");
player--; /* an kanei lathos kinisi gia na min paei ston epomeno pexti vazoume -- na paramini ston idio pexti */
}

checkwin();
if(checkwin()==1){
	printf("\n\nPlayer X Won\n\n");/*an h sinarthsh epistrepsi 1 tipwnoume oti nikaei o 'X'*/
     break;
}else if(checkwin()==2){
	printf("\n\nPlayer O Won\n\n");/*an h sinartisi epistepsi 2 tipwnoume oti nikaei o 'O'*/
	break;
}else 
  for(x=0; x<3; x++){
    for(y=0; y<3; y++)
      if(a[x][y]==' ')break;
    if(a[x][y]==' ')break;
}
                                          /*an piastoun kai oi 9 theseis kai dn exei vgei nikiths tipwnei isopalia*/

  if(x*y==9)  {
  	printf("\n\nMatch is Draw\n\n");
    break;
}


}

board(); /* emfanizi ton pinaka afou exoume grapsi 'X' h 'O'*/
}

		   

int checkwin(){
	int j;
	 if((a[0][0] =='X' && a[1][1] =='X' && a[2][2]=='X') ||
       (a[0][2] =='X' && a[1][1] == 'X' && a[2][0]=='X')){ /*sinthiki gia diagwnia gia ton 'X'*/
       
	   
         return 1;

     } else
    
           for(j=0;j<3;j++)
             if((a[j][0] =='X' && a[j][1] =='X' && a[j][2] =='X')||
                (a[0][j] =='X' && a[1][j] =='X' && a[2][j]=='X')){  /*sinthiki katheta kai orizontia gia ton 'X'*/
             return 1;
             
         }else
         
     
             if((a[0][0] =='O' && a[1][1] =='O' && a[2][2]=='O') ||
         (a[0][2] =='O' && a[1][1] == 'O' && a[2][0]=='O')){  /*sinthiki gia diagwnia gia ton 'O'*/
         return 2;
    
   }else
      
      
        for(j=0;j<3;j++)
          if((a[j][0] =='O' && a[j][1] =='O' && a[j][2] =='O')||
             (a[0][j] =='O' && a[1][j] =='O' && a[2][j] =='O')){ /*sinthiki katheta kai orizontia gia ton 'O'*/
		  return 2;
             


}
  

}









void board()/*tipwnei ti triliza*/
{
printf("\n\n");
printf(" %c | %c | %c  \n", a[0][0], a[0][1], a[0][2]);
printf("---+---+---\n");
printf(" %c | %c | %c  \n", a[1][0], a[1][1], a[1][2]);
printf("---+---+---\n");
printf(" %c | %c | %c  \n", a[2][0], a[2][1], a[2][2]);

 }

