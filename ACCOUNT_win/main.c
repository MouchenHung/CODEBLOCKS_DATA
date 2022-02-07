#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
/*Functions Initialized from header*/
#include "usefulTOOL.h"

long int NOLIMIT = 100000000;
typedef char* string;
char TIME[11];
char USER[20];


char date[20];
char pITEM_CLASS[50];
char pITEM_NAME[20];
int pITEM_VAL=0;
char mITEM_CLASS[20];
char mITEM_NAME[20];
int mITEM_VAL=0;

int totalSALARY=0, totalMONEY=0;

int r,c;
struct node{
    char *val1;
    char *val2;
    struct node *next;
};
typedef struct node Node;
Node *cur, *front_node, *rear_node, *tmp_node, *tfree_node; //for version1.


int scanint(const char *const message, int lower_limit, int upper_limit){
    int value;

    printf("%s", message);
    while (scanf("%d", &value)!=1 || value<lower_limit || value>upper_limit)
    {
        int chr;
        printf(SECTION2 WARNING_OUTPUT "--> Non-int or Out-board input!\n"); printf(NOCOLOR);
        do {
            chr = getchar();
        } while ((chr != EOF) && (chr != '\n'));
        printf("%s", message);
    }
    return value;
}

char *string_concat1(string *STR) {
   // 計算所需的陣列長度
   int len=0;

   while(*(STR+len)){
       //printf("%s ", *(STR+len));
       len++;
   }
   int length=20;
   // 產生新的陣列空間
   char *after = NULL;
   after = NULL;
   printf("***%s\n", after);
   after = (char *)malloc(sizeof(char) * length);
   printf("***%s\n", after);
   if(*after){
    free(after);
    printf("in\n");
   }
   printf("--%s\n", after);
   // 串接第二個字串至新的陣列空間
   for(int i=0; i<len; i++){
        strcat(after, *(STR+i));
   }

   return after;
}

char *string_concat2(string *STR) {
   // 計算所需的陣列長度
   int len=0;

   //printf("%s ", *(STR+1));

   while(*(STR+len)){
       printf("%s ", *(STR+len));
       len++;
   }
   int length=1;

   // 產生新的陣列空間
    char *result = (char*)malloc(sizeof(char) * length);
    printf("S---%s\n", result);

   for(int i=0; i<len; i++){
        strcat(result, *(STR+i));
        //printf("%s\n", result);
   }

   return result;
}
/*
void memoryFree_all(){ //free current Node, including [cur], [front_node], [rear_node] by dummy node [tfree_node].
    while(cur){
        tfree_node = cur;
        free(tfree_node);
        cur = cur->next;
        //printf("cur\n");
    }
    while(front_node){
        tfree_node = front_node;
        free(tfree_node);
        front_node = front_node->next;
        //printf("front_node\n");
    }
    while(rear_node){
        tfree_node = rear_node;
        free(tfree_node);
        rear_node = rear_node->next;
        //printf("rear_node\n");
    }
    printf("-->Node Memory has been clean !\n");
}

void AccountEntry(){
    char USER[20];
    char PASSWARD[20];
    char P[]="AA";
    char *p = P;
    char *pUSER = USER;


    char *aaa[100] = {"aa", "bb", "cc", "dd"};
    char *bbb[100] = {"aa1", "bb1", "cc1", "dd1"};
    struct node{
        char *val1;
        char *val2;
        struct node *next;
    };
    typedef struct node Node;
    Node *cur, *front_node, *rear_node, *tmp_node, *tfree_node; //for version1.

    cur=NULL, front_node=NULL, rear_node=NULL, tmp_node=NULL;
    int i=0, ll_size=0;
    while(aaa[i]){
        //printf("%s %s\n", aaa[i], bbb[i]);
        cur=(Node *) malloc(sizeof(Node));
        cur->val1 = aaa[i];
        cur->val2 = bbb[i];
        cur->next = NULL;
        if(rear_node==NULL){
            rear_node = front_node = cur;
        }
        else{
            rear_node->next = cur;
            rear_node = rear_node->next;
        }
        i++;
        ll_size++;
    }
    tmp_node = front_node;
    if(tmp_node){
        printf("-->Your current Linked List: << ");
        while(tmp_node){
            printf("val1=%s ", tmp_node->val1);
            printf("val2=%s ", tmp_node->val2);
            tmp_node = tmp_node->next;
        }
        printf(">> total: %d\n", ll_size);
    }
    else
        printf("-->Your current Linked List: << none >> total: %d\n", ll_size);
    memoryFree_all();
}

void AccountLL(char *aaa[100], char *bbb[100], int *ll_size){
    if(aaa && bbb){
        //printf("%s %s\n", aaa, bbb);
        cur=(Node *) malloc(sizeof(Node));
        cur->val1 = aaa;
        cur->val2 = bbb;
        cur->next = NULL;
        if(rear_node==NULL){
            rear_node = front_node = cur;
        }
        else{
            rear_node->next = cur;
            rear_node = rear_node->next;
        }
        *ll_size++;
    }

}*/

