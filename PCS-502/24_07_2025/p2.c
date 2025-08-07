#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>

void printer(int *a,int n)
{
	printf("The elements of the array are:-\n");
	for(int i=0;i<n;i++)
		printf("%d ",a[i]);
	printf("\n");
}

int main()
{
	printf("Satyam Singh Rawat(C) - 61\n");
	
	pid_t child_pid;
	
	int n;
	printf("Enter n: ");
	scanf("%d",&n);
	
	int *a = (int*)malloc(sizeof(int)*n);
	
	printf("Enter elements in the array:-\n");
	for(int i=0;i<n;i++)
		scanf("%d",&a[i]);

	//printer(a,n);
	
	child_pid = fork();
	
	int sum = 0;
	
	if(child_pid == 0)
	{
		printf("This is the Child Process -> PID:%d\n",getpid());
		printf("The odd elements are:-\n"); 
		for(int i=0;i<n;i++)
		{
			if(a[i]%2!=0)
			{	
				printf("%d ",a[i]);
				sum+=a[i];
			}
		}
		
		printf("\nThe sum of odd numbers = %d\n",sum);
	}
	else if(child_pid>0)
	{
		printf("This is the Parent Process -> PID:%d, Child PID: %d\n",getpid(),child_pid);	
		printf("The even elements are:-\n"); 
		for(int i=0;i<n;i++)
		{
			if(a[i]%2==0)
			{	
				printf("%d ",a[i]);
				sum+=a[i];
			}
		}
		
		printf("\nThe sum of even numbers = %d\n",sum);
	}
	else
		perror("Failed to fork\n");
	
	return 0;
}
