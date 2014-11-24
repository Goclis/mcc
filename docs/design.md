Mini C Compiler
====

一个简单的编译器，语法为C的子集，目标代码的运行环境为MIPS。

###MIPS指令集
目标的机器代码是基于MIPS指令集的，所以需要考虑一些MIPS指令的规则：

1. MIPS中的栈是向低地址增长的。
1. 。。。

####Push和Pop
MIPS指令集中没有原生的支持`push`和`pop`操作的指令，需要手动的组合指令来实现。

Push
```
sw reg 0($sp)
addiu $sp $sp -4
```

Pop
```
lw reg 4($sp)
addiu $sp $sp 4
```

###代码生成
- 使用1-register模型，返回值放于$a0。
- 局部变量、方法调用的参数等都放于活动记录（栈）中。

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

###参考资料

- [ANSI C grammar (Yacc)](http://www.quut.com/c/ANSI-C-grammar-y.html)
- [ANSI C grammar (Lex)](http://www.quut.com/c/ANSI-C-grammar-l.html)
- [使用Flex Bison 和LLVM编写自己的编译器](http://coolshell.cn/articles/1547.html)
- [Lex Yacc](http://blog.sina.com.cn/s/blog_58a84dcc01000bf7.html) 
- [Stanford compiler-004](https://coursera.org)

 



