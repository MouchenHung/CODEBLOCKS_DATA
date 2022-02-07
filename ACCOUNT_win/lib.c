#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "usefulTOOL.h"
#define max(a,b) ((a)>(b) ? (a) : (b))

/*mode[0]: password with '*', mode[1]: user name with 'type.' */
char *PrivatePassword1(int limitLEN, int mode){
    int i=0;
    char ch1, password[limitLEN], *output;

    while(i<limitLEN){
        if(i<0){
            i=0;
        }
        if(mode == 0){
            ch1=getch();

            //printf("++%d\n", ch1);

            //10 is ASCII of Enter key
            if(ch1 == 13){
                break;
            }
            else if(ch1 == 8){
                if(i){
                    printf("\b \b");//implementing the effect of backspace
                    i--;
                    continue;
                }
            }
            else
            {
                password[i]=ch1;
                printf("*");
                i++;
            }
        }
        else if(mode == 1){
            ch1=getch();
            //printf("++%d\n", ch1);
            //10 is ASCII of Enter key
            if(ch1 == 13){
                break;
            }
            else if(ch1 == 8){
                if(i){
                    printf("\b \b");//implementing the effect of backspace
                    i--;
                    continue;
                }
            }
            else
            {
                password[i]=ch1;
                printf("%c", password[i]);
                i++;
            }
        }
        //printf("%d %c\n", i, password[i]);

    }
    printf("\n");
    password[i]='\0';
    output = password;
    return output;
}

void WordCaseChange(char *words, int mode){
    int i=0;
    while (words[i])
    {
        switch (mode)
        {
        case 0:
            //A->a and a->A
            if (words[i] >= 'A' && words[i] <= 'Z'){
                words[i]+=32;
            }
            else if (words[i] >= 'a' && words[i] <= 'z'){
                words[i]-=32;
            }
            break;
        case 1:
            //A->a
            if (words[i] >= 'A' && words[i] <= 'Z'){
                words[i]+=32;
            }
            break;
        case 2:
            //a->A
            if (words[i] >= 'a' && words[i] <= 'z'){
                words[i]-=32;
            }
            break;
        default:
            printf("no such mode!\n");
            break;
        }


        i++;
    }
}

void mkdirs(char *muldir)
{
    int i,len;
    char str[512];
    strncpy(str, muldir, 512);
    len=strlen(str);
    for( i=0; i<len; i++ )
    {
        if( str[i]=='/' )
        {
            str[i] = '\0';
            if( access(str,0)!=0 )
            {
                mkdir( str, 0777 );
            }
            str[i]='/';
        }
    }
    if( len>0 && access(str,0)!=0 )
    {
        mkdir( str, 0777 );
    }
}

int AccountCopy(char* file_path, char* dest_path){
  FILE *fptr1,*fptr2;
  char ch;
  int count=0;
  fptr1=fopen(file_path,"r");
  fptr2=fopen(dest_path,"w");
  if( fptr1!=NULL && fptr2!=NULL)
  {
      while( (ch=getc(fptr1))!=EOF)
              {
              //printf("%c",ch);

              putc(ch,fptr2);
              }
             printf("\n");
      fclose(fptr1);
      fclose(fptr2);
      //printf("copy  YES!!\n");
  }
  else
      printf("--> Copy Faild!!\n");

}

void RebuildFile(char* file_path, char*** data, int const r, int const c){
    if( remove(file_path) == 0 )
        printf(GREEN "--> Rebuild %s success!\n" NOCOLOR, file_path);
    else
        perror(RED "--> Rebuild Failed!\n" NOCOLOR);
    ACCOUNT_WriteFile(file_path, data, r, c, 0);
}

