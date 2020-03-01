# 1. TCP拥堵说明  
# 1.1 摘要
对多种TCP拥塞控制算法进行简要说明，指出它们的优缺点、以及它们的适用环境。  
# 1.2 关键字
 TCP拥塞控制算法,优点,缺点   适用环境公平性  
# 1.3 公平性
公平性是在发生拥塞时各源端（或同一源端建立的不同TCP连接或UDP数据报）能公平地共享同一网络资源（如带宽、缓存等）。处于相同级别的源端应该得到相同数量的网络资源。产生公平性的根本原因在于拥塞发生必然导致数据包丢失，而数据包丢失会导致各数据流之间为争抢有限的网络资源发生竞争，争抢能力弱的数据流将受到更多损害。因此，没有拥塞，也就没有公平性问题。
TCP层上的公平性问题表现在两方面：  
(1) 面向连接的TCP和无连接的UDP在拥塞发生时对拥塞指示的不同反应和处理，导致对网络资源的不公平使用问题。在拥塞发生时，有拥塞控制反应机制的TCP数据流会按拥塞控制步骤进入拥塞避免阶段，从而主动减小发送入网络的数据量。但对无连接的数据报UDP，由于没有端到端的拥塞控制机制，即使网络发出了拥塞指示（如数据包丢失、收到重复ACK等），UDP也不会像TCP那样减少向网络发送的数据量。结果遵守拥塞控制的TCP数据流得到的网络资源越来越少，没有拥塞控制的UDP则会得到越来越多的网络资源，这就导致了网络资源在各源端分配的严重不公平。  
网络资源分配的不公平反过来会加重拥塞，甚至可能导致拥塞崩溃。因此如何判断在拥塞发生时各个数据流是否严格遵守TCP拥塞控制，以及如何“惩罚”不遵守拥塞控制协议的行为，成了目前研究拥塞控制的一个热点。在传输层解决拥塞控制的公平性问题的根本方法是全面使用端到端的拥塞控制机制。  
(2) 一些TCP连接之间也存在公平性问题。产生问题的原因在于一些TCP在拥塞前使用了大窗口尺寸，或者它们的RTT较小，或者数据包比其他TCP大，这样它们也会多占带宽。  
# 1.4 RTT不公平性  
AIMD(Additive Increase Multiplicative Decrease)拥塞窗口更新策略也存在一些缺陷，和式增加策略使发送方发送数据流的拥塞窗口在一个往返时延(RTT)内增加了一个数据包的大小，因此，当不同的数据流对网络瓶颈带宽进行竞争时，具有较小RTT的TCP数据流的拥塞窗口增加速率将会快于具有大RTT的TCP数据流，从而将会占有更多的网络带宽资源。  
# 1.5 附加说明  
中美之间的线路质量不是很好，rtt较长且时常丢包。TCP协议是成也丢包，败也丢包；TCP的设计目的是解决不可靠线路上可靠传输的问题，即为了解决丢包，但丢包却使TCP传输速度大幅下降。HTTP协议在传输层使用的是TCP协议，所以网页下载的速度就取决于TCP单线程下载的速度（因为网页就是单线程下载的）。
丢包使得TCP传输速度大幅下降的主要原因是丢包重传机制，控制这一机制的就是TCP拥塞控制算法。  
Linux内核中提供了若干套TCP拥塞控制算法，已加载进内核的可以通过内核参数net.ipv4.tcp_available_congestion_control看到。  
# 1.6 Vegas
1994年，Brakmo提出了一种新的拥塞控制机制TCP Vegas，从另外的一个角度来进行拥塞控制。从前面可以看到，TCP的拥塞控制是基于丢包的，一旦出现丢包，于是调整拥塞窗口，然而由于丢包不一定是由于网络进入了拥塞，但是由于RTT值与网络运行情况有比较密切的关系，于是TCP Vegas利用RTT值的改变来判断网络是否拥塞，从而调整拥塞控制窗口。如果发现RTT在增大，Vegas就认为网络正在发生拥塞，于是开始减小拥塞窗口，如果RTT变小，Vegas认为网络拥塞正在逐步解除，于是再次增加拥塞窗口。由于Vegas不是利用丢包来判断网络可用带宽，而是利用RTT变化来判断，因而可以更精确的探测网络的可用带宽，从而效率更好。然而Vegas的有一个缺陷，并且可以说致命的，最终影响TCP Vegas并没有在互联网上大规模使用。这个问题就是采用TCP Vegas的流的带宽竞争力不及未使用TCP Vegas的流，这是因为网络中路由器只要缓冲了数据，就会造成RTT的变大，如果缓冲区没有溢出的话，并不会发生拥塞，但是由于缓存数据就会导致处理时延，从而RTT变大，特别是在带宽比较小的网络上，只要一开始传输数据，RTT就会急剧增大，这个在无线网络上特别明显。在这种情况下，TCP Vegas降低自己的拥塞窗口，但是只要没有丢包的话，从上面看到标准的TCP是不会降低自己的窗口的，于是两者开始不公平，再这样循环下去，TCP Vegas的效率就非常低了。其实如果所有的TCP都采用Vegas拥塞控制方式的话，流之间的公平性会更好，竞争能力并不是Vegas算法本身的问题。  
适用环境：很难在互联网上大规模适用（带宽竞争力低）  
# 1.7 Reno  
Reno是目前应用最广泛且较为成熟的算法。该算法所包含的慢启动、拥塞避免和快速重传、快速恢复机制，是现有的众多算法的基础。从Reno运行机制中很容易看出，为了维持一个动态平衡，必须周期性地产生一定量的丢失，再加上AIMD机制--减少快，增长慢，尤其是在大窗口环境下，由于一个数据报的丢失所带来的窗口缩小要花费很长的时间来恢复，这样，带宽利用率不可能很高且随着网络的链路带宽不断提升，这种弊端将越来越明显。公平性方面，根据统计数据，Reno的公平性还是得到了相当的肯定，它能够在较大的网络范围内理想地维持公平性原则。  
Reno算法以其简单、有效和鲁棒性成为主流，被广泛的采用。  
但是它不能有效的处理多个分组从同一个数据窗口丢失的情况。这一问题在New Reno算法中得到解决。  
# 1.8 基于丢包反馈的协议  
近几年来，随着高带宽延时网络（High Bandwidth-Delay product network）的普及，针对提高TCP带宽利用率这一点上，又涌现出许多新的基于丢包反馈的TCP协议改进，这其中包括HSTCP、STCP、BIC-TCP、CUBIC和H-TCP。  
总的来说，基于丢包反馈的协议是一种被动式的拥塞控制机制，其依据网络中的丢包事件来做网络拥塞判断。即便网络中的负载很高时，只要没有产生拥塞丢包，协议就不会主动降低自己的发送速度。这种协议可以最大程度的利用网络剩余带宽，提高吞吐量。然而，由于基于丢包反馈协议在网络近饱和状态下所表现出来的侵略性，一方面大大提高了网络的带宽利用率；但另一方面，对于基于丢包反馈的拥塞控制协议来说，大大提高网络利用率同时意味着下一次拥塞丢包事件为期不远了，所以这些协议在提高网络带宽利用率的同时也间接加大了网络的丢包率，造成整个网络的抖动性加剧。  
# 1.9 友好性
BIC-TCP、HSTCP、STCP等基于丢包反馈的协议在大大提高了自身吞吐率的同时，也严重影响了Reno流的吞吐率。基于丢包反馈的协议产生如此低劣的TCP友好性的主要原因在于这些协议算法本身的侵略性拥塞窗口管理机制，这些协议通常认为网络只要没有产生丢包就一定存在多余的带宽，从而不断提高自己的发送速率。其发送速率从时间的宏观角度上来看呈现出一种凹形的发展趋势，越接近网络带宽的峰值发送速率增长得越快。这不仅带来了大量拥塞丢包，同时也恶意吞并了网络中其它共存流的带宽资源，造成整个网络的公平性下降。  
# 1.10 HSTCP(High Speed TCP)
HSTCP(高速传输控制协议)是高速网络中基于AIMD(加性增长和乘性减少)的一种新的拥塞控制算法,它能在高速度和大时延的网络中更有效地提高网络的吞吐率。它通过对标准TCP拥塞避免算法的增加和减少参数进行修改，从而实现了窗口的快速增长和慢速减少，使得窗口保持在一个足够大的范围，以充分利用带宽，它在高速网络中能够获得比TCP Reno高得多的带宽，但是它存在很严重的RTT不公平性。公平性指共享同一网络瓶颈的多个流之间占有的网络资源相等。  
TCP发送端通过网络所期望的丢包率来动态调整HSTCP拥塞窗口的增量函数。  
拥塞避免时的窗口增长方式： cwnd = cwnd + a(cwnd) / cwnd  
丢包后窗口下降方式：cwnd = (1-b(cwnd))*cwnd  
其中，a(cwnd)和b(cwnd)为两个函数，在标准TCP中，a(cwnd)=1，b(cwnd)=0.5，为了达到TCP的友好性，在窗口较低的情况下，也就是说在非BDP的网络环境下，HSTCP采用的是和标准TCP相同的a和b来保证两者之间的友好性。当窗口较大时（临界值LowWindow=38），采取新的a和b来达到高吞吐的要求。具体可以看RFC3649文档。
# 1.11 westwood
无线网络中，在大量研究的基础上发现tcpwestwood是一种较理想的算法，它的主要思想是通过在发送端持续不断的检测ack的到达速率来进行带宽估计，当拥塞发生时用带宽估计值来调整拥塞窗口和慢启动阈值，采用aiad(additive increase and adaptive decrease)拥塞控制机制。它不仅提高了无线网络的吞吐量,而且具有良好的公平性和与现行网络的互操作性。存在的问题是不能很好的区分传输过程中的拥塞丢包和无线丢包，导致拥塞机制频繁调用。  
# 1.12 H-TCP
高性能网络中综合表现比较优秀的算法是：h-tcp，但它有rtt不公平性和低带宽不友好性等问题。  
# 1.13 BIC-TCP
BIC-TCP的缺点：首先就是抢占性较强，BIC-TCP的增长函数在小链路带宽时延短的情况下比起标准的TCP来抢占性强，它在探测阶段相当于是重新启动一个慢启动算法，而TCP在处于稳定后窗口就是一直是线性增长的，不会再次执行慢启动的过程。其次，BIC-TCP的的窗口控制阶段分为binary search increase、max probing，然后还有Smax和Smin的区分，这几个值增加了算法上的实现难度，同时也对协议性能的分析模型增加了复杂度。在低RTT网络和低速环境中，BIC可能会过于“积极”，因而人们对BIC进行了进一步的改进，即CUBIC。是Linux在采用CUBIC之前的默认算法。
# 1.14 CUBIC
CUBIC在设计上简化了BIC-TCP的窗口调整算法，在BIC-TCP的窗口调整中会出现一个凹和凸(这里的凹和凸指的是数学意义上的凹和凸，凹函数/凸函数)的增长曲线，CUBIC使用了一个三次函数(即一个立方函数)，在三次函数曲线中同样存在一个凹和凸的部分，该曲线形状和BIC-TCP的曲线图十分相似，于是该部分取代BIC-TCP的增长曲线。另外，CUBIC中最关键的点在于它的窗口增长函数仅仅取决于连续的两次拥塞事件的时间间隔值，从而窗口增长完全独立于网络的时延RTT，之前讲述过的HSTCP存在严重的RTT不公平性，而CUBIC的RTT独立性质使得CUBIC能够在多条共享瓶颈链路的TCP连接之间保持良好的RTT公平性。  
CUBIC is a congestion control protocol for TCP (transmission control protocol) and thecurrent default TCP algorithm in Linux. The protocol modifies the linear window growth function of existing TCP standards to be a cubic function in order to improve the scalability of TCP over fast and long distance networks. It also achieves more equitable bandwidth allocations among flows with different RTTs (round trip times) by making the window growth to be independent of RTT – thus those flows grow their congestion window at the same rate. During steady state, CUBIC increases the window size aggressively when the window is far from the saturation point, and the slowly when it is close to the saturation point.This feature allows CUBIC to be very scalable when the bandwidth and delay product of the network is large, and at the same time, be highly stable and also fair to standard TCP flows.  
# 1.15 STCP  
STCP，Scalable TCP。  
STCP算法是由 Tom Kelly于 2003年提出的 ,通过修改TCP的窗口增加和减少参数来调整发送窗口大小 ,以适应高速网络的环境。该算法具有很高的链路利用率和稳定性，但该机制窗口增加和RTT成反比 ,在一定的程度上存在着 RTT不公平现象 ,而且和传统 TCP流共存时 ,过分占用带宽 ,其 TCP友好性也较差。  