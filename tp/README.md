# 1. UDT source
```
git clone https://git.code.sf.net/p/udt/git
```
# 2. Config dev ENV
```
cd git/udt
pwd         # output app  doc src win etc.
make -e os=linux arc=amd64  # follow the document.
cd /etc/ld.so.conf.d
sudo vim customized.conf    # add line with content {DIR}/git/udt
sudo /sbin/ldconfig
cd git/udt/app
./test        # now everything goes on, you can play with UDT now
```
# 3. Test UDT and TCP in a customized network
# 4. Test web throughput bottleneck
# 5. Congestion Control

CCC - Base Congestion Control Class  
CTCP - TCP NewReno  
CGTP - Group Transport Protocol  
CUDPBlast - Reliable UDP Blast  
CVegas - TCP Vegas  
CScalable - Scalable TCP  
CHS - HighSpeed TCP  
CBiC - BiC TCP  
CWestwood - TCP Westwood  
CFAST - FAST TCP
