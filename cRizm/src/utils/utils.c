
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


bool is_word_varname(const char c){
	return (c == '_' || ('a' <= c && c <= 'z') || ('0' <= c && c <= '9') || ('A' <= c && c <= 'Z'));
}

bool is_word_char(const char c){
	return ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z');
}

bool is_word_text(const char c){
	return (('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z'));
}

bool is_string_varname(const char* s){
   for (int i = 0; i < strlen(s); i++){
      if (is_word_varname(s[i]) == false)
         return false ;
   }
   return true;
}

bool is_word_numeric(const char c){
   return ('0'<=c && c<='9');
}
bool is_string_int(const char* s){
   for (int i = 0; i < strlen(s); i++){
      if (is_word_numeric(s[i]) == false)
         return false ;
   }
   return true;
}

bool is_string_text(const char* s){
   for (int i = 0; i < strlen(s); i++){
      if (is_word_text(s[i]) == false)
         return false ;
   }
   return true;
}

bool is_string_textint(const char* s){
   for (int i = 0; i < strlen(s); i++){
      if (is_word_text(s[i]) == false ){
        if (is_word_numeric(s[i]) == false )
            return false ;
      }
        
   }
   return true;
}


bool is_string_float(const char* s){
   bool dot_found = false ;
   int i =0 ;
   for (; s[i] != '\0'; i++) {
        if (is_word_numeric(s[i])==true) {
            continue; 
        }
        else if (s[i] == '.') {
            if (!dot_found) {
                dot_found = true; 
            }
            else {
                return false; 
            }
        }
        else {
            return false; 
        }
    }
    return dot_found; 
}

bool is_string_path(const char* s){
   int i =0 ;
   for (; s[i] != '\0'; i++) {
        if (is_word_numeric(s[i])==true ||is_word_char(s[i])==true || s[i] == '/') {
            continue; 
        }
        else {
            return false; 
        }
    }
    return true; 
}

bool is_string_simple_range(const char* s){
   bool dot_found = false ;
   int i =0 ;
   for (; s[i] != '\0'; i++) {
        if (is_word_numeric(s[i])==true) {
            continue; 
        }
        else if (s[i] == ':') {
            if (!dot_found) {
                dot_found = true; 
            }
            else {
                return false; 
            }
        }
        else {
            return false; 
        }
    }
    return dot_found; 
}

bool is_string_skip_range(const char* s){
   int doubledot_found = 0 ;
   int i =0 ;
   for (; s[i] != '\0'; i++) {
        if (is_word_numeric(s[i])==true) {
            continue; 
        }
        else if (s[i] == ':') {
            doubledot_found++;
        }
        else {
            return false; 
        }
    }
    return (doubledot_found==2); 
}


void read_strings(char** s){
    char** ps = s ;
    while(*ps){
        printf("%s",*ps);
        ps++;
    }
}




/*
 *      Copy the file content 2 times 
 *      ?????????????????????????????????
 */
char* readFile(const char* fileName) {
  long file_size;
  char* buffer;
  char* str;
  FILE *fp;


  fp = fopen(fileName, "r");
  if (fp == NULL) {
    printf("[x] - File not found.\n");
    return "";
  }
  fseek(fp, 0, SEEK_END);
  file_size = ftell(fp);
  rewind(fp);

  buffer = (char*) malloc(file_size * sizeof(char));
  fread(buffer, sizeof(char), file_size, fp);

  str = (char*) malloc((file_size + 1) * sizeof(char));
  strncpy(str, buffer, file_size);
  str[file_size] = '\0';

  free(buffer);

  return str;
}


/*
 *      Investigate difference with readFile() where buffer is not 
 *      the returned value
 */
char* read_file(const char* fileName) {
  long file_size;
  char* buffer;
  FILE *fp;

  fp = fopen(fileName, "r");
  if (fp == NULL) {
    printf("[x] - File not found.\n");
    return "";
  }
  fseek(fp, 0, SEEK_END);
  file_size = ftell(fp);
  rewind(fp);

  buffer = (char*) malloc((file_size+1) * sizeof(char));
  fread(buffer, sizeof(char), file_size, fp);
  buffer[file_size]='\0';

  return buffer;
}



char** split_string(const char* s, const char* d) {
    int numSubstrings = 1;
    const char* p = s;
    while (*p != '\0') {
        if (*p == *d) {
            numSubstrings++;
        }
        p++;
    }

    char** substrings = (char**) malloc((2*numSubstrings-1) * sizeof(char*));
    if (substrings == NULL) {
        return NULL;
    }

    int i = 0;
    char* token = strtok((char*) s, d);
    while (token != NULL) {
        substrings[i] = token;
        i++;
        substrings[i] = (char*) d;
        i++;
        token = strtok(NULL, d);
    }
    // substrings[i-1] = (char*) '\0';

    return substrings;
}
bool is_blank(const char* s){
  for (int i = 0; i < strlen(s); i++){
    if(s[i]!=' '){
      return false ;
    }
  }
  return true;
  
}
char** split(const char* s, const char* d) {
    char** substrings = (char**) malloc(2 * sizeof(char*));
    if (substrings == NULL) {
        return NULL;
    }

    // Find the position of the delimiter
    const char* delimiterPos = strchr(s, *d);
    if (delimiterPos == NULL) {
        // If the delimiter is not found, return the entire string as the first substring
        substrings[0] = strdup(s);
        substrings[1] = NULL;
    } else {
        // Allocate memory for the first substring and copy it
        int firstSubstringLength = delimiterPos - s;
        substrings[0] = (char*) malloc(firstSubstringLength + 1);
        if (substrings[0] == NULL) {
            free(substrings);
            return NULL;
        }
        strncpy(substrings[0], s, firstSubstringLength);
        substrings[0][firstSubstringLength] = '\0';

        // Allocate memory for the second substring and copy it
        int secondSubstringLength = strlen(delimiterPos + 1);
        substrings[1] = (char*) malloc(secondSubstringLength + 1);
        if (substrings[1] == NULL) {
            free(substrings[0]);
            free(substrings);
            return NULL;
        }
        strcpy(substrings[1], delimiterPos + 1);
    }

    return substrings;
}