void CreateUserAccount(char *A_file){
    int flag=0;
    printf("|| Create Account ||\n");
    char tmpUSER[20], tmpPASSWORD[20], tmpPASSWORD1[20];
    char *ptr;
    while(strcpy(tmpUSER, "exit")){
        printf(">>Please enter your new [ACCOUNT]: ");
        ptr = PrivatePassword1(20, 1);
        strcpy(tmpUSER, ptr);
        printf(">>Please enter your [PASSWORD]: ");
        ptr = PrivatePassword1(20, 0);
        strcpy(tmpPASSWORD, ptr);
        printf(">>Double check your [PASSWORD]: ");
        ptr = PrivatePassword1(20, 0);
        strcpy(tmpPASSWORD1, ptr);

        if(!strcmp(tmpPASSWORD,tmpPASSWORD1)){
            char *wline = (char *)malloc(sizeof(char) * (strlen(tmpUSER) + strlen(tmpPASSWORD)+1));
            int j, i=0;
            j=0;
            while(tmpUSER[j]){
                wline[i] = tmpUSER[j];
                i++; j++;
            }

            wline[i] = ' ';
            i++;

            j=0;
            while(tmpPASSWORD[j]){
                wline[i] = tmpPASSWORD[j];
                i++; j++;
            }
            wline[i] = '\0';
            printf("----%s\n", wline);
            FILE *fp = fopen(A_file, "a");
            fwrite("\n", sizeof(char), 1, fp);
            fwrite(wline, sizeof(char), strlen(wline), fp);
            fclose(fp);
            flag=1;
            printf(NORMAL_OUTPUT "--> New account has been Created successful!\n\n" NOCOLOR);

            break;
        }
        else{
            printf(WARNING_OUTPUT "--> Password double check failed!\n" NOCOLOR);
        }
    }
    if(!flag)
        printf(WARNING_OUTPUT "--> Account create failed!\n\n" NOCOLOR);
}

char *ShowStandardMoney1(int value){
    int maxsize = 20, buf, fub, flag=0;
    char *output = (char*)malloc(sizeof(char)*maxsize);
    output[0] = "1";
    char *ptr;
    char str[1] = " ", strVAL[20] = " ";

    sprintf(strVAL, "%d", value);
    int i=0, j=0, len=0, totalLEN=strlen(strVAL), v=strlen(strVAL)%3;
    int b_len = totalLEN;
    while(1){
        fub=1;
        sprintf(strVAL, "%d", value);
        if(strlen(strVAL)!=b_len){
            output[i] = '0';
            i++;
            j++;
            len++;
            b_len--;
        }

        for(int i=0; i<strlen(strVAL)-1; i++){
            fub*=10;
        }

        sprintf(str, "%d", value/fub);
        output[i] = str[0];


        len++;
        if(len==totalLEN){
            i++;
            break;
        }
        j++;
        if(j==v && !flag){
            i++;
            output[i] = ',';
            j=0, flag=1;
        }
        else if(j==3 && flag){
            i++;
            output[i] = ',';
            j=0;
        }
        else if(j==3 && v==0){
            i++;
            output[i] = ',';
            j=0;
        }

        value = value % fub;
        i++;
        b_len--;
    }
    output[i] = '\0';


    //printf("--> %s\n", output);
    ptr = output;
    return ptr;
}


