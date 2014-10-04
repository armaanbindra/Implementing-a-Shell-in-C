/* Shell Project in C(Extra Feautures) - ARMAAN BINDRA 10/10/2013 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include <ctype.h>
#include <sys/wait.h>
#include <time.h>

#define MAXTOKS 100
#define BUFFER_CAP 500
#define MAXTOKSIZE 45

//Struct for taking in the tokens and using them to parse in the shell commands



struct Token_String
{
    char** tok;
    int count;
    int status;
};


//an enum to refer to the specific status of the input

enum status_value { NORMAL, EOF_FOUND, INPUT_OVERFLOW ,OVERSIZE_TOKEN};


//the most important function that reads in the tokens
int read_name(struct Token_String *x,char * hist)
{
    char buffer[BUFFER_CAP];
    char * result;
    printf("armaan-shell running user:%s$ ",getenv("USER"));
    result = fgets(buffer,BUFFER_CAP, stdin);
    //strcat(hist,"\n");
    strcat(hist,buffer);
    x->tok = (char**) malloc(MAXTOKS);
    int i=0;int n;int j;j =0;
    while (buffer[j]!='\0') {
        x->tok[i] = (char*) malloc(MAXTOKSIZE+1);
        n = 0;
        while(!isspace(buffer[j]))
        {
            x->tok[i][n]=buffer[j];
            n++;
            j++;
        }
        x->tok[i][n]= '\0';
        
        ////////////////////
        if(i>=MAXTOKS){x->status = INPUT_OVERFLOW;break;}
        if(n>MAXTOKSIZE){x->status = OVERSIZE_TOKEN;break;}
        //printf("The first word is %s\n",x->tok[0]);
        else if (result != NULL)
        {
            x->status = NORMAL ;//printf("%s ",x->tok[i]);
        }
        //printf("You Entered the Text:%s\n",buffer);
        else {
            x->status = EOF_FOUND;
        }
        i++;
        int ws;
        while(isspace(buffer[j]))
        {
            ws++;
            j++;
        }
        // printf("j is %d\n",j);
    }
    x->count=i;
    //if(x->status == NORMAL){return 1;} else {return 0;}
    //hist_count++;
}
//a function that makes it convenient and easy to run some common commands without the user having to 
int checkCmd(char* arg1)
{
    int n;
    n=9;
  const char ** cmdList[n];
  cmdList[0] = "ls";
  cmdList[1] = "mkdir";
  cmdList[2] = "rm";
  cmdList[3] = "pwd";
  cmdList[4] = "cat";
  cmdList[5] = "make";
  cmdList[6] = "mv";
  cmdList[7] = "cp";
  cmdList[8] = "ssh";
  int i;int temInt;
  temInt=0;
  for(i=0;i<n;i++)
  {
      temInt=strncmp(arg1,cmdList[i],20);
      if(temInt==0){return 1;}
    }
  return 0;
}

// the main function that executes runs the command for a shell one time through
int shellInterface(char **environment,char* hist)
{
    int fd;
    struct Token_String parserObj;
    read_name(&parserObj,hist);
    int m;int last;
    int checkExit;char temp[40];strcpy(temp,"/bin/");
    checkExit = strncmp(parserObj.tok[0],"quit",10);
    int checkCD = strncmp(parserObj.tok[0],"cd",10);
    int checkClr = strncmp(parserObj.tok[0],"wipe",10);
    int checkHist = strncmp(parserObj.tok[0],"history",10);
    int myName = strncmp(parserObj.tok[0],"armaan",15);
    
    int checkCommand;
    checkCommand = checkCmd(parserObj.tok[0]);
    if(checkExit==0 ||checkExit==-32){_exit(1);}
    else if(checkCD==0 ||checkCD==-32){chdir(parserObj.tok[1]);}
    else if(checkClr==0 ||checkClr==-32){parserObj.tok[0]="/bin/clear";}
    else if(checkHist==0 ||checkHist==-32){printf(hist);}
    //printf("\n Lets try this checkCmd returns %d",checkCmd(parserObj.tok[0]));
    else if(checkCommand==1){strcat(temp,parserObj.tok[0]);parserObj.tok[0]=temp;}
    else if(myName ==0 || myName ==-32){printf("\nThis Shell was implemented by Armaan Bindra\nA Computer Science Major at St. Olaf College\n\n");}
    if (parserObj.status == OVERSIZE_TOKEN){printf("\nError: Token is Oversize\n");}
    if(parserObj.status == EOF_FOUND)
    {printf("Error: End of File was encountered before any before and characters could be read\n");}
    else if (parserObj.status == INPUT_OVERFLOW){printf("The Input Buffer was filled before a newline was encountered\n");}
    
    else {}
    parserObj.tok[parserObj.count]=0;
    int ret;  /* for return value from fork() */
    
    //printf("I am the PARENT.  My pid is %d\n", getpid());
    
    if ((ret = fork()) < 0) {
        printf("fork() FAILED");
        perror("echoline");
        _exit(1);
    }
    /* fork() succeeded */
    
    if (ret != 0) {
        //printf("I am the PARENT.  My pid is %d, and fork() returned %d.\n",getpid(), ret);
        wait(&ret);
        //printf("\nWaited For the Child Process!!\n");
        /* NOTE: parent should ordinarily wait(), to collect child's exit status */
    } else {
        //printf("I am the CHILD.  My pid is %d, and fork() returned %d.\n\n",getpid(), ret);
        //printf("\nparserObj.tok[0] is %s\n",parserObj.tok[0]);
        execve(parserObj.tok[0],parserObj.tok,environment);
        _exit(1);
    }
}

int main(int argc, char **argv, char **envp)
{
    char * hist;
    hist = (char*) malloc(1000);
    int i=0;
    while(i==0)
    {
        shellInterface(envp,hist);
        //printf(hist);
	}
    
}
