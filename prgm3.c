#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
struct str
{
	char s[10],ch;
};
typedef struct str st;

void* fun(void* arg)
{
	st* p=(st*) arg;
	int i,flag=0;
	printf("\n%s\n%c\n",p->s,p->ch);

	for(i=0;p->s[i]!='\0';i++)
		if(p->ch==p->s[i])
			flag=1;

	if(flag==1)
		printf("\nThe given character %c occcurs in the string \" %s\"\n",p->ch,p->s);
	else
		printf("\nThe given character %c doesn't occcur in the string \"%s\"\n",p->ch,p->s);
	pthread_exit(0);
}

void main()
{
	st m,*p;
	pthread_t tid;

	printf("\nEnter the string :\n");
	scanf("%s",m.s);
	getchar();
	printf("\nEnter the character:\n");
	scanf("%c",&m.ch);

	p=&m;

	pthread_create(&tid,NULL,fun,(void*) p);

	pthread_join(tid,NULL);

}
