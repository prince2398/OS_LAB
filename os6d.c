#include<stdio.h>
#include<sys/wait.h>

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
int main(){
  int n;
  printf("Enter no. of Processes: ");
  scanf("%d",&n);
  int ar[n],bt[n],pid[n],wt[n],btcopy[n],tq;
  printf("Enter Time Quanta     : ");
  scanf("%d",&tq);
  int i;
  for(i=0;i<n;i++){
    printf("Enter Arrival Time for Job %d : ",i+1 );
    scanf("%d",&ar[i]);
    printf("Enter Burstin Time for Job %d : ",i+1 );
    scanf("%d",&bt[i]);
    btcopy[i]=bt[i];
    pid[i]=i+1;
    wt[i]=0;
  }

  int timestamp=ar[0];
  int jobCompleted=0;
  int j=0,k=n;
  i=0;

  while(jobCompleted<n){

    for(j=0;j<n;j++){

      if(bt[j]>0&&ar[j]<=timestamp){
        
        for(i=0;i<n;i++){
          if(i!=j&&ar[i]<=timestamp&&bt[i]!=0)
          wt[i]+=(bt[j]-tq)>0?tq:(bt[j]-tq==0)?tq:bt[j];
        }
        bt[j]=(bt[j]-tq);
        if(bt[j]==0){
          timestamp+=tq;
          jobCompleted++;
        }
        else if(bt[j]<0){
          bt[j]+=tq;
          timestamp+=bt[j];
          bt[j]=0;
          jobCompleted++;

        }
        else{
          timestamp+=tq;
        }
      }

      else if(ar[j]>timestamp){
        if(jobCompleted==(j))
        timestamp++;
        break;
      }

    }
  }

  int totalwait=0;
  int totalturnaround=0;
  printf("Process  Arrival Burst Wait TurnAround\n");
  for(k=0;k<n;k++){
    printf("P%d \t %d \t %d \t %d \t %d\n",pid[k],ar[k],btcopy[pid[k]-1],wt[k],btcopy[pid[k]-1]+wt[k]);
    totalwait+=wt[k];
    totalturnaround+=btcopy[pid[k]-1]+wt[k];
  }

  printf("\nAverage Waiting Time : %f",(double)totalwait/n);
  printf("\nAverage TurnAround   : %f",(double)totalturnaround/n);
return 0;

}