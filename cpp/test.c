#include "stdio.h"
#include "string.h"

int main(){
    char str[50];
    int n,i,j,num1,num2;
    char* cmd[4] = {"get","insert","delete","show"};
    scanf("%d",&n);
    for(j=0; j<n; j++){
        scanf("%s",str);
        for(i = 0; i<4; i++){
            if(strstr(str,cmd[i])){
                switch (i)
                {
                case 0: //get
                    scanf("%d %d",&num1,&num2);
                    printf("%d %d\n",num1, num2);
                    break;
                case 1://insert
                    scanf("%d %d",&num1,&num2);
                    printf("%d %d\n",num1, num2);
                    break;
                case 2://delete
                    scanf("%d",&num1);
                    break;
                default:
                    break;
              }
              break;
            }
        }
    }
    
    return 0;
}

/*
#include <string.h>
#include <stdio.h>
 
int main () {
   char str[80] = "This is - www.runoob.com - website";
   const char s[2] = "-";
   char *token;
   
   // 获取第一个子字符串 
   token = strtok(str, s);
   
   // 继续获取其他的子字符串 
   while( token != NULL ) {
      printf( "%s\n", token );
    
      token = strtok(NULL, s);
   }
   
   return(0);
}*/