void ACCOUNT_WriteFile(char* file_path, char*** data, int const r, int const c, int mode){
    FILE *fp;
    fp = fopen(file_path, "a");

    if(mode==1){
        int size[c];
        int i,j,k;
        for ( j=0; j<c; j++ ) {
            size[j] = 0;
            for ( i=0; i<r; i++ )
                size[j] = max(strlen(data[i][j]),size[j]);
        }

        for ( i=0; i<r; i++ ) {
            for ( j=0; j<c; j++ ) {
                if ( j==3 || j>=6 ) { // 數字靠右
                    for ( k=0; k<size[j]-strlen(data[i][j]); k++ ){

                        if(j < (c-1)){
                        printf(" ");
                        fwrite(" ", 1, 1, fp);
                        }
                    }
                    printf("%s",data[i][j]);
                    fwrite(data[i][j], strlen(data[i][j]), 1, fp);



                } else { // 文字靠左
                    printf("%s",data[i][j]);
                    fwrite(data[i][j], strlen(data[i][j]), 1, fp);
                    if(j<(c-1)){
                        for ( k=0; k<size[j]-strlen(data[i][j])+1; k++ ){
                            printf(" ");
                            fwrite(" ", 1, 1, fp);
                        }
                    }

                }
            } printf("\n"); fwrite("\n", 1, 1, fp);
        } printf("\n"); fwrite("\n", 1, 1, fp);
    }

    if(mode==0){
        for(int i=0; i<r; i++){
            for(int j=0; j<c; j++){
                fwrite(data[i][j], strlen(data[i][j]), 1, fp);
                if(j<c-1){
                    fwrite(" ", 1, 1, fp);
                }

            }
            fwrite("\n", 1, 1, fp);
        }
    }

    fclose(fp);

}

void CostLimit(int *Remain, int *mSalary, int *val, int flag){
    if(flag==0){
        *Remain = *mSalary;
        //printf("month salary\n");
    }
    else if(flag==1)
    {
        *Remain += *val;
    }
    else if(flag==2)
    {
        *Remain -= *val;
    }
    else if(flag==3){
        if(*Remain<=IDEAL_MONTH){
            printf(WARNING_OUTPUT "--> !!!WARNING!!!\n");
            printf("--> Exceed COST NTD.%d for saving NTD.%d.\n", *Remain-IDEAL_MONTH, IDEAL_MONTH); printf(NOCOLOR);
        }
        else
            printf(NORMAL_OUTPUT "--> Available COST NTD.%d for saving NTD.%d.\n", *Remain-IDEAL_MONTH, IDEAL_MONTH); printf(NOCOLOR);
    }
    //printf("!!! %d %d %d !!!\n", *Remain, *mSalary, *val);
}


void Show_CostLimit(char*** data, int* row ){
    int REMAIN, mSalary, money;
    for(int i=0; i<*row; i++){
        if(!strcmp(data[i][1],"Salary")){
            mSalary = atoi(data[i][3]);
            CostLimit(&REMAIN, &mSalary, &money, 0);
        }
        else if(!strcmp(data[i][1],"Bonus")){
            money = atoi(data[i][3]);
            CostLimit(&REMAIN, &mSalary, &money, 1);
        }
        else if(!strcmp(data[i][1],"---")){
            money = atoi(data[i][6]);
            CostLimit(&REMAIN, &mSalary, &money, 2);
        }
    }
    CostLimit(&REMAIN, &mSalary, &money, 3);
}

