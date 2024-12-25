#include <stdio.h>
#include <graphics.h>
#include "2048base.h"
#include <stdlib.h >
/*÷˜≥Ã–Ú£¨≤‚ ‘”√*/
int main()
{
    int b[4][4] = { 4, 0, 0, 0,
        2, 0, 0, 0,
        8, 0, 0, 0,
        2, 0, 0, 0 };
    int *score = new int;
    *score = 0;
    int *x = (int *)b;
    while (1)
    {
        run(x, 4, score);
        system("cls");
        out(x, 4);
    }
    return 0;
}

