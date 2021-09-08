import os
import sys 
import getopt 
import subprocess 
import socket 
import time 
import threading 
import thread
import random
import time
import urllib

end_servers = sys.argv[2]
relay_nodes = sys.argv[4]
Tracefile = open("trace.txt","a")
Pingfile = open("ping.txt","a")

global relay_avg
global relay_hops
global direct_hops
global direct_avg


relay_avg = 0
relay_hops = 0
direct_hops = 0

rtt_table = [0]*11
hops_table = [0]*11
ip_table = [0]*11
hops_pos = [0]*11

print("Give alias:")
alias = sys.stdin.readline()
relay_node = raw_input("Give relay node ")
##RTT_or_HOPS = raw_input("RTT or HOPS")
pings = int(input("Give me ping "))
cport = int(input("Give me port "))

with open(end_servers) as fp:
    line = fp.readline().split(', ')
    while line:
    	    if line[-1]=='':
    		    break
	    
            if line[-1] == alias:
                alias=line[0]
                break
            
            line =  fp.readline().split(', ')
            

with open(relay_nodes) as x:
    line = x.readline().split(', ')
    while line:
    	    if line[-1]=='':
    		    break
	    
            if line[0] == relay_node:
                relay_node=line[1]
                break
            
            line =  x.readline().split(', ')


p1 = subprocess.Popen(['ping',alias,'-c '+str(pings)], stdout=subprocess.PIPE)
while True:
    line2 = p1.stdout.readline()
    if "avg" in line2:
        direct_avg = float(line2.split('/')[4])
        print 'Direct Mode RTT = ' + str(direct_avg)  
    if not line2:
        break
 


from subprocess import Popen, PIPE
p = Popen(["traceroute", str(alias)],stdout=PIPE)
while True:
    line = p.stdout.readline()
    direct_hops += 1
    if not line:
        break

print 'Direct Mode Number of hops are : ' + str(direct_hops-2)



def client(relayip,port):
    
    RMode_avg = 0
    RMode_hops = 0
    client_avg = 0
    number_of_hops = 0
    RECV_BUFFER_SIZE = 1024 
    # Create a TCP/IP socket
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    
    # Connect the socket to the port where the server is listening
    server_address = (relayip, int(port))
    print >>sys.stderr, 'connecting to %s port %s' % server_address
    sock.connect(server_address)
    
    try:
    # Send data
        ping = subprocess.Popen(['ping',relayip,'-c '+str(pings)], stdout=subprocess.PIPE)
        while True:
            line2 = ping.stdout.readline()
            if "avg" in line2:
                client_avg = float(line2.split('/')[4])
            if not line2:
                break
        from subprocess import Popen, PIPE
        p = Popen(["traceroute", relayip],stdout=PIPE)
        number_of_hops = 0
        while True:
            line = p.stdout.readline()
            number_of_hops += 1
            if not line:
                break

        message = "send"
        sock.sendall(message)
    
    # Look for the response
            
        data = sock.recv(RECV_BUFFER_SIZE)
        print >>sys.stderr, 'received "%s"' % data
        relay_avg = float(data.split()[5])
        relay_hops = int(data.split()[2])
        print 'Relay Mode Avg RTT = ' + str(client_avg + relay_avg)
        print 'Relay Mode Number Of Hops = ' + str((number_of_hops-2) + relay_hops)
        RMode_avg = client_avg + relay_avg
        RMode_hops = (number_of_hops-2) + relay_hops
        return RMode_avg,RMode_hops

    finally:
        print >>sys.stderr, 'closing socket'
        sock.close()
        
def downfile(relayip,port):
    
    RECV_BUFFER_SIZE = 1024 
    # Create a TCP/IP socket
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    
    # Connect the socket to the port where the server is listening
    server_address = (relayip, int(port))
    print >>sys.stderr, 'connecting to %s port %s' % server_address
    sock.connect(server_address)
    
    try:
    # Send data
        
        message = "download"
        sock.sendall(message)
    
    # Look for the response
            
        data = sock.recv(RECV_BUFFER_SIZE)
        print >>sys.stderr, 'received "%s"' % data
        
    finally:
        print >>sys.stderr, 'closing socket'
        sock.close()

        
##client(relay_node,cport)

with open(relay_nodes) as x:
    line = x.readline().split(', ')
    i = 0
    while line:
    	    if line[-1]=='':
    		    break
            if i == 3:
                    break
	    ip_table[i] = line[1]
            rtt_table[i],hops_table[i] = client(line[1],cport)
            print client(line[1],cport)
            i += 1
            line =  x.readline().split(', ')

min = 100000000
equal = 0
for x in range(11):
    if rtt_table[x]!=0:
        if rtt_table[x] == min:
            hops_pos[equal+1] == x   
	    equal += 1
        if rtt_table[x] < min:
            min = rtt_table[x]
            hops_pos[equal] = x



min_hop = 31

eqhops = 0
if equal > 0:
    for i in range(equal):
        if hops_table[hops_pos[i]] < min_hop:
            min_hop =  hops_table[hops_pos[i]]  
            hopminpos = hops_pos[i]
	    equal_hops[eqhops] = hops_pos[i]
	if hops_table[hops_pos[i]] == min_hop:
	    equal_hops[eqhops+1] = hops_pos[i]
	    eqhops+=1
elif equal == 0:
    re_ip = ip_table[hops_pos[0]]  
    downfile(re_ip,cport)
if eqhops == 0 and equal !=0:
    re_ip = ip_table[hopminpos]
    downfile(re_ip,cport)
elif eqhops > 0:
    random.choise(eqhops) 


