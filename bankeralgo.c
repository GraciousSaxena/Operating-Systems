#include<stdio.h>
#include<stdio.h>
int complete(int com[],int r){
	int i,flag=0;

	for(i=0;i<r;i++)
		if(com[i]==1)
			flag=1;
	return flag;
}


void main(){
	int i,j,k=0,p,r,com[10]={0},av[10],max[10][10],allot[10][10],nd[10][10],n;
	printf("\nEnter the no of processess:");
	scanf("%d",&p);
	printf("\nEnter the no of different resources:");
	scanf("%d",&r);

	for(i=0;i<r;i++){
		printf("\nEnter the currently available instances of resource type %d:",i+1);
		scanf("%d",&av[i]);
	}

	for(i=0;i<p;i++){
		printf("\nEnter the Max Value of resource req by process %d",i);
		for(j=0;j<r;j++){
			printf("\nResource of type %d:",j+1);
			scanf("%d",&max[i][j]);
		}
	}

	for(i=0;i<p;i++){
		printf("\nEnter the Alloted  Value of resource to process %d",i);
		for(j=0;j<r;j++){
			printf("\nResource of type %d:",j+1);
			scanf("%d",&allot[i][j]);
			nd[i][j]=max[i][j]-allot[i][j];
		}
	}

	n=p-1;

	while(n--){
		for(i=0;i<p;i++){
			for(j=0;j<r;j++)
				if(nd[i][j]<=av[j])
					k++;
			if(k==r && com[i]==0){
				printf("Process - %d\n",i);
				com[i]=1;
				for(j=0;j<r;j++)
					av[j]+=allot[i][j];
			}
			k=0;
		}

		if(n==p-2)
			if(complete(com,r)==0){
				printf("\nDeadlock\n");
				break;
			}
	}
}
