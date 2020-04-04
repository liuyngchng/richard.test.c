# 1. topo

topo as following  

![topo.png](./topo.png)  

end to end delay as table below:  

| No| from  | to | delay(ms) |  
| --| -- | -- | -- |  
| 1 | h1 | h2 | 2 |  
| 2 | h1 | h5 | 20 |  
| 3 | h1 | h9 | 30 |  
| 4 | h1  | h13 | 40 |  
| 5 | h1 | h17 | 50 |  

# 2. TCP Faireness  

setup 5 concurrent flow, traffic distribution as following  
![traffic.png](./traffic.png)  

throughput faireness details as below

| No  | delay(ms) |  throughput(Mbps) |  
| -- | -- | -- |  
| 1 | 2 | 240 |  
| 2 | 20 | 190 |  
| 3 | 30 | 180 |  
| 4  | 40 | 160 |  
| 5 | 50 | 140 |   

2ms  
![2ms.png](./tcp/2ms.png)  

20ms  
![20ms.png](./tcp/20ms.png)  

30ms  
![30ms.png](./tcp/30ms.png)  

40ms  
![40ms.png](./tcp/40ms.png)  

50ms  
![50ms.png](./tcp/50ms.png)  

# 3. conclusion
With the same bandwith, TCP congestion control would distribute  
more bandwith to the end with smaller delay time.
