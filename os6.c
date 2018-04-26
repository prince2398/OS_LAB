#include<stdio.h>
#include<stdlib.h>

void swapp(int ar[],int bt[],int pid[],int wt[],int i,int j){
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
        swapp(ar,bt,pid,wt,i,j);
      }
  }
  swapp(ar,bt,pid,wt,i+1,r);
  return i+1;
}

void customquicksort(int ar[],int bt[],int pid[],int wt[],int p,int r) {
  if(p<r){
    int q=partition(ar,bt,pid,wt,p,r);
    customquicksort(ar,bt,pid,wt,p,q-1);
    customquicksort(ar,bt,pid,wt,q+1,r);
  }
}

void SJF(){
  int n;
  printf("\nEnter no. of Processes: ");
  scanf("%d",&n);
  int ar[n],bt[n],pid[n],wt[n],btcopy[n];
  int i;

  for(i=0;i<n;i++){
    printf("\nEnter Arrival Time for Job %d : ",i+1 );
    scanf("%d",&ar[i]);
    printf("Enter Burst Time for Job %d   : ",i+1 );
    scanf("%d",&bt[i]);
    btcopy[i]=bt[i];
    pid[i]=i+1;
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
      if (timestamp-ar[k]>=0){
          wt[k]+=timestamp-ar[k];
      }else{
        wt[k]+=0;
      }
      
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
  printf("\nPid\tAt\tBt\tWt\tTat\n");
  for(k=n-1;k>=0;k--){
    printf("P%d \t %d \t %d \t %d \t %d\n",pid[k],ar[k],btcopy[pid[k]-1],wt[k],btcopy[pid[k]-1]+wt[k]);
    totalwait+=wt[k];
    totalturnaround+=btcopy[pid[k]-1]+wt[k];
  }

  printf("\nAverage Waiting Time : %f",(double)totalwait/n);
  printf("\nAverage TurnAround   : %f",(double)totalturnaround/n);

}

void SJFP(){
  int n;
  printf("\nEnter no. of Processes: ");
  scanf("%d",&n);
  int ar[n],bt[n],pid[n],wt[n],btcopy[n];
  int i;

  for(i=0;i<n;i++){
    printf("\nEnter Arrival Time for Job %d : ",i+1 );
    scanf("%d",&ar[i]);
    printf("Enter Burst Time for Job %d   : ",i+1 );
    scanf("%d",&bt[i]);
    btcopy[i]=bt[i];
    pid[i]=i+1;
    wt[i]=0;
  }

  int timestamp=ar[0];
  int jobCompleted=0;
  int j=0,k=n;
  i=0;
  
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

    for(j=0;j<n;j++){
      if(k<n&&ar[j]<=timestamp&&bt[j]!=0&&j!=k)
        wt[j]++;
    }

    timestamp++;

    if(k!=n){
      bt[k]--;
      if(bt[k]==0)
        jobCompleted++;
      customquicksort(ar,bt,pid,wt,0,n-1);
    }

    k=n;
  }

  int totalwait=0;
  int totalturnaround=0;
  printf("\nPid\tAt\tBt\tWt\tTat\n");
  for(k=0;k<n;k++){
    printf("P%d \t %d \t %d \t %d \t %d\n",pid[k],ar[k],btcopy[pid[k]-1],wt[k],btcopy[pid[k]-1]+wt[k]);
    totalwait+=wt[k];
    totalturnaround+=btcopy[pid[k]-1]+wt[k];
  }

  printf("\nAverage Waiting Time : %f",(double)totalwait/n);
  printf("\nAverage TurnAround   : %f",(double)totalturnaround/n);

}

