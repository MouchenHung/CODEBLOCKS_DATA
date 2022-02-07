#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>     //STDIN_FILENO
/*
int main()
{
    char btn[2];
    while(1)
     {

         printf("Type: ");
         gets(btn);
         printf(">> %c\n", btn[0]);

     }


    return 0;
}*/

int main(){
    while(1)
        keyboard();
}

void keyboard(void){
    int c = 0;
    char C;
    static struct termios oldTermios, newTermios;

    tcgetattr(STDIN_FILENO, &oldTermios);
    newTermios = oldTermios;

    cfmakeraw(&newTermios);

    tcsetattr(STDIN_FILENO, TCSANOW, &newTermios);
    C = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldTermios);

    switch (C) {
        case 27: // esc
            printf("\n\n");
            exit(0);
            break;
        case 105: // i
            printf("insert\n");
            break;
        default:
            printf("%c --> %d\n",C, C);
            break;

    }
}
