#include<stdio.h>
#include<stdlib.h>
#include "elevator.h"
int main(){
	int nrid;
	int nst;
	int* dests;
	int cost;
	scanf("%d",&nrid);/* Number of people*/
	scanf("%d",&nst);/* Max number of stations*/
	dests=malloc(nrid*sizeof(int));
	for(int i=0;i<nrid;i++)
		scanf("%d",&dests[i]);/* Destinations table*/
	cost=solve(nrid,nst,dests);
	printf("Cost is: %d\n",cost);
	free(dests);
	return 0;
}