char *ShowStandardMoney(int value){
    int maxsize = 20, i=0;
    string buf[5] = {" "};
    char tmp[4] = {" "};
    string tt[5] = {" "};
    char *ptr;
    char *output = (char*)malloc(sizeof(char)*maxsize);
    while((int)value/1000){
        sprintf(tmp, "%d", value%1000);

        output[i] = tmp[0];
        output[i+1] = tmp[1];
        output[i+2] = tmp[2];
        value/=1000;

        if(value>0){
            output[i+3] = ',';
            i+=4;
        }
        else
            i+=3;
    }
    if(value){
        sprintf(tmp, "%d", value);
        int j=0;
        while(tmp[j]){
            output[i] = tmp[j];
            printf("--%d %d\n", j, i);
            j++;
            i+=j;
        }
    }
    printf("%d\n", i);
    output[i-1] = '\0';

    printf("= %s\n", output);
    free(output);
    ptr = buf;
    return ptr;
}

int GetUserAccout(char *A_file){
    int flag=0;
    char *ptr;
    char PASSWORD[20];
    //cur=NULL, front_node=NULL, rear_node=NULL, tmp_node=NULL;
    //char szTest[1000] = {0};
    char *c1[100];
    char *c2[100];

    while(strcmp(USER,"exit")){
        printf(">>Please enter your [ACCOUNT]: ");
        ptr = PrivatePassword1(20, 1);
        strcpy(USER, ptr);

        if(!strcmp(USER,"new")){
            CreateUserAccount(A_file);
            continue;
        }

        printf(">>Please enter your [PASSWORD]: ");
        ptr = PrivatePassword1(20, 0);
        strcpy(PASSWORD, ptr);

        FILE *fp = fopen(A_file, "r");
        if(NULL == fp)
        {
            printf(WARNING_OUTPUT "\n--> Failed to open ACCOUNT FILE\n"); printf(NOCOLOR);
            return flag;
        }



        while(!feof(fp))
        {
            //memset(szTest, 0, sizeof(szTest));
            //fgets(szTest, sizeof(szTest) - 1, fp); // 包含了換行符
            //printf("%s", szTest);
            fscanf(fp, "%s %s\n", c1, c2);
            //printf("%s -- %s\n", c1, c2);
            if( !strcmp(USER,c1) && !strcmp(PASSWORD,c2)){
                printf(NORMAL_OUTPUT "\n--> Account found!\n\n"); printf(NOCOLOR);
                flag=1;
                break;
            }
        }
        fclose(fp);

        if(!flag){
            printf(WARNING_OUTPUT "\n--> Invalid account/password !\n\n"); printf(NOCOLOR);
        }
        else
            break;
    }
    //Change USER word from a->A
    WordCaseChange(USER, 2);
    return flag;
}

void COPY_ACCOUNT(char *ACCOUNT, char *TIME){
    char *_date = (char *)malloc(sizeof(char)* 6);
    _date[0] = TIME[0];
    _date[1] = TIME[1];
    _date[2] = TIME[2];
    _date[3] = TIME[3];
    _date[4] = TIME[5];
    _date[5] = TIME[6];
    _date[6] = '\0';

    char Monthly_RECORD[50] = "";
    strcat(Monthly_RECORD,ACPATH);
    strcat(Monthly_RECORD,USER);
    strcat(Monthly_RECORD,"/history_copy");
    mkdirs(Monthly_RECORD);
    strcat(Monthly_RECORD,"/mCOPY_");
    strcat(Monthly_RECORD,_date);
    strcat(Monthly_RECORD,".txt");
    if(FILE_PROCESS(ACCOUNT, FILE_EXIST)){
        AccountCopy(ACCOUNT, Monthly_RECORD);
        printf(NORMAL_OUTPUT"--> AUTO COPY Completed!\n" NOCOLOR);
    }
    else
        printf(NORMAL_OUTPUT"--> Copy failed, your Account file is empty\n" NOCOLOR);

    free(_date);
}

void *WriteFile(char *A_file, string *STR){
    int len=0;
    while(*(STR+len)){
       //printf("%s ", *(STR+len));
       len++;
    }
    FILE *fp;
    fp = fopen(A_file, "a");
    for(int i=0; i<len; i++){
        fwrite(*(STR+i), 1, strlen(*(STR+i)), fp);
    }

    fclose(fp);
}

