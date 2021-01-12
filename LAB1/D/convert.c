#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<fcntl.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/types.h>

int main(int argc,char **argv)
{
    char x;
    int count = 0;
    while(read(0,&x,1)>0)
    {
        // converting lower to upper and upper to lower.
        if(islower(x))
        {
           x = toupper(x);
        }
        else
        {
            x = tolower(x);
        }

        write(1,&x,1); // writing into Pipe.
    }

   close(0);
  close(1);

    exit(0);

}
