#include "lab4_util.h"

#define SYS_WRITE 1
#define STDOUT 1

extern int system_call();

int main (int argc , char* argv[], char* envp[])
{
  char * str="hello world!";
  if(system_call(SYS_WRITE,STDOUT,str,simple_strlen(str))!=simple_strlen(str)){
	str="there was am error writing.";
	system_call(SYS_WRITE,STDOUT,str,simple_strlen(str));	
  }
  	system_call(SYS_WRITE,STDOUT,"\n",sizeof("\n"));
  return 0;
}
