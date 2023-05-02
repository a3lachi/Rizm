#ifndef HEADER_PARSER_H
#define HEADER_PARSER_H
#include <stdbool.h>
#include "../lexer/lexer.h"

/*
 *
 *    SYNTAX :
 *      float : 3shri 
 *      int : ra9m  
 *      string : 7rof 
 *      bool : kayn 
 *      while : ma7d 
 *      for : li 
 *      if : lw 
 *      else : lwch 
 *      try : jrb 
 *      catch : chd
 * 
 */


typedef enum {
  PROGRAM,
  IMPORT_STATEMENT,
  VARIABLE_DECLARATION,
  EXPRESSION_STATEMENT, // print()
  WHILE_STATEMENT,
} Brmj_STRUCTURE ;



typedef enum {
  AST_ERROR_SEMICOLON_NFOUND,
  AST_ERROR_SPACE_NFOUND,
  AST_ERROR_DECLARE_INTEGER,
  AST_ERROR_DECLARE_FLOAT,
  AST_ERROR_DECLARE_STRING,
  AST_ERROR_DECLARE_BOOL,
  AST_ERROR_VARNAME_NFOUND,
  AST_ERROR_INT_NFOUND,
  AST_ERROR_AFTER_EQUAL,
  AST_ERROR_VALUE_NFOUND,
  AST_ERROR_AFTER_VALUE,
  AST_ERROR_AFTER_COMMA,
  AST_ERROR_EQUAL_NFOUND,
} Brmj_STRUCTURE_ERROR ;




typedef struct Brmj_AST {
  union 
  {
    Brmj_STRUCTURE s;
    Brmj_STRUCTURE_ERROR s_error ;
  } structure;
  int is_error;
  BrmjTokenS* tokens ;
  int start,end;

  union {
    struct {
      union {
        int value_int;
        float value_float;
        bool value_bool;
        char* value_s;
      } CONST ;
      // char* var_value;
      char* varname ;
      TokenType type ;
    } CONSTANT;
  } DATA;

  struct Brmj_AST* next ;
  struct Brmj_AST* childs ;

} Brmj_AST;


char* get_structure_type(Brmj_STRUCTURE structure);
char* get_structure_error(Brmj_STRUCTURE_ERROR serr);
void create_Brmj_AST(BrmjTokenS** tkns , int start_flag , char* value,TokenType type, Brmj_AST** nodes, char* varname);
Brmj_AST* parse_tokens(BrmjTokenS* tokens);
bool parse_declare_variable_tokens(int start_flag , Brmj_AST* nodes,BrmjTokenS** tkns , TokenType type);


void print_node_json(Brmj_AST* node, int indent_level , int print_tokens) ;
Brmj_AST* parse_tokens(BrmjTokenS* tokens);
void print_ast_recursive(Brmj_AST* nodes);
void print_ast(Brmj_AST* nodes , int print_tokens);
void free_ast(Brmj_AST* nodes);

#endif
