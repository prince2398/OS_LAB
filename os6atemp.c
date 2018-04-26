#include <stdio.h>

int timestamp = 0 ;

struct pro{
	int no;
	int st;
	int at;
	int bt;
	int wt;
	int ct;
	int tat;
};
typedef struct pro pro ;

int main(){

	int n,i,j,p,tbt=0;
	float w,t;
	printf("\nEnter no. of processes : ");
	scanf("%d",&n);
	int bt[n],jobsDone = 0;
	pro pros[n],temp;
	
	int k;
	//enter arrival time and burst time of all processes 
	for (i = 0; i < n; ++i){
		printf("\nEnter process no. %d .",i+1);
		pros[i].no = i+1 ; 

		printf("\nArrival time : ");
		scanf("%d",&pros[i].at);

		printf("Burst time : ");
		scanf("%d",&pros[i].bt);
		bt[i] = pros[i].bt;
		pros[i].st = 0;
		pros[i].wt = 0;
		pros[i].tat = 0;
		pros[i].ct = 0;
	}
	//sort according burst time
	for (i=0;i<n;i++){
		for(j=0;j<(n-i-1);j++){
			if (pros[j].bt > pros[j+1].bt){
				temp = pros[j];
				pros[j] = pros[j+1];
				pros[j+1] = temp;
			}
		}
	}
	//schedule
	while(jobsDone < n){

		for(j=0;j<n;j++){
	      if(pros[j].at<=timestamp&&pros[j].bt!=0){
	        k=j;
	        break;
	      }
	    }
		for(j=0;j<n;j++){
	      if(k<n&&pros[j].at<=timestamp&&pros[j].bt==pros[k].bt&&pros[j].at<pros[k].at)
	      	k=j;
	    }


	    if(k!=n){
		  	pros[k].wt+=(timestamp-pros[k].at>=0)?timestamp-pros[k].at:0;
		    pros[k].st = timestamp ; 
		    timestamp+=pros[k].bt;
		    pros[k].ct = timestamp;
		    pros[k].tat = pros[k].bt + pros[k].wt;
		    pros[k].bt=0;
		    jobsDone++;
		    //sort acc to bt
		   	for (i=0;i<n;i++){
				for(j=0;j<(n-i-1);j++){
					if (pros[j].bt > pros[j+1].bt){
						temp = pros[j];
						pros[j] = pros[j+1];
						pros[j+1] = temp;
					}
				}
			}
	    }else{
	    	timestamp+=1;
	    }

	    k=n;
	};

	printf("\nTable for all processes");

	printf("\npno\tat\tbt\tst\tct\twt\ttat");
	for (int i = 0; i < n; ++i){
		printf("\n%d\t%d\t%d\t%d\t%d\t%d\t%d\t",pros[i].no,pros[i].at,bt[pros[i].no - 1],pros[i].st,pros[i].ct,pros[i].wt,pros[i].tat);
	}

	printf("\n");
	//calculating average waiting time and average
	w=0;
	for (int i = 0; i < n; ++i){
		w+=pros[i].wt;
	}
	w = w/n;

	t=0;
	for (int i = 0; i < n; ++i)
		t+=pros[i].tat;
	t = t/n;

	printf("\nAverage Waiting Time : %f",w);
	printf("\nAverage Turn Around Time : %f",t);

	printf("\n");
	

	return 0 ;
}