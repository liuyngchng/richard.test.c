# 1. offical doc
[nsnam](https://www.nsnam.org/wiki/Installation)
# 2. setup ns3 in ubuntu 16.04
## 2.1 config setup env  

```
apt-get install gcc g++ python python3 python3-dev
apt-get install autoconf cvs bzr unrar
apt-get install gdb valgrind
apt-get install uncrustify
apt-get install doxygen graphviz imagemagick
apt-get install texlive texlive-extra-utils texlive-latex-extra texlive-font-utils texlive-lang-portuguese dvipng latexmk
apt-get install python3-sphinx dia
apt-get install gsl-bin libgsl-dev libgsl23 libgslcblas0
apt-get install tcpdump
apt-get install sqlite sqlite3 libsqlite3-dev
apt-get install libxml2 libxml2-dev
apt-get install cmake libc6-dev libc6-dev-i386 libclang-6.0-dev llvm-6.0-dev automake python-pip
 python3 -m pip install --user cxxfilt
apt-get install vtun lxc uml-utilities
apt-get install libboost-signals-dev libboost-filesystem-dev
```

## 2.2 setup ns3 from tar ball

```
tar -jxf ns-allinone-3.30.1.tar.bz2
cd ns-allinone-3.30.1
python3 build.py
```
## 2.3 Configuration with Waf
