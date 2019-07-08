#include "elevator.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
int fw(int start,int end,int* dests,int nrid){
	int counter=0;
	int val;
	for(int i=0;i<nrid;i++){
		val=0;
		if(dests[i]>start&&dests[i]<=end){
			if(dests[i]-start>end-dests[i])
				val=end-dests[i];
			else 
				val=dests[i]-start;
		}
		counter+=val;
	}
	return counter;

}
int mincostrec(int i,int j,int* dests,int nrid){/* Recursive method*/
	if(j==0)
		return fw(0,INT_MAX,dests,nrid);
	int min=INT_MAX;
	int value;
	for(int k=0;k<=i;k++){
		value=mincostrec(k,j-1,dests,nrid)-fw(k,INT_MAX,dests,nrid)+fw(k,i,dests,nrid)+fw(i,INT_MAX,dests,nrid);
		if(value<min)
			min=value;
	}
	return min;
}
int mincostmem(int i,int j,int* dests,int nrid,int** M){/* Recursive with memoization method*/
	if(M[i][j]!=-1)
		return M[i][j];
	if(j==0){
		M[i][j]=fw(0,INT_MAX,dests,nrid);
		return M[i][j];
	}
	int min=INT_MAX;
	int value;
	for(int k=0;k<=i;k++){
		value=mincostrec(k,j-1,dests,nrid)-fw(k,INT_MAX,dests,nrid)+fw(k,i,dests,nrid)+fw(i,INT_MAX,dests,nrid);
		if(M[k][j]!=-1)
			M[i][j]=value;
		if(value<min)
			min=value;
	}
	return min;
}
#ifdef REC
int solve(int nrid,int nst,int *dests){
	int counter=0;
	int max=-1;
	for(int i=0;i<nrid;i++)
		if(dests[i]>=max)
			max=dests[i];
	int min=INT_MAX;
	int min_station=INT_MAX;
	for(int i=0;i<=max;i++){
		int value=mincostrec(i,nst,dests,nrid);
		if(value<min){
			min_station=i;
			min=value;
		}
	}
	if(nst==0)
		printf("%s\n","No elevator stops");
	else
		printf("Last stop at floor %d\n", min_station);
	return min;
}
#endif
#ifdef MEM
int solve(int nrid,int nst,int *dests){
	int nfl=-1;
	for(int i=0;i<nrid;i++)
		if(dests[i]>=nfl)
			nfl=dests[i];
	int** M=malloc((nfl+1)*sizeof(int*));
	for(int i=0;i<=nfl;i++)
		M[i]=malloc((nst+1)*sizeof(int));
	for(int i=0;i<=nfl;i++)
		for(int j=0;j<=nst;j++)
			M[i][j]=-1;
	int min=INT_MAX;
	int min_station=INT_MAX;
	for(int i=0;i<=nfl;i++){
		int value=mincostmem(i,nst,dests,nrid,M);
		if(value<min){
			min_station=i;
			min=value;
		}
	}
	if(nst==0)
		printf("%s\n","No elevator stops");
	else
		printf("Last stop at floor %d\n", min_station);
	for(int i=0;i<=nfl;i++)
		free(M[i]);
	free(M);
	return min;
}
#endif
#ifdef DP
int solve(int nrid,int nst,int *dests){
	int nfl=-1;
	for(int i=0;i<nrid;i++)
		if(dests[i]>=nfl)
			nfl=dests[i];	
	int** M=malloc((nfl+1)*sizeof(int*));
	for(int i=0;i<nfl+1;i++)
		M[i]=malloc((nst+1)*sizeof(int));
	int** floor=malloc((nfl+1)*sizeof(int*));
	for(int i=0;i<=nfl;i++)
		floor[i]=malloc((nst+1)*sizeof(int));
	for(int j=0;j<=nst;j++){
		for(int i=0;i<=nfl;i++){
				if(j==0)
					M[i][j]=fw(0,INT_MAX,dests,nrid);
				else{
					int min_k=INT_MAX;
					int pos;
					for(int k=0;k<=i;k++){
						int value=M[k][j-1]- fw(k,INT_MAX,dests,nrid)+ fw(k,i,dests,nrid)+ fw(i,INT_MAX,dests,nrid);
						if(value<min_k){
							pos=k;
							min_k=value;
						}
					}
					M[i][j]=min_k;
					floor[i][j]=pos;
				}
		}
	}
	for(int j=0;j<=nst;j++){
		for(int i=0;i<=nfl;i++)
			printf("%3d ",M[i][j]);
		printf("\n");
	}
	int mincost=INT_MAX;
	for(int i=0;i<=nfl;i++)
		if(M[i][nst]<mincost)
			mincost=M[i][nst];
	if(nst==0)
		printf("%s\n","No elevator stops");
	else{
		int position_of_i;
		int value=mincost;
		for(int i=0;i<=nfl;i++){
			if(M[i][nst]==value){
				position_of_i=i;
				break;
			}
		}
		int max_station=nst;
		int* elevator=malloc(nst*sizeof(int));
		int counter=nst-1;
		elevator[counter--]=position_of_i;
		for(int i=nst-2;i>=0;i--){/* Founding elevator stops*/
			elevator[counter--]=floor[position_of_i][max_station];
			position_of_i=floor[position_of_i][max_station];
			max_station--;
		}
		printf("Elevator stops are: ");
		for(int i=0;i<nst;i++){
			if(elevator[i]==0)
				continue;
			printf("%d ",elevator[i]);
		}
		printf("\n");
		free(elevator);
	}
	for(int i=0;i<=nfl;i++)
		free(floor[i]);
	free(floor);
	for(int i=0;i<nfl+1;i++)
		free(M[i]);
	free(M);
	return mincost;
}
#endif