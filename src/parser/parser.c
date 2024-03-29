#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "parser.h"




char* get_structure_type(rizm_STRUCTURE structure) {
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
    case IF_STATEMENT : 
        return "IF_STATEMENT";
    default:
        return NULL;
  }
}

char* get_structure_error(rizm_STRUCTURE_ERROR structure) {
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
    case AST_ERROR_LBRACKET_NFOUND :
        return "AST_ERROR_LBRACKET_NFOUND";
    case AST_ERROR_RBRACKET_NFOUND :
        return "AST_ERROR_RBRACKET_NFOUND";
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
    case AST_ERROR_LPAREN_NFOUND :
        return "AST_ERROR_LPAREN_NFOUND";
    case AST_ERROR_RPAREN_NFOUND :
        return "AST_ERROR_RPAREN_NFOUND";
    case AST_ERROR_LBRACE_NFOUND :
        return "AST_ERROR_LBRACE_NFOUND";
    case AST_ERROR_RBRACE_NFOUND :
        return "AST_ERROR_RBRACE_NFOUND";
    default:
        return NULL;
  }
}

void create_rizm_AST(rizmTokenS** tkns,int start_flag,char* value,TokenType type, rizm_AST** nodes, char* varname){
  if (start_flag == 1){
    (*nodes)->next = malloc(sizeof(rizm_AST));
    *nodes = (*nodes)->next;
  }
  else {
    (*nodes)->childs = malloc(sizeof(rizm_AST));
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


bool parse_declare_variable_tokens(int start_flag , rizm_AST* node,rizmTokenS** ptokens , TokenType type){
    rizmTokenS*  p_tkns=((*ptokens));
    printf("Token value : %s\n",((*ptokens))->token.value);
    *ptokens=(*ptokens)->next;
    rizm_AST* nodes = node ;
  
//   if ((*ptokens)->token.type == SPACES){
    // *ptokens = (*ptokens)->next;
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
                    rizmTokenS *pt=*ptokens ;
                    if ((*ptokens)->next)
                      *ptokens = (*ptokens)->next;
                    pt->next=NULL;
                    rizmTokenS  *curr_pt=*ptokens;
                    if ((*ptokens)->token.type == SPACES){
                      *ptokens = (*ptokens)->next;
                      create_rizm_AST( &p_tkns , start_flag, value, type,  &nodes,  varname);
                      p_tkns = curr_pt ;
                      // UPDATE p_tkns
                    }
                    else if ((*ptokens)->token.type == UKNOWN_STRING || (*ptokens)->token.type == UKNOWN_VARNAME){
                      create_rizm_AST( &p_tkns , start_flag, value, type,  &nodes,  varname);
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
                    rizmTokenS* pt=*ptokens;
                    if ((*ptokens)->next)
                      *ptokens = (*ptokens)->next;
                    pt->next=NULL;
                    create_rizm_AST( &p_tkns , start_flag, value, type,  &nodes,  varname);
                    return true;
                  }
                  else {
                    printf("[x] - Error : %s\n",get_structure_error(AST_ERROR_AFTER_VALUE));
                    return false ;
                  }
                }
                else if ((*ptokens)->token.type == COMMA){
                  rizmTokenS *pt=*ptokens ;
                  if ((*ptokens)->next)
                    *ptokens = (*ptokens)->next;
                  pt->next=NULL;
                  rizmTokenS  *curr_pt=*ptokens;
                  if ((*ptokens)->token.type == SPACES){
                    *ptokens = (*ptokens)->next;
                    create_rizm_AST( &p_tkns , start_flag, value, type,  &nodes,  varname);
                    p_tkns = curr_pt ;
                  }
                  else if ((*ptokens)->token.type == UKNOWN_STRING || (*ptokens)->token.type == UKNOWN_VARNAME){
                    create_rizm_AST( &p_tkns , start_flag, value, type,  &nodes,  varname);
                    p_tkns = curr_pt ;
                  }
                  else{
                    printf("[x] - Error : %s\n",get_structure_error(AST_ERROR_AFTER_COMMA));
                    return false ;
                  }
                }
                else if ((*ptokens)->token.type == SEMICOLON) {
                  rizmTokenS* pt=*ptokens;
                  if ((*ptokens)->next)
                    *ptokens = (*ptokens)->next;
                  pt->next=NULL;
                  create_rizm_AST( &p_tkns , start_flag, value, type,  &nodes,  varname);
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
                // rizmTokenS* pt=*ptokens;
                *ptokens = (*ptokens)->next;
                if ((*ptokens)->token.type == COMMA){
                  rizmTokenS *pt=*ptokens ;
                  if ((*ptokens)->next)
                    *ptokens = (*ptokens)->next;
                  pt->next=NULL;
                  rizmTokenS  *curr_pt=*ptokens;
                  if ((*ptokens)->token.type == SPACES){
                    *ptokens = (*ptokens)->next;
                    create_rizm_AST( &p_tkns , start_flag, value, type,  &nodes,  varname);
                    p_tkns = curr_pt ;
                  }
                  else if ((*ptokens)->token.type == UKNOWN_STRING || (*ptokens)->token.type == UKNOWN_VARNAME){
                    create_rizm_AST( &p_tkns , start_flag, value, type,  &nodes,  varname);
                    p_tkns = curr_pt ;
                  }
                  else{
                    printf("[x] - Error : %s\n",get_structure_error(AST_ERROR_AFTER_COMMA));
                    return false ;
                  }
                }
                else if ((*ptokens)->token.type == SEMICOLON) {
                  printf("\n\nMMMMMMMMMMMM\n\n");
                  rizmTokenS* pt=*ptokens;
                  if ((*ptokens)->next)
                    *ptokens = (*ptokens)->next;
                  pt->next=NULL;
                  create_rizm_AST( &p_tkns , start_flag, value, type,  &nodes,  varname);
                  return true;
                }
                else {
                  printf("[x] - Error : %s\n",get_structure_error(AST_ERROR_AFTER_VALUE));
                  return false ;
                }
              }
              else if ((*ptokens)->token.type == COMMA){
                rizmTokenS *pt=*ptokens ;
                if ((*ptokens)->next)
                  *ptokens = (*ptokens)->next;
                pt->next=NULL;
                rizmTokenS  *curr_pt=*ptokens;
                if ((*ptokens)->token.type == SPACES){
                  *ptokens = (*ptokens)->next;
                  create_rizm_AST( &p_tkns , start_flag, value, type,  &nodes,  varname);
                  p_tkns = curr_pt ;
                }
                else if ((*ptokens)->token.type == UKNOWN_STRING || (*ptokens)->token.type == UKNOWN_VARNAME){
                  create_rizm_AST( &p_tkns , start_flag, value, type,  &nodes,  varname);
                  p_tkns = curr_pt ;
                }
                else{
                  printf("[x] - Error : %s\n",get_structure_error(AST_ERROR_AFTER_COMMA));
                  return false ;
                }
              }
              else if ((*ptokens)->token.type == SEMICOLON) {
                rizmTokenS* pt=*ptokens;
                if ((*ptokens)->next)
                  *ptokens = (*ptokens)->next;
                pt->next=NULL;
                create_rizm_AST( &p_tkns , start_flag, value, type,  &nodes,  varname);
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
                  rizmTokenS *pt=*ptokens ;
                  if ((*ptokens)->next)
                    *ptokens = (*ptokens)->next;
                  pt->next=NULL;
                  rizmTokenS  *curr_pt=*ptokens;
                  if ((*ptokens)->token.type == SPACES){
                    *ptokens = (*ptokens)->next;
                    create_rizm_AST( &p_tkns , start_flag, value, type,  &nodes,  varname);
                    p_tkns = curr_pt ;
                  }
                  else if ((*ptokens)->token.type == UKNOWN_STRING || (*ptokens)->token.type == UKNOWN_VARNAME){
                    create_rizm_AST( &p_tkns , start_flag, value, type,  &nodes,  varname);
                    p_tkns = curr_pt ;
                  }
                  else{
                    printf("[x] - Error : %s\n",get_structure_error(AST_ERROR_AFTER_COMMA));
                    return false ;
                  }
                }
                else if ((*ptokens)->token.type == SEMICOLON) {
                  rizmTokenS* pt=*ptokens;
                  if ((*ptokens)->next)
                    *ptokens = (*ptokens)->next;
                  pt->next=NULL;
                  create_rizm_AST( &p_tkns , start_flag, value, type,  &nodes,  varname);
                  return true;
                }
                else {
                  printf("[x] - Error : %s\n",get_structure_error(AST_ERROR_AFTER_VALUE));
                  return false ;
                }
              }
              else if ((*ptokens)->token.type == COMMA){
                rizmTokenS *pt=*ptokens ;
                if ((*ptokens)->next)
                  *ptokens = (*ptokens)->next;
                pt->next=NULL;
                rizmTokenS  *curr_pt=*ptokens;
                if ((*ptokens)->token.type == SPACES){
                  *ptokens = (*ptokens)->next;
                  create_rizm_AST( &p_tkns , start_flag, value, type,  &nodes,  varname);
                  p_tkns = curr_pt ;
                }
                else if ((*ptokens)->token.type == UKNOWN_STRING || (*ptokens)->token.type == UKNOWN_VARNAME){
                  create_rizm_AST( &p_tkns , start_flag, value, type,  &nodes,  varname);
                  p_tkns = curr_pt ;
                }
                else{
                  printf("[x] - Error : %s\n",get_structure_error(AST_ERROR_AFTER_COMMA));
                  return false ;
                }
              }
              else if ((*ptokens)->token.type == SEMICOLON) {
                rizmTokenS* pt=*ptokens;
                if ((*ptokens)->next)
                  *ptokens = (*ptokens)->next;
                pt->next=NULL;
                create_rizm_AST( &p_tkns , start_flag, value, type,  &nodes,  varname);
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
                rizmTokenS *pt=*ptokens ;
                if ((*ptokens)->next)
                  *ptokens = (*ptokens)->next;
                pt->next=NULL;
                rizmTokenS  *curr_pt=*ptokens;
                if ((*ptokens)->token.type == SPACES){
                  *ptokens = (*ptokens)->next;
                  create_rizm_AST( &p_tkns , start_flag, value, type,  &nodes,  varname);
                  p_tkns = curr_pt ;
                }
                else if ((*ptokens)->token.type == UKNOWN_STRING || (*ptokens)->token.type == UKNOWN_VARNAME){
                  create_rizm_AST( &p_tkns , start_flag, value, type,  &nodes,  varname);
                  p_tkns = curr_pt ;
                }
                else{
                  printf("[x] - Error : %s\n",get_structure_error(AST_ERROR_AFTER_COMMA));
                  return false ;
                }
              }
              else if ((*ptokens)->token.type == SEMICOLON) {
                rizmTokenS* pt=*ptokens;
                if ((*ptokens)->next)
                  *ptokens = (*ptokens)->next;
                pt->next=NULL;
                create_rizm_AST( &p_tkns , start_flag, value, type,  &nodes,  varname);
                return true;
              }
              else {
                printf("[x] - Error : %s\n",get_structure_error(AST_ERROR_AFTER_VALUE));
                return false ;
              }
            }
            else if ((*ptokens)->token.type == COMMA){
              rizmTokenS *pt=*ptokens ;
              if ((*ptokens)->next)
                *ptokens = (*ptokens)->next;
              pt->next=NULL;
              rizmTokenS  *curr_pt=*ptokens;
              if ((*ptokens)->token.type == SPACES){
                *ptokens = (*ptokens)->next;
                create_rizm_AST( &p_tkns , start_flag, value, type,  &nodes,  varname);
                p_tkns = curr_pt ;
              }
              else if ((*ptokens)->token.type == UKNOWN_STRING || (*ptokens)->token.type == UKNOWN_VARNAME){
                create_rizm_AST( &p_tkns , start_flag, value, type,  &nodes,  varname);
                p_tkns = curr_pt ;
              }
              else{
                printf("[x] - Error : %s\n",get_structure_error(AST_ERROR_AFTER_COMMA));
                return false ;
              }
            }
            else if ((*ptokens)->token.type == SEMICOLON) {
              rizmTokenS* pt=*ptokens;
              if ((*ptokens)->next)
                *ptokens = (*ptokens)->next;
              pt->next=NULL;
              create_rizm_AST( &p_tkns , start_flag, value, type,  &nodes,  varname);
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
    // return true ;
//   }
//   else {
//     printf("[x] - Error : %s\n",get_structure_error(AST_ERROR_SPACE_NFOUND));
//   }
    return false;
}


