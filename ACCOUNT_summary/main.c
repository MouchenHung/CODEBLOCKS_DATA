#include <stdio.h>
#include <stdlib.h>
#include "./usefulTOOL.h"

#define ENABLE 1
#define DISABLE 0
#define COSTLIMIT_POWER DISABLE
#define REBUILD_POWER DISABLE

#define IDEAL_MONTH 40000
#define IDEAL_YEAR 500000
#define IDEAL_PHASE 1000000

void ShowTOTAL(char *A_file0, char *A_file1){
    int r,c, diff_y, diff_p;
    int isSalaryACCOUNT=1;
    float percent_y, percent_p;
    int totalSalary = 0, totalMoney = 0;
    int totalARRY[10] = {0};
    char*** out;
    out = fileline(A_file0,&r,&c);
    totalSalary = atoi(out[r-1][7]);
    totalARRY[0] = atoi(out[r-1][8]);

    out = fileline(A_file1,&r,&c);
    totalARRY[1] = atoi(out[r-1][8]);

    printf(GREEN "----------| CURRENT TOTAL ACCOUNT ANALYSIS|----------\n" NOCOLOR);
    int i=0;
    while(totalARRY[i]){
        totalMoney+=totalARRY[i];
        i++;
    }

    diff_y = IDEAL_YEAR-totalMoney;
    diff_p = IDEAL_PHASE-totalMoney;
    percent_y = (float)totalMoney*100/IDEAL_YEAR;
    percent_p = (float)totalMoney*100/IDEAL_PHASE;

    if(isSalaryACCOUNT)
        printf("--> Your total SALARY : " YELLOW "NTD.%s" NOCOLOR "\n", SSM(totalSalary));
    printf("--> Your total ACCOUNT: " YELLOW "NTD.%s" NOCOLOR "\n", SSM(totalMoney));

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

void ShowAndReadAllStatus1(char *A_file, int isSalaryACCOUNT, int print_flag){
    int r, c;
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

        if(isSalaryACCOUNT)
            printf("--> Your total SALARY : " YELLOW "NTD.%s" NOCOLOR "\n", sSSM(out[r-1][7]));
        printf("--> Your total ACCOUNT: " YELLOW "NTD.%s" NOCOLOR "\n", sSSM(out[r-1][8]));
        /*
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
        }*/
    }
    printf("=====================================================================================================================\n");
    //Rebuild the TXT file with sorted data
    if(REBUILD_POWER)
        RebuildFile(A_file, out, r, c);
    printf("\n\n\n");

}

int main()
{
    char CTBC_path[100] = "/home/mouchen/Documents/CODEBLOCKS_data/ACCOUNT/bin/Debug/USER_ACCOUNT/MOUCHEN/MOUCHEN.txt";
    char DAWHO_path[100] = "/home/mouchen/Documents/CODEBLOCKS_data/ACCOUNT/bin/Debug/USER_ACCOUNT/MCDAWHO/MCDAWHO.txt";
    char*** out1;
    char*** out2;

    printf(BLUE "----------{ CTBC BANK }----------\n" NOCOLOR);
    printf(GREEN "--> Description: SALARY ACCOUNT\n" NOCOLOR);
    ShowAndReadAllStatus1(CTBC_path, 1, ENABLE);
    printf(BLUE "----------{ DAWHO BANK }----------\n" NOCOLOR);
    printf(GREEN "--> Description: SETTLEMENT ACCOUNT(SP STOCK)\n" NOCOLOR);
    ShowAndReadAllStatus1(DAWHO_path, 0, ENABLE);

    ShowTOTAL(CTBC_path, DAWHO_path);
    printf("\n");
    return 0;
}
