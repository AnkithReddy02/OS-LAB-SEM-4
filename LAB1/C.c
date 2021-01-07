#include<stdio.h> // for input/output.
#include<ctype.h> // islower(x),tolower(x),toupper(x) -> included in 'ctype.h';
#include<stdlib.h> // -> for exiting from program.

void main()
{
    char s;
    char x[100000];

    int len = 0; // length of the string entered until EOF.

    printf("Enter a string(until you press(if your last char is newline then only one time else double times(ctrl+D) : ");
    printf("\n");


    while((s=getchar())!=EOF) // read unitl EOF.
    {
        if(islower(s)) // return true is s is in lower case.
        {
            s  =  toupper(s); // returns uppercase of s;
        }
        else
        {
            s  =  tolower(s); // returns lowercase of s; non-alpha doesnot effect the use of tolower(x) function.
        }
        x[len++] = s;
    }

    printf("\nText/String after changing uppercase to lowercase and vice versa : \n");
    for(int i=0;i<len;i++)
    {

        printf("%c",x[i]);
        if(i==len-1)
        {
            printf("\n");
        }
    }



    exit(0);


}