bool parse_if_statement(rizm_AST* nodes , rizmTokenS** tkns) {
    rizmTokenS *ptoken = *tkns;
    if (ptoken->token.type == IF) {
        printf("Starting the parser..\n");
        ptoken = ptoken->next ;
        if (ptoken->token.type == LPAREN) {
            rizmTokenS *pptokens = ptoken ;
            rizmTokenS *ppptokens = pptokens;
            ptoken = ptoken->next ;
            while (ptoken->token.type != RPAREN) {
                ptoken = ptoken->next;
                ppptokens = ppptokens->next;
            }
            ppptokens->next=NULL;
            pptokens = pptokens->next;
            printf("[x] - IF statement bool expression : \n");
            print_tokens(pptokens);
            printf("Token type after RPAREN %s\n",get_token_type(ptoken->next->token.type));
            if (ptoken->next->token.type == LBRACE) {
                rizmTokenS *body_tokens = ptoken ;
                rizmTokenS *pbody = body_tokens ;
                ptoken = ptoken->next->next ;
                while (ptoken->token.type != RBRACE) {
                    ptoken = ptoken->next;
                    pbody = pbody->next;
                }
                pbody->next = NULL;
                body_tokens = body_tokens->next->next;
                printf("[x] - BODY\n");
                print_tokens(body_tokens);

                rizm_AST *if_ast = malloc(sizeof(rizm_AST));
                if_ast->DATA.IF_DECLARATION.bool_tokens = pptokens;
                if_ast->DATA.IF_DECLARATION.body_tokens = body_tokens;
                if_ast->structure.s = IF_STATEMENT;
                nodes->next = if_ast;
                // print_ast(if_ast,1);
                *tkns = ptoken;
                return true;
            }
            else {
                printf("[x] - Error : %s\n",get_structure_error(AST_ERROR_LBRACE_NFOUND));
                printf("-------------------------------------------------------------------------------------------------------------\n\n\n\n");
            }
            *tkns = ptoken;
        }
        else {
            printf("[x] - Error : %s\n",get_structure_error(AST_ERROR_LPAREN_NFOUND));
            printf("-------------------------------------------------------------------------------------------------------------\n\n\n\n");
        }
    }
    return false;
}

