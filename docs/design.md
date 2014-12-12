Mini C Compiler
====

一个简单的编译器，语法为C的子集，目标代码的运行环境为MIPS。

###开发环境
- Visual Studio 2010
- Flex & Bison

####Flex & Bison
```
bison -d -o parser.cpp parser.y
flex -o tokens.cpp tokens.l
```

###使用
```
mcc.exe inputfile

mcc.exe test.c
```

输入文件有后缀时输出代码为去掉后缀的，否则会添加上`.out`，输入输出文件名映射例子如下：

- test: test.out
- test.c: test
- another.c.c: another

###MIPS指令集
目标的机器代码是基于MIPS指令集的，所以需要考虑一些MIPS指令的规则：

1. MIPS中的栈是向低地址增长的。
1. 。。。

####Push和Pop
MIPS指令集中没有原生的支持`push`和`pop`操作的指令，需要手动的组合指令来实现。

Push
```
sw reg 0($sp)
addiu $v1 $zero 4
subu $sp $sp $v1
```

Pop
```
lw reg 4($sp)
addiu $sp $sp 4
```

###代码生成
- 使用1-register模型，返回值放于某个寄存器中。
- 局部变量、方法调用的参数等都放于活动记录（栈）中。

####模块结构
因为目标代码只有一种（MIPS汇编代码），我们直接将代码生成过程中需要保存的一些中间值保存在了语法树的结点以及MccRobot中。

####寄存器的使用
- $v0：返回值。
- $v1：双操作数的另外一个。
- $zero：零寄存器。

####指令的使用
__规定__

- $dst：目标寄存器。
- $srcX：源寄存器X。
- im：立即数，16位。

__指令及功能__

- addiu $dst $src im: 立即数无符号加，$dst = $src + im。
- addi $dst $src im: 立即数有符号加，$dst = $src + im。
- addu $dst $src1 $src2: 无符号加，$dst = $src1 + $src2。
- subu $dst $src1 $src2: 减法，$dst = $src1 - $src2。
- sw $src im($dst): 写内存（32位），Memory[$dst + im] = $src。
- lw $dst im($src): 加载内存（32位），$dst = Memory[$src + im]。
- mult $src1 $src2: 有符号乘，(HI, LO) = $src1 * $src2。
- mflo $dst: 取出乘法结果的低32位或者除法结果的商，$dst = LO。
- mfhi $dst: 取出乘法结果的高32位或者除法结果的余数，$dst = HI。
- sltu $dst $src1 $src2: 无符号比较，如果$src1小于$src2，那么$dst = 1，否则$dst = 0。
- beq $src1 $src2 branch: 相等则跳转。
- bne $src1 $src2 branch: 不相等则跳转。


####活动记录的设计
调用者，为被调用者的活动记录设置一些值，下面这些均属于被调用者，需要由被调用者负责释放。
```
-----
调用者的$fp
-----
参数n           反向压入参数
-----
....
-----
参数1
-----
                <---- stack top
-----
```

被调用者，在其返回时，需要恢复$fp以及$sp。
```
-----
调用者的$fp           <---- $sp需要恢复至此，用此处的值恢复$fp
-----
参数(s)
-----
$ra             保存返回地址    <---- frame pointer
-----
局部变量空间
-----
                <---- stack stop
-----
```

####局部变量的内存分配
因为MCC要求局部变量的声明必须集中在方法的开头处，所以，可以将局部变量的内存分配问题集中地处理。

目前设计为局部变量的内存分配来自于AR，根据$fp的向下偏移量进行访问。

对于普通变量，4个字节即可。

对于数组变量，数组的开头放在栈顶。

例子
```
int i;
int j[3];
int k;
```

AR（下面是栈顶）
```
-----
$ra					<---- $fp
-----
i					<---- i即$fp-4
-----
j[2]
-----
j[1]
-----
j[0]				<---- j即$fp-16，由此推出j[i] = $fp-16+4*i
-----
k					<---- k即$fp-20
-----
					<---- $sp
-----
```

####全局变量的内存分配
全局变量的内存统一分配到栈底。

因为MiniC的语法支持全局变量和方法声明穿插，需要缓存为全局变量的内存分配的代码，最后再拼接起来。

####栈的开始
按照MIPS设计的CPU未对此做限制，编译器可以自由的决定栈底。

####语法树各结点代码生成分析（具体到目标系统拥有的指令）
对于每个结点内部的表达式的生成，以`Gen(name)`来代替，执行的结果保存在$v0中，如一个二元操作符表达式的执行如下：
```
Gen(m_left_operand)
...
Gen(m_right_operand)
...
```

__MccArrayAccessExpression__

```
Gen(m_id)						// 计算出数组基地址
Push $v0
Gen(m_index)					// 下标表达式的生成，值存于$v0，有符号数
addiu $v1 $zero 4				// li $v1 4
mult $v0 $v1
mflo $v0						// 取出乘法结果低32位，认作乘法结果
Pop $v1
add $v0 $v0 $v1					// 结果
```