void ShowLatestStatus(){
    printf(NORMAL_OUTPUT SECTION2 "--> %s %s %s %d %s %s %d (current status: %d %d)\n", date, pITEM_CLASS, pITEM_NAME, pITEM_VAL, mITEM_CLASS, mITEM_NAME, mITEM_VAL, totalSALARY, totalMONEY); printf(NOCOLOR);
}

void ShowAndReadAllStatus1(char *A_file, int print_flag){
    int diff_y, diff_p;
    float percent_y, percent_p;
        char*** out = fileline(A_file,&r,&c);

        isort(out,r);
        if(print_flag){
            showFile(out,r,c);
            if(COSTLIMIT_POWER){
                Show_CostLimit(out, &r);
            }
            diff_y = IDEAL_YEAR-atoi(out[r-1][8]);
            diff_p = IDEAL_PHASE-atoi(out[r-1][8]);
            percent_y = (float)atoi(out[r-1][8])*100/IDEAL_YEAR;
            percent_p = (float)atoi(out[r-1][8])*100/IDEAL_PHASE;
            //printf("%.1f\n", percent_y);
            printf("--> Your total SALARY : " YELLOW "NTD.%s" NOCOLOR "\n", out[r-1][7]);
            printf("--> Your total ACCOUNT: " YELLOW "NTD.%s" NOCOLOR "\n", out[r-1][8]);

            if(diff_y>0){
                printf("--> Need " YELLOW "NTD.%d" NOCOLOR " to year target %d, approximately " YELLOW "%d" NOCOLOR " month --- " YELLOW "%.1f %" NOCOLOR ".\n", diff_y, IDEAL_YEAR, (int)diff_y/IDEAL_MONTH, percent_y);
            }
            else{
                printf("--> " YELLOW "[ YEARLY SAVING PLAN SUCCESS ]" NOCOLOR "\n");
            }

            if(diff_p>0){
                printf("--> Need " YELLOW "NTD.%d" NOCOLOR " to phase target %d, approximately " YELLOW "%d" NOCOLOR " month --- " YELLOW "%.1f %" NOCOLOR ".\n\n", diff_p, IDEAL_PHASE, (int)diff_p/IDEAL_MONTH, percent_p);
            }
            else{
                printf("--> " YELLOW "[ PHASELY SAVING PLAN SUCCESS ]" NOCOLOR "\n");
            }
        }
        printf("=====================================================================================================================\n");
        //Rebuild the TXT file with sorted data
        RebuildFile(A_file, out, r, c);
        printf("\n\n\n");

        //Give the latest numbers
        pITEM_VAL = atoi(out[r-1][3]);
        mITEM_VAL = atoi(out[r-1][6]);
        totalSALARY = atoi(out[r-1][7]);
        totalMONEY = atoi(out[r-1][8]);


}

void ShowAndReadAllStatus(char *A_file, int print_flag){
    char *c1[20], *c2[20], *c3[20], *c4[20], *c5[20], *c6[20], *c7[20], *c8[20], *c9[20];
    char szTest[1000] = {0};
    string ARRAY[100][100] = {" "};

    FILE *fp = fopen(A_file, "r");
    if(NULL == fp){
        printf(WARNING_OUTPUT "--> Can't open your ACCOUNT FILE named { %s }.\n", A_file); printf(NOCOLOR);
    }

    if(print_flag){
        printf(NORMAL_OUTPUT "--> Current Account Status:\n"); printf(NOCOLOR);
    }

    int i=0;
    int REMAIN, mSalary, cost;
    char asd[30];
    while(!feof(fp))
    {
        //memset(szTest, 0, sizeof(szTest));
        //fgets(szTest, sizeof(szTest) + 1, fp); // 包含了換行符
        //strcpy(asd, fp);
        fscanf(fp, "%s %s %s %s %s %s %s %s %s\n", c1, c2, c3, c4, c5, c6, c7, c8, c9);

        if(!strcmp(c2,"Salary")){
            mSalary = atoi(c4);
            CostLimit(&REMAIN, &mSalary, &cost, 0);
        }
        else if(!strcmp(c2,"Bonus")){
            cost = atoi(c4);
            CostLimit(&REMAIN, &mSalary, &cost, 1);
        }
        else if(!strcmp(c2,"---")){
            cost = atoi(c7);
            CostLimit(&REMAIN, &mSalary, &cost, 2);
        }
        //printf("%s\n", asd);
        //ARRAY[i][0] = c1; ARRAY[i][1] = c2; ARRAY[i][2] = c3; ARRAY[i][3] = c4; ARRAY[i][4] = c5; ARRAY[i][5] = c6; ARRAY[i][6] = c7; ARRAY[i][7] = c8; ARRAY[i][8] = c9;
        if(print_flag){
            //printf("== %s\n", szTest);
            printf(NORMAL_OUTPUT "|%s %s %s %s %s %s %s %s %s\n", c1, c2, c3, c4, c5, c6, c7, c8, c9); printf(NOCOLOR);

        }
        i++;
    }
    fclose(fp);
    CostLimit(&REMAIN, &mSalary, &cost, 3);
    if(print_flag)
        printf("\n");

    pITEM_VAL = atoi(c4);
    mITEM_VAL = atoi(c7);
    totalSALARY = atoi(c8);
    totalMONEY = atoi(c9);
}

