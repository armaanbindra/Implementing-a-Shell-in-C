 /* Shell Project in C(Basic Assignment) - ARMAAN BINDRA 10/10/2013 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include <ctype.h>
#include <sys/wait.h>

#define MAXTOKS 100
#define BUFFER_CAP 500
#define MAXTOKSIZE 15

//Struct for taking in the tokens and using them to parse in the shell commands
struct name
  {
    char** tok;
    int count;
    int status;
  };
//an enum to refer to the specific status of the input
enum status_value { NORMAL, EOF_FOUND, INPUT_OVERFLOW ,OVERSIZE_TOKEN};

//the most important function that reads in the tokens
int read_name(struct name *x)
{
  char buffer[BUFFER_CAP];
  char * result;
  printf("armaan-shell running$ ");
  result = fgets(buffer,BUFFER_CAP, stdin);
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
}

// the main function that executes runs the command for a shell one time through
int shellInterface(char **environment)
{

  struct name parserObj;
  read_name(&parserObj);
    int m;int last;
    int checkExit;
    checkExit = strncmp(parserObj.tok[0],"quit",10);
    //printf("it is %d",checkExit);
    if(checkExit==0 ||checkExit==-32){_exit(1);}
    //printf("\nThere are a total of %d tokens.\n",parserObj.count);
  for(m =0;m<parserObj.count;m++)
    {
      //printf("%s\n",parserObj.tok[m]);
    }
    
  if (parserObj.status == OVERSIZE_TOKEN){printf("\nError: Token is Oversize\n");}
  if(parserObj.status == EOF_FOUND)
    {printf("Error: End of File was encountered before any before and characters could be read\n");}
  else if (parserObj.status == INPUT_OVERFLOW){printf("The Input BUffer was filled before a newline was encountered\n");}
  
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
        execve(parserObj.tok[0],parserObj.tok,environment);
        _exit(1);
    }
}

int main(int argc, char **argv, char **envp)
{
  int i=0;
  while(i==0)
    {
      shellInterface(envp);
    }
}
