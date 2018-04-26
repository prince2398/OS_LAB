#include <stdio.h>

void print_array(int a[],int sz){
	int i;
	for ( i = 0; i < sz; ++i)
	{
		printf("%d ", a[i]);		
	}
}
void main(){
	int n ,i,j,temp;
	printf("Size of array : ");
	scanf("%d",&n);
	int a[n];
	for (i=0 ;i <n ; i++ ){
		scanf("%d",&a[i]);
	}

	for (i=0;i<n;i++){
		for(j=0;j<(n-i-1);j++){
			if (a[j]>a[j+1])
			{
				temp = a[j];
				a[j] = a[j+1];
				a[j+1] = temp;
			}
		}
		printf("\n%d run \n",i+1);
		print_array(a,n);
	}

	printf("\nsorted array : \n");
	print_array(a,n);
	printf("\n");
}