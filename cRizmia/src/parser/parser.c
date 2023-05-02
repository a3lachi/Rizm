#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "parser.h"




char* get_structure_type(Brmj_STRUCTURE structure) {
  switch (structure) {
    case PROGRAM:
        return "PROGRAM";
    case IMPORT_STATEMENT:
        return "IMPORT_STATEMENT";
    case VARIABLE_DECLARATION:
        return "VARIABLE_DECLARATION";
    case EXPRESSION_STATEMENT:
        return "EXPRESSION_STATEMENT";
    case WHILE_STATEMENT:
        return "WHILE_STATEMENT";
    default:
        return NULL;
  }
}

char* get_structure_error(Brmj_STRUCTURE_ERROR structure) {
  switch (structure) {
    case AST_ERROR_SEMICOLON_NFOUND:
        return "AST_ERROR_SEMICOLON_NFOUND";
    case AST_ERROR_SPACE_NFOUND:
        return "AST_ERROR_SPACE_NFOUND";
    case AST_ERROR_DECLARE_INTEGER:
        return "AST_ERROR_DECLARE_INTEGER";
    case AST_ERROR_INT_NFOUND:
        return "AST_ERROR_INT_NFOUND";
    case AST_ERROR_VARNAME_NFOUND:
        return "AST_ERROR_VARNAME_NFOUND";
    case AST_ERROR_AFTER_EQUAL:
        return "AST_ERROR_AFTER_EQUAL";
    case AST_ERROR_VALUE_NFOUND:
        return "AST_ERROR_VALUE_NFOUND";
    case AST_ERROR_AFTER_COMMA:
        return "AST_ERROR_AFTER_COMMA";
    case AST_ERROR_DECLARE_BOOL:
        return "AST_ERROR_DECLARE_BOOL";
    case AST_ERROR_DECLARE_STRING:
        return "AST_ERROR_DECLARE_STRING";
    case AST_ERROR_DECLARE_FLOAT:
        return "AST_ERROR_DECLARE_FLOAT";
    case AST_ERROR_AFTER_VALUE:
        return "AST_ERROR_AFTER_VALUE";
    case AST_ERROR_EQUAL_NFOUND:
        return "AST_ERROR_EQUAL_NFOUND";
    default:
        return NULL;
  }
}

void create_Brmj_AST(BrmjTokenS** tkns,int start_flag,char* value,TokenType type, Brmj_AST** nodes, char* varname){
  if (start_flag == 1){
    (*nodes)->next = malloc(sizeof(Brmj_AST));
    *nodes = (*nodes)->next;
  }
  else {
    (*nodes)->childs = malloc(sizeof(Brmj_AST));
    *nodes = (*nodes)->childs;
  }
  (*nodes)->structure.s= VARIABLE_DECLARATION ;
  (*nodes)->childs = NULL;
  (*nodes)->tokens= *tkns;
  (*nodes)->DATA.CONSTANT.type= type == UKNOWN_INT ? INTEGER : type == UKNOWN_FLOAT ? FLOAT : type == VALUE_BOOL ? BOOL : STRING   ;
  (*nodes)->DATA.CONSTANT.varname = varname ;
  if (type == UKNOWN_INT)
    (*nodes)->DATA.CONSTANT.CONST.value_int = atoi(value);
  else if (type == VALUE_BOOL)
    (*nodes)->DATA.CONSTANT.CONST.value_bool = strcmp(value,"true") == 0 ? true : false ;
  else if (type == UKNOWN_FLOAT)
    (*nodes)->DATA.CONSTANT.CONST.value_float = atof(value);
  else if (type == VALUE_STRING)
    (*nodes)->DATA.CONSTANT.CONST.value_s = value;
}


