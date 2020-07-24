
## 1. 描述典型的网络拓扑以及各自的优缺点。


## 2. 描述OSI参考模型和TCP/IP参考模型。


## 3. 讲解TCP连接的建立和释放过程。


## 4. 描述TCP拥塞控制的机制。


## 5. 请描述无线网络和有线网络各自的特点。


## 6. 用伪代码实现快排算法。


## 7.请描述对容器技术的理解，如机制，优缺点等。


## 8. 请描述C语言的编译过程。


## 9. 请描述SDN网络的工作机制。


## 10. 请简述无线自组织网络的工作机制。


## 11. 请描述ARM架构处理器和Intel处理器指令集的异同。


## 12. 请描述线程和进程的区别。


## 13.请描述epoll 和 select的工作机制。

## 14. 计算sizeof

size of 属于Macro, function, 关键字 


以下为Linux下的32位C程序，请计算sizeof的值。
```
    char str[] = “Hello” ; 
    char  *p = str ; 
    int n = 10; 
```
 请计算
（1）sizeof(str)= （2）sizeof(p) =
（3）sizeof(n)=
【标准答案】   
（1）6,（2）4 ,（3 ）4  

## 15. 计算size
```
void *p=malloc(100);
``` 
请计算sizeof(p)=   

【标准答案】   
（4）4、（5）4

## 16. 查找错误  
请问下面程序有什么错误?   
``` 
int a[60][250][1000],i,j,k;
for(k=0;k<=1000;k++)
    for(j=0;j<250;j++)
 	    for(i=0;i<60;i++)
 		    a[i][j][k]=0;
```
【标准答案】   
把循环语句内外换一下。

## 17. 查找错误   

以下是求一个数的平方的程序,请找出错误:   
```
##define SQUARE(a)((a)*(a))
int a=5;
int b;
b=SQUARE(a++);
```
【标准答案】   
宏在预编译时会以替换的形式展开，仅仅会替换。涉及到宏的地方，不要用++-- ，   
标准中对此没有规定，因此最终结果将会依赖于不同的编译器。   
执行程序的答案可能是25、也有可能是36。   

## 18. 获取输出

```
 int modify_value()
 {
    return(x+=10);
 }
 int change_value(int x)
 {
    return(x+=1);
 }
 void main()
 {
    int x =10;
    x++;
    change_value(x);
    x++;
    modify_value();
    printf("First output:%dn",x);
    x++;
    change_value(x);
    printf("Second output:%dn",x);
    modify_value();
    printf("Thirdoutput:%dn",x);
}
```
输出?
【标准答案】   
12、13、13

## 19. 编写strcpy函数   

已知strcpy函数的原型是   

```
 char *strcpy(char *strDest, const char *strSrc);
```

其中strDest是目的字符串，strSrc 是源字符串。   
（1）不调用C++/C 的字符串库函数，请编写函数strcpy 。   
（2）strcpy 能把 strSrc 的内容复制到strDest，为什么还要char * 类型的返回值？   

## 20. 写出二分查找的代码   

【参考答案】   
```
int binary_search(int* arr, int key, int n)
{
    int low = 0;
    int high = n - 1 ;
    int m id;
    while (low <= high)
    {
	    mid = (high + low) / 2;
	    if (arr[mid] > k)
		    high = mid -1 ;
        else if (arr[mid] < k)
            low = mid + 1;
        else
            return mid;
    }
    return -1;
}
```
## 20. 位域

“位域”( bit field）

## 21.  智能指针（c++)

## 22. static modifier 的含义

## 23. char a[3] ='abc';

## 24. C int, char, float, double, long 

## 25. & 和 * 区别  

&是alias必须初始化，指针需要走构造和析构

## 26. ++a, a++ 在C和C++中的区别  

C++中 a++有临时变量赋值的过程  

## 27. IPC
共享内存， signal, socket(unisocket, 普通socket)  

## 28. inline function

递归函数不能用递归， 长函数不能用递归

## 29. 函数形参  （argument)

少量形参放在寄存器 ，大量放寄存器

## 30. 计算机组成原理

内存、寄存器、Bus，CPU， 南北桥

## 31. lock
mutex-lock, share-lock(C中没有)  
read-lock, write-lock, spin-lock(占锁占CPU）
dead-lock  
## 32. C 中的数据结构， list, array, hash, tree

## 33. 算法
quicksort, binary-search


## 34. switch 中是否可以做范围的判断？

C中可以
switch a:
	case 1 ... 9:
		break; 

## 35. 内存释放和分配  

malloc free

## 36. 网络

TCP, socket, 端口 

## 37. shell, op

cat, grep, find, tail, head, ps, netstat, iostat, top, gdb(), find, 查看运行时内存泄漏, 


## 38. Bigendian, Small edian
