#include <stdio.h>
#include <stdlib.h>

#define history 5

typedef unsigned char  INT8U;

static int ambientTempOffsetTbl_S5X[] = {
	 1, 2, 3, 4, 5,
	 6, 7, 8, 9, 10
};
static int*	ambientTempOffsetTbl = ambientTempOffsetTbl_S5X;

int main(void)
{
    FILE *fPtr;
    char s[4];
    char *buf = NULL;
    int retVAL, tmp;

    fPtr = fopen("atest.txt", "r");
    if (!fPtr) {
        printf("fail open...\n");
        exit(1);
    }
    fseek(fPtr, 0, SEEK_END);
    int size = ftell(fPtr);
    printf("%d\n", size);

    buf = malloc(size);

    fseek(fPtr, 0, SEEK_SET);
    fread(buf, sizeof(char), size, fPtr);


    fseek(fPtr, 0, SEEK_SET);
    retVAL = fscanf(fPtr, "%s", s);
    printf("[fscanf test1] %s (%d)\n", s, retVAL);
    fseek(fPtr, 2, SEEK_SET);
    retVAL = fscanf(fPtr, "%s", s);
    printf("[fscanf test2] %s (%d)\n", s, retVAL);
    fseek(fPtr, 0, SEEK_SET);
    retVAL = fscanf(fPtr, "%d%s", s);
    printf("[fscanf test3] %s (%d)\n", s, retVAL);
    fseek(fPtr, -1, SEEK_END);
    retVAL = fscanf(fPtr, "%s", s);
    printf("[fscanf test4] %s (%d)\n", s, retVAL);
    if (retVAL==EOF)
    {
        printf("error occur\n");
    }

    fclose(fPtr);

    printf("1. %s\n", buf);

    #ifdef history
    printf("2. history defined\n");
    #endif

    #if (history > 10)
    printf("--> greater than 10\n");
    #elif (history < 2)
    printf("--> less than 2\n");
    #else
    printf("--> between 2 and 10\n");

    #endif // history


    printf("\nTEST2. COVERITY 39127\n");
    int offsetQty = ( sizeof(ambientTempOffsetTbl)/sizeof(ambientTempOffsetTbl[0]) );
    int a = sizeof(ambientTempOffsetTbl);
    int b = sizeof(ambientTempOffsetTbl[0]);
    printf("result1 --> %d %d %d %d\n", offsetQty, a, b, sizeof(int));
    printf("result2 --> %d\n", sizeof(ambientTempOffsetTbl_S5X)/sizeof(ambientTempOffsetTbl_S5X[0]));


    INT8U VV = 0XFF;
    printf("\nTEST3. READING VALUE\n--> %x %d\n", VV, VV);


    printf("\nTEST4. \n");
    int EvtData2 = 0x16;
    int EvtData3 = 0x16;
    int MC_DBG_LST[15];
	memset(MC_DBG_LST, 0, sizeof(MC_DBG_LST));

    int bit_count=0;
	for (int i=0; i<15; i++)
	{

		if (i<8)
		{
		    printf("%d | %d\n", i, bit_count);
			if (EvtData2 & (1 << bit_count))
            {
                MC_DBG_LST[i] = 1;
            }
            bit_count+=1;
            if (i == 7)
                bit_count = 0;
		}
		else
		{
		    printf("%d | %d\n", i, bit_count);
			if (EvtData3 & (1 << bit_count))
            {
                MC_DBG_LST[i] = 1;
            }
            bit_count+=1;
		}
	}
	printf("%d\n", MC_DBG_LST[0]);

	int i=0;
	while (i!=15)
    {
        printf("--> %d\n", MC_DBG_LST[i]);
        i+=1;
    }


    return 0;
}
