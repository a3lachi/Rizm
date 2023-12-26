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
  IF_STATEMENT,
} rizm_STRUCTURE ;



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
  AST_ERROR_LPAREN_NFOUND,
  AST_ERROR_RPAREN_NFOUND,
  AST_ERROR_LBRACKET_NFOUND,
  AST_ERROR_RBRACKET_NFOUND,
  AST_ERROR_LBRACE_NFOUND,
  AST_ERROR_RBRACE_NFOUND,
} rizm_STRUCTURE_ERROR ;




typedef struct rizm_AST {
  union 
  {
    rizm_STRUCTURE s;
    rizm_STRUCTURE_ERROR s_error ;
  } structure;
  int is_error;
  rizmTokenS* tokens ;
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

    struct {
        rizmTokenS bool_tokens ;
        rizmTokenS body_tokens ;
    } IF_DECLARATION ;
  } DATA;

  struct rizm_AST* next ;
  struct rizm_AST* childs ;

} rizm_AST;


char* get_structure_type(rizm_STRUCTURE structure);
char* get_structure_error(rizm_STRUCTURE_ERROR serr);
void create_rizm_AST(rizmTokenS** tkns , int start_flag , char* value,TokenType type, rizm_AST** nodes, char* varname);
rizm_AST* parse_tokens(rizmTokenS* tokens);
bool parse_declare_variable_tokens(int start_flag , rizm_AST* nodes,rizmTokenS** tkns , TokenType type);
bool parse_if_statement(rizm_AST* nodes , rizmTokenS** tkns);

void print_node_json(rizm_AST* node, int indent_level , int print_tokens) ;
rizm_AST* parse_tokens(rizmTokenS* tokens);
void print_ast_recursive(rizm_AST* nodes);
void print_ast(rizm_AST* nodes , int print_tokens);
void free_ast(rizm_AST* nodes);

#endif
