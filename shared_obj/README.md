# 1.get shared object
```
gcc test_a.c test_b.c test_c.c -fPIC -shared -o libtest.so
```
# 2. link
 
将test.c与动态库libtest.so链接生成执行文件test：
```
gcc test.c -L. -ltest -o test
```
-fPIC 选项作用于编译阶段，告诉编译器产生与位置无关代码（Position-Independent Code）；
这样一来，产生的代码中就没有绝对地址了，全部使用相对地址，
所以代码可以被加载器加载到内存的任意位置，都可以正确的执行。
这正是共享库所要求的，共享库被加载时，在内存的位置不是固定的。