bool parse_declare_variable_tokens(int start_flag , Brmj_AST* node,BrmjTokenS** ptokens , TokenType type){
  BrmjTokenS*  p_tkns=((*ptokens));
  printf("VVVV %s\n",((*ptokens))->token.value);
  *ptokens=(*ptokens)->next;
  Brmj_AST* nodes = node ;
  
  if ((*ptokens)->token.type == SPACES){
    *ptokens = (*ptokens)->next;
    while ((*ptokens)->token.type != SEMICOLON){
      if ((*ptokens)->token.type == UKNOWN_STRING || (*ptokens)->token.type == UKNOWN_VARNAME){
        
        char* varname =(char*) (*ptokens)->token.value;
        
        *ptokens = (*ptokens)->next;
        if ((*ptokens)->token.type == SPACES){
          *ptokens = (*ptokens)->next;
          if ((*ptokens)->token.type == EQUAL){
            *ptokens = (*ptokens)->next;
            if ((*ptokens)->token.type == SPACES){
              *ptokens = (*ptokens)->next;
              if ((*ptokens)->token.type == type){
                char* value = (char*) (*ptokens)->token.value;
                *ptokens = (*ptokens)->next;
                if ((*ptokens)->token.type == SPACES){
                  *ptokens = (*ptokens)->next;
                  if ((*ptokens)->token.type == COMMA){
                    // CUT p_tkns AT COMMA
                    BrmjTokenS *pt=*ptokens ;
                    if ((*ptokens)->next)
                      *ptokens = (*ptokens)->next;
                    pt->next=NULL;
                    BrmjTokenS  *curr_pt=*ptokens;
                    if ((*ptokens)->token.type == SPACES){
                      *ptokens = (*ptokens)->next;
                      create_Brmj_AST( &p_tkns , start_flag, value, type,  &nodes,  varname);
                      p_tkns = curr_pt ;
                      // UPDATE p_tkns
                    }
                    else if ((*ptokens)->token.type == UKNOWN_STRING || (*ptokens)->token.type == UKNOWN_VARNAME){
                      create_Brmj_AST( &p_tkns , start_flag, value, type,  &nodes,  varname);
                      p_tkns = curr_pt ;
                    }
                    else{
                      printf("[x] - Error : %s\n",get_structure_error(AST_ERROR_AFTER_COMMA));
                      return false ;
                    }
                  }
                  else if ((*ptokens)->token.type == SEMICOLON) {
                    printf("L3ARIDA 2\n");
                    // CUT p_tkns at SEMICOLON
                    BrmjTokenS* pt=*ptokens;
                    if ((*ptokens)->next)
                      *ptokens = (*ptokens)->next;
                    pt->next=NULL;
                    create_Brmj_AST( &p_tkns , start_flag, value, type,  &nodes,  varname);
                    return true;
                  }
                  else {
                    printf("[x] - Error : %s\n",get_structure_error(AST_ERROR_AFTER_VALUE));
                    return false ;
                  }
                }
                else if ((*ptokens)->token.type == COMMA){
                  BrmjTokenS *pt=*ptokens ;
                  if ((*ptokens)->next)
                    *ptokens = (*ptokens)->next;
                  pt->next=NULL;
                  BrmjTokenS  *curr_pt=*ptokens;
                  if ((*ptokens)->token.type == SPACES){
                    *ptokens = (*ptokens)->next;
                    create_Brmj_AST( &p_tkns , start_flag, value, type,  &nodes,  varname);
                    p_tkns = curr_pt ;
                  }
                  else if ((*ptokens)->token.type == UKNOWN_STRING || (*ptokens)->token.type == UKNOWN_VARNAME){
                    create_Brmj_AST( &p_tkns , start_flag, value, type,  &nodes,  varname);
                    p_tkns = curr_pt ;
                  }
                  else{
                    printf("[x] - Error : %s\n",get_structure_error(AST_ERROR_AFTER_COMMA));
                    return false ;
                  }
                }
                else if ((*ptokens)->token.type == SEMICOLON) {
                  BrmjTokenS* pt=*ptokens;
                  if ((*ptokens)->next)
                    *ptokens = (*ptokens)->next;
                  pt->next=NULL;
                  create_Brmj_AST( &p_tkns , start_flag, value, type,  &nodes,  varname);
                  return true;
                }
                else {
                  printf("[x] - Error : %s\n",get_structure_error(AST_ERROR_AFTER_VALUE));
                  return false ;
                }
              }
              else {
                printf("[x] - Error : %s\n",get_structure_error(AST_ERROR_VALUE_NFOUND));
                return false ;
              }
            }
            else if ((*ptokens)->token.type == type){
              
              char* value = (char*) (*ptokens)->token.value;
              *ptokens = (*ptokens)->next;
              if ((*ptokens)->token.type == SPACES){
                // BrmjTokenS* pt=*ptokens;
                *ptokens = (*ptokens)->next;
                if ((*ptokens)->token.type == COMMA){
                  BrmjTokenS *pt=*ptokens ;
                  if ((*ptokens)->next)
                    *ptokens = (*ptokens)->next;
                  pt->next=NULL;
                  BrmjTokenS  *curr_pt=*ptokens;
                  if ((*ptokens)->token.type == SPACES){
                    *ptokens = (*ptokens)->next;
                    create_Brmj_AST( &p_tkns , start_flag, value, type,  &nodes,  varname);
                    p_tkns = curr_pt ;
                  }
                  else if ((*ptokens)->token.type == UKNOWN_STRING || (*ptokens)->token.type == UKNOWN_VARNAME){
                    create_Brmj_AST( &p_tkns , start_flag, value, type,  &nodes,  varname);
                    p_tkns = curr_pt ;
                  }
                  else{
                    printf("[x] - Error : %s\n",get_structure_error(AST_ERROR_AFTER_COMMA));
                    return false ;
                  }
                }
                else if ((*ptokens)->token.type == SEMICOLON) {
                  printf("\n\nMMMMMMMMMMMM\n\n");
                  BrmjTokenS* pt=*ptokens;
                  if ((*ptokens)->next)
                    *ptokens = (*ptokens)->next;
                  pt->next=NULL;
                  create_Brmj_AST( &p_tkns , start_flag, value, type,  &nodes,  varname);
                  return true;
                }
                else {
                  printf("[x] - Error : %s\n",get_structure_error(AST_ERROR_AFTER_VALUE));
                  return false ;
                }
              }
              else if ((*ptokens)->token.type == COMMA){
                BrmjTokenS *pt=*ptokens ;
                if ((*ptokens)->next)
                  *ptokens = (*ptokens)->next;
                pt->next=NULL;
                BrmjTokenS  *curr_pt=*ptokens;
                if ((*ptokens)->token.type == SPACES){
                  *ptokens = (*ptokens)->next;
                  create_Brmj_AST( &p_tkns , start_flag, value, type,  &nodes,  varname);
                  p_tkns = curr_pt ;
                }
                else if ((*ptokens)->token.type == UKNOWN_STRING || (*ptokens)->token.type == UKNOWN_VARNAME){
                  create_Brmj_AST( &p_tkns , start_flag, value, type,  &nodes,  varname);
                  p_tkns = curr_pt ;
                }
                else{
                  printf("[x] - Error : %s\n",get_structure_error(AST_ERROR_AFTER_COMMA));
                  return false ;
                }
              }
              else if ((*ptokens)->token.type == SEMICOLON) {
                BrmjTokenS* pt=*ptokens;
                if ((*ptokens)->next)
                  *ptokens = (*ptokens)->next;
                pt->next=NULL;
                create_Brmj_AST( &p_tkns , start_flag, value, type,  &nodes,  varname);
                return true;
              }
              else {
                printf("[x] - Error : %s\n",get_structure_error(AST_ERROR_AFTER_VALUE));
                return false ;
              }
            }
            else {
              printf("[x] - Error : %s\n",get_structure_error(AST_ERROR_AFTER_EQUAL));
              return false ;
            }
          }
          else {
            printf("[x] - Error : %s\n",get_structure_error(AST_ERROR_EQUAL_NFOUND));
            return false ;
          }
        }
        else if ((*ptokens)->token.type == EQUAL){
          *ptokens = (*ptokens)->next;
          printf("RUN THOUGH\n\n");
          if ((*ptokens)->token.type == SPACES){
            *ptokens = (*ptokens)->next;
            if ((*ptokens)->token.type == type){
              char* value = (char*) (*ptokens)->token.value;
              *ptokens = (*ptokens)->next;
              if ((*ptokens)->token.type == SPACES){
                *ptokens = (*ptokens)->next;
                if ((*ptokens)->token.type == COMMA){
                  BrmjTokenS *pt=*ptokens ;
                  if ((*ptokens)->next)
                    *ptokens = (*ptokens)->next;
                  pt->next=NULL;
                  BrmjTokenS  *curr_pt=*ptokens;
                  if ((*ptokens)->token.type == SPACES){
                    *ptokens = (*ptokens)->next;
                    create_Brmj_AST( &p_tkns , start_flag, value, type,  &nodes,  varname);
                    p_tkns = curr_pt ;
                  }
                  else if ((*ptokens)->token.type == UKNOWN_STRING || (*ptokens)->token.type == UKNOWN_VARNAME){
                    create_Brmj_AST( &p_tkns , start_flag, value, type,  &nodes,  varname);
                    p_tkns = curr_pt ;
                  }
                  else{
                    printf("[x] - Error : %s\n",get_structure_error(AST_ERROR_AFTER_COMMA));
                    return false ;
                  }
                }
                else if ((*ptokens)->token.type == SEMICOLON) {
                  BrmjTokenS* pt=*ptokens;
                  if ((*ptokens)->next)
                    *ptokens = (*ptokens)->next;
                  pt->next=NULL;
                  create_Brmj_AST( &p_tkns , start_flag, value, type,  &nodes,  varname);
                  return true;
                }
                else {
                  printf("[x] - Error : %s\n",get_structure_error(AST_ERROR_AFTER_VALUE));
                  return false ;
                }
              }
              else if ((*ptokens)->token.type == COMMA){
                BrmjTokenS *pt=*ptokens ;
                if ((*ptokens)->next)
                  *ptokens = (*ptokens)->next;
                pt->next=NULL;
                BrmjTokenS  *curr_pt=*ptokens;
                if ((*ptokens)->token.type == SPACES){
                  *ptokens = (*ptokens)->next;
                  create_Brmj_AST( &p_tkns , start_flag, value, type,  &nodes,  varname);
                  p_tkns = curr_pt ;
                }
                else if ((*ptokens)->token.type == UKNOWN_STRING || (*ptokens)->token.type == UKNOWN_VARNAME){
                  create_Brmj_AST( &p_tkns , start_flag, value, type,  &nodes,  varname);
                  p_tkns = curr_pt ;
                }
                else{
                  printf("[x] - Error : %s\n",get_structure_error(AST_ERROR_AFTER_COMMA));
                  return false ;
                }
              }
              else if ((*ptokens)->token.type == SEMICOLON) {
                BrmjTokenS* pt=*ptokens;
                if ((*ptokens)->next)
                  *ptokens = (*ptokens)->next;
                pt->next=NULL;
                create_Brmj_AST( &p_tkns , start_flag, value, type,  &nodes,  varname);
                return true;
              }
              else {
                printf("[x] - Error : %s\n",get_structure_error(AST_ERROR_AFTER_VALUE));
                return false ;
              }
            }
            else {
              printf("[x] - Error : %s\n",get_structure_error(AST_ERROR_VALUE_NFOUND));
              return false ;
            }
          }
          else if ((*ptokens)->token.type == type){
            char* value = (char*) (*ptokens)->token.value;
            *ptokens = (*ptokens)->next;
            if ((*ptokens)->token.type == SPACES){
              *ptokens = (*ptokens)->next;
              if ((*ptokens)->token.type == COMMA){
                BrmjTokenS *pt=*ptokens ;
                if ((*ptokens)->next)
                  *ptokens = (*ptokens)->next;
                pt->next=NULL;
                BrmjTokenS  *curr_pt=*ptokens;
                if ((*ptokens)->token.type == SPACES){
                  *ptokens = (*ptokens)->next;
                  create_Brmj_AST( &p_tkns , start_flag, value, type,  &nodes,  varname);
                  p_tkns = curr_pt ;
                }
                else if ((*ptokens)->token.type == UKNOWN_STRING || (*ptokens)->token.type == UKNOWN_VARNAME){
                  create_Brmj_AST( &p_tkns , start_flag, value, type,  &nodes,  varname);
                  p_tkns = curr_pt ;
                }
                else{
                  printf("[x] - Error : %s\n",get_structure_error(AST_ERROR_AFTER_COMMA));
                  return false ;
                }
              }
              else if ((*ptokens)->token.type == SEMICOLON) {
                BrmjTokenS* pt=*ptokens;
                if ((*ptokens)->next)
                  *ptokens = (*ptokens)->next;
                pt->next=NULL;
                create_Brmj_AST( &p_tkns , start_flag, value, type,  &nodes,  varname);
                return true;
              }
              else {
                printf("[x] - Error : %s\n",get_structure_error(AST_ERROR_AFTER_VALUE));
                return false ;
              }
            }
            else if ((*ptokens)->token.type == COMMA){
              BrmjTokenS *pt=*ptokens ;
              if ((*ptokens)->next)
                *ptokens = (*ptokens)->next;
              pt->next=NULL;
              BrmjTokenS  *curr_pt=*ptokens;
              if ((*ptokens)->token.type == SPACES){
                *ptokens = (*ptokens)->next;
                create_Brmj_AST( &p_tkns , start_flag, value, type,  &nodes,  varname);
                p_tkns = curr_pt ;
              }
              else if ((*ptokens)->token.type == UKNOWN_STRING || (*ptokens)->token.type == UKNOWN_VARNAME){
                create_Brmj_AST( &p_tkns , start_flag, value, type,  &nodes,  varname);
                p_tkns = curr_pt ;
              }
              else{
                printf("[x] - Error : %s\n",get_structure_error(AST_ERROR_AFTER_COMMA));
                return false ;
              }
            }
            else if ((*ptokens)->token.type == SEMICOLON) {
              BrmjTokenS* pt=*ptokens;
              if ((*ptokens)->next)
                *ptokens = (*ptokens)->next;
              pt->next=NULL;
              create_Brmj_AST( &p_tkns , start_flag, value, type,  &nodes,  varname);
              return true;
            }
            else {
              printf("[x] - Error : %s\n",get_structure_error(AST_ERROR_AFTER_VALUE));
              return false ;
            }
          }
          else {
            printf("[x] - Error : %s\n",get_structure_error(AST_ERROR_AFTER_EQUAL));
            return false ;
          }
        }
        else {
          printf("[x] - Error : %s\n",get_structure_error(AST_ERROR_EQUAL_NFOUND));
          return false ;
        }
        start_flag=1;
      }
      else {
        printf("[x] - Error : %s\n",get_structure_error(AST_ERROR_VARNAME_NFOUND));
        return false ;
      }
    }
    return true ;
  }
  else {
    printf("[x] - Error : %s\n",get_structure_error(AST_ERROR_SPACE_NFOUND));
  }
  return false;
}


