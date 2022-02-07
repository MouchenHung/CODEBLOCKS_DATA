#ifndef USEFULTOOL_H_INCLUDED
#define USEFULTOOL_H_INCLUDED

#define ENABLE 1
#define DISABLE 0

/*Function Gate*/
//[PRIVATE] - key to open each project's functions in need from usefulTOOL.h
#define PRIVATE_KEY ACCOUNT

//[PUBLIC] - USER and PASSWORD function
#define USERPASSWORD_POWER ENABLE

//[PUBLIC] - monthly save money function
#define COSTLIMIT_POWER ENABLE

//[PUBLIC] - variable color sets of print
#define COLOR_POWER ENABLE
    #define OS_COLOR 1 //0: DisableFunction 1: LINUX, 2:WINDOWS

//[PUBLIC] - file access function
#define FILEACCESS_POWER ENABLE

//[PUBLIC] - TERMIOS function
#define TERMIOS_POWER ENABLE

//[PUBLIC] - Add space with section diff
#define SECTIONSPACE_POWER ENABLE

//[PUBLIC] - Word Case Switch function
#define WORDCASE_POWER ENABLE

//[PUBLIC] - Show standard money format function
#define ShowMoneyStandardFormat_POWER ENABLE

//[PUBLIC] - String with no space
#define StrNoSpace_POWER ENABLE

/*=================================================================================================================================================*/
/*{PUBLIC FUNCTION SECTION}*/
/*=================================================================================================================================================*/

/*[PUBLIC FUNCTION] PRINT COLOR
  [description] Linux: switch ENABLE freely, Window: set Enable only download ANSI first, type the command down below
                "reg add HKEY_CURRENT_USER\Console /v VirtualTerminalLevel /t REG_DWORD /d 0x00000001 /f" */
#if COLOR_POWER
    #define NOCOLOR "\033[m"
    #define RED "\033[0;32;31m"
    #define LIGHT_RED "\033[1;31m"
    #define GREEN "\033[0;32;32m"
    #define LIGHT_GREEN "\033[1;32m"
    #define BLUE "\033[0;32;34m"
    #define LIGHT_BLUE "\033[1;34m"
    #define DARY_GRAY "\033[1;30m"
    #define CYAN "\033[0;36m"
    #define LIGHT_CYAN "\033[1;36m"
    #define PURPLE "\033[0;35m"
    #define LIGHT_PURPLE "\033[1;35m"
    #define BROWN "\033[0;33m"
    #define YELLOW "\033[1;33m"
    #define LIGHT_GRAY "\033[0;37m"
    #define WHITE "\033[1;37m"
//Customize your Linux print COLOR here
    #define SYSTEM NOCOLOR
    #define COMMENT LIGHT_BLUE
    #define NORMAL_OUTPUT GREEN
    #define WARNING_OUTPUT RED

#else
    #define NOCOLOR ""
    #define RED ""
    #define LIGHT_RED ""
    #define GREEN ""
    #define LIGHT_GREEN ""
    #define BLUE ""
    #define LIGHT_BLUE ""
    #define DARY_GRAY ""
    #define CYAN ""
    #define LIGHT_CYAN ""
    #define PURPLE ""
    #define LIGHT_PURPLE ""
    #define BROWN ""
    #define YELLOW ""
    #define LIGHT_GRAY ""
    #define WHITE ""
//Customize your Linux print COLOR here
    #define SYSTEM NOCOLOR
    #define COMMENT LIGHT_BLUE
    #define NORMAL_OUTPUT GREEN
    #define WARNING_OUTPUT RED

#endif // COLOR_POWER

/*[PUBLIC FUNCTION] FILE ACCESS
  [description] Function ACCESS from io.h*/
#if FILEACCESS_POWER
    #define FILE_EXIST 0
    #define FILE_EXECUTE 1
    #define FILE_WRITE 2
    #define FILE_READ 4
    void mkdirs(char *);
#endif // FILEACCESS_POWER

/*[PUBLIC FUNCTION] TERMIOS
  [description] get char in LINUX*/
#if TERMIOS_POWER
    //static struct termios old, current;
    void initTermios(int );
    void resetTermios(void );
    char getch_(int );
    char getch();
    char getche();
#endif // TERMIOS_POWER

/*[PUBLIC FUNCTION] USER&PASSWORD
  [description] user and password platform*/
#if USERPASSWORD_POWER
    char *PrivatePassword1(int limitLEN, int mode);
#endif // USERPASSWORD_POWER

/*[PUBLIC FUNCTION] section space
  [description] print with space diff*/
#if SECTIONSPACE_POWER
    #define SECTION0 ""
    #define SECTION1 "     "
    #define SECTION2 "          "
#endif // SECTIONSPACE_POWER

/*[PUBLIC FUNCTION] Word Case function
  [description] A->a && a->A*/
#if WORDCASE_POWER
    void WordCaseChange( char* , int );
#endif // WORDCASE_POWER

/*[PUBLIC FUNCTION] Show Money Standard Format
  [description] 1234 --> 1,234*/
#if ShowMoneyStandardFormat_POWER
    char *SSM(int );
    char *sSSM(char* );
#endif // ShowMoneyStandardFormat_POWER

/*[PUBLIC FUNCTION] String with no space
  [description] */
#if StrNoSpace_POWER
    char* StrNoSpace(char *);
#endif // StrNoSpace_POWER


/*=================================================================================================================================================*/
/*{PRIVATE FUNCTION SECTION}*/
/*=================================================================================================================================================*/

/*[PRIVATE FUNCTION] PRINT COLOR*/
#if PRIVATE_KEY == ACCOUNT
    #define ACPATH "./USER_ACCOUNT/"
    #define ACCOUNT_LIST "account_list.txt"
    #define CONFIG_LIST "config_list.txt"
    #define EXPENSE_LIST "expense_list.txt"
    #define TRANSACTION_LIST ".txt"

    #define AUTO_COPY ENABLE
    /*FROM lib.c*/
    char**** fileline( char* , int* , int* );
    void showFile ( char*** , int const , int const );
    void Show_CostLimit(char*** , int* , int );
    void isort ( char*** file, int const r);
    void RebuildFile(char*, char***, int const , int const );
    int AccountCopy(char* , char* );
    void CreateUserAccount(char *);

#endif // PRIVATE_KEY


#endif // USEFULTOOL_H_INCLUDED
