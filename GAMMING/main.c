#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <termios.h>
#include <sys/time.h>
/* Standard file descriptors.  */
#define	STDIN_FILENO	0	/* Standard input.  */
#define	STDOUT_FILENO	1	/* Standard output.  */
#define	STDERR_FILENO	2	/* Standard error output.  */

int action = 0;

void Display(int x, int y){
    for (int i=0; i<20; i++){
        for (int j=0; j<20; j++){
            if (i==0 || i==19)
                printf("= ");
            else{
                if (j==0 || j==19)
                    printf("| ");
                else if (i==x && j==y)
                    printf("* ");
                else
                    printf("  ");
                usleep(100);
            }
        }
        printf("\n");
    }
    printf("\n");
}

void KeyboardListen( void ){
    static int game_pos = 10;
    int game_x = 20, game_y = 15, c;
    char C = ' ';
    static struct termios oldTermios, newTermios;

    tcgetattr(STDIN_FILENO, &oldTermios);
    newTermios = oldTermios;

    cfmakeraw(&newTermios);

    tcsetattr(STDIN_FILENO, TCSANOW, &newTermios);
    C = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldTermios);
    switch (C) {
        case 27: // esc
            //printf("--> out\n");
            exit(0);
            break;
        case 87: // i
            //printf("--> up\n");
            action = 1;
            break;
        case 83: // i
            //printf("--> up\n");
            action = 2;
            break;
        case 65: // a
            //printf("--> left\n");
            action = 3;
            //PLAYGROUND(action, &game_pos, game_x, game_y);
            break;
        case 68: // d
            //printf("--> right\n");
            action = 4;
            //PLAYGROUND(action, &game_pos, game_x, game_y);
            break;

        case -1: //non type
            action = 0;
            //PLAYGROUND(action, &game_pos, game_x, game_y);
            break;

        default:
            printf("--> No such action!\n");
            break;

    }
}

void *ActionListen(void *arg){
    //printf("start listening to user action...\n");
    while(1){
        KeyboardListen();
    }
}

int main()
{
    int X=15,Y=15;
    pthread_t tid;
	pthread_attr_t attr;

    pthread_create(&tid, NULL,ActionListen,NULL);

    printf("Game start!\n\n");
    while(1){
        if (action){
            if (action == 1){
                Y+=1;
            }
            else if (action == 2){
                Y-=1;
            }
            else if (action == 3){
                X-=1;
            }
            else if (action == 4){
                X+=1;
            }
        }
        Display(X,Y);
        printf("\n");
        sleep(2);
        //exit(0);
    }

    return 0;
}
