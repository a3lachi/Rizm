#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "lexer.h"
#include "../utils/utils.h"
#include <stdbool.h>



TokenType tokenize_string(const char* myStr){
   if (strcmp(myStr, "int") == 0) return INTEGER;
   else if (strcmp(myStr, "string") == 0) return STRING;
   else if (strcmp(myStr, "float") == 0) return FLOAT;
   else if (strcmp(myStr, "true") == 0) return VALUE_BOOL;
   else if (strcmp(myStr, "false") == 0) return VALUE_BOOL;
   else if (strcmp(myStr, "bool") == 0) return BOOL;
   else if (strcmp(myStr, "if") == 0) return IF;
   else if (strcmp(myStr, "else") == 0) return ELSE;
   else if (strcmp(myStr, "while") == 0) return WHILE;
   else if (strcmp(myStr, "print") == 0) return PRINT;
   else if (strcmp(myStr, "import") == 0) return IMPORT;
   else if (strcmp(myStr, "//") == 0) return COMMENT;
   else if (strcmp(myStr, "return") == 0) return RETURN;
   else if (strcmp(myStr, "for") == 0) return FOR;
   else if (strcmp(myStr, "in") == 0) return IN;
   else if (is_string_int(myStr)==true) return UKNOWN_INT;
   else if (is_string_text(myStr)==true) return UKNOWN_STRING;
   else if (is_string_float(myStr)==true) return UKNOWN_FLOAT;
   else if (is_string_varname(myStr)==true) return UKNOWN_VARNAME;
   else if (is_string_simple_range(myStr)==true) return RANGE;
   else if (is_string_skip_range(myStr)==true) return RANGE_SKIP;
   else if (is_string_textint(myStr)==true) return STRING_INT;
   else if (is_string_path(myStr)==true) return PATH;
   return UKNOWN;
}

TokenType tokenize_char(const char myStr){
   if (myStr == ';') return SEMICOLON;
   else if (myStr == ':') return COLON;
   else if (myStr == '\'') return QUOTE;
   else if (myStr == '"') return DOUBLEQUOTE;
   else if (myStr == '(') return LPAREN;
   else if (myStr == ')') return RPAREN;
   else if (myStr == '{') return LBRACE;
   else if (myStr == '}') return RBRACE;
   else if (myStr == '=') return EQUAL;
   else if (myStr == '+') return PLUS;
   else if (myStr == '-') return MINUS;
   else if (myStr == '*') return MULTIPLY;
   else if (myStr == '/') return DIVIDE;
//    else if (myStr == ' ') return SPACE;
   else if (myStr == '>') return GREATER;
   else if (myStr == '<') return LESS;
   else if (myStr == '[') return LBRACKET;
   else if (myStr == ',') return COMMA;
//    else if (myStr == '\n') return NEWLINE;
   else if (myStr == ']') return RBRACKET;
   else if (is_word_numeric(myStr)==true) return UKNOWN_INT;
   else if (is_word_char(myStr)==true) return UKNOWN_STRING;
   return UKNOWN;
}

char* get_token_type(TokenType type) {
   switch (type) {
      case INTEGER:
         return "INTEGER";
      case FLOAT:
         return "FLOAT";
      case STRING:
         return "STRING";
      case BOOL:
         return "BOOL";
      case IF:
         return "IF";
      case ELSE:
         return "ELSE";
      case WHILE:
         return "WHILE";
      case SEMICOLON:
         return "SEMICOLON";
      case COLON:
         return "COLON";
      case NAME:
         return "NAME";
      case LPAREN:
         return "LPAREN";
      case RPAREN:
         return "RPAREN";
      case LBRACE:
         return "LBRACE";
      case RBRACE:
         return "RBRACE";
      case EQUAL:
         return "EQUAL";
      case PLUS:
         return "PLUS";
      case MINUS:
         return "MINUS";
      case MULTIPLY:
         return "MULTIPLY";
      case DIVIDE:
         return "DIVIDE";
      case PRINT:
         return "PRINT";
      case QUOTE:
         return "QUOTE";
      case DOUBLEQUOTE:
         return "DOUBLEQUOTE";
      case VALUE:
         return "VALUE";
      case IMPORT:
         return "IMPORT";
      case COMMENT:
         return "COMMENT";
      case EMPTYLINE:
         return "EMPTYLINE";
      case UKNOWN:
         return "UKNOWN";
      case PATH:
         return "PATH";
      case VALUE_BOOL:
         return "VALUE_BOOL";
      case SPACE:
         return "SPACE";
      case EMPTY:
         return "EMPTY";
      case LESS:
         return "LESS";
      case TRU:
         return "TRU";
      case FALS:
         return "FALS";
      case GREATER:
         return "GREATER";
      case SPACES:
         return "SPACES";
      case NEWLINES:
         return "NEWLINES";
      case RETURN:
         return "RETURN";
      case FOR:
         return "FOR";
      case NEWLINE:
         return "NEWLINE";
      case IN:
         return "IN";
      case RBRACKET:
         return "RBRACKET";
      case LBRACKET:
         return "LBRACKET";
      case VALUE_STRING:
         return "VALUE_STRING";
      case UKNOWN_INT:
         return "UKNOWN_INT";
      case UKNOWN_STRING:
         return "UKNOWN_STRING";
      case UKNOWN_FLOAT:
         return "UKNOWN_FLOAT";
      case UKNOWN_VARNAME:
         return "UKNOWN_VARNAME";
      case RANGE:
         return "RANGE";
      case COMMA:
         return "COMMA";
      case RANGE_SKIP:
         return "RANGE_SKIP";
      case STRING_INT:
         return "STRING_INT";
      default:
         return NULL;
   }
}

