all:
	gcc -std=c99 -o otp otp.c
	gcc -std=c99 -o caesars caesars.c
	gcc -std=c99 -o spartans spartan.c
	gcc -std=c99 -o vigenere vigenere.c

clean:
	rm otp caesars spartans vigenere 

test:
	echo "Test for otp";
	echo asdfgtyhSDF57  | ./otp;
	echo ABCDZASDF  | ./otp;
	echo  X72YQASDFK  | ./otp;
	echo Ab47XxzB | ./otp;

	echo "Test for caesars";
	echo asdfgtyhSDF57 5 | ./caesars;
	echo ABCDZASDF 7 | ./caesars;
	echo  X72YQASDFK 3 | ./caesars;
	echo Ab47XxzB 7 | ./caesars;

	echo "Test for spartans";
	echo 5 7 asdfgtyhSDF57  | ./spartans;
	echo 4 5 ABCDZASDF  | ./spartans;
	echo 5 9 X72YQASDFK  | ./spartans;
	echo 7 7 Ab47XxzB | ./spartans;
	echo 4 5 Iamhurtverybadlyhelp  | ./spartans;

	echo "Test for vigenere";
	echo ASDFGH QWER  | ./vigenere;
	echo ABCDZASDF SAFDSGFD | ./vigenere;
	echo  XYQASDFK ATSK | ./vigenere;
	echo ASIRYJ KZJTH | ./vigenere;


