this is a test for c
# 1. cmd
```
gcc main.c -o main      # comile and link source file in one step, output a executable bin file
gcc -c main.c           # produce object file from source, default file name is main.o, you can use -o get a customized name
gcc main.o              # link a object file to produce a execute bin file
```
# 2. gcc
gcc process step
- precompile source file -> precompiled file
- precompiled file -> assembly file
- assembly file -> object file
- link object file -> executable file

# 3. gcc options

GCC 选项区分大小写

| option | note |
| :-- | :-- |
| -E | 预处理指定的源文件，不进行编译,例如宏展开、文件包含、删除部分代码等 |
| -S | 编译指定的源文件，生成汇编源程序，但是不进行汇编 |
| -c |  编译、汇编指定的源(c源程序,汇编源程序)文件，生成目标文件,但是不进行链接 |
| -o [file1] [file2] | 将文件 file2(c源程序，汇编源程序,目标文件) 编译成可执行文件 file1 |
| -I directory | 指定 include 包含文件的搜索目录 |
| -g | 生成调试信息，该程序可以被调试器调试 |
| -save-temps | GCC 会正常地编译和链接，但是会把预处理器输出、汇编语言和对象文件全部存储在当前目录下 (.i 预处理文件, .s 汇编源文件,.o 目标文件)|

# 4. gcc 预处理选项

- `-E -C`   
  头文件较大或源文件包括了多个头文件时，预处理器输出可能会庞杂难读。使用-C选项可删除源文件和头文件中的注释   
- `-Dname[=definition]`  
在处理源文件之前，先定义宏 name。宏 name 必须是在源文件和头文件中都没有被定义过的。将该选项搭配源代码中的#ifdef name命令使用，可以实现条件式编译。如果没有指定一个替换的值，该宏被定义为值 1
- `-Uname`  
如果在命令行或 GCC 默认设置中定义过宏 name，则“取消”name 的定义。`-D`和`-U`选项会依据在命令行中出现的先后顺序进行处理  
- `-Idirectory[:directory[...]]`  
当通过 #include 命令把所需的头文件包括进源代码中时，除系统标准 include 目录之外，指定其他的目录对这些头文件进行搜索
- `-iquote directory[:directory[...]] `
这是在最近 GCC 版本中新增的选项，它为在 #include 命令中采用引号而非尖括号指定的头文件指定搜索目录  
- `-isystem directory[:directory[...]]`  
该选项在标准系统 include 目录以外为系统头文件指定搜索目录，且它指定的目录优先于标准系统 include 目录被搜索。在目录说明开头位置的等号，被视作系统根目录的占位符，可以使用`--sysroot` 或 `-isysroot` 选项来修改它
- `-isysroot directory`  
该选项指定搜索头文件时的系统根目录。例如，如果编译器通常在 /usr/include 目录及其子目录下搜索系统头文件，则该选项将引导到 directory/usr/include 及其子目录下进行搜索
- `-I-`  
在较新版本的 GCC 中，该选项被`-iquote`替代。在旧版本中，该选项用于将命令行的所有`-Idirectory`选项分割为两组。所有在`-I-`左边加上`-I`选项的目录，被视为等同于采用`-iquote`选项；这指的是，它们只对 `#include` 命令中采用引号的头文件名进行搜索。    
所有在`-I-`右边加上`-I`选项的目录，将对所有`#include`命令中的头文件名进行搜索，无论文件名是在引号还是尖括号中。  
而且，如果命令行中出现了`-I-`，那么包括源文件本身的目录不再自动作为搜索头文件的目录

# 5. include  

