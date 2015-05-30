/* Greedy: First asks the use how much chance is owed 
and then returns the minimum number of coins with which
said change can be made.

ex:
input: 0.41
returns: 4

HarvardX - CS50 Intro to Programming
Hana Um
*/
#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    float f = 0;
    int coins = 0;
    
    do {
        printf("How much change is owed? ");
        f = GetFloat();
    }
    while (f < 0);
    
    int num = round(f*100);
    while (num > 0){
        if (num >= 25){
            num -= 25;
        }
        else if (num >= 10){
            num -= 10;
        }
        else if (num >= 5){
            num -=5;
        }
        else if (num >= 1){
            num -= 1;
        }
        coins++;
    }
    
    printf("%i\n", coins);
}
