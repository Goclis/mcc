##一、生成代码的分析

###栈及活动记录的分析
分析如下程序运行时的活动记录及栈状态。

```
int fun(int a, int b, int c[10])
{
    int i;
    int j[5];
    
    // 一些操作...
    
    return j[1];
}

int main()
{
    int arr[10];
    return fun(1, 2, arr); 
}
```

使用1-register的模型生成`fun`方法的代码。
```
fun:
    move $fp $sp         ; 设置frame pointer
    sw $ra 0($sp)          ; 保存返回地址
    addiu $sp $sp -4    ; 完成返回地址压栈操作

    addiu $sp $sp -4    ; 给局部变量i分配栈空间，编译器保存此位置为i，即$fp - 4，访问i即0($fp-4)
    addiu $sp $sp -4    ; 给局部变量j分配栈空间，这句的空间对应于j[4]，往后四句分别对应3-0
    addiu $sp $sp -4
    addiu $sp $sp -4
    addiu $sp $sp -4
    addiu $sp $sp -4    ; 编译器保存此位置为j，即$fp - 24，访问j[0]即0($fp-24)

    ; 一系列操作，先忽略
    
    ; 处理返回值，放于$a0中
    lw $a0 j+4   ; j[1]
    
    ; 恢复栈，首先是局部变量
    addiu $sp $sp 24
    
    ; 获取返回地址并弹出活动记录
    lw $a0 4($sp)
    addiu $sp $sp 20 ; 3个参数+返回地址+保存的frame pointer
    lw $fp 0($sp)        ; 恢复frame pointer
    
    ; 跳转return
    jr $ra
```

使用1-register模型生成`main`方法的代码。
```
main:
    ; 类似fun，设置frame pointer，保存返回地址
    move $fp $sp
    sw $ra 0($sp)
    addiu $sp $sp -4
    
    ; 局部变量分配空间，类似在fun中的处理
    addiu $sp $sp -4    ; 10句，从arr[9]到arr[0]，编译器保存一个指向arr的位置，即$fp - 40
    
    ; 调用fun前的处理
    sw $fp 0($sp)    ; 保存frame pointer
    addiu $sp $sp -4    ; 完成push
    
    ; 执行对arr的压栈，这是个变量访问表达式，我们可以通过编译器记录的值找到arr的位置，即$fp - 40，该值会被放于$a0
    sw $a0 0($sp)    ; 压栈
    addiu $sp $sp -4 ; 完成push

    li $a0 2    ; 加载立即数，可以看成是对2这个表达式生成代码
    sw $a0 0($sp)    ; 压栈
    addiu $sp $sp -4    ; 完成push

    li $a0 1    ; 加载立即数，可以看成是对1这个表达式生成代码
    sw $a0 0($sp)    ; 压栈
    addiu $sp $sp -4    ; 完成push

    jal fun   ; 调用fun方法
```

以上的过程基本上完成了对程序的代码生成，除了没有引入main方法的进入和退出相应的指令，这个暂时没考虑。

接着我们来总结一下生成上面这样的代码是遵循怎样的规则：

1. 我们在生成代码中使用的是1-register模型，这个模型假设我们的目标系统有至少一个寄存器可以用来放置返回值或者说是结果值。然后除此之外，使用的stack machine的模型，即每一个表达式运行前后栈是不会变化的，即`Expression preserves stack state`。
1. 我们考虑下在每个方法体内的代码，主要有两类，变量声明和语句，其实我们这的语句和表达式差不多，下文就用表达式代替了。
    - 变量声明：我们需要为变量分配内存空间，然后编译器要记住该位置，目前是基于frame pointer去记录这些值的，分配的空间在最后还是得释放这些空间，我们才能恢复栈的状态。在为变量分配空间的时候，我们约定了一些规则。对于普通的整型变量（我们的语法只支持整型），简单地push为其分配空间，然后记住它和frame pointer的偏移量。对于数组变量，将它当成一系列的整型即可，不过我们是从大到小进行压栈分配空间的，即数组的首元素在栈顶。
    - 表达式：除了变量声明，在我们的语法中就只有表达式了，比如说赋值语句等等，包括方法调用，也是表达式。我们这里约定的是一切表达式的返回值都存储在$a0寄存器中，也就是我们的1-register模型中的1。所以，在你执行完每一个表达式后，它的值在$a0中，如果你要执行下一个表达式，记得把$a0压到栈中保存它的值。

下面来说说活动记录的格式。首先，对于调用者，也就是main，它需要做的是把自己的$fp压入栈中，紧接着，将要传入调用方法的参数按照反序压入栈中。比如我们的例子中就是下面这么个模样。
```
-----
main的$fp
-----
arr
-----
2
-----
1
-----

```