对于include目录而言，通常的搜索顺序是：  
(1) 包含指定源文件的目录（对于在 #include 命令中以引号包括的文件名）。  
(2) 采用-iquote选项指定的目录，依照出现在命令行中的顺序进行搜索。只对 #include 命令中采用引号的头文件名进行搜索。  
(3) 采用-I选型指定的目录，依照出现在命令行中的顺序进行搜索。  
(4) 采用环境变量 CPATH 指定的目录。  
(5) 采用-isystem选项指定的目录，依照出现在命令行中的顺序进行搜索。  
(6) 采用环境变量 C_INCLUDE_PATH 指定的目录。  
(7) 系统默认的 include 目录  
# 6. gcc -S
- 编译器的核心任务是把C程序翻译成机器的汇编语言（`assembly language`）。汇编语言是人类可以阅读的编程语言，也是相当接近实际机器码的语言。由此导致每种 `CPU` 架构都有不同的汇编语言。  
- 实际上，`GCC` 是一个适合多种 `CPU` 架构的编译器，不会把C程序语句直接翻译成目标机器的汇编语言，而是在输入语言和输出汇编语言之间，利用一个中间语言，称为 `RegisterTransfer Language`（简称 `RTL`，寄存器传输语言）。借助于这个抽象层，在任何背景下，编译器可以选择最经济的方式对给定的操作编码。
- 在交互文件中针对目标机器的抽象描述，为编译器重新定向到新架构提供了一个结构化的方式。但是，从 `GCC` 用户角度来看，我们可以忽略这个中间步骤。
- 通常情况下，`GCC` 把汇编语言输出存储到临时文件中，并且在汇编器执行完后立刻删除它们。但是可以使用`-S`选项，让编译程序在生成汇编语言输出之后立刻停止。
- 如果没有指定输出文件名，那么采用`-S`选项的 `GCC` 编译过程会为每个被编译的输入文件生成以`.s`作为后缀的汇编语言文件。如下例所示：
```
$ gcc -S circle.c
```
编译器预处理 circle.c，将其翻译成汇编语言，并将结果存储在 circle.s 文件中。
如果想把 C 语言变量的名称作为汇编语言语句中的注释，可以加上`-fverbose-asm`选项：
```
$ gcc -S -fverbose-asm circle.c
```
# 7. gcc -l
## 7.1 链接器  
- 链接器把多个二进制的目标文件（`object file`）链接成一个单独的可执行文件。在链接过程中，它必须把符号（变量名、函数名等一些列标识符）用对应的数据的内存地址（变量地址、函数地址等）替代，以完成程序中多个模块的外部引用。
- 链接器也必须将程序中所用到的所有`C`标准库函数加入其中。对于链接器而言，链接库不过是一个具有许多目标文件的集合，它们在一个文件中以方便处理。
- 当把程序链接到一个链接库时，只会链接程序所用到的函数的目标文件。在已编译的目标文件之外，如果创建自己的链接库，可以使用 ar 命令。
- 标准库的大部分函数通常放在文件 libc.a 中（文件名后缀.a代表“archieve”），或者放在用于共享的动态链接文件 libc.so 中（文件名后缀.so代表“share object”，译为“共享对象”）。这些链接库一般位于 /lib/ 或 /usr/lib/，或者位于 GCC 默认搜索的其他目录。
- 当使用 `GCC` 编译和链接程序时，`GCC` 默认会链接 libc.a 或者 libc.so，但是对于其他的库（例如非标准库、第三方库等），就需要手动添加。
## 7.2 demo
`GCC` 的`-l`选项可以让我们手动添加链接库。下面我们编写一个数学程序 main.c，并使用到了 cos() 函数，它位于 <math.h> 头文件
```
#include <stdio.h>      /* printf */
#include <math.h>       /* cos */
#define PI 3.14159265
int main ()
{
    double param, result;
    param = 60.0;
    result = cos ( param * PI / 180.0 );
    printf ("The cosine of %f degrees is %f.\n", param, result );
    return 0;
}
```
为了编译这个 main.c，必须使用-l选项，以链接数学库：
```
$ gcc main.c -o main.out -lm
```
数学库的文件名是 `libm.a`。前缀`lib`和后缀`.a`是标准的，`m`是基本名称，`GCC` 会在`-l`选项后紧跟着的基本名称的基础上自动添加这些前缀、后缀，本例中，基本名称为 `m`。
```
在支持动态链接的系统上，GCC 自动使用在 Darwin 上的共享链接库 libm.so 或 libm.dylib。
```
## 7.3 自定义的链接库  
`GCC` 会自动在标准库目录中搜索文件，例如 `/usr/lib`，如果想链接其他目录中的库，就得特别指明。有三种方式可以链接在 GCC 搜索路径以外的链接库  
- 把链接库作为一般的目标文件  
GCC 指定该链接库的完整路径与文件名。
例如，如果链接库名为 libm.a，并且位于 /usr/lib 目录，那么下面的命令会让 GCC 编译 main.c，然后将 libm.a 链接到 main.o
```
$gcc main.c -o main.out /usr/lib/libm.a
```
- 使用`-L`选项
为 `GCC` 增加另一个搜索链接库的目录
```
$ gcc main.c -o main.out -L/usr/lib -lm
```
可以使用多个`-L`选项，或者在一个`-L`选项内使用冒号分割的路径列表
- `LIBRARYPATH`  
把包括所需链接库的目录加到环境变量 `LIBRARYPATH` 中

生成自定义的archieve文件
```
gcc -c a.c
gcc -c b.c
gcc -c c.c
ar -fr abc.a a.o b.o c.o

```

```
```
