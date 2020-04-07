## 1. Introduction  
This is a test project.
## 2. gnuplot
```
sudo apt-get install gunplot
gnuplot
set terminal png size 1024,768
set output "1.png"
set autoscale    					# 轴向标记自动控制
set xlabel "time(s)"	 			# X轴标题
set ylabel "traffic(KB/s)"			# Y轴标题
set title 'TCP Throughput'			# 设置标题
set style data lines    			# 数据显示方式为连线
set grid    						# 显示网格
set label 1 "time(s)" at 190,21000   // set  label   
set label 2 "time(s)" at 10,91000    // set  label
plot "a.dat" using 1:2 title 'line1 ' ,'' using 1:3 title "line2"  with linespoints # 使用文件a.dat的第1列和第2列作为X轴和Y轴数据，示例名"line1",使用a.dat的第1列和第3列作为X轴和Y轴数据，示例名为"line2"，
exit
plot 'data.csv' using 1:2 title '50ms' ,'' using 1:3 title '40ms', '' using 1:4 title '30ms', '' using 1:5 title '20ms', '' using 1:6 title '2ms'
```

## 3. throughput

```
ifstat -nwbt
```
