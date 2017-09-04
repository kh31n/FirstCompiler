#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define DEBUG

int main(int argc,char *argv[]) {
  FILE *fp;
  char c;
  char buf[1000];
  char command[1000];
  char argument[1000];
  int cnt_c = 0;
  int cnt_arg = 0;
  int flag = 0;
  int i;
  if(argc == 0)
    puts("Please Specify Program File.");
  if((fp = fopen(argv[1], "r")) == NULL) {
    puts("File open Error.");
    exit(EXIT_FAILURE);
  }
  while(fgets(buf, sizeof(buf), fp) != NULL) {
    for(i = 0; buf[i] != '\0'; i++) {
      c = buf[i];
      if(c == '\"') {
        flag = 1;
      } else if(c == '\n') {
        flag = 0;
      }
      if((flag == 0 && c >= 'a' && c <= 'z') || (flag == 0 && c >= 'A' && c <= 'Z')) {
        command[cnt_c++] = buf[i];
      } else if(flag && c != '\"') {
        argument[cnt_arg++] = c;
      } else {
        continue;
      }
    }
  }
  command[cnt_c] = '\0';
#ifdef DEBUG
  printf("%s\n", command);
  printf("%s\n", argument);
#endif
  if(strcmp(command, "puts") == 0)
    puts(argument);
  fclose(fp);
  return 0;
}