TokenType tokenize(const char* s){
   if (strlen(s)==1)
      return tokenize_char(*s);
   else if (strlen(s)==0)
      return EMPTY;
   else 
      return tokenize_string(s);
}

bool is_char_op(const char c){
	switch (c) {
	case '+':
	case '-':
	case '*':
	case '/':
	case '%':
	case '&':
	case '|':
	case '^':
	case '!':
	case '~':
	case '=':
	case '<':
	case '>':
	case '.':
	case '@':
		return true;
	default:
		return false;
	}
}

TOKEN create_token(TokenType type, const char* value, unsigned int line , unsigned int col ) {
   TOKEN token ;
   token.type = type ;
   token.value = value ;
   token.line = line ;
   token.col = col ;
   return token ;
}

rizmToken create_rizmToken(TokenType type, char* value){
   rizmToken token ;
   token.type = type ; 
   token.value = value ;
   return token ;
}

rizmToken tokenize_rizm(char* s){
   TokenType tokenType = tokenize(s);
   rizmToken token = create_rizmToken(tokenType,s);
   return token;
}

void process_tokens(rizmTokenS* tokens){
   rizmTokenS* headSpaces , *ptokens = tokens ;
   int count = 0;
   char* countStr  ;
   while (ptokens){
      if (ptokens->token.type == SPACE) {
         headSpaces = ptokens ;
         count++;
         ptokens=ptokens->next;
         while (ptokens && ptokens->token.type == SPACE){
            count++;
            rizmTokenS* currtoken = ptokens ;
            ptokens=ptokens->next;
            free(currtoken);
         }
         headSpaces->next = ptokens ;
         countStr = malloc(sizeof(char) * 10);
         snprintf(countStr, 10,"%d", count);
         headSpaces->token.value = countStr;
         headSpaces->token.type = SPACES;
         count = 0;
      }
      else if (ptokens && ptokens->token.type == NEWLINE) {
         headSpaces = ptokens ;
         count++;
         ptokens=ptokens->next;
         while (ptokens && ptokens->token.type == NEWLINE){
            rizmTokenS* currtoken = ptokens ;
            count++;
            ptokens=ptokens->next;
            free(currtoken);
         }
         headSpaces->next = ptokens ;
         countStr = malloc(sizeof(char) * 10);
         snprintf(countStr, 10,"%d", count);
         headSpaces->token.value = countStr;
         headSpaces->token.type = NEWLINES;
         count = 0;
      }
      else if (ptokens && ptokens->token.type == QUOTE) {
         headSpaces = ptokens ;
         rizmTokenS* p_tokens = ptokens; 
         ptokens=ptokens->next;
         int count = strlen(ptokens->token.value) ;
         while(ptokens && ptokens->token.type!=QUOTE){
            ptokens=ptokens->next;
            count += strlen(ptokens->token.value);
         }
         if (ptokens &&  ptokens->token.type == QUOTE){
            char* s_value = malloc((count+1)*sizeof(char));
            s_value[0]='\'' ;
            s_value[1]='\0';
            p_tokens = p_tokens ->next;
            while(p_tokens && p_tokens->token.type!=QUOTE){
               strcat(s_value,p_tokens->token.value);
               p_tokens=p_tokens->next;
            }
            s_value[count]='\'' ;
            s_value[count+1]='\0' ;
            headSpaces->next = ptokens->next ;
            headSpaces->token.type = VALUE_STRING;
            headSpaces->token.value = s_value;
         }
         ptokens=ptokens->next;
      }
      else if (ptokens && ptokens->token.type == DOUBLEQUOTE) {
         headSpaces = ptokens ;
         rizmTokenS* p_tokens = ptokens; 
         int count = 1 ;
         ptokens=ptokens->next;
         while(ptokens && ptokens->token.type!=DOUBLEQUOTE){
            count += strlen(ptokens->token.value);
            ptokens=ptokens->next;
         }
         
         if (ptokens &&  ptokens->token.type == DOUBLEQUOTE){
            char* s_value = malloc((count+2)*sizeof(char));
            s_value[0]='\"' ;
            s_value[1]='\0';
            p_tokens = p_tokens ->next;
            while(p_tokens && p_tokens->token.type!=DOUBLEQUOTE){
               strcat(s_value,p_tokens->token.value);
               p_tokens=p_tokens->next;
            }
            s_value[count]='\"' ;
            s_value[count+1]='\0' ;
            headSpaces->next = ptokens->next ;
            headSpaces->token.type = VALUE_STRING;
            headSpaces->token.value = s_value ;
            
         }
         ptokens=ptokens->next;
      }
      else {
         ptokens=ptokens->next;
      }
   }
}

