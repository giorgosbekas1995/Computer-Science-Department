import os
import sys 
import getopt 
import subprocess 
import socket 
import time 
import threading 
import thread

end_servers = sys.argv[2]
number_of_hops = 0
Tracefile = open("trace.txt","a")
Pingfile = open("ping.txt","a")
pings = 5
print("Give alias:")
alias = sys.stdin.readline()


with open(end_servers) as fp:
    line = fp.readline().split(', ')
    while line:
            if line[-1]=='':
                break
        
            if line[-1] == alias:
                alias=line[0]
                break
            
            line =  fp.readline().split(', ')


ping = subprocess.Popen(['ping',alias,'-c '+str(pings)], stdout=subprocess.PIPE)


while True:
    line2 = ping.stdout.readline()
    Pingfile.write(str(line2))
    print line2
    if "avg" in line2:
        print line2.split('/')[1] + ' = ' + line2.split('/')[4]
    if not line2:
        break
 

Pingfile.close()





from subprocess import Popen, PIPE
p = Popen(["traceroute",str(alias)],stdout=PIPE)
while True:
    line = p.stdout.readline()
    Tracefile.write(str(line))
    number_of_hops += 1
    print line
    if not line:
        break
    # Do stuff with line
Tracefile.close()

print("Hops: ",  number_of_hops-2)

