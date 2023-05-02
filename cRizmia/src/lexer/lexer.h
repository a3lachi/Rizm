#ifndef HEADER_LEXER_H
#define HEADER_LEXER_H

#include <stdbool.h>



typedef enum {
  INTEGER,
  FLOAT,
  STRING,
  BOOL,
  IF,
  ELSE,
  WHILE,
  SEMICOLON,
  TRU,
  FALS,
  COLON,
  NAME,
  LPAREN,
  RPAREN,
  LBRACE,
  RBRACE,
  EQUAL,
  PLUS,
  MINUS,
  MULTIPLY,
  DIVIDE,
  RETURN,
  FOR,
  PRINT,
  QUOTE,
  DOUBLEQUOTE,
  VALUE,
  IMPORT,
  COMMENT,
  EMPTYLINE,
  UKNOWN,
  SPACE,
  EMPTY,
  NEWLINES,
  GREATER,
  LESS,
  IN,
  RBRACKET,
  LBRACKET,
  UKNOWN_INT,
  UKNOWN_STRING,
  UKNOWN_FLOAT,
  UKNOWN_VARNAME,
  RANGE_SKIP,
  VALUE_BOOL,
  RANGE,
  PATH,
  COMMA,
  SPACES,
  STRING_INT,
  VALUE_STRING,
  NEWLINE,
} TokenType ;


typedef struct TOKEN
{
  TokenType type ;
  const char* value ;
  unsigned int line ;
  unsigned int col ;
} TOKEN ;



typedef struct BrmjToken
{
  TokenType type ;
  char* value ;
} BrmjToken ;

typedef struct BrmjTokenS
{
  BrmjToken token ;
  struct BrmjTokenS* next ;
} BrmjTokenS ;

TokenType tokenize_string(const char* myStr) ;
TOKEN create_token(TokenType type, const char* value, unsigned int line , unsigned int col ) ;
TokenType tokenize_char(const char myStr) ;

BrmjToken create_BrmjToken(TokenType type, char* value);
BrmjToken tokenize_Brmj(char* s);
char* get_token_type(TokenType type);
BrmjTokenS* tokenize_program(char** s);
void print_tokens(BrmjTokenS* tokens);
void print_tokens_two(BrmjTokenS* tokens ,int indent);
void process_tokens(BrmjTokenS* tokens);
void free_tokens(BrmjTokenS* tokens);
BrmjTokenS* copy_tokens(BrmjTokenS* tokens) ;
#endif 