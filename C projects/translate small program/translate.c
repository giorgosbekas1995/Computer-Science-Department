#include <stdio.h>



char cmap[255][3];

void init_cmap(){
	cmap[193][0]=65;
	cmap[194][0]=86;
	cmap[195][0]=71;
	cmap[196][0]=68;
	cmap[197][0]=69;
	cmap[198][0]=90;
	cmap[199][0]=72;
	cmap[200][0]=56;
	cmap[201][0]=73;
	cmap[202][0]=75;
	cmap[203][0]=76;
	cmap[204][0]=77;
	cmap[205][0]=78;
	cmap[206][0]=75; cmap[206][1]=83;
	cmap[207][0]=79;
	cmap[208][0]=80;
	cmap[209][0]=82;
	cmap[211][0]=83;
	cmap[212][0]=84;
	cmap[213][0]=89;
	cmap[214][0]=70;
	cmap[215][0]=88;
	cmap[216][0]=80; cmap[216][1]=83;
	cmap[217][0]=87;
	cmap[225][0]=97;
	cmap[226][0]=118;
	cmap[227][0]=103;
	cmap[228][0]=100;
	cmap[229][0]=101;
	cmap[230][0]=122;
	cmap[231][0]=104;
	cmap[232][0]=56;
	cmap[233][0]=105;
	cmap[234][0]=107;
	cmap[235][0]=108;
	cmap[236][0]=109;
	cmap[237][0]=110;
	cmap[238][0]=107; cmap[238][1]=115;
	cmap[239][0]=111;
	cmap[240][0]=112;
	cmap[241][0]=114;
	cmap[242][0]=115;
	cmap[243][0]=115;
	cmap[244][0]=116;
	cmap[245][0]=121;
	cmap[246][0]=102;
	cmap[247][0]=120;
	cmap[248][0]=112; cmap[248][1]=115;
	cmap[249][0]=119;
	cmap[182][0]=39; cmap[182][1]=65;
	cmap[184][0]=39; cmap[184][1]=69;
	cmap[185][0]=39; cmap[185][1]=72;
	cmap[186][0]=39; cmap[186][1]=73;
	cmap[188][0]=39; cmap[188][1]=79;
	cmap[191][0]=39; cmap[191][1]=87;
	cmap[190][0]=39; cmap[190][1]=89;
	cmap[220][0]=97; cmap[220][1]=39;
	cmap[221][0]=101; cmap[221][1]=39;
	cmap[222][0]=104; cmap[222][1]=39;
	cmap[223][0]=105; cmap[223][1]=39;
	cmap[252][0]=111; cmap[252][1]=39;
	cmap[253][0]=121; cmap[253][1]=39;
	cmap[254][0]=119; cmap[254][1]=39;
	cmap[218][0]=73;  cmap[218][1]=34;
	cmap[219][0]=89;  cmap[219][1]=34;
	cmap[250][0]=105; cmap[250][1]=34;
	cmap[251][0]=121; cmap[251][1]=34;
	cmap[224][0]=121; cmap[224][1]=39; cmap[224][2]=34;
	cmap[192][0]=105; cmap[192][1]=39; cmap[192][2]=34;
	cmap[181][0]=39; cmap[181][1]=34;
	cmap[180][0]=39;
}

void print(int c){
int i=0;
	if(cmap[c][i]=='\0'){
            putchar(c);
                }else
      while(cmap[c][i]!='\0' && i<3){
            putchar(cmap[c][i]);

           i++;
        }
}


int main(){

int c;

 init_cmap();
		while((c=getchar())!=EOF){

		if(c==204){
		c=getchar();
		if(c==208||c==240){
		putchar(66);
		}else{
		putchar(77);
		print(c);
		}
		}else
		if(c==236){
		c=getchar();
		if(c==208||c==240){
		putchar(98);
		}else{
		putchar(109);
		print(c);
		}
		}else
                if(c==205){
                c=getchar();
                if(c==212||c==244){
                putchar(68);
                }else{
                putchar(78);
                print(c);
                }
                }else
                if(c==237){
                c=getchar();
                if(c==212||c==244){
                putchar(100);
                }else{
                putchar(110);
                print(c);
                }
                }else
		print(c);



	}


}
