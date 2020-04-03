#!/usr/bin/python

from mininet.net import Mininet
from mininet.node import Controller, RemoteController, OVSController
from mininet.node import CPULimitedHost, Host, Node
from mininet.node import OVSKernelSwitch, UserSwitch
from mininet.node import IVSSwitch
from mininet.cli import CLI
from mininet.log import setLogLevel, info
from mininet.link import TCLink, Intf
from subprocess import call

def myNetwork():

    net = Mininet( topo=None,
                   build=False,
                   ipBase='10.0.0.0/8')

    info( '*** Adding controller\n' )
    info( '*** Add switches\n')
    s7 = net.addSwitch('s7', cls=OVSKernelSwitch, failMode='standalone')
    s10 = net.addSwitch('s10', cls=OVSKernelSwitch, failMode='standalone')
    s9 = net.addSwitch('s9', cls=OVSKernelSwitch, failMode='standalone')
    s8 = net.addSwitch('s8', cls=OVSKernelSwitch, failMode='standalone')
    s5 = net.addSwitch('s5', cls=OVSKernelSwitch, failMode='standalone')
    s2 = net.addSwitch('s2', cls=OVSKernelSwitch, failMode='standalone')
    s6 = net.addSwitch('s6', cls=OVSKernelSwitch, failMode='standalone')
    s3 = net.addSwitch('s3', cls=OVSKernelSwitch, failMode='standalone')
    s4 = net.addSwitch('s4', cls=OVSKernelSwitch, failMode='standalone')
    s1 = net.addSwitch('s1', cls=OVSKernelSwitch, failMode='standalone')

    info( '*** Add hosts\n')
    h14 = net.addHost('h14', cls=Host, ip='10.0.0.14', defaultRoute=None)
    h15 = net.addHost('h15', cls=Host, ip='10.0.0.15', defaultRoute=None)
    h5 = net.addHost('h5', cls=Host, ip='10.0.0.5', defaultRoute=None)
    h6 = net.addHost('h6', cls=Host, ip='10.0.0.6', defaultRoute=None)
    h16 = net.addHost('h16', cls=Host, ip='10.0.0.16', defaultRoute=None)
    h7 = net.addHost('h7', cls=Host, ip='10.0.0.7', defaultRoute=None)
    h8 = net.addHost('h8', cls=Host, ip='10.0.0.8', defaultRoute=None)
    h9 = net.addHost('h9', cls=Host, ip='10.0.0.9', defaultRoute=None)
    h1 = net.addHost('h1', cls=Host, ip='10.0.0.1', defaultRoute=None)
    h10 = net.addHost('h10', cls=Host, ip='10.0.0.10', defaultRoute=None)
    h11 = net.addHost('h11', cls=Host, ip='10.0.0.11', defaultRoute=None)
    h2 = net.addHost('h2', cls=Host, ip='10.0.0.2', defaultRoute=None)
    h12 = net.addHost('h12', cls=Host, ip='10.0.0.12', defaultRoute=None)
    h3 = net.addHost('h3', cls=Host, ip='10.0.0.3', defaultRoute=None)
    h13 = net.addHost('h13', cls=Host, ip='10.0.0.13', defaultRoute=None)
    h4 = net.addHost('h4', cls=Host, ip='10.0.0.4', defaultRoute=None)

    info( '*** Add links\n')
    s1h1 = {'bw':1000,'delay':'8ms'}
    net.addLink(s1, h1, cls=TCLink , **s1h1)
    s1h2 = {'bw':1000,'delay':'8ms'}
    net.addLink(s1, h2, cls=TCLink , **s1h2)
    s5s1 = {'bw':1000,'delay':'8ms'}
    net.addLink(s5, s1, cls=TCLink , **s5s1)
    s7s5 = {'bw':1000,'delay':'8ms'}
    net.addLink(s7, s5, cls=TCLink , **s7s5)
    s7s6 = {'bw':1000,'delay':'8ms'}
    net.addLink(s7, s6, cls=TCLink , **s7s6)
    s6s4 = {'bw':1000,'delay':'8ms'}
    net.addLink(s6, s4, cls=TCLink , **s6s4)
    s4h13 = {'bw':1000,'delay':'8ms'}
    net.addLink(s4, h13, cls=TCLink , **s4h13)
    s4h16 = {'bw':1000,'delay':'8ms'}
    net.addLink(s4, h16, cls=TCLink , **s4h16)
    s1h3 = {'bw':1000,'delay':'8ms'}
    net.addLink(s1, h3, cls=TCLink , **s1h3)
    s1h4 = {'bw':1000,'delay':'8ms'}
    net.addLink(s1, h4, cls=TCLink , **s1h4)
    s5s8 = {'bw':1000,'delay':'8ms'}
    net.addLink(s5, s8, cls=TCLink , **s5s8)
    s8s6 = {'bw':1000,'delay':'8ms'}
    net.addLink(s8, s6, cls=TCLink , **s8s6)
    s5s2 = {'bw':1000,'delay':'8ms'}
    net.addLink(s5, s2, cls=TCLink , **s5s2)
    s6s3 = {'bw':1000,'delay':'8ms'}
    net.addLink(s6, s3, cls=TCLink , **s6s3)
    s2h5 = {'bw':1000,'delay':'8ms'}
    net.addLink(s2, h5, cls=TCLink , **s2h5)
    s2h6 = {'bw':1000,'delay':'8ms'}
    net.addLink(s2, h6, cls=TCLink , **s2h6)
    s2h7 = {'bw':1000,'delay':'8ms'}
    net.addLink(s2, h7, cls=TCLink , **s2h7)
    s2h8 = {'bw':1000,'delay':'8ms'}
    net.addLink(s2, h8, cls=TCLink , **s2h8)
    s3h9 = {'bw':1000,'delay':'8ms'}
    net.addLink(s3, h9, cls=TCLink , **s3h9)
    s3h10 = {'bw':1000,'delay':'8ms'}
    net.addLink(s3, h10, cls=TCLink , **s3h10)
    s3h11 = {'bw':1000,'delay':'8ms'}
    net.addLink(s3, h11, cls=TCLink , **s3h11)
    s3h12 = {'bw':1000,'delay':'8ms'}
    net.addLink(s3, h12, cls=TCLink , **s3h12)
    s4h14 = {'bw':1000,'delay':'8ms'}
    net.addLink(s4, h14, cls=TCLink , **s4h14)
    s4h15 = {'bw':1000,'delay':'8ms'}
    net.addLink(s4, h15, cls=TCLink , **s4h15)
    s1s9 = {'bw':1000,'delay':'8ms'}
    net.addLink(s1, s9, cls=TCLink , **s1s9)
    s9s2 = {'bw':1000,'delay':'8ms'}
    net.addLink(s9, s2, cls=TCLink , **s9s2)
    s3s10 = {'bw':1000,'delay':'8ms'}
    net.addLink(s3, s10, cls=TCLink , **s3s10)
    s4s10 = {'bw':1000,'delay':'8ms'}
    net.addLink(s4, s10, cls=TCLink , **s4s10)
    s9s7 = {'bw':1000,'delay':'8ms'}
    net.addLink(s9, s7, cls=TCLink , **s9s7)
    s9s8 = {'bw':1000,'delay':'8ms'}
    net.addLink(s9, s8, cls=TCLink , **s9s8)
    s10s8 = {'bw':1000,'delay':'8ms'}
    net.addLink(s10, s8, cls=TCLink , **s10s8)
    s10s7 = {'bw':1000,'delay':'8ms'}
    net.addLink(s10, s7, cls=TCLink , **s10s7)

    info( '*** Starting network\n')
    net.build()
    info( '*** Starting controllers\n')
    for controller in net.controllers:
        controller.start()

    info( '*** Starting switches\n')
    net.get('s7').start([])
    net.get('s10').start([])
    net.get('s9').start([])
    net.get('s8').start([])
    net.get('s5').start([])
    net.get('s2').start([])
    net.get('s6').start([])
    net.get('s3').start([])
    net.get('s4').start([])
    net.get('s1').start([])

    info( '*** Post configure switches and hosts\n')

    CLI(net)
    net.stop()

if __name__ == '__main__':
    setLogLevel( 'info' )
    myNetwork()

