#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib.c"

int main() {
    int r,c;
    char*** out = fileline("mouchen.txt",&r,&c);
    showFile(out,r,c);
    Show_CostLimit(out, &r);
    
    isort(out,r);
    showFile(out,r,c);
    Show_CostLimit(out, &r);

    printf("%s\n", out[r-1][3]);
	return 0;
}
