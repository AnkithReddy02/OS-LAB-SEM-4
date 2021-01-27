#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h> 
#include<sys/stat.h> 
#include<string.h>
#include<limits.h>
#include<signal.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<dirent.h>

void handler(int signum)
{
    printf("\n");
    return;
}
int countPipes(char *s)
{
    char *str = s;
        
    char *token;
    
    int count = 0;
    
    
    while(token = strtok_r(str,"|",&str))
    {
        count++;
    }
    return count - 1;
    
    
}
void pipeCommands(char *s,int numPipes)
{
    int status = 0;
    
    int i = 0,j=0;
    
    int pipefds[2*numPipes];
    
    pid_t pid;
    
    
    for(i=0;i< numPipes ;i++)
    {
        if(pipe(pipefds+i*2)<0)
        {
            fprintf(stderr,"\nPipe creation failure\n");
            exit(1);
        }
    }
    
    char *str = s;
        
    char *token;
    
    int count = 0;
    
    // printf("str : %s\n",str);
    
    while(token = strtok_r(str,"|",&str))
    {
        //fprintf(stderr,"%s\n",token);
        
        if(token[0]==' ')
        {
            int i=0;
            
            for(int i=0;token[i]!='\0';i++)
            {
                token[i] = token[i+1];
            }
        }
        char *program[100000];
        
        char *progToken = token;
        
        int len = 0;
        
        while(progToken = strtok_r(token," ",&token))
        {
            program[len] = progToken;
            
            len++;
        }
        program[len] = "\0";
        
        //--------------------------------------------------
        // pipes
        //printf("%d\n",numPipes);
        
        pid = fork();
        
        if(pid==0)
        {
            if(j/2!=numPipes)
            {
                if(dup2(pipefds[j + 1], 1) < 0)
                {
                    perror("\ndup2 error\n");
                    exit(1);
                }
            }
            if(j!=0)
            {
                if(dup2(pipefds[j-2], 0) < 0)
                {
                    perror("\ndup2 error\n");
                    exit(1);

                }
            }
            
            for(i = 0; i < 2*numPipes; i++)
            {
                close(pipefds[i]);
            }
            
            //fprintf(stderr,"%s\n",program[0]);
            
            int flag = execvp(program[0],program);
            
            if(flag < 0)
            {
                fprintf(stderr,"execvp error");
                exit(1);
            }
        }
        else if(pid < 0)
        {
            fprintf(stderr,"\nFork error..exiting..\n");
            exit(1);
        }
        
        j = j + 2;
        
        
        
        
    
        
    }
    
    
    
    for(i = 0; i < 2*numPipes ; i++)
    {
        close(pipefds[i]);
    }
    
    //printf("%d\n",j);

    for(i = 0;i <numPipes + 1;i++)
     {
          wait(&status);
     }
    
    
    
    
}
int main()
{
    signal(SIGINT, handler);  // Register signal and signal handler
    
    // exit,ls,pwd,cd ,mkdir,sleep
    char s[100000];
    
    
    
    while(1)
    {
        char cwd[PATH_MAX];
                
        if (getcwd(cwd, sizeof(cwd)) != NULL)
        {
            printf("%s : ", cwd);
        }
                
        scanf("%[^\n]%*c",s);
        
        char x[100000];
        
        int i = 0;
        
        while(s[i]!='\0')
        {
            x[i] = s[i];
            i++;
        }
        x[i] = '\0';
        
        int numPipes = countPipes(s);
        
        if(numPipes)
        {
            pipeCommands(x,numPipes);
            continue;
        }
        
        char *str = s;
        
        char *token;
        
        while(token = strtok_r(str," ",&str))
        {
            
            if(strcmp(token,"exit")==0)
            {
                exit(0);
            }
            else if(strcmp(token,"ls")==0)
            {
                struct dirent *de;  
  
                DIR *dr = opendir("."); 
              
                if (dr == NULL)  
                { 
                    printf("\nCould not open current directory\n" ); 
                    return 0; 
                } 
              
                while ((de = readdir(dr)) != NULL) 
                {
                    printf("%s\n", de->d_name); 
                }
              
                closedir(dr);     
            }
            else if(strcmp(token,"pwd")==0)
            {
                char cwd[PATH_MAX];
                
                if (getcwd(cwd, sizeof(cwd)) != NULL)
                {
                   printf("%s\n", cwd);
                }
            }
            else if(strcmp(token,"echo")==0)
            {
                
                int count = 0; // 2 if string end.("")

                while(token = strtok_r(str," ",&str))
                {
                   
                    for(int i=0;token[i]!='\0';i++)
                    {
                        if(token[i]=='"')
                        {
                            count++;
                            if(count==2)
                            {
                                break;
                            }
                        }
                        else
                        {
                            printf("%c",token[i]);
                        }
                    }
                    if(count==2)
                    {
                        break;
                    }
                    printf(" ");
                }
                printf("\n");
                
            }
            else if(strcmp(token,"mkdir")==0)
            {
                token = strtok_r(str," ",&str);
                 
                if (mkdir(token, 0777) == -1) 
                {
                    fprintf(stderr,"\nUnable to create directory/directory already present\n");
                } 
            }
            else if(strcmp(token,"sleep")==0)
            {
                int flag = 0;
                token = strtok_r(str," ",&str);
                
                for(int i=0;token[i]!='\0';i++)
                {
                    if(token[strlen(token)-1]==';')
                    {
                        break;
                    }
                    if(!(token[i]>='0'&&token[i]<='9'))
                    {
                        fprintf(stderr,"\nsleep: invalid time interval '%s'\n",token);
                        flag = 1;
                        break;
                    }
                }
                
                if(!flag)
                {
                    int x = atoi(token);
                
                    sleep(x);
                }
                
                
            }
            else if(strcmp(token,"cd")==0)
            {
                token = strtok_r(str," ",&str);
                
                if(chdir(token)==-1)
                {
                    fprintf(stderr,"\nUnable to change the directory\n");
                }
                
            }
            else if(strcmp(token,"cat")==0)
            {
                token = strtok_r(str," ",&str);
                
                int fileRead = 0;
                
                if((token[0]=='<')||token[0]!='>')
                {
                    
                    if(token[0]=='<'&&token[1]!='\0')
                    {
                        for(int i=0;i<strlen(token);i++)
                        {
                            token[i] = token[i+1];
                        }
                        
                    }
                    else if(token[0]=='<'&&token[1]=='\0')
                    {
                        token = strtok_r(str," ",&str);
                    }
                    
                    fileRead = open(token,O_RDONLY);
                    
                    if(fileRead<0)
                    {
                        fprintf(stderr,"\ninput file not found/Unable to open file\n");
                        break;
                    }
                    
                    
                    
                }
                
                if(token[0]!='>')
                token = strtok_r(str," ",&str);
                
                int fileWrite = 1;
                
                
                if(token &&token[0]=='>')
                {
                    if(token[0]=='>'&&token[1]!='\0')
                    {
                        for(int i=0;i<strlen(token);i++)
                        {
                            token[i] = token[i+1];
                        }
                    }
                    else if(token[0]=='>'&&token[1]=='\0')
                    {
                        token = strtok_r(str," ",&str);
                    }
                    fileWrite = open(token,O_WRONLY | O_CREAT | O_TRUNC);
                    
                    if(fileWrite==-1)
                    {
                        fprintf(stderr,"\nUnable to create/write to file\n");
                        break;
                    }
                   
                    
                    
                }
                 char x;
                while(read(fileRead,&x,1))
                {
                   write(fileWrite,&x,1) ;
                }
                
                printf("\n");
                
                
            }
            else if(strcmp(token,"source")==0)
            {
                token = strtok_r(str," ",&str);
                
                int fileRead = open(token,O_RDONLY);
                
                if(fileRead<0)
                {
                    fprintf(stderr,"\nUnable to open file\n");
                    break;
                }
                
                char t[100000]; // storin gin string;
                
                int len  = 0;
                
                char x;
                
                while(read(fileRead,&x,1))
                {
                    
                    if(x=='\n')
                    {
                        t[len] = ' ';
                        t[len+1] = ';';
                        t[len+2] = ' ';
                        len += 2;
                    }
                    else
                    {
                        t[len] = x;
                    }
                    
                  
                    
                    len++;
                }
                t[len] = '\0';
                
                str = t; // reassigning str to t; 
                
            }
            // programm with arguments;
            else if(strcmp(token,";")!=0)
            {
                struct stat status;
                if(stat(token,&status) != 0)
                {
                    fprintf(stderr,"\nfile is not present..\n");
                    break;
                }
                
                char *args[100000];
                
                
                int len = 0;
                
                args[0] = token;
                
                while(token= strtok_r(str," ",&str))
                {
                    args[len] = token;
                    
                    len++;
                }
                int background = 0;
                
                if((args[len-1],"&")==0)
                {
                    args[len-1] = "\0";
                    background = 1;
                }
                pid_t flag=0;
                
                if((flag = fork())!=-1)
                {
                    // parent.
                    if(flag)
                    {
                        // waiting for child to complete as process is not backgorund.
                      if(background==0)
                      {
                          int status;
                           
                          while(waitpid(flag, NULL, 0)>0);
                      }
                     
                          background = 0;
                          // again for printing prompt;
                          break;
                      
                    }
                    // child.
                    else
                    {
                        int x = execvp(args[0],args);
                        //printf("%d\n",x);
                        fprintf(stderr,"\nError in running the program\n");
                    }
                }
                // fork error.
                else
                {
                    fprintf(stderr,"\nFork error\n");
                }
                
            }
        }
    }
    
}


