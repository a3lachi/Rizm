
# Rizm
This project involves the development of a compiled programming language in C and Python.
The main goal of this project is to **benchmark** different programming languages and **deeply understand** their core paradigms.

The inspiration behind this project is to "really know" : What happens when I tell Python to print('I am printing') ?  How the array selection operator [] is used in the built-in types ? How C agregates data ? how to override built-in features ?


<br>



Rizm, at this stage, is not yet designed (precisely, I still don't know what happens after generating the AST tree, I served 2 dishes so far, a lexer and a parser), but its goal is to offer as much **precision** as possible, **with**, powerful abstraction layers. This I think will make of it a lifetime project that will integrate all precision models I can construct in the remaining time I have alive.

<br>

> "**Rizm**" is derived from "Khawarizmia" which translates from arabic to "Algorithm" <br>

> The word "algorithm" is derived from the name "AlKhwarizmi". Latinized as "Algoritmi", which was later translated into English as "Algorithm" <br>

<br>

# Compiler 
-**Lexer**: Breaks down the input source code into a series of tokens.

-**Parser**: Generates from the tokens an abstract syntax tree (AST) that represents the structure of the program.

-**CodeGenerator**: Responsible for generating executable code from the AST.

-**Optimizer**: Optimize the generated code to improve performance or reduce code size.




