MiniC Compiler
===

### Environments and Tools
- Visual Studio 2013 Community
- Flex && Bison

### Usages
####Normal
__input__

```
% mcc.exe file_path

eg:
% mcc.exe test # relative path
% mcc.exe C:\Users\XXX\Desktop\test # absolute path
```

__output__

Three files:

- test.out: MIPS assembly code, **.out** might be omitted if input file has suffix extension such as test.c.
- ram.coe: File to initialize RAM.
- rom.coe: File to initialize ROM, with bios code.

####Special
If you want to use the compiler to compile the system call method, and then add the output to bios-init, you can use it with following command.

__input__
```
% mcc.exe system_calls --no-bios
```

__output__

Three files:

- test.out: MIPS assembly code.
- ram.coe: File to initialize RAM.
- rom.coe: File to initialize ROM, without bios code.

### References
1. Stanford compiler-004 on coursera.org.
1. Some reference books.