char** split_strings(char** input, const char* delimiter) {
    // First, count the number of substrings
    int num_substrings = 0;
    char** current_input = input;
    while (*current_input != NULL) {
        char* current_string = *current_input;
        while (*current_string != '\0') {
            if (strncmp(current_string, delimiter, strlen(delimiter)) == 0) {
                num_substrings++;
            }
            num_substrings++;
            current_string++;
        }
        current_input++;
    }
    
    // Allocate memory for the output array of strings
    char** output = malloc((num_substrings + 1) * sizeof(char*)); // Add 1 for the terminating NULL pointer
    if (output == NULL) {
        return NULL; // Failed to allocate memory
    }
    
    // Split the input strings and fill the output array
    int output_index = 0;
    current_input = input;
    while (*current_input != NULL) {
        char* current_string = *current_input;
        char* substring_start = current_string;
        while (*current_string != '\0') {
            if (strncmp(current_string, delimiter, strlen(delimiter)) == 0) {
                int substring_length = current_string - substring_start;
                output[output_index] = malloc((substring_length + 1) * sizeof(char)); // Add 1 for the terminating '\0'
                if (output[output_index] == NULL) {
                    // Failed to allocate memory for a substring, free the previously allocated memory and return NULL
                    for (int i = 0; i < output_index; i++) {
                        free(output[i]);
                    }
                    free(output);
                    return NULL;
                }
                strncpy(output[output_index], substring_start, substring_length);
                output[output_index][substring_length] = '\0';
                output_index++;
                output[output_index] = malloc((strlen(delimiter) + 1) * sizeof(char)); // Add 1 for the terminating '\0'
                if (output[output_index] == NULL) {
                    // Failed to allocate memory for the delimiter, free the previously allocated memory and return NULL
                    for (int i = 0; i < output_index; i++) {
                        free(output[i]);
                    }
                    free(output);
                    return NULL;
                }
                strncpy(output[output_index], delimiter, strlen(delimiter));
                output[output_index][strlen(delimiter)] = '\0';
                output_index++;
                substring_start = current_string + strlen(delimiter);
            }
            current_string++;
        }
        // Add the last substring, even if it doesn't end with the delimiter
        int substring_length = current_string - substring_start;
        output[output_index] = malloc((substring_length + 1) * sizeof(char)); // Add 1 for the terminating '\0'
        if (output[output_index] == NULL) {
            // Failed to allocate memory for the last substring, free the previously allocated memory and return NULL
            for (int i = 0; i < output_index; i++) {
                free(output[i]);
            }
            free(output);
            return NULL;
        }
        strncpy(output[output_index], substring_start, substring_length);
        output[output_index][substring_length] = '\0';
        output_index++;
        current_input++;
    }
    output[output_index] = NULL; // Add the terminating NULL pointer
    
    return output;
}


char** perform_split(char** s){
    char** splited = split_strings(s,"\n");
    splited = split_strings(splited," ");
    splited = split_strings(splited,";");
    splited = split_strings(splited,",");
    splited = split_strings(splited,">=");
    splited = split_strings(splited,"<=");
    splited = split_strings(splited,"<");
    splited = split_strings(splited,">");
    splited = split_strings(splited,"(");
    splited = split_strings(splited,")");
    splited = split_strings(splited,"{");
    splited = split_strings(splited,"}");
    splited = split_strings(splited,"[");
    splited = split_strings(splited,"]");
    splited = split_strings(splited,"'");
    splited = split_strings(splited,"\"");
    splited = split_strings(splited,"=");
    return splited ;
}


/*
 * This function read a file and return an array of strings splited by the rules defined in perform_split
 */
char** read_program(char* f){
    char** program = (char**) malloc(1*sizeof(char*));
    program[0] = read_file(f) ;
    // printf("------------ PROGRAM ------------------------------------------------------------------------------------------\n%s\n---------------------------------------------------------------------------------------------------------------\n\n\n\n",program[0]);
    char** plines = perform_split(program);
    free(program);
    return plines ;
}

char** read_shell_command(char* f){
    char** program = (char**) malloc(1*sizeof(char*));
    program[0] = f ;
    char** plines = perform_split(program);
    free(program);
    return plines ;
}