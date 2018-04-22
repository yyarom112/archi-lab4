#include "lab4_util.h"

#define SYS_WRITE 1
#define STDOUT 1
#define SYS_READ 0
#define SYS_OPEN 2
#define SYS_CLOSE 3
#define SYS_LSEEK 8
#define SYS_EXIT 60

extern int system_call();
int strlen_private(char* s);

int main (int argc , char* argv[], char* envp[])
{
  if(argc<3)
	system_call(SYS_EXIT,0x55);
  char * file=argv[1];
  char* toChange=argv[2];
  int fileDescriptor,num, counter;
  if(strlen_private(toChange)>5)
	return 0x55;
  fileDescriptor=system_call(SYS_OPEN,file,2,0777);
  system_call(SYS_LSEEK,fileDescriptor,0x1015,0);
  num=system_call(SYS_WRITE,fileDescriptor,toChange,strlen_private(toChange));
  if(num>5 ||num!=strlen_private(toChange) )
	return 0x55;
  counter=5-strlen_private(toChange);
  while(counter>0){
	  num=system_call(SYS_WRITE,fileDescriptor,"",1);
	  counter--;
  	if(num!=1)
		return 0x55;
}

  system_call(SYS_CLOSE,fileDescriptor);
  return 0;
}

int strlen_private(char* s){
    int length = 0;
    while(s[length]!='\0')
    {
        length++;
    }
 return length;
}
