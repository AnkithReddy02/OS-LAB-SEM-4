#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<fcntl.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/types.h>

int main(int argc,int **argv)
{
    char x;
    int count = 0;
    while(read(0,&x,1)>0)
    {
          // fprintf(stderr,"%c\n",x);
        write(1,&x,1); // writing into output file.
        if(!isalpha(x))
        {
            count++;
        }
    }

    close(0);
    close(1);

    fprintf(stderr,"Number of non-alpha characters : %d\n",count);

    exit(0);

}
