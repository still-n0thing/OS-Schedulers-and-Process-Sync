#include <stdio.h> 
#include <pthread.h> 

int n= 20;
int flag[20]; //change 10 with number n 
int turn; 
const int MAX = 100; 
int ans = 0; 

//in start of program
void lock_init() 
{ 
	int i;
	for(i=0;i<n;i++)
	{
		flag[i] = 0;	
	} 
	turn = 0; 
} 

// Before entering critical section 
void lock(int self) 
{ 
	//flag[self]=1 show that process self want to enter in critical section 
	if(self <=n-1 && self >=0)
	{
		flag[self] = 1;
	} 
	
	// first give chance to another process
	turn = n-self; 
	//wait untill other process are in critical section 
	if(n-1-self != self)
	{
		while (flag[n-1-self]==1 && turn==n-self) ; 

	}	
	else if(n-2-self >= 0)
	{
		while (flag[n-2-self]==1 && turn==n-self) ;
	}
} 

//when goes out of critical section
void unlock(int self) 
{ 
	//flag[self] = 0 show that process self going out of critical section
	if(self <=n && self >=0)
	{
		flag[self] = 0;
	}
} 


//every process run the same function
void* func(void *s) 
{ 
	int i = 0; 
	int self = (int*)s;
 

	lock(self); 
	//critical section starts here	
	
	printf("Thread Entered: %d\n", self); 
	//ans variable changed by every thread
	for (i=0; i<MAX; i++) 
		ans++; 
	//critical section ends here
	unlock(self); 
} 

// Driver code 
int main() 
{  
	pthread_t threads[n];
	lock_init(); 
	
	void *retvals[n];
	int count;
	for (count = 0; count < n; ++count)
	{
		if (pthread_create(&threads[count], NULL,func,(void*)count) != 0)
		{
		  fprintf(stderr, "error: Cannot create thread # %d\n", count);
		  break;
		}
	}
	for (int i = 0; i < n; ++i)
	{
		if (pthread_join(threads[i], &retvals[i]) != 0)
		{
		  fprintf(stderr, "error: Cannot join thread # %d\n", i);
		}
	}

	//if both are same then we say that our solution is correct
	printf("Ans variable after each thread: %d | Ans should be : %d\n", ans, MAX*n); 

	return 0; 
} 

// compile : gcc peterson.cpp -o peter -pthread