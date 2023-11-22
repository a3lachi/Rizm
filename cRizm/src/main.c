#include "lexer/lexer.h"
#include "parser/parser.h"
#include "utils/utils.h"
#include "rizm/rizm.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*
 *
 *    INSTALL :
 *      run : make clean ; make ;
 *      Now you have an executable file "rizm" which will be the interpreter for 
 *      .rm files. 
 *      NOTE : make sure "rizm" executable have the right permissions
 *             you can use : chown 755 ./rizm
 *    
 * 
 * 
 *    USE :
 *      To run a program from a file : ./rizm prog.la 
 *      To start rizm, rizm CLI : ./rizm 
 * 
 */


int main(int argc, char* argv[]) {

  // RUN A PROGRAM : ./rizm prog.la
  if (argv[1]){ 
    char** PROGRAM = read_program(argv[1]); 
    
    rizmTokenS* TOKENS = tokenize_program(PROGRAM) ;
    print_tokens(TOKENS);




    rizm_AST* AST = parse_tokens(TOKENS);
    int PRINT_TOKENS = 1 ;
    print_ast(AST,PRINT_TOKENS);



    free(PROGRAM);
    free_tokens(TOKENS);
    free_ast(AST);
  }
  // RUN rizm CLI : ./rizm
  else {
    run_rizm_shell();
  }
  return 0;
}