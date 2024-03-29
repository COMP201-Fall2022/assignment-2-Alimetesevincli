/* 
 * COMP201 - Assignment2
 * 
 * <Ali Mete Sevinçli 0079675>
 * 
 * main.c - Source file with your solutions to the assignment.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define input_MAXC 4096
#define NPTRS   2


bool isValidIP(char input[]) {
    char val[] = "1234567890."; 
    int i;
    int a;
    int flag = 0;
    int c = strlen(input);
    for(i = 0; i < strlen(input);i++){
      for(a = 0; a < strlen(val);a++){
        if(input[i] == val[a]){
          flag = 1;
        }
      }
      if(flag == 0){
        return false;
      }
      flag = 0;
    }
    char* subs = strtok(input, ".");
    while (subs != NULL) {
        int numb = atoi(subs);
        if(numb > 255){
            return false;
        }
        if(strlen(subs) != 1){
          char zero[2] = "0";
          if(subs[0] == zero[0]){
            return false;
          }
          
        }
        
        subs = strtok(NULL, ".");
    }
    
    
    // Your code here

    return true; 
}

char *toHex(char input[]) {
  long decimalnum, quotient, remainder;
  int i, j = 0;
  char hexadecimalnum[100];
  char* subs = strtok(input, ".");
  int counter = 0;
  char sub_part2[20];
  char sub_part3[3];

    
  while (subs != NULL) {
    
    int numb = atoi(subs);
    quotient = numb;
    subs = strtok(NULL, ".");
    while (quotient != 0)
    {
        remainder = quotient % 16;
        if (remainder < 10)
            hexadecimalnum[j++] = 48 + remainder;
        else
            hexadecimalnum[j++] = 55 + remainder;
        quotient = quotient / 16;
    }
    char sub_part[4];

    for (i = j; i >= 0; i--){
            sub_part[j-i] =hexadecimalnum[i];
      }
    

    if(counter == 0){
      sub_part2[0] = sub_part[1];
      sub_part2[1] = sub_part[2];
      sub_part2[2] = '.';
      sub_part2[3] = '\0';
    }
    else if(counter == 3){
      char sub_part3[3];
      sub_part3[0] = sub_part[1];
      sub_part3[1] = sub_part[2];
      sub_part3[2] = '\0';
      strcat(sub_part2,sub_part3);
    } 
    else{
      char sub_part3[4];
      sub_part3[0] = sub_part[1];
      sub_part3[1] = sub_part[2];
      sub_part3[2] = '.';
      sub_part3[3] = '\0';
      strcat(sub_part2,sub_part3);
    }
    counter += 1;
} 
  
  
  
  int o;
  char final_1[strlen(sub_part2+1)];
  int p = strlen(sub_part2);
  for(o = 0; o < p; o++){
    input[o] = sub_part2[o];
  }
  int m = strlen(input);
  for(o; o < m; o++){
    input[o] = '\0';
  }
  return input; 

}

bool checkQuery(char query[], char IP[]) {
    // Your code here
    
  int length = strlen(query);
  if(strncmp(query, IP, length) == 0){
    return true;
  }
  else{
    return false;
  }
    }

char *modifyIP(char search_num[], char IP[],char new_num[]) {
    // Your code here
    
    int len_s = strlen(search_num);
    int len_n = strlen(new_num);
    int len = strlen(IP);
    if(len_s == len_n){
      int i, a, s;
      int counter = 0;
      int flag = 0;
      for(i = 0; i < len; i++){
        for(a = 0; a < len_s;a++){
          int z = (a+i);
          if(IP[z] == search_num[a]){
            for(z; z < (a+i+len_s);z++ ){
              if(IP[z] == search_num[z-i]){
                counter +=1;
              }
            }
            if(counter == strlen(search_num)){
               s = i;
               for(s = i; s<(i+len_s); s++ ){
                 IP[s] = new_num[s-i];
               }
               break;
               
          
        }
        counter = 0;
          }
          
        }
        
      } 
    }
    return IP;
}

int main(int argc, char **argv) {
//Some setups to read file!

    // Reading samples from txt
    char input_buf[input_MAXC],
            **input_lines = NULL;
    size_t input_nptrs = NPTRS,
            input_used = 0;
    FILE *input_fp = fopen("sample.txt", "r");

    if (!input_fp) {
        perror("file open failed");
        return 1;
    }
    if ((input_lines = malloc(input_nptrs * sizeof *input_lines)) == NULL) {
        perror("malloc-input_lines");
        exit(EXIT_FAILURE);
    }
    while (fgets(input_buf, input_MAXC, input_fp)) {
        size_t input_len;
        input_buf[(input_len = strcspn(input_buf, "\n"))] = 0;
        if (input_used == input_nptrs) {
            void *input_tmp = realloc(input_lines, (2 * input_nptrs) * sizeof *input_lines);
            if (!input_tmp) {
                perror("realloc-input_lines");
                break;
            }
            input_lines = input_tmp;
            input_nptrs *= 2;
        }
        if (!(input_lines[input_used] = malloc(input_len + 1))) {
            perror("malloc-input_lines[input_used]");
            break;
        }
        memcpy(input_lines[input_used], input_buf, input_len + 1);
        input_used += 1;
    }
    if (input_fp != stdin)
        fclose(input_fp);


    // Reading queries from txt
    char input_buf_query[input_MAXC],
            **input_lines_query = NULL;
    size_t input_nptrs_query = NPTRS,
            input_used_query = 0;

    FILE *input_fp_query = fopen("queries.txt", "r");

    if (!input_fp_query) {
        perror("file open failed");
        return 1;
    }
    if ((input_lines_query = malloc(input_nptrs_query * sizeof *input_lines_query)) == NULL) {
        perror("malloc-input_lines");
        exit(EXIT_FAILURE);
    }
    while (fgets(input_buf_query, input_MAXC, input_fp_query)) {
        size_t input_len_query;
        input_buf_query[(input_len_query = strcspn(input_buf_query, "\n"))] = 0;
        if (input_used_query == input_nptrs_query) {
            void *input_tmp = realloc(input_lines_query, (2 * input_nptrs_query) * sizeof *input_lines_query);
            if (!input_tmp) {
                perror("realloc-input_lines");
                break;
            }
            input_lines_query = input_tmp;
            input_nptrs_query *= 2;
        }
        if (!(input_lines_query[input_used_query] = malloc(input_len_query + 1))) {
            perror("malloc-input_lines[input_used]");
            break;
        }
        memcpy(input_lines_query[input_used_query], input_buf_query, input_len_query + 1);
        input_used_query += 1;
    }
    if (input_fp_query != stdin)
        fclose(input_fp_query);


    printf("\nnumber of IP inputs %ld",input_used);
    printf("\nnumber of query IP inputs %ld",input_used_query);

    char temp_str[50];

    int numberOfValids = 0;
    int j;

    char *IPs[120];

    for (j = 0;j<input_used;j++){
        strcpy(temp_str, input_lines[j]);
        if (isValidIP(temp_str)){
            input_lines[j] = toHex(input_lines[j]);
            IPs[numberOfValids] = input_lines[j];
            numberOfValids ++;
        }
    }

    for(j=0;j<numberOfValids;j++){
        printf("\n%s",IPs[j]);
    }

    printf("\n\n*******\n");
    printf("\nnumber of valid IPs: %d",numberOfValids);
    printf("\n\n*******\n");


    int query_stats[input_used_query];
    // Your code here for keeping the statistics of the network.
    // At the end following for loop should print each of the queries.




    // End of your code
    printf("Query statistics are:\n");
    for (j=0; j<input_used_query;j++){
        printf("\n%d",query_stats[j]);
    }


    // Code below is for testing modifyIP function.

    char search[6];
    char new_num[6];
    char new_num2[10];
    char longer_search[13];
    char search2[10];

    strcpy(search,"48.30");
    strcpy(new_num,"45.40");
    strcpy(longer_search,"45.40.11.a11");
    strcpy(search2, "2.59.8.ee");
    strcpy(new_num2, "25.a.22.f");

    printf("\n\nModification test cases are:\n");

    printf("\n%s",IPs[1]);
    modifyIP(search,IPs[1],new_num);
    printf("\n%s",IPs[1]);

    printf("\n%s",IPs[2]);
    modifyIP(longer_search,IPs[2],new_num);
    printf("\n%s",IPs[2]);

    printf("\n%s",IPs[3]);
    modifyIP(search,IPs[3],new_num);
    printf("\n%s",IPs[3]);

    printf("\n%s",IPs[4]);
    modifyIP(search2,IPs[4],new_num2);
    printf("\n%s",IPs[4]);


    for (size_t i = 0; i < input_used; i++) {
        free (input_lines[i]);}
    free (input_lines);

    for (size_t i = 0; i < input_used_query; i++) {
        free (input_lines_query[i]);}
    free (input_lines_query);

}