Brmj_AST* parse_tokens(BrmjTokenS* tokens) {
  printf("-------- PARSER ---------------------------------------------------------------------------------------------\n");
  if (tokens){
    BrmjTokenS* ptokens = tokens ;
    Brmj_AST* pnodes = malloc(sizeof(Brmj_AST)) , *nodes ;
    nodes = pnodes ;
    pnodes->structure.s= PROGRAM ;
    int start_flag = 0;
    pnodes->tokens = copy_tokens(tokens) ;
    int row=1 ;
    while(ptokens){
      if (ptokens->token.type == INTEGER || ptokens->token.type == BOOL || ptokens->token.type == STRING || ptokens->token.type == FLOAT ){
        TokenType type = ptokens->token.type == INTEGER ? UKNOWN_INT :   ptokens->token.type == BOOL  ? VALUE_BOOL : ptokens->token.type == STRING ? VALUE_STRING : UKNOWN_FLOAT  ;
        printf("ZID TO %s \n",get_token_type(ptokens->token.type));
        if (parse_declare_variable_tokens(start_flag,  pnodes  ,&ptokens,type)==true){
          if (start_flag==0)
            pnodes = pnodes->childs;
          while(pnodes->next)
            pnodes = pnodes->next ;
          start_flag = 1 ;
          // ptokens = ptokens->next;
          printf("SALA %s\n",get_token_type(ptokens->token.type));
        }
        else {
          printf("[x] - Error in line %d : %s\n", row , get_structure_error(ptokens->token.type == INTEGER ? AST_ERROR_DECLARE_INTEGER :   ptokens->token.type == BOOL  ? AST_ERROR_DECLARE_BOOL : ptokens->token.type == STRING ? AST_ERROR_DECLARE_STRING : AST_ERROR_DECLARE_FLOAT ));
          printf("-------------------------------------------------------------------------------------------------------------\n\n\n\n");
          return nodes;
        }
      }
      else if(ptokens->token.type == NEWLINES) {
        printf("SKIP %s\n",get_token_type(ptokens->token.type));
        row+= atoi(ptokens->token.value);
        ptokens = ptokens->next;
      }
      else {
        printf("THRK %s\n",get_token_type(ptokens->token.type));
        ptokens = ptokens->next;
      }
      
    }
    // pnodes->next = NULL;
    printf("-------------------------------------------------------------------------------------------------------------\n\n\n\n");
    return nodes ;
  }
  printf("-------------------------------------------------------------------------------------------------------------\n\n\n\n");
  return NULL;
}



