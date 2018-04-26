#include <stdio.h>

void print_array(int a[],int sz){
	int i;
	for ( i = 0; i < sz; ++i)
	{
		printf("%d ", a[i]);		
	}
}

void main(){
	int n ,i,j,key;
	printf("Size of array : ");
	scanf("%d",&n);
	int a[n];
	for (i=0 ;i <n ; i++ ){
		scanf("%d",&a[i]);
	}

	for (int i = 0; i < n; ++i)
	{
		int key=a[i];
		j=i-1;
		while(j>=0&&key<a[j]){
			a[j+1] = a[j];
			j--;
		}
		a[j+1] = key;
		printf("\n%d run \n",i+1);
		print_array(a,n);


	}

	printf("\nsorted array : \n");

	print_array(a,n);
	printf("\n");
}