void AddTransaction(char *A_file){

    char PITEM_VAL[15], MITEM_VAL[15], TOTALSALARY[15], TOTALMONEY[15];
    char ***out;
    string content[19];
    string *packet;
    int pclass, mclass, int_flag, dMode;
    string pClass[] = {"Salary", "Bonus", "Deposit", "Others"};
    string mClass[] = {"Withdraw", "MonthlyPayment", "Others"};
    //string content[] = {date, " ", pITEM_CLASS, " ", pITEM_NAME, " ", PITEM_VAL, " ", mITEM_CLASS, " ", mITEM_NAME, " ", MITEM_VAL, " ", TOTALSALARY, " ", TOTALMONEY, "\n", NULL};

    int mode, flag=0, str_len=0;

    while(!flag){
        mode = scanint(SECTION1 ">>Enter CALCULATION mode(["COMMENT"0"NOCOLOR"]:quit ["COMMENT"1"NOCOLOR"]:plus ["COMMENT"2"NOCOLOR"]:minus): ", 0, 2);
        switch(mode){
        case 0:
            printf(NORMAL_OUTPUT SECTION1"--> End CALCULATION section !\n\n"); printf(NOCOLOR);
            flag=1;
            break;
        case 1:
            printf(SECTION2 "|| PLUS MODE ||\n");
            dMode = scanint(SECTION2 ">>[date mode] (["COMMENT"0"NOCOLOR"]default ["COMMENT"1"NOCOLOR"]manual): ", 0, 1);
            if(dMode==0){
                //TIME = GetCurentTIME();
                strcpy(date, TIME);
                printf(NORMAL_OUTPUT SECTION2 "--> %s\n", TIME); printf(NOCOLOR);
            }
            else if(dMode==1){
                Message6();
                while(str_len!=10){
                    printf(SECTION2 ">>[date]: ");
                    scanf("%s", date);
                    str_len = strlen(date);
                    if(str_len!=10)
                        printf(WARNING_OUTPUT SECTION2 "--> String length not 10 !\n"); printf(NOCOLOR);
                }
            }

            Message3();
            pclass = scanint(SECTION2 ">>[ITEM CLASS]: ", 0, 3);
            strcpy(pITEM_CLASS, pClass[pclass]);
            printf(SECTION2 ">>[ITEM NAME]: ");
            scanf("%s", pITEM_NAME);
            pITEM_VAL = scanint(SECTION2 ">>[ITEM VALUE]: ", 0, NOLIMIT);

            strcpy(mITEM_CLASS, "---");
            strcpy(mITEM_NAME, "---");
            mITEM_VAL=0;

            if(!strcmp(pITEM_CLASS,"Salary")){
                totalSALARY+=pITEM_VAL;
                totalMONEY+=pITEM_VAL;
            }
            else if(!strcmp(pITEM_CLASS,"Bonus")){
                totalSALARY+=pITEM_VAL;
                totalMONEY+=pITEM_VAL;
            }
            else if(!strcmp(pITEM_CLASS,"Deposit")){
                totalMONEY+=pITEM_VAL;
            }
            else{
                totalMONEY+=pITEM_VAL;
            }
            ShowLatestStatus();
            sprintf(PITEM_VAL, "%d", pITEM_VAL);
            sprintf(MITEM_VAL, "%d", mITEM_VAL);
            sprintf(TOTALSALARY, "%d", totalSALARY);
            sprintf(TOTALMONEY, "%d", totalMONEY);
            content[0] = date;
            content[1] = " ";
            content[2] = pITEM_CLASS;
            content[3] = " ";
            content[4] = pITEM_NAME;
            content[5] = " ";
            content[6] = PITEM_VAL;
            content[7] = " ";
            content[8] = mITEM_CLASS;
            content[9] = " ";
            content[10] = mITEM_NAME;
            content[11] = " ";
            content[12] = MITEM_VAL;
            content[13] = " ";
            content[14] = TOTALSALARY;
            content[15] = " ";
            content[16] = TOTALMONEY;
            content[17] = "\n";
            content[18] = NULL;

            //printf("%s %s %s %s %s %s %s %s %s\n\n", date, pITEM_CLASS, pITEM_NAME, PITEM_VAL, mITEM_CLASS, mITEM_NAME, MITEM_VAL, TOTALSALARY, TOTALMONEY);

            packet = &content;
            WriteFile(A_file, packet);
            out = fileline(A_file,&r,&c);
            isort(out,r);
            //Rebuild the TXT file with sorted data
            printf(SECTION2);
            RebuildFile(A_file, out, r, c);
            printf("\n");
            break;

        case 2:
            printf(SECTION2"|| MINUS MODE ||\n");

            dMode = scanint(SECTION2">>[date mode] (["COMMENT"0"NOCOLOR"]default ["COMMENT"1"NOCOLOR"]manual): ", 0, 1);
            if(dMode==0){
                //TIME = GetCurentTIME();
                strcpy(date, TIME);
                printf(SECTION2 NORMAL_OUTPUT "--> %s\n", TIME); printf(NOCOLOR);
            }
            else if(dMode==1){
                Message6();
                while(str_len!=10){
                    printf(SECTION2">>[date]: ");
                    scanf("%s", date);
                    str_len = strlen(date);
                    if(str_len!=10)
                        printf(SECTION2 WARNING_OUTPUT "--> String length not 10 !\n"); printf(NOCOLOR);
                }
            }

            Message4();
            mclass = scanint(SECTION2">>[ITEM CLASS]: ", 0, 2);
            strcpy(mITEM_CLASS, mClass[mclass]);
            printf(SECTION2">>[ITEM NAME]: ");
            scanf("%s", mITEM_NAME);
            mITEM_VAL = scanint(SECTION2">>[ITEM VALUE]: ", 0, NOLIMIT);

            strcpy(pITEM_CLASS, "---");
            strcpy(pITEM_NAME, "---");
            pITEM_VAL=0;
            if(totalMONEY >= mITEM_VAL){
                if(!strcmp(mITEM_CLASS,"Withdraw")){
                    totalMONEY-=mITEM_VAL;
                }
                else if(!strcmp(mITEM_CLASS,"MonthlyPayment")){
                    totalMONEY-=mITEM_VAL;
                }
                else{
                    totalMONEY-=mITEM_VAL;
                }
            }
            else{
                printf(SECTION1 WARNING_OUTPUT "-->You don't have enough money in your ACCOUNT !\n\n"); printf(NOCOLOR);
                break;
            }

            ShowLatestStatus();
            sprintf(PITEM_VAL, "%d", pITEM_VAL);
            sprintf(MITEM_VAL, "%d", mITEM_VAL);
            sprintf(TOTALSALARY, "%d", totalSALARY);
            sprintf(TOTALMONEY, "%d", totalMONEY);
            content[0] = date;
            content[1] = " ";
            content[2] = pITEM_CLASS;
            content[3] = " ";
            content[4] = pITEM_NAME;
            content[5] = " ";
            content[6] = PITEM_VAL;
            content[7] = " ";
            content[8] = mITEM_CLASS;
            content[9] = " ";
            content[10] = mITEM_NAME;
            content[11] = " ";
            content[12] = MITEM_VAL;
            content[13] = " ";
            content[14] = TOTALSALARY;
            content[15] = " ";
            content[16] = TOTALMONEY;
            content[17] = "\n";
            content[18] = NULL;
            //printf("%s %s %s %s %s %s %s %s %s\n\n", date, pITEM_CLASS, pITEM_NAME, PITEM_VAL, mITEM_CLASS, mITEM_NAME, MITEM_VAL, TOTALSALARY, TOTALMONEY);
            packet = &content;
            WriteFile(A_file, packet);
            out = fileline(A_file,&r,&c);
            isort(out,r);
            //Rebuild the TXT file with sorted data
            printf(SECTION2);
            RebuildFile(A_file, out, r, c);
            printf("\n");
            break;

        default:
            Message2();
            break;
        }
    }
}

