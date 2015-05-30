/* Mario: Creates an ascending half-pyramid of hashes (#) with the height of the pyramid 
depending on the user's input.

input: 8
returns: 
       ##
      ###
     ####
    #####
   ######
  #######
 ########
#########

HarvardX - CS50 Intro to Programming
Hana Um
*/

#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int n, i, j;

    do
    {
        printf("Please enter a number between 0 and 23: ");
        n = GetInt();
    }
    while (n < 0 || n > 23);
    
    for (i = 0; i < n; i++)
    {   
        for (j = 0; j < (n - 1 - i); j++)
        {
            printf(" ");
        }
        for (j = 0; j < (i + 2); j++)
        {
            printf("#");
        } 
        printf("\n");    
    }
}   
