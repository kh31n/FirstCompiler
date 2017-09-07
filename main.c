#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define DEBUG

int main(int argc,char *argv[]) {
  FILE *fp;
  char c;
  char command[100][100];
  char argument[1000];
  int cnt_command1 = 0;
  int cnt_command2 = 0;
  int cnt_command2_array[100];
  int cnt_command2_array_index = 0;
  int cnt_argument = 0;
  int flag_command1 = 0;
  int flag_command2 = 0;
  int i,j;
  
  if(argc == 0)
    puts("Please Specify Program File.");
  
  if((fp = fopen(argv[1], "r")) == NULL) {
    puts("File open Error.");
    exit(EXIT_FAILURE);
  }
  
  while((c = fgetc(fp)) != EOF) {
    if(flag_command2 && c == ' ') {
      cnt_command1++;
      cnt_command2_array[cnt_command2_array_index++] = cnt_command2;
      cnt_command2 = 0;
      flag_command2 = 0;
      continue;
    }
    if(flag_command1 || c == '\"') {
      flag_command1 = 1;
      if(c != '\"')
        argument[cnt_argument++] = c;
    } else if((flag_command1 == 0 && c >= 'a' && c <= 'z') || (flag_command1 == 0 && c >= 'A' && c <= 'Z')) {
      flag_command2 = 1;
      command[cnt_command1][cnt_command2++] = c;
    }
    if(c == '\n')
      flag_command1 = 0;
  }
  for(i = 0; i < cnt_command1; i++)
    command[i][cnt_command2_array[i]] = '\0';
  argument[cnt_argument - 1] = '\0';
  
#ifdef DEBUG
  for(i = 0; i < cnt_command1; i++)
    printf("%s\n", command[i]);
  printf("%s\n", argument);
#endif
  
  for(i = cnt_command1 - 1; i >= 0; i--) {
    if(strcmp(command[i], "toupper") == 0)
      for(j = 0; j < cnt_argument - 1; j++)
        argument[j] = toupper(argument[j]);
    else if(strcmp(command[i], "puts") == 0)
      puts(argument);
  }
  
  fclose(fp);
  return 0;
}
