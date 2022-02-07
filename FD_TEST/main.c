#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <assert.h>



int ReadKeyboard()
{
    int keyboard;
    int ret, i;
    char c;
    fd_set readfd;
    struct timeval timeout;
    keyboard = open("/dev/tty", O_RDONLY | O_NONBLOCK);
    assert(keyboard > 0);
    while (1)
    {
        timeout.tv_sec = 5;
        timeout.tv_usec = 0;
        FD_ZERO(&readfd);
        FD_SET(keyboard, &readfd);
        ret = select(keyboard + 1, &readfd, NULL, NULL, &timeout);

        //select error when ret = -1
        if (ret == -1)
            perror("select error");

        //data coming when ret>0
        else if (ret)
        {
            if (FD_ISSET(keyboard, &readfd))
            {
                i = read(keyboard, &c, 1);
                if ('/n' == c)
                    continue;
                printf("Keyboard input is %c/n", c);

                if ('q' == c)
                    break;
            }
        }
        //time out when ret = 0
        else if (ret == 0)
            printf("time out/n");
    }
}

/*
int isready(int fd)
{
     int rc;
     fd_set fds;
     struct timeval tv;

     FD_ZERO(&fds);
     FD_SET(fd,&fds);
     FD_SET(fd+1,&fds);

     tv.tv_sec = tv.tv_usec = 0;

     rc = select(fd, &fds, NULL, NULL, &tv);

     if (rc < 0)   //error
        return -1;

     return FD_ISSET(fd,&fds) ? 1 : 0;

}*/

int main()
{
    printf("Hello world!\n");

    fd_set fdset;
    //printf("isREADY? %d\n", isready(4));

    ReadKeyboard();
    return 0;
}
