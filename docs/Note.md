Note
======

##Why this file?
After finishing the phase to build the abstract syntax tree, I decided to let the semantic error check alone temporarily and enter the code generation phase. However, it's new to me, so learning is neccessary. Hence, I create this file to write down some information which will help me in future when I really start code generation phase.

##MIPS Instruction Set
The generated code is based on MIPS instruction set, which has following convention.

1. Stack increases to low address.
1. Maybe more conventions that compiler needs to concern about.

###Push and Pop
MIPS doesn't have instruction to directly support push and pop operation. Compiler has to combine some instructions to support `push` and `pop`.

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


##Tips to Build Code Generator
Just my thoughts, maybe wrong, thanks for pointing out.

- Design your activation record, remember to combine with what your grammar supports and what your target instruction set supports.
- Analyse each production in your grammar and related node in abstract syntax tree.
- Be clear with what is in runtime and what is in compile time. For example, stack operation is runtime operation, calculating static variable reference (by using frame pointer or constant array index) is in compile time.
- Take care of operations that will influence stack pointer, especially function call.

##Analyses for MCC
Because the mcc is a curriculum project, I don't have much time to write down everything here (It is asked to hand in soon...). However, I will try to write down something typical.

