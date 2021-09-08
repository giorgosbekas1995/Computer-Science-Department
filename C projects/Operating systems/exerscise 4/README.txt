\# Giorgos Bekas
# Leitourgika hy345
# Assignment 4
Ylopoihsh tis Lowest Demand First scheduling policy, 
ston metalagmeno mou kernel :P
Vrisko to task me to mikrotero demand_time kai to ektelw.
An dne vrethei kanena, dld an to min einai 101, tote
ekteleitai o Linux scheduler xwris allages, opws lete kai sthn
ekfwnhsh

Eftiaksa dyo programma gia na testarw tis allages ston scheduler
To ena exei demand_time 20 kai to allo 40 epeidh sthn ekfwnhsh
mas eipate na afhnoume apostasi

Ta exw valei arketa megala wste na treksoun kai ta dyo.
Ta etreksa etsi:
./test1.out &
./test2.out &

Xreiasthke na dw sthn kernel/sched.c ton kwdika tis
pick_next_task <--- edw ekana tis allages kuriws
kai thn __sched schedule
