###Todos
- MccBreakStatement
- MccContinueStatement
- MccExpression
- 考虑一下全局变量的内存分配问题。
- 考虑一下main函数放置的位置，是否需要特别的移至生成的代码的最下端。
- 结束代码生成后，考虑语义错误检查，可能需要修改.l和.y来加入定位信息。

###Done
- 完成了基础的tokens.l和parser.y文件的编写，并利用flex和bison进行了词法和语法分析程序的生成。
- 完成了抽象语法树的设计，并将其结合到parser.y的语义动作中了。
- 已经实现了输入一个符合minic语法的源文件，构造出语法树的过程。
- 完成了活动记录及栈的分析，并考虑了参数、返回值、局部变量的分析。
- 完成了对各个语句代码生成的分析。
- 完成了对局部变量内存分配的分析，直接放到AR中。
- 完成了在MccRobot和MccFunctionDeclaration中对代码生成运行状态的记录。
- 完成了MccReturnStatement的生成代码。
- 完成了MccIfStatement的生成代码。
- 完成了MccWhileStatement的生成代码。
