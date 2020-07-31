#include<stdio.h>
#include<stdlib.h>
#include<math.h>
int tree[2050]={0};

int power(int x,int n){
	int i;
	if(n==0)
		return 1;
	for(i=1;i<n;i++)
		x*=2;
	return x;
}




int place(int node){
	while(node!=0){
		node=node%2==0?(node-1)/2:node/2;
		if(tree[node]>1)
			return 0;
	}
	return 1;
}


void makedivided(int node){
	while(node!=0){
		node=node%2==0?(node-1)/2:node/2;
		tree[node]=1;
	}
}

void seg_alloc(int ts,int r){
	int i,s=ts,fl=0;
	if(r>ts){
		printf("\nERROR:Not Enough Memory\n");
		return ;
	}

	while(s!=0){
		if(r<ts && r>s/2)
			break;
		else{
			fl++;
			s/=2;
		}
	}
	for(i=power(2,fl)-1;i<=power(2,fl+1)-2;i++){
		if(tree[i]==0 && place(i)){
			tree[i]=r;
			makedivided(i);
			printf("\nAllocation Successfull\n");
			break;
		}
	}

	if(i==power(2,fl+1))
		printf("\nNot enough Memory\n");
}

void make_free(int r){
	int node=0;
	while(tree[node]!=r)
		node++;
	tree[node]=0;
	while(node!=0){
		if(tree[node%2==0?node-1:node+1]==0){
			tree[node%2==0?(node-1)/2:node/2]=0;
			node=node%2==0?(node-1)/2:node/2;
		}
		else
			break;
	}
}

void printing(int ts,int node){
	int perm=0,ulimit,llimit,tab;
	if(node==0)
		perm=1;
	else if(node%2==0)
		perm=tree[(node-1)/2]==1?1:0;
	else
		perm=tree[node/2]==1?1:0;

	if(perm){
		llimit=0,ulimit=0,tab=0;
		while(1){
			if(node>=llimit && node<=ulimit)
				break;
			else{
				tab++;
				llimit=power(2,tab)-1;
				ulimit=power(2,tab+1)-2;
			}
		}

		printf("%d",ts/power(2,tab));
		if(tree[node]>1)
			printf(" -->Allocated %d",tree[node]);
		else if(tree[node]==1){
			printf(" -->Divided \n");
			printing(ts,2*node+1);
			printing(ts,2*node+2);
		}
		else
			printf(" -->Free ");
	}
}

void main(){
	int ch,r,ts;
	printf("\nEnter the total size of memory available :");
	scanf("%d",&ts);
	for(;;){
		printf("\nPress \n 1 for Allocating memory to process\n 2 for Deallocating  memory from process\n 3 for Displaying the memory allocation \n 4 for exiting n  :");
		scanf("%d",&ch);
		switch(ch){
			case 1:printf("\nEnter the memory required by process:");
			       scanf("%d",&r);
			       seg_alloc(ts,r);
			       break;
			case 2:printf("\nEnter the size of the process:");
			       scanf("%d",&r);
			       make_free(r);
			       break;
			case 3:printing(ts,0);
			       break;
			default:exit(0);
		}
	}
}
