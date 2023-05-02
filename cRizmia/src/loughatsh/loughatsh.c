#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../lexer/lexer.h"
#include "../parser/parser.h"
#include "../utils/utils.h"


int MAX_COMMAND_SIZE = 1024 ;




void run_Brmj_shell(void){
  char command_line[MAX_COMMAND_SIZE];
  printf("Brmj 0.1.0 [BrmjtSH 0.0.1]\n");
  printf("Type \"quit();\" to leave program, \"copyright\", \"credits\" or \"license\" for more information.\n");
  printf("-|> ");

  fgets(command_line, MAX_COMMAND_SIZE, stdin);
  char* p_char = command_line ;
  while(*p_char != '\n'){
    p_char++;
  }
  *p_char='\0';
  Brmj_AST* AST ;
  int PRINT_TOKENS = 0 ;
  if ( strcmp(command_line,"quit();")==0){
    return;
  }
  else if(*command_line!='\0'){
    AST = parse_tokens(tokenize_program(read_shell_command(command_line)));
    print_ast(AST,PRINT_TOKENS);
  }

  while(true){
    printf("-|> ");
    fgets(command_line, MAX_COMMAND_SIZE, stdin);
    p_char = command_line ;
    while(*p_char != '\n'){
      p_char++;
    }
    *p_char='\0';
    if ( strcmp(command_line,"quit();")==0){
      return;
    }
    else if(*command_line!='\0'){
      Brmj_AST* CLI_AST = parse_tokens(tokenize_program(read_shell_command(command_line)));
      print_ast(CLI_AST,PRINT_TOKENS);
      free_ast(CLI_AST);
    }
  }
}