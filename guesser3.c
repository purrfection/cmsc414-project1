/* guesser.c */

#include <stdio.h>    /* for printf() */
#include <stdlib.h>   /* for EXIT_SUCCESS */

int your_fcn()
{
    printf("You won!\n");
    exit(EXIT_SUCCESS);
    return 0;
}

int main()
{
    int mine = 0;
    int yours = 0;

    yours = your_fcn();
    mine = yours + 1;

    if(mine > yours)
        printf("You lost!\n");
    else
        printf("You won!\n");

    return EXIT_SUCCESS;
}
