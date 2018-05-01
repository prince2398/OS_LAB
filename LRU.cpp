#include <bits/stdc++.h>
#define MAX 100 
using namespace std; 

int searchvector(vector<int> v,int item){

	for (int i = 0; i < v.size(); ++i)
	{
		if (item == v[i]){
			return 1;
		}
	}
	return 0;
}

int extract_min(int arr[],int sz){
	int min = arr[0];
	int min_i = 0;

	for (int i = 1; i < sz; ++i){
		if (min>arr[i]){
			min = arr[i];
			min_i = i;
		}
	}
	return min_i;
}

int main(){
	int lru , hits = 0 , miss = 0 ;
	// int pages[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2};
	// int pages[] = {1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5};
	//int n = sizeof(pages)/sizeof(int);
	int n;
	int f_no = 4;
	
	cout<<"\nEnter no. of pages : ";
	cin>>n;
	int pages[n];
	cout<<"\nEnter string of pages: ";
	for (int i = 0; i < n; ++i){
		cin>>pages[i];
	}
	getchar();
	
	cout<<"\nEnter the no. of frames: ";
	cin>>f_no;

	int indexes[n];
	for (int i = 0; i < n; ++i){
		indexes[i] = MAX;
	}
	vector<int> frames;

	for (int i = 0; i < n; ++i){
		int p = pages[i];
		if(searchvector(frames,p)){
			hits++;
		}else{
			if (frames.size() >= f_no){
				lru = extract_min(indexes ,sizeof(indexes)/sizeof(int));
				frames.erase(remove(frames.begin(),frames.end(),lru),frames.end());
				indexes[lru] = MAX;
			}
			frames.push_back(p);
			miss++;
		}
		indexes[pages[i]] = i;
	}

	cout<<"\nhits = "<<hits;
	cout<<"\nmiss = "<<miss<<endl;

}
