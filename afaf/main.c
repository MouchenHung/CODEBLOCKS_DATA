#include <stdio.h>

typedef char* string;
typedef unsigned char unit8;
typedef signed short unit16;

char *string_concat(char *str1, char *str2) {
   // 計算所需的陣列長度
   int length=strlen(str1)+strlen(str2)+1;

    char *result;
    result=NULL;
    printf("S---%s\n", result);
   // 產生新的陣列空間
    result = (char*)malloc(sizeof(char) * length);
    printf("S---%s\n", result);
   // 複製第一個字串至新的陣列空間
   strcpy(result, str1);
   // 串接第二個字串至新的陣列空間
   strcat(result, str2);

   return result;
}

char *string_concat1(string *STR) {
   // 計算所需的陣列長度
   int len=0;

   //printf("%s ", *(STR+1));

   while(*(STR+len)){
       printf("%s ", *(STR+len));
       len++;
   }
   printf("%d\n", strlen(STR+1));
   int length=1;

   // 產生新的陣列空間
    char *result = (char*)malloc(sizeof(char) * length);
    printf("S---%s\n", result);

   for(int i=0; i<len; i++){
        strcat(result, *(STR+i));
        printf("%s\n", result);
   }



   return result;
}


char *WriteFile1(char *A_file, string *STR){
    string a[10];
    *a = STR;
    int len=0;
    while(*(STR+len)){
       printf("%s ", *(STR+len));
       len++;
    }
    printf("%d", len);
    printf(" %d\n", sizeof((*a)));
    FILE *fp;
    fp = fopen(A_file, "w");
    for(int i=0; i<len; i++){
        fwrite(*(STR+i), 1, 3, fp);
        printf("fuck\n");
        //fwrite("ABC", 1, 3, fp);
    }
    fclose(fp);
    return STR;
}


void WriteFile(char *A_file, char *text){
    FILE *fp;
    fp = fopen(A_file, "a");
    printf("%s\n", text);
    fwrite(text, 1, sizeof(text)-4, fp);
    fclose(fp);
}
/*

int main ()
{
   FILE *fp;
   char str[] = "This is jikexueyuan.com";

   fp = fopen( "file.txt" , "w" );
   fwrite(str , 1 , sizeof(str)-1 , fp );

   fclose(fp);

   return(0);
}*/

int main(){
    #if 0
    string content2[] = {"aaaa", "bb", NULL};
    //string *p = content2;
    string *p = content2;

    //WriteFile("ab.txt", "DDAD");
    //char *s = string_concat1(p);
    char *s = WriteFile1("abs.txt", p);
    #endif // 0

    int aa[4] = {0};
    printf("%d %d %d %d\n", aa[0], aa[1], aa[2], aa[3]);

    aa[0] = 1;
    printf("%d %d %d %d\n", aa[0], aa[1], aa[2], aa[3]);

    return 0;
}