__MccAssignStatement__

```
Gen(m_left_operand)				// 应该计算出地址
Push $v0
Gen(m_right_operand)			// 计算出值
Pop $v1
sw $v0 0($v1)					// 赋值
```

__MccIdentifer__

```
// position由编译器生成代码时保存起来，为相对$fp的偏移
1. 全局变量
1.1. 数组变量
addiu $v0 $zero 4000	// 4000为全局环境的的$fp，暂不定
addiu $v1 $zero position
subu $v0 $v0 $v1

1.2. 普通变量
addiu $v0 $zero 4000
sw $v0 (-position)$v0


2. 局部变量
2.1. 数组变量
addiu $v1 $zero position
subu $v0 $fp $v1

2.2. 普通变量
sw $v0 (-position)$fp
```

__MccBreakStatement__

```
j break_label					// break_label由编译器维护
```

__MccContinueStatment__

```
j continue_label				// continue_label由编译器维护
```

__MccIfStatement__

```
Gen(m_condition)				// 条件
beq $v0 0 false_branch_label	// false_branch_label由编译器生成维护
Gen(m_if)
j false_branch_label_end		// false_branch_label拼接上"_end"
false_branch_label:
Gen(m_else)						// 如果有的话
false_branch_label_end:
```

__MccWhileStatement__

```
while_start_label:				// 由编译器生成维护
Gen(m_condition)				// 条件
beq $v0 0 break_label			// break_label由编译器生成维护
Gen(m_statement)				// While body
break_label:					// 跳出while循环的地方
```

__MccIntLiteral__

```
addi $v0 $zero value			// li $v0 value，value由该结点自己维护
```

__MccReturnStatement__

```
Gen(m_expr)						// 执行返回的表达式
addiu $sp $sp local_var_size	// pop掉局部变量的内存，local_var_size由编译器维护
lw $ra 4($sp)					// 取出返回地址
addiu $sp $sp args_fp_size		// pop掉剩余的活动记录的内存，包括参数等，args_fp_size由编译器维护
lw $fp 0($sp)					// 恢复$fp
jr $ra
```

__MccMethodCallExpression__

```
Push($fp)					// 保存$fp
Gen(argn)
Push($v0)					// 计算并保存参数n
...							// ... 反向计算参数
Gen(arg1)
Push($v0)					// 计算并保存参数1
jal func_name				// func_name为目标的方法名
```

__MccVariableDeclaration__

```
addiu $v1 $zero size
subu $sp $sp $v1				// size是该变量的大小，数组变量要考虑所有元素
```

__MccFunctionDeclaration__

```
// 如果包含定义（即非方法声明），往下
fun:							// 方法的名字
Gen(local_var_1)				// 局部变量1
...
Gen(local_var_n)				// 局部变量n
Gen(statement_1)				// 语句1
...
Gen(statement_n)				// 语句n

// 如果语句中在最后无返回语句（包含在条件语句体里的不算），往下
addiu $sp $sp local_var_size	// pop掉局部变量的内存，local_var_size由编译器维护
lw $ra 4($sp)					// 取出返回地址
addiu $sp $sp args_fp_size		// pop掉剩余的活动记录的内存，包括参数等，args_fp_size由编译器维护
lw $fp 0($sp)					// 恢复$fp
jr $ra	
```

__MccUnaryOperatorExpression__

```
Gen(m_operand)					// 计算值
// 以下根据操作数不同而不同
(1) ~
								// 没发现支持

(2) -
subu $v0 $zero $v0

(3) +
								// 不需要

(4) !
sltu $v0 $zero $v0

(5) $
								// 需要定好端口映射后才能确定
```

__MccBinaryOperatorExpression__

```
Gen(m_left_operand)				// 左操作数
----
// 这部分只有逻辑AND和逻辑OR需要，quick_branch_label由编译器生成
(1) &&
beq $v0 $zero quick_branch_label

(2) ||
bne $v0 $zero quick_branch_label
----
Push($v0)						// 保存左操作数
Gen(m_right_operand)			// 右操作数
Pop($v1)

// 以下根据操作数不同做不同操作，$v1（左） OP $v0（右）
(1) ||
sltu $v0 $zero $v0

(2) ==
beq $v0 $v1 branch
addiu $v0 $zero 0
j branch_end
branch:
addiu $v0 $zer0 1
branch_end:

(3) !=
bne $v0 $v1 branch
addiu $v0 $zero 0
j branch_end
branch:
addiu $v0 $zer0 1
branch_end:

(4) <=
slt $v0 $v0 $v1
sltu $v0 $zero $v0

(5) <
slt $v0 $v1 $v0

(6) >
slt $v0 $v0 $v1

(7) >=
slt $v0 $v1 $v0
sltu $v0 $zero $v0

(8) &&
and $v0 $v1 $v0
sltu $v0 $zero $v0

(9) +
add $v0 $v1 $v0

(10) -
sub $v0 $v1 $v0

(11) *
mult $v1 $v0
mflo $v0

(12) /
div $v1 $v0
mflo $v0

(13) %
div $v1 $v0
mfhi $v0

(14) &
and $v0 $v1 $v0

(15) ^
xor $v0 $v1 $v0

(16) <<
sllv $v0 $v1 $v0

(17) >>
srlv $v0 $v1 $v0

(18) |
or $v0 $v1 $v0

----
// 这部分只有逻辑AND和逻辑OR需要，quick_branch_label由编译器生成
quick_branch_label:
----
```