int GetAccountHistory(char *A_file){
    int F_flag = FILE_PROCESS(A_file, FILE_EXIST);
    if(!F_flag){
        FILE *fp = fopen(A_file, "w");
        fwrite("[date] [pITEM_CLASS] [pITEM_NAME] [pITEM_VAL] [mITEM_CLASS] [mITEM_NAME] [mITEM_VAL] [totalSALARY] [totalCURRENT]\n", 1, 114, fp);
        fclose(fp);
    }
    else
        ShowAndReadAllStatus1(A_file, 1);
        //ShowAndReadAllStatus(A_file, 0);


    enum Action1{
        QUIT = 0, GETCURR = 1, ADDTRANSACTION = 2
    };

    int flag=0, mode;
    while(!flag){
        mode = scanint(">>Enter FUNCTION mode(["COMMENT"0"NOCOLOR"]:quit ["COMMENT"1"NOCOLOR"]:Show Current Status ["COMMENT"2"NOCOLOR"]:Add Transaction): ", 0, 2);
        switch(mode){
            case QUIT:
                printf(NORMAL_OUTPUT "--> Out of section!\n"); printf(NOCOLOR);
                flag=1;
                return 1;
                break;

            case GETCURR:
                ShowAndReadAllStatus1(A_file, 1);
                break;

            case ADDTRANSACTION:
                AddTransaction(A_file);
                break;

            default:
                Message1();
                break;
        }


    }
    return 0;
}

