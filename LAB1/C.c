#include<stdio.h> // for input/output.
#include<ctype.h> // islower(x),tolower(x),toupper(x) -> included in 'ctype.h';
#include<string.h> // for string operations.
#include<stdlib.h> // -> for exiting from program.

void main()
{
    char s[100000];
    
    printf("Enter a string : ");
    
    scanf("%[^\n]%*c",s);  // gets(s); -> another way to input string with spaces.
    

    for(int i=0;i<strlen(s);i++)
    {
        if(islower(s[i])) // return true is s[i] is in lower case.
        {
            s[i]  =  toupper(s[i]); // returns uppercase of s[i];
        }
        else
        {
            s[i]  =  tolower(s[i]); // returns lowercase of s[i]; non-alpha doesnot effect the use of tolower(x) function. 
        }
    }
    
    printf("String after reversing lowercase and uppercase letters : %s\n",s);
    
    exit(0);
    
    
}