特别地讲一下，这里的arr只压入了arr的首元素的位置，这样更符合于数组的概念，至于在被调用方法中的执行过程中，它是知道arr是个数组变量并且知道它的大小的，所以它可以通过在访问位置`arr + index * 4`来获取`arr[index]`，这也是为什么我们在为数组变量分配空间时按照反序。同理，参数的传递反序也是为了在被调用方法的执行过程中，它可以通过`frame pointer + 4 * i`来访问第i个参数。

接着，调用者使用`jal label`跳转到调用的方法，就完成了。jal这个指令会把下一条指令的地址保存到$ra中，也就是被调用方法该返回的地址。

对被调用者而言，它需要保存返回地址，设置它的frame pointer，然后才开始执行它的body，继续扩展上面的活动记录。

设置frame pointer并压栈保存返回地址。
```
-----
....
-----
1
-----
$ra，保存返回地址              <---- 将frame pointer设置为这里
-----
```

为局部变量分配空间。
```
-----
$ra                          <---- $fp
-----
i                            <---- 编译器需要记住i指向这里，即$fp - 4
-----
j[4]
-----
j[3]
-----
j[2]
-----
j[1]
-----
j[0]                         <---- 编译器需要记住j指向这里，即$fp - 24
-----
```

紧接着是一系列我们省略的操作，无非是一些语句和表达式，记住，在它们执行完后，栈是不会变的，所以我们的活动记录也没变。
分析下返回的操作。因为要返回j[1]，我们需要拿到把j[1]的值放到$a0中，j[1]的值根据j的位置计算即可，为`j + 1 * 4`，即`$fp - 20`，把对应位置的值放到$a0。
现在我们有返回值了，可以返回了，但是，别忘记得把活动记录的空间释放掉，在这里有两部分，我们的局部变量以及先前调用者（main）为我们压入的一些值（那些也属于fun的活动记录）。局部变量的栈很容易计算，逆过来即可，现在，栈又变成了下面这样。
```
-----
main的$fp
-----
arr
-----
2
-----
1
-----
$ra                         <---- $fp
-----
                            <---- $sp
-----
```

这个时候，我们先把返回值恢复过来，即4($sp)。栈指针还得往回的大小也很明显了，为20，即返回值（4）+旧的frame pointer（4）+参数个数（3）*4，接着恢复frame pointer，即0($sp)。

恢复完毕，执行返回跳转，jr $ra。

###语句的代码生成的分析
遵循stack machine的原则，一切表达式的执行前后，栈的状态都不会变化，所以计算的结果都应该是存在累积器$a0中的。这个原则在mcc中可以将表达式和语句等价起来，即语句的执行前后，栈的状态都不会变化。

但是，要注意的是，我们的一个方法定义中可能有多条语句执行，保存$a0的事是交给调用者来做的，所以说，对于第一条语句，是不需要保存$a0的，因为当前$a0还未被任何人使用。

最需要明确的一点是，所有的语句都是由我们的语法树结点构成的，所以，本质上来说，我们只需要遵守stack machine的原则，组合这些结点对应的代码即可，分析的顺序应该由叶子到根。

__MccIntLiteral__

```
lw $a0 int_value    ; 可能需要转换为16进制，取决于汇编器
```

__MccIdentifier__

```
lw $a0 id_address   ; 这个直接查表获取相应的地址
```

__MccArrayAccessExpression__

```
; IDENT [expr]
; 1. 计算expr的值，放于$a0中，expr是个表达式，只要返回值为整型即可
; ...

; 2. 保存expr的值（压栈）
sw $a0 $sp
addiu $sp $sp -4

; 3. 获取IDENT对应的变量的地址，这步即MccIdentifier
lw $a0 id_address

; 4. 结合两个值
; 4.1 取出expr的值
lw $s0 4($sp)
addiu $sp $sp 4
; 4.2 根据epxr值计算下标offset，即乘以4，这里假设乘法指令为$s0<-$s0 * im
multiu $s0 $s0 4
; 4.3 与$a0相加
addu $a0 $s0
```

__MccMethodCallExpression__

```
; 1. 压入当前活动记录的frame pointer
sw $fp 0($sp)
addiu $sp $sp -4

; 2. 从后往前计算各个参数对应的Expression，将它们的返回值压入栈，下面随便举个栗子
exec expr2
sw $a0 0($sp)
addiu $sp $sp -4
exec expr1
sw $a0 0($sp)
addiu $sp $sp -4

; 3. 编译器查照IDENT对应的地址
jal fun
```

__MccBinaryOperatorExpression__

