## 1. Introduction  
This is a test project for richard to test some code snippet for c language.
## 2. gnuplot
```
sudo apt-get install gunplot
gnuplot
gnuplot> set terminal png size 640,480
gnuplot> set output "cwnd.png"
gnuplot> plot "cwnd.dat" using 1:2 title 'Congestion Window' with linespoints
gnuplot> exit
```
