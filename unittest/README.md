# 1. TCP Test
# 1.1 长肥管道网络（LFN，long fat network）throughput test
 测试结果如下表所示  

| Bandwidth | Delay | Protocol | Throughput |  File |
| --- | ---| --- | ---|  -- |
| 1Gbps | 5ms | TCP | 900Mbps |  tcp_traffic_1Gbps_5ms.png |
| 1Gbps | 50ms | TCP | 600Mbps |  tcp_traffic_1Gbps_50ms.png |
| 1Gbps | 50ms | UDT | 240Mbps | udt_traffic_1Gbps_50ms.png |

1Gbps 5ms 网络吞吐量测试结果如下图  
![tcp/tcp_traffic_1Gbps_5ms.png](./tcp/tcp_traffic_1Gbps_5ms.png)

1Gbps 50ms 网络吞吐量测试结果如下图  
![tcp/tcp_traffic_1Gbps_50ms.png](./tcp/tcp_traffic_1Gbps_50ms.png)

# 1.2 Congestion Window
Test condition

| Bandwidth | Delay | packetSize  | dataRate | File |
| --- | ---| --- | --- | --- |  
| 100Mbps | 1ms | 1040byte | 100Mbps | tcp/cwnd100Mbps1ms.png |
| 1Gbps | 5ms | 1040byte | 500Mbps | tcp/cwnd1Gbps5ms.png |
| 1Gbps | 50ms | 1040byte | 500Mbps | tcp/cwnd1Gbps50ms.png |

Congestion windows size changed as following   
![tcp/cwnd100Mbps1ms.png](./tcp/cwnd100Mbps1ms.png)  
![tcp/cwnd1Gbps5ms.png](./tcp/cwnd1Gbps5ms.png)  
![tcp/cwnd1Gbps50ms.png](./tcp/cwnd1Gbps50ms.png)  
# 2. UDT
## 2.1 network traffic
```
ifstat -i lo
```
| Bandwidth | Delay | Protocol | Throughput |  File |
| --- | ---| --- | ---|  -- |
| 1Gbps | 5ms | UDT |  |   |
| 1Gbps | 50ms | UDT | 240Mbps |  udt_traffic_1Gbps_50ms.png |

1Gbps 50ms 网络吞吐量测试结果如下图  
![tcp/udt_traffic_1Gbps_50ms.png](./udt/udt_traffic_1Gbps_50ms.png)
