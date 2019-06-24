# 1. gcc -g
```
gcc -g main.c -o main
```
-g　选项生成 gdb　需要的一些信息

# 2. start debug
```
gdb main  # start debug executable main
break function # set break point for a function
run main  # start run executable main
info locals   # view local variables
p variable_name # print a variable value
```

control
```
c    # run to next break point
next        # step over
step        # step into
```
