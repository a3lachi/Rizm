#include "lexer/lexer.h"
#include "parser/parser.h"
#include "utils/utils.h"
#include "Brmjtsh/Brmjtsh.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*
 *
 *    INSTALL :
 *      run : make clean ; make ;
 *      Now you have an executable file "Brmj" which will be the interpreter for 
 *      .la files. 
 *      NOTE : make sure "Brmj" executable have the right permissions
 *             you can use : chown 755 ./Brmj
 *    
 * 
 * 
 *    USE :
 *      To run a program from a file : ./Brmj prog.la 
 *      To start Brmjtsh, Brmj CLI : ./Brmj 
 * 
 */


int main(int argc, char* argv[]) {

  // RUN A PROGRAM : ./Brmj prog.la
  if (argv[1]){ 
    char** PROGRAM = read_program(argv[1]); 
    
    BrmjTokenS* TOKENS = tokenize_program(PROGRAM) ;
    print_tokens(TOKENS);

    Brmj_AST* AST = parse_tokens(TOKENS);
    int PRINT_TOKENS = 1 ;
    print_ast(AST,PRINT_TOKENS);

    free(PROGRAM);
    free_tokens(TOKENS);
    free_ast(AST);
  }
  // RUN BrmjTSH CLI : ./Brmj
  else {
    run_Brmj_shell();
  }
  return 0;
}