void print_ast_recursive(Brmj_AST* nodes){
  Brmj_AST* pnodes = nodes ;
  while(pnodes){
    pnodes->is_error==1 ? printf("[x] - %s\n",get_structure_error(pnodes->structure.s_error)) :  printf("[x] - %s\n",get_structure_type(pnodes->structure.s));
    pnodes = pnodes->next ;
  }
}

void print_node_json(Brmj_AST* node, int indent_level , int print_tokens) {
    if (node == NULL) {
      printf("{}");
        return;
    }
    printf("%*s{\n", 1, "");
    printf("%*s\"STRUCT\": \"", indent_level + 2, "");
    printf("\033[0;34m");
    printf("%s",get_structure_type(node->structure.s));
    printf("\033[0m\",\n");
    if (node->structure.s == VARIABLE_DECLARATION){
      printf("%*s\"TYPE\": ", indent_level + 2, "");
      printf("\033[0;36m");
      printf("%s",get_token_type(node->DATA.CONSTANT.type));
      printf("\033[0m,\n");
      printf("%*s\"VARNAME\": ", indent_level + 2, "");
      printf("\033[0;32m");
      printf("%s",node->DATA.CONSTANT.varname);
      printf("\033[0m,\n");
      printf("%*s\"VALUE\": ", indent_level + 2, "");
      printf("\033[0;33m");
      if (node->DATA.CONSTANT.type == INTEGER)
        printf("%d",node->DATA.CONSTANT.CONST.value_int);
      else if (node->DATA.CONSTANT.type == FLOAT)
        printf("%f",node->DATA.CONSTANT.CONST.value_float);
      else if (node->DATA.CONSTANT.type == BOOL)
        printf("%s",node->DATA.CONSTANT.CONST.value_bool == true ? "true" : "false");
      else
        printf("%s",node->DATA.CONSTANT.CONST.value_s);
      printf("\033[0m,\n");
    }
    printf("\033[0m");
    if (print_tokens == 1) {
      printf("%*s\"TOKENS\": \n", indent_level + 2, "");
      print_tokens_two(node->tokens,indent_level+2);
    }
    printf("%*s\"NEXT\": ", indent_level + 2, "");
    print_node_json(node->next, indent_level + 4,print_tokens);
    printf(",\n");
    if (node->childs){
      printf("%*s\"CHILDS\": ", indent_level + 2, "");
      print_node_json(node->childs, indent_level + 4,print_tokens);
      printf("\n");
    }
    printf("%*s}", indent_level-1, "");
}


void print_ast(Brmj_AST* nodes, int print_tokens){
  printf("-------- AST ---------------------------------------------------------------------------------------------\n");
  print_node_json( nodes, 0 , print_tokens);
  printf("\n----------------------------------------------------------------------------------------------------------\n");
}




void free_ast(Brmj_AST* nodes){
  Brmj_AST* curr = nodes;
   while (curr != NULL) {
      Brmj_AST* temp = curr;
      curr = curr->next;
      free(temp);
   }
}