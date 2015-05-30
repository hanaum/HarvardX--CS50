/* Vigenere Cipher: ecrypts messages using a sequence of keys.
if p is some plaintext and k is a keyword 
(i.e., an alphbetical string, whereby A and a represent 0, while Z and z represent 25), 
then each letter, c_i, in the ciphertext, c, is computed as:

c_i = (p_i + k_j) % 26

ex:
input: Meet me at the park at eleven am
returns: Negh zf av huf pcfx bt gzrwep oz

HarvardX - CS50 Intro to Programming
Hana Um
*/

#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    if (argc == 2){
        string inputWord = argv[1];
        
        for (int i = 0, n = strlen(inputWord); i < n; i++) {
            if (!isalpha(inputWord[i])) {
                printf("Only input letters please!");
                return 1;
            }
        }
        string text = GetString();
        int n = strlen(text);
        int c = 0;
        
        for (int index = 0; index < n; index++) {
            if (isalpha(text[index])) {  
                if (isupper(text[index])) {
                    printf("%c", (text[index] - 'A' + toupper(inputWord[c % strlen(inputWord)]) - 'A') % 26 + 'A'); 
                }  
                else if (islower(text[index])) {
                    printf("%c", (text[index] - 'a' + tolower(inputWord[c % strlen(inputWord)]) - 'a') % 26 + 'a'); 
                }
                c++;
            }
            else {
                printf("%c", text[index]); 
            }
        }
        printf("\n");
        return 0;
    }
    else{
        printf("Please enter a string of letters!");
        return 1;
    }  
}
