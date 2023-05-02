


# Introduction

To code is not to use an API, a software engineer is not a customer ordering **food**. He is a tool builder, what leads to : how can I build a tool using tools I abstractly use and not genuinely know ? It's correct that if the tools I'm using are "powerful" I will build "better", I am left then with two options :
1. Know the happening abstraction layers before I got here
2. Use abstraction and pretend I know what I'm doing

This project aim to explore the gap between the two scenarios, from keyboard strokes to the hardware changing state passing by all the algorithms used by every piece of code.

<br>


# Rizm



This project involves the development of a compiled programming language in C, C++, Rust, and Go.
The main goal of this project is to **benchmark** different programming languages and **deeply understand** their core paradigms.

The inspiration behind this project is to "really know" : What happens when I tell Python to print('I am printing') ?  How the array selection operator [] is used in the built-in types ? How C agregate data ? can I write a programming language in Arabic ? **وي تبشلحة علاش لا**.

Rizm Project is a playground to discover all the underlaying cooking C, C++, Go and Rust do before serving delicious **food**.

<br>

> "**Rizm**" is derived from "Khawarizmia" which translates from arabic to "Algorithm" <br>

> The word "algorithm" is derived from the name "AlKhwarizmi". Latinized as "Algoritmi", which was later translated into English as "Algorithm" <br>

<br>

**This being said, Rizm is an algorithm factory, it dosen't serve food, it serves **chefs** who will "precisely" cook the **food** you want**

Rizm, at this stage, is not yet designed (precisely, I still don't know what happens after generating the AST tree, I served 2 dishes so far, a lexer and a parser), but its goal is to offer as much **precision** as possible, **with**, powerful abstraction layers. This I think will make of it a lifetime project that, will integrate all precision models I can construct in the remaining time I have alive.



# Compiler 
-**Lexer**: Breaks down the input source code into a series of tokens.

-**Parser**: Generates from the tokens an abstract syntax tree (AST) that represents the structure of the program.

-**CodeGenerator**: Responsible for generating executable code from the AST.

-**Optimizer**: Optimize the generated code to improve performance or reduce code size.


