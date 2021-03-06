#include<stdio.h>
#include<stdlib.h>

void swap(int ar[],int bt[],int pid[],int wt[],int i,int j){
  int temp;

  temp=ar[i];
  ar[i]=ar[j];
  ar[j]=temp;

  temp=bt[i];
  bt[i]=bt[j];
  bt[j]=temp;

  temp=pid[i];
  pid[i]=pid[j];
  pid[j]=temp;

  temp=wt[i];
  wt[i]=wt[j];
  wt[j]=temp;
}
int partition(int ar[],int bt[],int pid[],int wt[],int p,int r){
  int x=bt[r];
  int i=p-1;
  int j;
  for(j=p;j<r;j++){
      if(bt[j]<x){
        i=i+1;
        swap(ar,bt,pid,wt,i,j);
      }
  }
  swap(ar,bt,pid,wt,i+1,r);
  return i+1;

}
void customquicksort(int ar[],int bt[],int pid[],int wt[],int p,int r) {
  
  if(p<r){
    int q=partition(ar,bt,pid,wt,p,r);
    customquicksort(ar,bt,pid,wt,p,q-1);
    customquicksort(ar,bt,pid,wt,q+1,r);
  }
}

int main()
{ int n;
  printf("Enter no. of Processes: ");
  scanf("%d",&n);
  int ar[n],bt[n],pid[n],wt[n],btcopy[n];
  int i,temp;
  for(i=0;i<n;i++){
    printf("Enter Arrival Time for Job %d : ",i+1 );
    scanf("%d",&ar[i]);
    printf("Enter Burst Time for Job %d : ",i+1 );
    scanf("%d",&bt[i]);
    btcopy[i]=bt[i];
    pid[i]=i+1;//p1,p2,p3...
    wt[i]=0;
  }

  int timestamp=0;
  int k,j;

  timestamp=ar[0];
  int jobCompleted=0;
  customquicksort(ar,bt,pid,wt,0,n-1);
  
 
  while(jobCompleted<n){

      
    for(j=0;j<n;j++){
      if(ar[j]<=timestamp&&bt[j]!=0){
        k=j;
        break;
      }
    }

      
    for(j=0;j<n;j++){
      if(k<n&&ar[j]<=timestamp&&bt[j]==bt[k]&&ar[j]<ar[k])
      k=j;
    }

     
    if(k!=n){
      wt[k]+=(timestamp-ar[k]>=0)?timestamp-ar[k]:0;
      timestamp+=bt[k];
      bt[k]=0;
      jobCompleted++;
      customquicksort(ar,bt,pid,wt,0,n-1);

    }
    else{
      timestamp+=1;
    }
      k=n;
  }


  int totalwait=0;
  int totalturnaround=0;
  printf("Process  Arrival Burst Wait TurnAround\n");
  for(k=n-1;k>=0;k--){
  printf("P%d \t %d \t %d \t %d \t %d\n",pid[k],ar[k],btcopy[pid[k]-1],wt[k],btcopy[pid[k]-1]+wt[k]);
  totalwait+=wt[k];
  totalturnaround+=btcopy[pid[k]-1]+wt[k];
  }

  printf("\nAverage Waiting Time : %f",(double)totalwait/n);
  printf("\nAverage TurnAround   : %f",(double)totalturnaround/n);
  return 0;

}