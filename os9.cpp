#include <bits/stdc++.h>

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
int main(){
	
	int n,hits=0,miss=0;
	//int pages[20] = {7,0,1,2,0,3,0,4,2,3,0,3,2,1,2,0,1,7,0,1};
	//int pages[12] = {5,4,3,2,5,4,6,5,4,3,2,6};
	int p_no;
	cout<<"\nEnter no. pages : ";
	cin>>p_no;

	int pages[p_no];

	cout<<"\nEnter string containing Pages : ";
	for (int i = 0; i < p_no; ++i){
		cin>>pages[p_no];
	}
	cout<<"\nEnter no. of memory frames: ";
	cin>>n;

	vector<int> cache;

	int p;
	for (int i = 0; i < p_no; ++i){
		p = pages[i];
		if (searchvector(cache,p)){
			hits++;	
		}else{
			if (cache.size() >= n){
				cache.erase(cache.begin());
			}	
			cache.push_back(p);

			miss++;
		}
	}

	cout<<"\nhits = "<<hits;
	cout<<"\nmiss = "<<miss<<endl;

	return 0;
}