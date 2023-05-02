#ifndef HEADER_UTILS_H
#define HEADER_UTILS_H
#include <stdbool.h>




bool is_word_text(const char c) ;
bool is_string_text(const char* s) ;
bool is_char_op(const char c) ;
bool is_word_varname(const char c) ;
bool is_string_varname(const char* s) ;
bool is_string_int(const char* s);
bool is_string_float(const char* s);
bool is_word_numeric(const char c);
bool is_word_char(const char c);
bool is_string_simple_range(const char* s);
bool is_string_textint(const char* s);
bool is_string_path(const char* s);
bool is_string_skip_range(const char* s);


void read_strings(char** s);
char** read_program(char* f);
char** read_shell_command(char* f);

char* readFile(const char* fileName) ;
char* read_file(const char* fileName) ;


char** split_string(const char* s , const char* d) ;
char** split(const char* s, const char* d) ;
bool is_blank(const char* s);

char** split_strings(char** input, const char* delimiter);
char** perform_split(char** s);

#endif 