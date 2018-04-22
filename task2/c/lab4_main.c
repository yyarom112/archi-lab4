#include "lab4_util.h"
#include <sys/types.h>



#define SYS_WRITE 1
#define STDOUT 1
#define SYS_OPEN 2
#define SYS_READ 0
#define SYS_LSEAK 8
#define SYS_CLOSE 3
#define SYS_GETDENTS 78
#define SYS_EXIT 60

#define BUF_SIZE 1024


extern int system_call();
void string_path_ready (char* a, char* b,char* output);
void search_for_all (char* path);
int strlen_private(char* s);
void search_for_all_file_in_exactly_name (char* path,char* name);
void Active_on_files (char* path,char* file_name,char* command, int* flag);
void string_coomand_ready (char* a, char* b,char* output);

struct linux_dirent {
    long d_ino;
    off_t d_off;
    unsigned short d_reclen;
    char d_name[];
};


int main(int argc, char *argv[]) {
int i;
char* file_name;
char* command;
int flag=0;
if(argc==1)
	    search_for_all(".");
else{
  for(i=1; i<argc; i++){
    if(simple_strcmp(argv[i],"-n")==0){
	if(argc<3){
		system_call(SYS_WRITE,2,"expted 3 arguments but got less.",strlen_private("expted 3 arguments but got 				less."));
		system_call(SYS_WRITE,2,"\n",1);
		system_call(SYS_EXIT,0x55);
		}
	file_name=argv[++i];
	search_for_all_file_in_exactly_name(".",file_name);
	}
    else{
	 if(simple_strcmp(argv[i],"-e")==0){
		if(argc<4){
			system_call(SYS_WRITE,STDOUT,"expted 3 arguments but got less.",strlen_private("expted 3 arguments but got less."));
			system_call(SYS_WRITE,STDOUT,"\n",1);
			system_call(SYS_EXIT,0x55);
		}
		file_name=argv[++i];
		command=argv[++i];
		Active_on_files(".",file_name,command,&flag);
		if(flag==0){
			system_call(SYS_WRITE,STDOUT,"NotExistingFile",strlen_private("NotExistingFile"));
			system_call(SYS_WRITE,STDOUT,"\n",1);
		}
		}
	}
  }
}
    return 0;
}

void string_path_ready (char* a, char* b,char* output){
    int i=0,j=0;
    for(;i<simple_strlen(a);i++)
        output[i]=a[i];
    output[i]='/';
    i++;
    for(;j<simple_strlen(b);j++){
        output[i]=b[j];
	i++;
	}
    output[i]='\0';
}

void string_coomand_ready (char* a, char* b,char* output){
    int i=0,j=0;
    for(;i<simple_strlen(a);i++)
        output[i]=a[i];
    output[i]=' ';
    i++;
    for(;j<simple_strlen(b);j++){
        output[i]=b[j];
	i++;
	}
    output[i]='\0';
}

void search_for_all (char* path){
    int fd, nread;
    char buf[BUF_SIZE];
    struct linux_dirent *d;
    int i;
    char d_type;
    char* name;
    fd=system_call(SYS_OPEN,path, 0,0777);
    if (fd == -1)
        return;

    for (;;) {

        nread = system_call(SYS_GETDENTS, fd, buf, BUF_SIZE);
        if (nread == -1)
            return;

        if (nread == 0)
            break;

        for (i = 0; i < nread;) {
            d = (struct linux_dirent *) (buf + i);
            d_type = *(buf + i + d->d_reclen - 1);
            if (d->d_ino != 0) {
                name = d->d_name;
                if (d_type == 8 || d_type == 4) {
                    if (simple_strcmp(name, ".") != 0 && simple_strcmp(name, "..") != 0) {
                        char newPath[strlen_private(path)+strlen_private(name)+2];
                        string_path_ready(path, name,newPath);
			system_call(SYS_WRITE,STDOUT,newPath,strlen_private(newPath));
			system_call(SYS_WRITE,STDOUT,"\n",1);
                        if (d_type == 4)
                            search_for_all(newPath);
                    }
		}

            }
                i += d->d_reclen;
        }
    }
}

void search_for_all_file_in_exactly_name (char* path,char* file_name){
    int fd, nread;
    char buf[BUF_SIZE];
    struct linux_dirent *d;
    int i;
    char d_type;
    char* name;
    if(simple_strcmp(file_name,".")==0){
	system_call(SYS_WRITE,STDOUT,".",1);
	system_call(SYS_WRITE,STDOUT,"\n",1);
	}
    fd=system_call(SYS_OPEN,path, 0,0777);
    if (fd == -1)
        return;

    for (;;) {

        nread = system_call(SYS_GETDENTS, fd, buf, BUF_SIZE);
        if (nread == -1)
            return;

        if (nread == 0)
            break;

        for (i = 0; i < nread;) {
            d = (struct linux_dirent *) (buf + i);
            d_type = *(buf + i + d->d_reclen - 1);
            if (d->d_ino != 0) {
                name = d->d_name;
                if (d_type == 8 || d_type == 4) {
                    if (simple_strcmp(name, ".") != 0 && simple_strcmp(name, "..") != 0) {
                        char newPath[strlen_private(path)+strlen_private(name)+2];
                        string_path_ready(path, name,newPath);
			if(simple_strcmp(name,file_name)==0){
			system_call(SYS_WRITE,STDOUT,newPath,strlen_private(newPath));
			system_call(SYS_WRITE,STDOUT,"\n",1);
			}
                        if (d_type == 4)
                            search_for_all_file_in_exactly_name(newPath,file_name);
                    }
		}

            }
                i += d->d_reclen;
        }
    }
}


void Active_on_files (char* path,char* file_name,char* command, int* flag){
    int fd, nread;
    char buf[BUF_SIZE];
    struct linux_dirent *d;
    int i;
    char d_type;
    char* name;
    if(simple_strcmp(file_name,".")==0){
	system_call(SYS_WRITE,STDOUT,".",1);
	system_call(SYS_WRITE,STDOUT,"\n",1);
	}
    fd=system_call(SYS_OPEN,path, 0,0777);
    if (fd == -1)
        return;

    for (;;) {

        nread = system_call(SYS_GETDENTS, fd, buf, BUF_SIZE);
        if (nread == -1)
            return;

        if (nread == 0)
            break;

        for (i = 0; i < nread;) {
            d = (struct linux_dirent *) (buf + i);
            d_type = *(buf + i + d->d_reclen - 1);
            if (d->d_ino != 0) {
                name = d->d_name;
                if (d_type == 8 || d_type == 4) {
                    if (simple_strcmp(name, ".") != 0 && simple_strcmp(name, "..") != 0) {
                        char newPath[strlen_private(path)+strlen_private(name)+2];
                        string_path_ready(path, name,newPath);
			if(simple_strcmp(name,file_name)==0){
				char command_path[strlen_private(command)+strlen_private(newPath)+2];
				string_coomand_ready(command,newPath,command_path);
				simple_system(command_path);
				*flag=1;
			}
                        if (d_type == 4)
                            Active_on_files(newPath,file_name,command,flag);
                    }
		}

            }
                i += d->d_reclen;
        }
    }
}

int strlen_private(char* s){
    int length = 0;
    while(s[length]!='\0')
    {
        length++;
    }
 return length;
}

