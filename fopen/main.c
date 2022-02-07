#include <stdio.h>
#include <stdlib.h>

int main(){
    FILE *pFile;

    char data[]={ '6','1','1', '1' };
    char recv[10];
    //char data[10] = {1,2,1,1};


    while(1)
    {
        /* write file */

        pFile = fopen( "write.txt","w" );
        if( NULL == pFile ){
            printf( "WRITE ERR: open failure" );
            return 1;
        }else{
            fwrite(data,1,sizeof(data),pFile);
            printf("write success\n");
        }
        fclose(pFile);

        sleep(1);


        /* read file */
        pFile = fopen( "write.txt","r" );
        if( NULL == pFile ){
            printf( "READ ERR: open failure" );
            return 1;
        }
        else{
            fread(recv, sizeof(recv), 1, pFile);
            printf("read success\n");
        }
        fclose(pFile);

        printf("--> data [0]: %c\n", recv[0]);
        printf("--> data [1]: %c\n", recv[1]);
        data[0]+=1;
        sleep(2);
        return 1;
    }
    return 0;
}
