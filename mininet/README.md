# 1. GUI
 
 ```
 cd mininet/examples
 python ./miniedit.py
 ```
 
 File -> Export Level 2 Script -> test.py
 
 ```
 sudo python ./test.py
 iperf h1 h2                    #   测试两个主机h1和h2之间的TCP带宽
 iperfupd bw h1 h2              #   测试两个主机h1和h2之间的UDP带宽
 ```

 h1 ping h2 发现 unreachable时，因为没有添加流表，手动添加流表
 ```
 dpctl add-flow "idle_timeout=60000,in_port=2,actions=output:1"
 
 dpctl add-flow "idle_timeout=60000,in_port=1,actions=output:2"
 ```
 表示端口1进来的流量从端口2转发，当等待60s没有流量转发的话就删除流表


