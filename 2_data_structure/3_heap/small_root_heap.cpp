//小根堆 

const int N;
int n;
int heap[N+1],l;


void _heap_up(int heap[],int l,int x)
{
	for (int i=x; i>1; i=i/2)
	{   int f=i/2;
	    if  (heap[i]<heap[f])  swap(heap[i],heap[f]);
	    else break;
	}
}

void _heap_down(int heap[],int l,int x)
{
	for (int i=x,s=i*2; s<=l; i=s,s=i*2)
	{
		if  (s+1<=l && heap[s+1]<heap[s])  s=s+1;
		if  (heap[i]>heap[s])  swap(heap[i],heap[s]);
		else break;
	}
}

void heap_up(int heap[],int l,int x)
{
	while (x>1)
	{   int f=x/2;
	    if  (heap[x]<heap[f])  {  swap(heap[x],heap[f]);  x=f;}
	    else break;
	}
}

void heap_down(int heap[],int l,int x)
{
	while (x*2<=l)
	{   int s=x*2;
	    if  (s+1<=l&&heap[s+1]<heap[s])  s=s+1;
	    if  (heap[x]>heap[s])  {  swap(heap[x],heap[s]);  x=s;}
	    else break;
	}
}

void heap_in(int x)
{
	heap[++l]=x;
	heap_up(heap,l,l);
}

int heap_out()
{
	int sol=heap[1];
	heap[1]=heap[l--];
	heap_down(heap,l,1);
	
	return sol;
}


