#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/*Functions Initialized from header*/
#include "usefulTOOL.h"

typedef char* string;

int IDEAL_MONTH;
int IDEAL_YEAR;
int IDEAL_PHASE;
string Config_Name[20] = {"IDEAL_MONTH", "IDEAL_YEAR", "IDEAL_PHASE", NULL};
string Config_Data[3];


long int NOLIMIT = 100000000;

char TIME[11];
char date[20];
char USER[20];

char pITEM_CLASS[50];
char pITEM_NAME[20];
int pITEM_VAL=0;
char mITEM_CLASS[20];
char mITEM_NAME[20];
int mITEM_VAL=0;

int totalSALARY=0, totalMONEY=0;

char CONFIG_FILE[50] = CONFIG_LIST;

int new_FLAG=0;

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
        printf(SECTION2 WARNING_OUTPUT "--> Non-int or Out-board input!\n" NOCOLOR);
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
            new_FLAG=1;
            continue;
        }

        printf(">>Please enter your [PASSWORD]: ");
        ptr = PrivatePassword1(20, 0);
        strcpy(PASSWORD, ptr);

        FILE *fp = fopen(A_file, "r");
        if(NULL == fp)
        {
            printf(WARNING_OUTPUT "\n--> Failed to open [account_list.txt] FILE\n"); printf(NOCOLOR);
            return flag;
        }



        while(!feof(fp))
        {
            fscanf(fp, "%s %s\n", c1, c2);
            //printf("%s -- %s\n", c1, c2);
            if( !strcmp(USER,c1) && !strcmp(PASSWORD,c2)){
                printf(NORMAL_OUTPUT "--> Account found!\n\n"); printf(NOCOLOR);
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

void WriteFileSingle(char *A_file, char *STR, int mode_flag){
    FILE *fp;
    fp = (mode_flag==0) ? fopen(A_file, "w") : fopen(A_file, "a");
    fwrite(STR, sizeof(char), strlen(STR), fp);
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
            Show_CostLimit(out, &r, IDEAL_MONTH);
        }
        diff_y = IDEAL_YEAR-atoi(out[r-1][8]);
        diff_p = IDEAL_PHASE-atoi(out[r-1][8]);
        percent_y = (float)atoi(out[r-1][8])*100/IDEAL_YEAR;
        percent_p = (float)atoi(out[r-1][8])*100/IDEAL_PHASE;

        printf("--> Your total SALARY : " YELLOW "NTD.%s" NOCOLOR "\n", sSSM(out[r-1][7]));
        printf("--> Your total ACCOUNT: " YELLOW "NTD.%s" NOCOLOR "\n", sSSM(out[r-1][8]));

        if(diff_y>0){
            printf("--> Need " YELLOW "NTD.%s" NOCOLOR " to year target " COMMENT "NTD.%s" NOCOLOR ", approximately " YELLOW "%d" NOCOLOR " month --- " YELLOW "%.1f%" NOCOLOR ".\n", SSM(diff_y), SSM(IDEAL_YEAR), (int)diff_y/IDEAL_MONTH, percent_y);
        }
        else{
            printf("--> " YELLOW "[ YEARLY SAVING PLAN SUCCESS ]" NOCOLOR "\n");
        }

        if(diff_p>0){
            printf("--> Need " YELLOW "NTD.%s" NOCOLOR " to phase target " COMMENT "NTD.%s" NOCOLOR ", approximately " YELLOW "%d" NOCOLOR " month --- " YELLOW "%.1f%" NOCOLOR ".\n\n", SSM(diff_p), SSM(IDEAL_PHASE), (int)diff_p/IDEAL_MONTH, percent_p);
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

    int mode, flag=0, str_len;

    while(!flag){
        mode = scanint(SECTION1 ">>Enter CALCULATION mode(["COMMENT"0"NOCOLOR"]:quit ["COMMENT"1"NOCOLOR"]:plus ["COMMENT"2"NOCOLOR"]:minus): ", 0, 2);
        str_len=0;
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
            //strcpy(pITEM_NAME, StrNoSpace(pITEM_NAME));
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
                        printf(SECTION2 WARNING_OUTPUT "--> String length not 10 !\n"NOCOLOR);
                }
            }

            Message4();
            mclass = scanint(SECTION2">>[ITEM CLASS]: ", 0, 2);
            strcpy(mITEM_CLASS, mClass[mclass]);
            printf(SECTION2">>[ITEM NAME]: ");
            scanf("%s", mITEM_NAME);
            //strcpy(mITEM_NAME, StrNoSpace(mITEM_NAME));
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



void ReadFile(char *A_file, int print_flag){
    int i=0;
    string ARR_VER[20]={}, ARR_VAL[20]={};

    FILE *fp = fopen(A_file, "r");
    if(NULL == fp)
    {
        printf(WARNING_OUTPUT "\n--> Failed to open [config_list.txt] FILE\n"); printf(NOCOLOR);
    }

    while(!feof(fp)){
        char *tmpC1 = (char *)malloc(sizeof(char)*20);
        char *tmpC2 = (char *)malloc(sizeof(char)*20);
        fscanf(fp, "%s %s\n", tmpC1, tmpC2);
        if(print_flag)
            printf(SECTION2 NORMAL_OUTPUT "%s" NOCOLOR " --> %s\n", tmpC1, tmpC2);

        if(!strcmp(tmpC1, "IDEAL_MONTH")){
            ARR_VER[i] = tmpC1;
            ARR_VAL[i] = tmpC2;
            IDEAL_MONTH = atoi(tmpC2);
            i++;
        }
        else if(!strcmp(tmpC1, "IDEAL_YEAR")){
            ARR_VER[i] = tmpC1;
            ARR_VAL[i] = tmpC2;
            IDEAL_YEAR = atoi(tmpC2);
            i++;
        }
        else if(!strcmp(tmpC1, "IDEAL_PHASE")){
            ARR_VER[i] = tmpC1;
            ARR_VAL[i] = tmpC2;
            IDEAL_PHASE = atoi(tmpC2);
            i++;
        }
        else{
            printf(WARNING_OUTPUT "--> No such config variable named [%s]\n", tmpC1); printf(NOCOLOR);
        }

    }
    fclose(fp);
    ARR_VER[i]=NULL; ARR_VAL[i]=NULL;
    //printf("%s -- %s\n", ARR_VER[0], ARR_VAL[0]);
    //printf("%s -- %s\n", ARR_VER[1], ARR_VAL[1]);
    while(ARR_VER[i]!=NULL && ARR_VAL[i]!=NULL){
        free(ARR_VER[i]);
        free(ARR_VAL[i]);
    }

}

void WriteConfigFile(char *A_file){
    int flag, i=0;
    char sIDEAL_YEAR[20], sIDEAL_PHASE[20], sIDEAL_MONTH[20];

    sprintf(sIDEAL_MONTH, "%d", IDEAL_MONTH);
    sprintf(sIDEAL_YEAR, "%d", IDEAL_YEAR);
    sprintf(sIDEAL_PHASE, "%d", IDEAL_PHASE);
    Config_Data[0] = sIDEAL_MONTH;
    Config_Data[1] = sIDEAL_YEAR;
    Config_Data[2] = sIDEAL_PHASE;
    flag=0;
    while(Config_Name[i]!=NULL){
        WriteFileSingle(A_file, Config_Name[i], flag);
        WriteFileSingle(A_file, " ", 1);
        WriteFileSingle(A_file, Config_Data[i], 1);
        WriteFileSingle(A_file, "\n", 1);
        flag=1;
        i++;
    }
    printf(SECTION2 NORMAL_OUTPUT "--> Variable saved!\n\n" NOCOLOR);
}

void GetSetConfiguration(char *A_file, int GS_flag){
    int i;

    printf(SECTION2 "|| CONFIG SETTING MODE ||\n");

    if(GS_flag==2){
        int flag=0;
        i=0;
        while(Config_Name[i]){
            WriteFileSingle(A_file, Config_Name[i], flag);
            WriteFileSingle(A_file, " ", 1);
            WriteFileSingle(A_file, "1000", 1);
            WriteFileSingle(A_file, "\n", 1);
            flag=1;
            i++;
        }

    }

    //show current CONFIG file status
    ReadFile(A_file, GS_flag);

    //Setting Mode if GS_flag=1
    if(GS_flag){
        i=0;
        int tmp_val;
        char VER[20], str[20], tmp_DATA[20];

        //Save new updated data to TXT file
        FILE *fp = fopen(A_file, "w");

        while(1){
            printf(SECTION2 ">> Enter a variable([exit] to exit): ");
            scanf("%s", VER);

            if(!strcmp(VER, "exit")){
                fclose(fp);
                printf(SECTION2 NORMAL_OUTPUT "--> Out of section!\n\n"); printf(NOCOLOR);

                break;
            }
            else if(!strcmp(VER, Config_Name[0])){
                printf(SECTION2 ">> Enter a value: ");
                scanf("%d", &tmp_val);
                IDEAL_MONTH = tmp_val;

                //write new settings to CONFIG file
                WriteConfigFile(A_file);
                //show current CONFIG file status
                ReadFile(A_file, 1);

            }

            else if(!strcmp(VER, Config_Name[1])){
                printf(SECTION2 ">> Enter a value: ");
                scanf("%d", &tmp_val);
                IDEAL_YEAR = tmp_val;

                //write new settings to CONFIG file
                WriteConfigFile(A_file);
                //show current CONFIG file status
                ReadFile(A_file, 1);

            }
            else if(!strcmp(VER, Config_Name[2])){
                printf(SECTION2 ">> Enter a value: ");
                scanf("%d", &tmp_val);
                IDEAL_PHASE = tmp_val;

                //write new settings to CONFIG file
                WriteConfigFile(A_file);
                //show current CONFIG file status
                ReadFile(A_file, 1);
            }
            else{
                printf(SECTION2 WARNING_OUTPUT "--> No such config variable named %s\n", VER);printf(NOCOLOR);
            }

        }

    }

}

int GetAccountHistory(char *TOTAL_RECORD_FILE, char *CONFIG_FILE){
    int F_flag = FILE_PROCESS(TOTAL_RECORD_FILE, FILE_EXIST);
    if(!F_flag){
        FILE *fp = fopen(TOTAL_RECORD_FILE, "w");
        fwrite("[date] [pITEM_CLASS] [pITEM_NAME] [pITEM_VAL] [mITEM_CLASS] [mITEM_NAME] [mITEM_VAL] [totalSALARY] [totalCURRENT]\n", 1, 114, fp);
        fclose(fp);
    }
    else
        ShowAndReadAllStatus1(TOTAL_RECORD_FILE, 1);

    enum Action1{
        QUIT = 0, GETCURR = 1, ADDTRANSACTION = 2, SETCONFIG = 3
    };

    int flag=0, mode;
    while(!flag){
        mode = scanint(">>Enter FUNCTION mode(["COMMENT"0"NOCOLOR"]:quit ["COMMENT"1"NOCOLOR"]:Show Current Status ["COMMENT"2"NOCOLOR"]:Add Transaction ["COMMENT"3"NOCOLOR"]:Set Config Variables): ", 0, 2);
        switch(mode){
            case QUIT:
                printf(NORMAL_OUTPUT "--> Out of section!\n"); printf(NOCOLOR);
                flag=1;
                return 1;
                break;

            case GETCURR:
                ShowAndReadAllStatus1(TOTAL_RECORD_FILE, 1);
                break;

            case ADDTRANSACTION:
                AddTransaction(TOTAL_RECORD_FILE);
                break;

            case SETCONFIG:
                GetSetConfiguration(CONFIG_FILE, 1);
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
        int c_len = strlen(USER)+strlen("_config.txt")+1;

        char TRANSACTION_FILE[len], config_file[c_len];
        memset(TRANSACTION_FILE, '\0', len);
        memset(config_file, '\0', c_len);

        strcat(TRANSACTION_FILE,USER);
        strcat(TRANSACTION_FILE,".txt");

        strcat(config_file,USER);
        strcat(config_file,"_config.txt");

        int comb_size = strlen(ACPATH)+strlen(USER)+strlen(TRANSACTION_FILE)+1;
        int c_comb_size = strlen(ACPATH)+strlen(USER)+strlen(config_file)+1;
        int i=0, j;
        char *TOTAL_RECORD_FILE = (char *)malloc(sizeof(char)* comb_size);
        char *CONFIG_FILE = (char *)malloc(sizeof(char)* c_comb_size);
        j=0;
        while(ACPATH[j]){
            TOTAL_RECORD_FILE[i] = ACPATH[j];
            CONFIG_FILE[i] = ACPATH[j];
            i++;
            j++;
        }
        j=0;
        while(USER[j]){
            TOTAL_RECORD_FILE[i] = USER[j];
            CONFIG_FILE[i] = USER[j];
            i++;
            j++;
        }
        mkdirs(TOTAL_RECORD_FILE);

        TOTAL_RECORD_FILE[i] = '/';
        CONFIG_FILE[i] = '/';
        i++;

        int tmp_i_1=i;
        j=0;
        while(TRANSACTION_FILE[j]){
            TOTAL_RECORD_FILE[tmp_i_1] = TRANSACTION_FILE[j];
            tmp_i_1++;
            j++;
        }
        TOTAL_RECORD_FILE[tmp_i_1] = '\0';

        int tmp_i_2=i;
        j=0;
        while(config_file[j]){
            CONFIG_FILE[tmp_i_2] = config_file[j];
            tmp_i_2++;
            j++;
        }
        CONFIG_FILE[tmp_i_2] = '\0';



        if(new_FLAG){
            printf(NORMAL_OUTPUT "--> It's your first time log in , please sets your own CONFIG variables!\n\n" NOCOLOR);
            GetSetConfiguration(CONFIG_FILE, 2);
        }
        else{
            ReadFile(CONFIG_FILE, 0);
        }

        if(GetAccountHistory(TOTAL_RECORD_FILE, CONFIG_FILE) && AUTO_COPY){
            //Copy every access to this APP
            COPY_ACCOUNT(TOTAL_RECORD_FILE, TIME);
        }
        free(TOTAL_RECORD_FILE);
    }

    return 0;
}