char *GetCurentTIME(){
    time_t timep;
    struct tm *p;
    time (&timep);
    p=gmtime(&timep);
    int int_y, int_m, int_d;
    char str_y[5];
    char str_m[3];
    char str_d[3];

    int_y = 1900+p->tm_year;
    int_m = 1+p->tm_mon;
    int_d = p->tm_mday;

    sprintf(str_y, "%d", int_y);
    sprintf(str_m, "%d", int_m);
    sprintf(str_d, "%d", int_d);
    //printf("len = %d %d %d\n", strlen(str_y), strlen(str_m), strlen(str_d));
    //printf("%d %d %d\n", int_y, int_m, int_d);
    //printf("--> %s.%s.%s\n\n", str_y, str_m, str_d);

    //printf("%d-",1900+p->tm_year);      /*获取当前年份,从1900开始，所以要加1900*/
    //printf("%d-",1+p->tm_mon);          /*获取当前月份,范围是0-11,所以要加1*/
    //printf("%d ",p->tm_mday);           /*获取当前月份日数,范围是1-31*/
    //printf("%d:",8+p->tm_hour);         /*获取当前时,这里获取西方的时间,刚好相差八个小时*/
    //printf("%d:",p->tm_min);            /*获取当前分*/
    //printf("%d\n",p->tm_sec);           /*获取当前秒*/
    char TIME[11] = {0};
    if(strlen(str_m)!=2){
        snprintf(TIME, sizeof(TIME), "%s.0%s.%s", str_y, str_m, str_d);
    }
    else if(strlen(str_d)!=2){
        snprintf(TIME, sizeof(TIME), "%s.%s.0%s", str_y, str_m, str_d);
    }
    else if(strlen(str_m)!=2 && strlen(str_d)!=2){
        snprintf(TIME, sizeof(TIME), "%s.0%s.0%s", str_y, str_m, str_d);
    }
    else
    {
        snprintf(TIME, sizeof(TIME), "%s.%s.%s", str_y, str_m, str_d);
    }


    //printf("DAY string: %s\n", TIME);
    char *dummy = TIME;
    return dummy;
}

