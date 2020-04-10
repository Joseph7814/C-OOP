#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include <string.h>
#include<fcntl.h>
#include<pthread.h>
pthread_mutex_t plock; //lock for process Synchronization
int main()
{
pthread_mutex_init(&plock, NULL);
int i,n,p[20]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20},min,k=1,btime=0;
int bt[20],temp,j,at[20],wt[20],tt[20],ta=0,sum=0;
float wavg=0,tavg=0,tsum=0,wsum=0;
printf(" ---Shortest Job First Scheduling (SJFS)---\n");
printf("\nEnter the No. of processes in Queue :");
scanf("%d",&n);

for(i=0;i<n;i++)
{
        
        printf("\n Process %d\n",i+1);
	pthread_mutex_lock(&plock);// lock for pre-emption
	label:
        printf("Arrival time:");
        scanf("%d",&at[i]);
	if (at[i]==0)
	{
		printf("\n Arrival time should not be zero! please Re-enter the correct arrival time \n");
		goto label;
	}	
        bt[i]=at[i]*2;
        printf("Burst Time:%d\n",bt[i]);
        printf("----------------------------------------");
	pthread_mutex_unlock(&plock);//unlock for pre-emption
}

/*Sorting on the basis of Arrival Time*/

for(i=0;i<n;i++)
{
	for(j=0;j<n;j++)
	{
		if(at[i]<at[j])
		{
			temp=p[j];
			p[j]=p[i];
			p[i]=temp;
			temp=at[j];
			at[j]=at[i];
			at[i]=temp;
			temp=bt[j];
			bt[j]=bt[i];
			bt[i]=temp;
		}
	}
}



for(j=0;j<n;j++)
{
	btime=btime+bt[j];
	min=bt[k];
		for(i=k;i<n;i++)
			{
			if (btime>=at[i] && bt[i]>min)
				{
					temp=p[k];
					p[k]=p[i];
					p[i]=temp;
					temp=at[k];
					at[k]=at[i];
					at[i]=temp;
					temp=bt[k];
					bt[k]=bt[i];
					bt[i]=temp;
				}
			}
	k++;
}

wt[0]=0;
for(i=1;i<n;i++)
{
		wt[i]=0;
		for(int j=0;j<i;j++)
			wt[i]+=bt[j];
		wsum+=wt[i];
}

wavg=(wsum/n);
	for(i=0;i<n;i++)
	{
	ta=ta+bt[i];
	tt[i]=ta-at[i];
	tsum=tsum+tt[i];
	}

tavg=(tsum/n);

printf("\n OUTCOME:-");
/*Organize the table on the basis of Burst time,Arrival Time, Waiting time and Turn-Around Time */
printf("\nProcess\t Burst\t Arrival\t Waiting\t Turn-around" );
for(i=0;i<n;i++)
{
	printf("\n p%d\t %d\t %d\t\t %d\t\t\t%d",p[i],bt[i],at[i],wt[i],tt[i]);
}

printf("\n\nAVG WAITING TIME : %f",wavg);
printf("\nAVG TURN AROUND TIME : %f\n",tavg);
return 0;
}
