#include<stdio.h>
#include<stdlib.h>
#include<dirent.h>
#include<sys/stat.h>
#include<grp.h>
#include<pwd.h>
#include<sys/types.h>
#include<time.h>
void ls(){
	DIR *d;
	struct dirent *de;
	struct stat buf;
	struct passwd *p;
	struct group *g;
	struct tm *t;
	char time[26];	
	d=opendir(".");
	
	while((de=readdir(d))!=NULL)
	{
		if(de->d_type==DT_REG)
			printf("-");
		else if(de->d_type==DT_DIR)
			printf("d");
		else if(de->d_type==DT_CHR)
			printf("c");
		else if(de->d_type==DT_BLK)
			printf("b");
		else if(de->d_type==DT_SOCK)
			printf("s");
		else if(de->d_type==DT_FIFO)
			printf("p");
		else if(de->d_type==DT_LNK)
			printf("l");
		else //if(de->d_type==Dt_UNKNOWN)
			printf("u");

		stat(de->d_name,&buf);

		printf( (buf.st_mode & S_IRUSR ? "r":"-"));
		printf( (buf.st_mode & S_IWUSR ? "w":"-"));
		printf( (buf.st_mode & S_IXUSR ? "x":"-"));

		printf( (buf.st_mode & S_IRGRP ? "r":"-"));
		printf( (buf.st_mode & S_IWGRP ? "w":"-"));
		printf( (buf.st_mode & S_IXGRP ? "x":"-"));

		printf( (buf.st_mode & S_IROTH ? "r":"-"));
		printf( (buf.st_mode & S_IWOTH ? "w":"-"));
		printf( (buf.st_mode & S_IXOTH ? "x":"-"));

		printf("%3ld",buf.st_nlink);

		p=getpwuid(buf.st_uid);
		printf(" %8s ",p->pw_name);

		g=getgrgid(buf.st_gid);
		printf(" %8s ",g->gr_name);

		t=localtime(&buf.st_mtime);
		strftime(time,sizeof(time),"%b %d %H:%M",t);
		printf("  %s",time);
		printf("  %s\n",de->d_name);
	}
}
	

void main(){
	int ch;
	for(;;){
		printf("\n Press \n 1 for ls -l command\n 2 for cp command\n 3 for EXIT \n:");
		scanf("%d",&ch);
		switch(ch){
			case 1:ls();
			       break;
			case 2://cp();
			       break;
			default:exit(0);
		}
	}
}

