MiniC Compiler
===

__Steps__

1. Write .l and .y files, and then use flex and bison to generate the basic front end.
2. Create a visual studio project, import the files got from step 1.
3. Base on front end generated by flex and bison, do semantic error checking.
4. ...

__Flex and Bison__

```
bison -d -o parser.cpp parser.y
flex -o tokens.cpp tokens.y
```

__Windows Fixed__

1. replace `#include <unistd.h>` in tokens.cpp to `#include <stdio.h>` and `#include <io.h>`


__References__

1. Stanford compiler-004 on coursera.org.
1. Some reference books.