void Priority(){

  int n;
  printf("\nEnter no. of Processes: ");
  scanf("%d",&n);
  int ar[n],bt[n],pid[n],wt[n],btcopy[n],priority[n];
  int i;
  for(i=0;i<n;i++){
    printf("\nEnter Arrival Time for Job %d : ",i+1 );
    scanf("%d",&ar[i]);
    printf("Enter Burst Time for Job %d   : ",i+1 );
    scanf("%d",&bt[i]);
    printf("Enter Priority for Job %d     : ",i+1 );
    scanf("%d",&priority[i]);
    btcopy[i]=bt[i];//copy bt to btcopy
    pid[i]=i+1;//p1,p2,p3...
    wt[i]=0;//Init
  }
  int timestamp=ar[0];
  int jobCompleted=0;
  int j=0,k=n;
  i=0;
  //sort acc to priority --- ar,pid,bt are head data to be moved with process
  //0 => Highest Priority
  customquicksort(ar,priority,pid,bt,0,n-1);

  while(jobCompleted<n){

    //Select the job with highest priority
    for(j=0;j<n;j++){
      if(ar[j]<=timestamp&&bt[j]!=0){
        k=j;
        break;
      }
    }

    //For clash of 2 or more jobs use one with lesser at
    for(j=0;j<n;j++){
      if(k<n&&ar[j]<=timestamp&&priority[j]==priority[k]&&ar[j]<ar[k])
      k=j;
    }

    //Waiting
    for(j=0;j<n;j++){
      if(k<n&&ar[j]<=timestamp&&bt[j]!=0&&j!=k)
      wt[j]++;
    }

    //Increement timestamp by 1
    timestamp++;
    if(k!=n){//Not idle time
      bt[k]--;
      if(bt[k]==0)
      jobCompleted++;
    }

    k=n;//init to value not allowed try sample run to know


  }

  int totalwait=0;
  int totalturnaround=0;
  printf("\nPid\tAt\tBt\tWt\tTat\n");
  for(k=0;k<n;k++){
  printf("P%d \t %d \t %d \t %d \t %d\n",pid[k],ar[k],btcopy[pid[k]-1],wt[k],btcopy[pid[k]-1]+wt[k]);
  totalwait+=wt[k];
  totalturnaround+=btcopy[pid[k]-1]+wt[k];
  }

  printf("\nAverage Waiting Time : %f",(double)totalwait/n);
  printf("\nAverage TurnAround   : %f",(double)totalturnaround/n);

}

/*
RoundRobin Scheduling
Sample Data
ar={0,2,8,9}
bt={3,4,2,3}
tq=2
*/
void RoundRobin(){

  int n;
  printf("\nEnter no. of Processes: ");
  scanf("%d",&n);
  int ar[n],bt[n],pid[n],wt[n],btcopy[n],tq;
  printf("Enter Time Quanta     : ");
  scanf("%d",&tq);
  int i;
  for(i=0;i<n;i++){
    printf("\nEnter Arrival Time for Job %d : ",i+1 );
    scanf("%d",&ar[i]);
    printf("Enter Burst Time for Job %d   : ",i+1 );
    scanf("%d",&bt[i]);
    btcopy[i]=bt[i];//copy bt to btcopy
    pid[i]=i+1;//p1,p2,p3...
    wt[i]=0;//Init
  }

  int timestamp=ar[0];
  int jobCompleted=0;
  int j=0,k=n;
  i=0;

  while(jobCompleted<n){

    for(j=0;j<n;j++){

      if(bt[j]>0&&ar[j]<=timestamp){
        //waitingtime for all other than one being executed(j)
        for(i=0;i<n;i++){
          if(i!=j&&ar[i]<=timestamp&&bt[i]!=0)
          wt[i]+=(bt[j]-tq)>0?tq:(bt[j]-tq==0)?tq:bt[j];
        }
        bt[j]=(bt[j]-tq);
        if(bt[j]==0){
          timestamp+=tq;
          jobCompleted++;
        }//if
        else if(bt[j]<0){
          bt[j]+=tq;
          timestamp+=bt[j];
          bt[j]=0;
          jobCompleted++;

        }//else-if
        else{
          timestamp+=tq;
        }//else
      }//if

      else if(ar[j]>timestamp){//next job arrives in future
        if(jobCompleted==(j))//If all previous jobs are completed and next job arrives in future
        timestamp++;//Idle Time
        break;//the process has not arrived yet so break this for loop and start again from j=0
      }//else-if

    }//for
  }//while

  int totalwait=0;
  int totalturnaround=0;
  printf("\nPid\tAt\tBt\tWt\tTat\n");
  for(k=0;k<n;k++){
  printf("P%d \t %d \t %d \t %d \t %d\n",pid[k],ar[k],btcopy[pid[k]-1],wt[k],btcopy[pid[k]-1]+wt[k]);
  totalwait+=wt[k];
  totalturnaround+=btcopy[pid[k]-1]+wt[k];
  }

  printf("\nAverage Waiting Time : %f",(double)totalwait/n);
  printf("\nAverage TurnAround   : %f",(double)totalturnaround/n);

}

int main(){
  int ch;
  do {
    printf("\n\n1. SJF without Preemption\n");
    printf("2. SJF with Preemption\n");
    printf("3. Priority\n");
    printf("4. Round Robin\n");
    printf("0. Exit\n");
    printf("Enter your choice: ");
    scanf("%d",&ch );
    switch (ch) {
      case 1:
          SJF();
          break;
      case 2:
         SJFP();
         break;
      case 3:
          Priority();
          break;
      case 4:
          RoundRobin();
          break;
      default:
      if(ch)
      printf("Incorrect choice\n");
      break;
    }
  } while(ch!=0);
  return 0;
}