###语义错误检查
为了方便每种语义错误检查有独立的空间去保存检查过程中的信息，每种语义错误对应有一个相应的Checker进行检查，发现错误会产生相应的Error，每个Checker有针对各个语法树结点的重载方法。

针对每种语义错误检查，调用语法树结点的`semantic_detect`方法，接着每个结点会获取到当前的Checker，然后将自己的指针作为参数传入到Checker的方法中，各个Checker根据结点以及自身要检查的错误，做不同的处理。

####1、变量类型检查
__目的__

变量的类型不能为VOID，但语法上允许，要对此进行检查。

__相关Mcc Class__

- MccVariableTypeChecker：检查如下语法树结点。
	- MccVariableDeclaration：直接检查。
	- MccFunctionVariableDeclaration：检查其内部的局部变量列表。
- MccVariableTypeError：相关联的Error类，报告如下信息。
	- 变量名
	- 变量所在行

####2、方法定义参数名缺失
__目的__

语法允许方法声明及方法定义时不指定参数的名字，但是在语义上不允许方法定义的参数名缺失，需要检查。

__相关Mcc Class__

- MccMethodParameterNameExistChecker：检查如下语法树结点。
	- MccFunctionDeclaration：如果是方法定义，检查参数列表。
- MccMethodDefinitionLackParameterNameError：相关联的Error类，报告如下信息。
	- 方法名
	- 第几个参数
	- 参数所在行

####3、循环跳转语句必须在while语句中
__目的__

语法允许`break`以及`continue`语句出现在非while语句的体里，但语义上不允许，需要检查。

__相关Mcc Class__

- MccJumpInWhileChecker：检查如下语法树结点。
	- MccFunctionDeclaration：检查内部的语句列表。
	- MccWhileStatement
	- MccBlockStatement：与MccWhileStatement相关。
	- MccBreakStatement
	- MccContinueStatement
- MccJumpOutOfWhileError：相关联的Error类，报告如下信息。
	- 语句类型，break或者continue
	- 语句所在行

####4、变量及方法的ID的冲突
__目的__

语法不对变量及方法定义时的名字做任何约束，但是语义上对变量及方法的ID有如下约定：

- 方法的ID全局唯一，即一旦被使用后将全局占用，不支持重载，不支持重复声明。
- 变量的ID在域中唯一，MiniC只有两种域，全局域及各个方法实现的域，所以全局变量是可以在方法域内被覆盖的。

__相关Mcc Class__

- Must pass
	- MccMethodParameterNameExistChecker
- MccIdentifierConflictChecker：检查如下语法树结点。
	- MccVariableDeclaration：要区分全局和局部变量。
	- MccFunctionDeclaration：要区分声明和定义。
	- MccFunctionParameter：等同于局部变量。
- MccIdentifierConflictError：相关联的Error类，报告如下信息。
	- 冲突的ID的行号
	- 与之冲突的ID的行号
	- 冲突的ID

####5、变量存在性
__目的__

语法不关心使用的变量是否存在，语义需要检查。

__相关Mcc Class__

- Must pass
	- MccMethodParameterNameExistChecker
- MccVariableReferenceChecker
	- MccVariableDeclaration：记录变量定义。
	- MccFunctionDeclaration：记录局部变量定义，并检查内部语句。
	- MccAssignStatement：左右操作数都可能是变量。
	- MccWhileStatement：条件和内部语句都可能是变量。
	- MccBlockStatement：与while相关。
	- MccIfStatement：条件及两个体的语句。
	- MccReturnStatement
	- MccBinaryOperatorExpression
	- MccUnaryOperatorExpression
	- MccIdentifier
- MccUndefinedVariableError
	- 未定义变量名
	- 行号

###参考资料

- [ANSI C grammar (Yacc)](http://www.quut.com/c/ANSI-C-grammar-y.html)
- [ANSI C grammar (Lex)](http://www.quut.com/c/ANSI-C-grammar-l.html)
- [使用Flex Bison 和LLVM编写自己的编译器](http://coolshell.cn/articles/1547.html)
- [Lex Yacc](http://blog.sina.com.cn/s/blog_58a84dcc01000bf7.html) 
- [Stanford compiler-004](https://coursera.org)

 