void Message1(){
    printf(COMMENT "\n=============================\n->HELP:\n");
    printf("->cmd[0]: End Section.\n");
    printf("->cmd[1]: Get current account status.\n");
    printf("->cmd[2]: Add new transaction.\n");
    printf("->cmd[OTHERS]: Call HELP.\n=============================\n\n");
    printf(NOCOLOR);
}

void Message2(){
    printf(COMMENT SECTION1"\n=============================\n->HELP:\n");
    printf(SECTION1"->cmd[0]: End Section.\n");
    printf(SECTION1"->cmd[1]: PLUS MODE.\n");
    printf(SECTION1"->cmd[2]: MINUS MODE.\n");
    printf(SECTION1"->cmd[OTHERS]: Call HELP.\n"SECTION1"=============================\n\n");
    printf(NOCOLOR);
}

void Message3(){
    printf(COMMENT SECTION2"~~~~~~~~~~~~~~~~~~~~~\n");
    printf(SECTION2"->cmd[0]: Salary.\n");
    printf(SECTION2"->cmd[1]: Bonus.\n");
    printf(SECTION2"->cmd[2]: Deposit.\n");
    printf(SECTION2"->cmd[3]: Others.\n"SECTION2"~~~~~~~~~~~~~~~~~~~~~\n");
    printf(NOCOLOR);
}

void Message4(){
    printf(COMMENT SECTION2"~~~~~~~~~~~~~~~~~~~~~\n");
    printf(SECTION2"->cmd[0]: Withdraw.\n");
    printf(SECTION2"->cmd[1]: Monthly Payment.\n");
    printf(SECTION2"->cmd[2]: Others.\n"SECTION2"~~~~~~~~~~~~~~~~~~~~~\n");
    printf(NOCOLOR);
}

void Message5(){
    printf(COMMENT SECTION2"~~~~~~~~~~~~~~~~~~~~~\n");
    printf(SECTION2"->cmd[0]: Current Time.\n");
    printf(SECTION2"->cmd[1]: Manual Time.\n"SECTION2"~~~~~~~~~~~~~~~~~~~~~\n");
    printf(NOCOLOR);
}

void Message6(){
    printf(COMMENT SECTION2"~~~~~~~~~~~~~~~~~~~~~\n");
    printf(SECTION2"->format ex: 2020.08.08\n"SECTION2"~~~~~~~~~~~~~~~~~~~~~\n");
    printf(NOCOLOR);
}

int FILE_PROCESS(char *filename, int mode){
   return (access(filename, mode) == 0);
}


int main()
{
    char *pp;
    pp = ShowStandardMoney1(12345678);
    printf("%s\n", pp);
    pp = ShowStandardMoney1(1234);
    printf("%s\n", pp);
    int flag=1;
    char ACCOUNT_FILE[50] = ACCOUNT_LIST;
    printf("-----| WELCOME TO ACCOUNT APP |-----\n");
    flag = GetUserAccout(ACCOUNT_FILE);

    if(flag==1){
        char *_time;
        _time = GetCurentTIME();
        strcpy(TIME, _time);
        printf("----- Hi [%s] , your log in DAY: %s -----\n", USER, TIME);

        int len = strlen(USER)+strlen(".txt")+1;
        char TRANSACTION_FILE[len];
        memset(TRANSACTION_FILE, '\0', len);
        strcat(TRANSACTION_FILE,USER);
        strcat(TRANSACTION_FILE,".txt");

        int comb_size = strlen(ACPATH)+strlen(USER)+strlen(TRANSACTION_FILE)+1;
        int i=0, j;
        char *Total_RECORD = (char *)malloc(sizeof(char)* comb_size);
        j=0;
        while(ACPATH[j]){
            Total_RECORD[i] = ACPATH[j];
            i++;
            j++;
        }
        j=0;
        while(USER[j]){
            Total_RECORD[i] = USER[j];
            i++;
            j++;
        }
        mkdirs(Total_RECORD);
        Total_RECORD[i] = '/';
        i++;
        j=0;
        while(TRANSACTION_FILE[j]){
            Total_RECORD[i] = TRANSACTION_FILE[j];
            i++;
            j++;
        }
        Total_RECORD[i] = '\0';




        if(GetAccountHistory(Total_RECORD) && AUTO_COPY){
            //Copy every access to this APP
            COPY_ACCOUNT(Total_RECORD, TIME);
        }
        free(Total_RECORD);
    }

    return 0;
}
