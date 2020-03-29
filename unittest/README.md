# 1. TCP Test
# 1.1 长肥管道网络（LFN，long fat network）throughput test
 测试结果如下表所示  

| Bandwidth | Delay | Protocol | Throughput |  File |
| --- | ---| --- | ---|  -- |
| 1Gbps | 5ms | TCP | 900Mbps |  1Gbps_5ms_mark.png |
| 1Gbps | 50ms | TCP | 600Mbps |  1Gbps_50ms_mark.png |

1Gbps 5ms 网络吞吐量测试结果如下图  
![1Gbps_5ms_mark.png](./1Gbps_5ms_mark.png)

1Gbps 50ms 网络吞吐量测试结果如下图  
![1Gbps_50ms_mark.png](./1Gbps_50ms_mark.png)

# 1.2 Congestion Window
Test condition

| Bandwidth | Delay | Protocol | packetSize |  packetSnd | sndRate | File |
| --- | ---| --- | ---| --- | --- | --- |  
| 1Gbps | 5ms | TCP | 1040byte |  1000 | 1Mbps | cwnd1Mbps.png |
| 1Gbps | 5ms | TCP | 1040byte |  1000 | 500Mbps | cwnd500Mbps.png |

Congestion windows size changed as following  
Send rate as 1Mbps   
![cwnd1Mbps.png](./cwnd1Mbps.png)   
