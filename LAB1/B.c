#include<stdio.h> // standard input output
#include<ctype.h> // for using isalpha(although not necessary to use).
#include<stdlib.h> // used to exit (in this program) program.

void main(int argc, char const *argv[])
{
        char s;

        int count = 0; // count -> character not in range of 'a' - 'z' and 'A' - 'Z';
        
        printf("Keep on  entering characters until you pressed(ctrl + D doubletimes at end -> EOF) : \n");



        while((s=getchar())!=EOF)
        {
            if(!((s>='a'&&s<='z')||(s>='A'&&s<='B'))) // condition for checking alphabet or not.
            {
                count++; // if they are not alphabet , then increment count;
            }

            /*

            // isalpha(x) returns 1 if x is uppercase character ,
            // returns 2 if x is lowercase , returns 0 if x is not alphabet
            // this method also can be done.

            if(isalpha(s)==0)
            {
                count++;
            }

            */
        }

        fprintf(stderr,"\nNumber of non alpha characters : %d\n",count); // printing on to stderr

        exit(0);
}
