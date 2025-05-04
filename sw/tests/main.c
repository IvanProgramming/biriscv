#include <stdint.h>
#include <stdio.h>

/* прототипы трёх ASM-тестов -----------------------------------------*/
extern int addi(void);
extern int sub (void);
extern int and (void); 
extern int simple (void);
extern int or  (void);

void runTest(int (test)(void), char name[])
{
    printf("TEST %s...", name);
    int result = test();
    if (result != 0)
    {
        printf("ERR: %d\n", result);
    }
    else 
    {
        printf("OK\n");
    }
}

/* main ---------------------------------------------------------------*/
int main(void)
{
    printf("Tests\n");

    runTest(simple, "simple");
    runTest(or, "or");
    runTest(addi, "addi");
    runTest(and, "and");
    runTest(sub, "sub");

    return 0;
}
