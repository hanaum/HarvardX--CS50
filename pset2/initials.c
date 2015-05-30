/* Initializing: Prints out the intials of a string 
name passed in as an input.

ex:
input: Hana Um
returns: HU

HarvardX - CS50 Intro to Programming
Hana Um
*/
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    string n = GetString();
    int i;
    
    printf("%c", toupper(n[0]));
    
    for (i = 0; i < strlen(n); i++) {
        if (n[i] == ' ')
            printf("%c", toupper(n[i + 1]));
    }
    printf("\n");      
}
