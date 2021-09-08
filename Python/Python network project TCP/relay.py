import os
import sys
import getopt
import subprocess
import socket
import time
import threading
import thread
import urllib

end_servers = sys.argv[2]
files2download = sys.argv[4]
Tracefile = open("trace.txt","a")
Pingfile = open("ping.txt","a")
print("Give alias:")
alias = sys.stdin.readline()
url = ""
global relay_hops
global rtt_avg


pings = int(input("Give me ping "))
rport = int(input("Give me port "))

with open(end_servers) as fp:
    line = fp.readline().split(', ')
    while line:
    	    if line[-1]=='':
    		    break
	    
            if line[-1] == alias:
                alias=line[0]
                break
            
            line =  fp.readline().split(', ')


with open(files2download) as fp:
    line = fp.readline()
    while line:
    	    if line[-1]=='':
    		    break
	    print line
            if alias in line:
                url=line
                break
            
            line =  fp.readline()

def Relay_socket(port):
    
    RECV_BUFFER_SIZE = 1024 

    # Create a TCP/IP socket
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    
    # Bind the socket to the port
    
    #By setting the host name to the empty string, it tells the bind() method to fill in the address of the current machine.
    
    server_address = ('', int(port))
    print >>sys.stderr, 'starting up on %s port %s' % server_address
    sock.bind(server_address)
    
    # Listen for incoming connections
    sock.listen(1)
    
    while True:
        # Wait for a connection
        print >>sys.stderr, 'waiting for a connection'
        connection, client_address = sock.accept()
        
        try:
            print >>sys.stderr, 'connection from', client_address
            
            while True:

                data = connection.recv(RECV_BUFFER_SIZE)
                print >>sys.stderr, 'received "%s"' % data
                if data == "download":
                    file = urllib.urlretrieve(url, "img.png")
                    connection.sendall(str(file))
                    break
                if data:
                    ping = subprocess.Popen(['ping',alias,'-c '+str(pings)], stdout=subprocess.PIPE)
                    while True:
                        line2 = ping.stdout.readline()
                        if "avg" in line2:
                            rtt_avg = line2.split('/')[4]
                            print  'Relay -> End_server avg RTT = ' + rtt_avg
                        if not line2:
	                    break

                    from subprocess import Popen, PIPE
	            p = Popen(["traceroute", str(alias)],stdout=PIPE)
                    relay_hops = 0
                    while True:
                        line = p.stdout.readline()
                        relay_hops += 1
                        if not line:
                            break
                    
                    print 'Relay -> End_server hops = ' + str(relay_hops-2)
                    print >>sys.stderr, 'sending back to the client ' + str(relay_hops-2) + 'hops and ' + rtt_avg + ' rtt avg' 
                    connection.sendall("relay_hops = " + str(relay_hops-2) + " relay_avg = " + rtt_avg)
                else:
                    print >> sys.stderr, 'no more data from', client_address
                    break

        finally:
            # Clean up the connection
            connection.close()


Relay_socket(rport)