rizm_AST* parse_tokens(rizmTokenS* tokens) {
  printf("-------- PARSER ---------------------------------------------------------------------------------------------\n");
  if (tokens){
    rizmTokenS* ptokens = tokens ;
    rizm_AST* pnodes = malloc(sizeof(rizm_AST)) , *nodes ;
    nodes = pnodes ;
    pnodes->structure.s= PROGRAM ;
    int start_flag = 0;
    pnodes->tokens = copy_tokens(tokens) ;
    int row=1 ;
    while(ptokens){
      if (ptokens->token.type == INTEGER || ptokens->token.type == BOOL || ptokens->token.type == STRING || ptokens->token.type == FLOAT ){
        TokenType type = ptokens->token.type == INTEGER ? UKNOWN_INT :   ptokens->token.type == BOOL  ? VALUE_BOOL : ptokens->token.type == STRING ? VALUE_STRING : UKNOWN_FLOAT  ;
        printf("Token Type : %s \n",get_token_type(ptokens->token.type));
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
      else if (ptokens->token.type == IF){
        if (parse_if_statement(pnodes,&ptokens)==true) {
            printf("Parsing IF statement : %s\n",get_token_type(ptokens->token.type))  ;
            // ptokens = ptokens->next;
            if (pnodes->next)
                pnodes = pnodes->next;

        }
        else {
            printf("[x] - Error in line %d : %s\n", row , "AST_IF_STATEMENT_ERROR");
            printf("-------------------------------------------------------------------------------------------------------------\n\n\n\n");
            return nodes;
        }

        
      }
      else if(ptokens->token.type == NEWLINES) {
        row+= atoi(ptokens->token.value);
        ptokens = ptokens->next;
      }
      else if (ptokens->token.type == PRINT){
        printf("WTF\n");
        ptokens = ptokens->next;
      }
      else {
        printf("[x] - Else Token : %s\n",get_token_type(ptokens->token.type));
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



void print_ast_recursive(rizm_AST* nodes){
  rizm_AST* pnodes = nodes ;
  while(pnodes){
    pnodes->is_error==1 ? printf("[x] - %s\n",get_structure_error(pnodes->structure.s_error)) :  printf("[x] - %s\n",get_structure_type(pnodes->structure.s));
    pnodes = pnodes->next ;
  }
}

void print_node_json(rizm_AST* node, int indent_level , int print_tokens) {
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
    if (node->structure.s == IF_STATEMENT) {
        printf("%*sIF BOOL\n",indent_level+2,"");
        print_tokens_two(node->DATA.IF_DECLARATION.bool_tokens,indent_level+2);
        printf("%*sIF BODY\n",indent_level+2,"");
        print_tokens_two(node->DATA.IF_DECLARATION.body_tokens,indent_level+2);
    }
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


void print_ast(rizm_AST* nodes, int print_tokens){
  printf("-------- AST ---------------------------------------------------------------------------------------------\n");
  print_node_json( nodes, 0 , print_tokens);
  printf("\n----------------------------------------------------------------------------------------------------------\n");
}


void free_ast(rizm_AST* nodes){
  rizm_AST* curr = nodes;
   while (curr != NULL) {
      rizm_AST* temp = curr;
      curr = curr->next;
      free(temp);
   }
}
