#include <stdio.h>
#include <stdlib.h>

enum{
    a,
    b = 0x12,
    c,
    d = 0xFF,
    e,
    f,
    g = 0xce
};

void TEF(int *var){
    printf("hello --> %d\n", *var);
}

typedef struct{
    int *a1;
    int a2;
    int *a3;
    void *TEF;
}TE;

int main()
{
    printf("-----TEST1. ENUM-----\n");
    printf("enum 'a'=%d, 'b'=%d, 'c'=%d, 'd'=%d, 'e'=%d, 'f'=%d, 'g'=%d\n", a,b,c,d,e,f,g);

    int aa = 0x0045;
    printf("-->%x\n", ~aa);
    aa &= ~aa;
    printf("-->%x", aa);

    printf("-----TEST2. POINTER-----\n");
    int tmp1, tmp2 = 5;
    int tmp3[3] = {0};
    TE structTE;

    structTE.a1 = &tmp1;
    structTE.TEF = TEF;

    *structTE.a1 = tmp2;
    structTE.a3 = tmp3;

    structTE.a3[1] = 40;

    printf("-->a1=%d\n-->a2=%d\n-->a3=%d\n-->tmp1=%d\n-->TMP3=%d\n", *structTE.a1, structTE.a2, structTE.a3[0], tmp1, tmp3[1]);

    return 0;
}