rizmTokenS* tokenize_program(char** s) {
   rizmTokenS* tokens ;
   rizmTokenS* ptoken = NULL;
   rizmToken token ;
   while(*s){
      token = tokenize_rizm(*s);
      if (token.type != EMPTY){
         if (ptoken == NULL) {
            ptoken = (rizmTokenS*) malloc(sizeof(rizmTokenS));
            tokens = ptoken;
         } else {
            ptoken->next = (rizmTokenS*) malloc(sizeof(rizmTokenS));
            ptoken = ptoken->next;
         }
         ptoken->token = token;
         ptoken->next = NULL;
      }
      s++;
   }
   process_tokens(tokens);
   return tokens ;
}

void print_tokens(rizmTokenS* tokens) {
   printf("-------- LEXER TOKENS -----------------------------------------------------------------------------------------\n");
   while(tokens)
  {
      printf("[x] - ");
      printf("\033[0;36m");
      printf("%s",get_token_type(tokens->token.type));
      printf("\033[0m");
      printf(" - ");
      printf("\033[0;34m");
      printf("%s\n",tokens->token.value);
      printf("\033[0m");
      tokens=tokens->next;
  }
  printf("----------------------------------------------------------------------------------------------------------------\n\n\n");
}

void print_tokens_two(rizmTokenS* tokens,int indent){
while(tokens)
  {
      printf("%*s   |- ",indent,"");
      printf("\033[0;35m");
      printf("%s",get_token_type(tokens->token.type));
      printf("\033[0m");
      printf(" , ");
      if (tokens->token.type == INTEGER || tokens->token.type == STRING || tokens->token.type == BOOL || tokens->token.type == FLOAT)
         printf("\033[0;36m");
      else if (tokens->token.type == UKNOWN_INT || tokens->token.type == VALUE_STRING || tokens->token.type == VALUE_BOOL  )
         printf("\033[0;33m");
      else if (tokens->token.type == SPACES)
         printf("\033[0;35m");
      printf("%s\n",tokens->token.value);
      printf("\033[0m");
      tokens=tokens->next;
  }
}

void free_tokens(rizmTokenS* tokens){
   rizmTokenS* curr = tokens;
   while (curr != NULL) {
      rizmTokenS* temp = curr;
      curr = curr->next;
      free(temp);
   }
}

rizmTokenS* copy_tokens(rizmTokenS* tokens) {
    rizmTokenS* new_tokens = NULL;
    rizmTokenS* current_token = tokens;
    rizmTokenS* current_new_token = NULL;
    
    while (current_token != NULL) {
        rizmTokenS* new_token = (rizmTokenS*) malloc(sizeof(rizmTokenS));
        if (new_token == NULL) {
            return NULL;
        }
        new_token->token = current_token->token;
        new_token->next = NULL;
        
        if (new_tokens == NULL) {
            new_tokens = new_token;
            current_new_token = new_token;
        } else {
            current_new_token->next = new_token;
            current_new_token = new_token;
        }
        
        current_token = current_token->next;
    }
    
    return new_tokens;
}