char**** fileline( char* file_path, int* row, int* colum ) {
	FILE *fp;
	//char *line=NULL;
	char line[255];
    int line_n=0;
	size_t len=0;
	ssize_t read;


	fp = fopen(file_path,"r");
    if(NULL == fp){
        printf(WARNING_OUTPUT "--> Can't open your ACCOUNT FILE named { %s }.\n", file_path); printf(NOCOLOR);
    }
	while ( ((read = fgets(&line,&len,fp))!=0) ) {
        line_n++;
	}
    fclose(fp);
	fp = fopen(file_path,"r");
	//printf("Total %d lines.\n",line_n);
	char ***out = (char***)malloc(sizeof(char**)*line_n);
	int line_idx=0;
	int inline_p0, inline_p1, inline_len, inline_idx, inline_pidx;

	while ( ((read = fgets(&line,&len,fp))!=0) ) {
        out[line_idx]=(char**)malloc(sizeof(char**)*9);
        inline_p0=0,inline_p1=0,inline_idx=0,inline_pidx = 0;
        inline_len = strlen(line);
        out[line_idx][inline_pidx] = (char*)malloc(sizeof(char*)*inline_len);
        while ( *(line+inline_p1)!='\0') {
            //printf("%c",*(line+inline_p1));
            if (*(line+inline_p1)==' ') {
                out[line_idx][inline_pidx][inline_idx] = '\0';
                //printf("\n[%d,%d,%s]\n",line_idx,inline_pidx,out[line_idx][inline_pidx]);
                inline_len -= (inline_p1-inline_p0);
                out[line_idx][++inline_pidx] = (char*)malloc(sizeof(char*)*(inline_len));
                while ( *(line+inline_p1)==' ' ) inline_p1++;
                inline_p0=inline_p1;
                inline_idx=0;
            } else if (*(line+inline_p1)=='\n') {
                break;
            } else {
                out[line_idx][inline_pidx][inline_idx] = *(line+inline_p1);
                inline_idx++;
                inline_p1++;
            }
        }
        out[line_idx][inline_pidx][inline_idx] = '\0';
        line_idx++;
	} fclose(fp);
    *row = line_idx;
    *colum = inline_pidx+1;

	return out;
}
void showFile ( char*** f , int const r, int const c) {
    int i,j,k;
    // check max length
    int size[c] ;
    int total_len=0;
    char buffer[40];
    for ( j=0; j<c; j++ ) {
        size[j] = 0;
        for ( i=0; i<r; i++ )
            size[j] = max(strlen(f[i][j]),size[j]);
        total_len += size[j];
    }
    time_t rawtime;
    struct tm* timeinfo;
    time (&rawtime);
    timeinfo = localtime (&rawtime);
    strftime(buffer,40," Data: %F %T. (UTC+8) ",timeinfo);
    for ( j=0; j<40; j++ ) printf("="); printf("%s",buffer);
    for ( j=0; j<total_len-40-strlen(buffer)+8; j++ ) printf("="); printf("\n"); printf("\n");
    for ( i=0; i<r; i++ ) {
        for ( j=0; j<c; j++ ) {
            if ( j==3 || j>=6 ) { // 數字靠右
                for ( k=0; k<size[j]-strlen(f[i][j]); k++ ) printf(" "); printf("%s ",f[i][j]);
            } else { // 文字靠左
                printf("%s",f[i][j]); for ( k=0; k<size[j]-strlen(f[i][j])+1; k++ ) printf(" ");
            }
        } printf("\n");
    } printf("\n");
}

int date2int ( char const * date ) {
    char* tmp=(char*)malloc(sizeof(char)*strlen(date));
    int idx=0;
    int p0=0;
    do { if (*(date+p0)!='.') tmp[idx++]=*(date+p0); } while (*(date+(p0++))!='\0');
    tmp[idx]='\0'; idx=atoi(tmp); free(tmp);
    return idx;
}
/*
numbs[0]: date
numbs[1]: pITEM_VAL
numbs[2]: mITEM_VAL
numbs[3]: totalSalary
numbs[4]: totalCURRENT
numbs[5]: 0-minus 1-plus

*/
void numArray ( char** line, int* numbs, int setDefalut ) {
    int i;
    numbs[0] = ( setDefalut ? 0 : date2int(line[0]));
    numbs[1] = ( setDefalut ? 0 : atoi(line[3]));
    for (i=2;i<5;i++) numbs[i] = ( setDefalut ? 0 : atoi(line[i+4]) );
    numbs[5] = ( setDefalut ? 0 : ( !strcmp(line[1],"Salary") || !strcmp(line[1],"Bonus") ? 1 : 0 ));
}
void isort ( char*** file, int const r) {
    int i,j;
    int dateArr[r];
    int numbs[r][6];
    char** tmp;
    dateArr[0] = 0;
    numArray(file[0],numbs[0],1);
    // First intersection sort
    for ( i=1; i<r; i++ ) { dateArr[i]=date2int(file[i][0]); }
    for ( i=2; i<r; i++ ) {
        int key = dateArr[i];
        tmp = file[i];
        for ( j=i-1;j>0 && key<dateArr[j];j--) {
            file[j+1] = file[j];
            dateArr[j+1] = dateArr[j];
        }
        file[j+1] = tmp;
        dateArr[j+1] = key;
    }
    // Then recount amount
    for (i=1; i<r; i++ ) {
        char buffer[10];
        numArray(file[i],numbs[i],0);
        numbs[i][3] = numbs[i-1][3] + ( numbs[i][5]==1 ? numbs[i][1] : 0 );
        numbs[i][4] = numbs[i-1][4] + ( numbs[i][5]==1 ? numbs[i][1] : numbs[i][1] - numbs[i][2] );
        sprintf(buffer,"%d",numbs[i][3]);
        strcpy(file[i][7],buffer);
        sprintf(buffer,"%d",numbs[i][4]);
        strcpy(file[i][8],buffer);
    }
}
