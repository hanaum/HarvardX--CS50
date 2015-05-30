/* Caesar Cipher: encrypts messages by rotating each letter by "k" positions, 
wrapping around from Z to A as needed.

ex:
input: Be sure to drink your Ovaltine!
returns: Or fher gb qevax lbhe Binygvar!

HarvardX - CS50 Intro to Programming
Hana Um
*/

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    if (argc != 2){
        printf("Input 1 integer in Terminal!\n");
        return 1;
    } 
    int k;
    k = atoi(argv[1]);
    string m = GetString();
    
    for (int i = 0, n = strlen(m); i < n; i++) {
        if (isalpha(m[i])) {
            if (isupper(m[i]))
                printf("%c", (((m[i] - 'A') + k) % 26) + 'A');
            else if (islower(m[i]))
                printf("%c", (((m[i] - 'a') + k) % 26) + 'a');
        }
        else 
            printf("%c", m[i]);
    }
    printf("\n"); 
}
