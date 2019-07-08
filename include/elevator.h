int fw(int start,int end,int* dests,int nrid);
int mincostrec(int i,int j,int* dests,int nrid);
int mincostmem(int i,int j,int* dests,int nrid,int** M);
int solve(int nrid,int nst,int *dests);