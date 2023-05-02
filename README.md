
شحال من عام وانا تنكودي يالاه كتشفت بلي عمري كوديت 😆 قطع لايدير لخير

# Introduction

To code is not to use an API, a software engineer is not a customer ordering food. He is a tool builder, what leads to : how can I build a tool using tools I abstractly use and not genuinely know ? It's correct that if the tools I'm using are "powerful" I will build "better", I am left then with two options :
1. Know the happening abstraction layers before I got here
2. Use abstraction and pretend I know what I'm doing

This project aim to explore the gap between the two scenarios, from keyboard strokes to the hardware changing state passing by all the algorithms used by every piece of code.

<br>


# Rizmia



This project involves the development of a compiled programming language in C, C++, Rust, and Go.
The main goal of this project is to **benchmark** different programming languages and **deeply understand** their core paradigms.

The inspiration behind this project is to "really know" : What happens when I tell Python to print('I am printing') ?  How the array selection operator [] is used in the built-in types ? How C agregate data ? can I write a programming language in Arabic ? **وي تبشلحة علاش لا**.

<br>

> "**Rizmia**" is the last word of "Khawarizmia" which translates from arabic to "Algorithm" <br>

> (it is widely adopted to write Arabic using Latin alphabt) <br>

> The word "algorithm" is derived from the name "AlKhwarizmi". Latinized as "Algoritmi", which was later translated into English as "Algorithm"






# Compiler 
-**Lexer**: Breaks down the input source code into a series of tokens that can be easily processed by the compiler.

-**Parser**: Responsible for taking the tokens produced by the Lexer and generating an abstract syntax tree (AST) that represents <br> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; the structure of the program.

-**ASTNode**: Represents a node in the abstract syntax tree.

-**CodeGenerator**: Responsible for generating executable code from the AST.

-**Optimizer**: Optimize the generated code to improve performance or reduce code size.