```
; 1. 计算左操作数对应的Expression，存到$a0中
...

; 2. 保存左操作数的值到栈中，准备执行右操作数
sw $a0 0($sp)
addiu $sp $sp -4

; 3. 计算右操作数对应的Expression，存到$a0中
...

; 4. 取出存到栈中的左操作数
lw $s0 4($sp)
addiu $sp $sp 4

; 5. 根据不同的操作数，进行不同的指令计算，左值在$s0，右值在$a0，结果放在$a0中
...

; 5.1 OR_BINARY     特殊处理，只要有一个操作数计算出了真值，就结束
; 5.2 EQ_BINARY
; 5.3 NE_BINARY
; 5.4 LE_BINARY
; 5.5 LT_BINARY
; 5.6 GT_BINARY
; 5.7 GE_BINARY
; 5.8 AND_BINARY    特殊处理，只要有一个操作数计算出了非真的值，就结束
; 5.9 PLUS_BINARY
; 5.10 MINUS_BINARY
; 5.11 MULT_BINARY
; 5.12 DIV_BINARY
; 5.13 MD_BINARY
; 5.14 BIT_AND_BINARY
; 5.15 EXCLUSIVE_BINARY
; 5.16 LSHIFT_BINARY
; 5.17 RSHIFT_BINARY
; 5.18 BIT_OR_BINARY
```

__MccUnaryOperatorExpression__

```
; 1. 计算操作数对应的Expression，存到$a0中
...

; 2. 根据操作符的不同，对$a0执行不同的操作，存到$a0中
; 2.1 NEG_UNARY
; 2.2 NEGATIVE_UNARY
; 2.3 POSITIVE_UNARY
; 2.4 NOT_UNARY
; 2.5 PORT_UNARY
```

__MccBreakStatement__

一个跳转语句，需要跳转到循环的结束处，由编译器负责记录位置。

__MccContinueStatement__

一个跳转语句，需要跳转到循环的条件表达式开始处，由编译器负责记录位置。

__MccReturnStatement__

```
; 1. 计算相关的表达式的值，保存到$a0中
...

; 2. 回收当前活动记录的空间，取出返回地址，跳转，参见一开始的fun的例子
...
```

__MccBlockStatement__

按照各自的规则生成列表中的每一个语句即可。

__MccIfStatement__

```
; 1. 生成条件表达式的代码，表达式运行的结果存在$a0中
...

; 2. 判断$a0的值，决定是否跳转false_branch
beq $a0 0 false_branch

; 3. 生成true_branch的语句块，即if_part语句
...

; 4. 加上false_branch的标头，名字由编译器去决定
...

; 5. 生成false_branch的语句块，即else_part语句
...
```

__MccWhileStatement__

```
; 1. 增加while_condition的标号，用于跳转回来，名字由编译器决定，这里定位while_condition
...

; 2. 生成条件表达式的代码，表达式运行结果存在$a0中
...

; 3. 判断$a0的值，决定是否跳过while body，即跳到while_end标号，名字同样由编译器决定
beq $a0 0 while_end

; 4. 生成while body的语句的代码
...

; 5. while body结束，跳转回while_condition
jp while_condition

; 6. 生成while_end的标号
...
```

__MccVariableDeclaration__

目前不区分全局变量和局部变量，全局变量占用的栈算在main的活动记录中。

其实就是一个简单的申请栈空间，编译器记录变量名的过程。
```
; 1. 如果为数组变量，将数组的大小存于$a0中，否则$a0设置为1
...

; 2. 计算需要分配的栈空间，即$a0 * 4
mult $a0 $a0 4

; 3. 根据计算出来的大小分配栈空间，编译器需要记录当前的栈位置为该变量名的起始，以$fp为基准记录吧
subiu $sp $sp $a0
```

__MccFunctionDeclaration__

这个也是一个记录名字，生成代码的过程。
```
; 1. 以方法的名字为标号名，生成该标号，编译器记录下该位置
...

; 2. 方法内部的声明的代码生成
...

; 3. 方法内部的语句的代码生成
...

; 4. 方法结尾处如果没有return语句进行回收，需要手动生成回收活动记录以及跳转返回的过程，参见MccReturnStatement
...
```

##二、语义错误检查
目前有如下需要进行的语义错误检查。

###1. 变量声明时的类型不能为VOID。
这个可以放到语法分析中，在Bison的语义动作中添加检查，这种错误应避免去终止程序，应绕过继续检查。
在var_decl中需要检查，在local_decl也需要检查。

###2. 方法定义时的参数列表必须得有形参名。
这是为了实现无形参名的方法声明而产生的副作用。在规约成方法定义时可以对其进行检查，也可以放在Bison中进行。
需要注意的是单个的VOID参数的方法定义是可以无形参名的，因为它表示无参数列表。
```
int fun(void)
{
    // ok
}
int fun2(int)
{
    // error
}
```

###3. continue语句和break语句的检查
外层必须有一个while语句。

###4. return语句
检查返回是否与方法的返回值匹配。

###5. 赋值语句
```
$ 'expr' = 'expr'
```
需要为上面这个文法做检查。

###6. 表达式语句
各种表达式语句的文法中，操作数都是expr，最终落实到的终结符是IDENT或者int_literal。但是IDENT可能为方法的IDENT，所以需要做语义检查。

如下表达式就需要检查左右是否都为整型，否则没法操作。
```
expr & expr
```
