#include <stdio.h>
#include <stdlib.h>

int main()
{
    int status;
    printf("Hello world!\n");
    status = system("ls /home/mouchen/Documents");
    printf("status return: %d\n", status);

    FILE * fp;
    if ((fp = popen("ls /home", "r")) == NULL)
    {
        perror("open failed!");
        return -1;
    }
    return 0;
}
