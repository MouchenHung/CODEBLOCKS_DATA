#include <stdio.h>
#include <stdlib.h>

int main()
{
    printf("Hello world!\n");
    return 0;
}


void AddCreditTransaction(){
    int mode, flag=0;

    while(!flag){
        printf(SECTION2"|| CREDIT CARD MODE ||\n");

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
    }
}
