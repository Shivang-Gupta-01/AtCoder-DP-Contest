#include<bits/stdc++.h>
using namespace std;

int minCost = INT_MAX;
// Recursive Solution -> Top Down
void frogA(int index,int n,int cost,string &path,vector<int> &heights){

	if(index>=n){
		return;
	}
	if(index==n-1){
		minCost = min(minCost,cost);
		cout<<path+to_string(index)<<" "<<cost<<"\n";
		return;
	}
    string temp = path + to_string(index);
	frogA(index+1,n,cost+abs(heights[index+1]-heights[index]),temp,heights);
	frogA(index+2,n,cost+abs(heights[index+2]-heights[index]),temp,heights);
}

// Recursive Solution -> Bottom up
void frogAb(int n,int cost,string &path, vector<int> &heights){
	if(n<0){
		return;
	}
	if(n==0){
		minCost = min(minCost,cost);
		path = path + to_string(n);
        reverse(path.begin(),path.end());
		cout<<path<<" "<<cost<<'\n';
		return;
	}
	string temp = path + to_string(n);
	frogAb(n-1,cost + abs(heights[n] - heights[n-1]),temp,heights);
	frogAb(n-2,cost + abs(heights[n] - heights[n-2]),temp,heights);
}

// Memoisation -> Top Down
int frogAMemoised(int index,int n,vector<int> &heights,vector<int> &dp){
	if(index==n-1){
		return 0;
	}

	int op1 = abs(heights[index] - heights[index+1]) + frogAMemoised(index+1,n,heights,dp);
	int op2 = INT_MAX;
	if(index+2<n){
		op2 = abs(heights[index] - heights[index+2]) + frogAMemoised(index+2,n,heights,dp);
	}

	return dp[index] = min(op1,op2);
}

// Mempoisation -> Bottom Up
int frogAbMemoised(int n,vector<int> &heights,vector<int> dp){
	if(n==0){
		return 0;
	}
    if(dp[n]!=-1){
        return dp[n];
    }
	int op1 = abs(heights[n] - heights[n-1]) + frogAbMemoised(n-1,heights,dp);
    int op2 = INT_MAX;
    if(n>1){
        op2 = abs(heights[n] - heights[n-2]) + frogAbMemoised(n-2,heights,dp);
    }
	return dp[n] = min(op1,op2);
}

// Iterative -> Tabulation DP

int frogATabulated(int n,vector<int> &heights)
{
	vector<int> dp(n);
	dp[n-1] = 0;

	for(int i=n-2;i>=0;i--){
		int onejump = abs(heights[i]-heights[i+1]) + dp[i+1];
		int twojump = INT_MAX;
		if(i+2<n){
			twojump = abs(heights[i]-heights[i+2]) +dp[i+2];
		}

		dp[i] = min(onejump,twojump);
	}

	return dp[0];

}

int frogATabulated2(int n,vector<int> hieghts)
{
	vector<int> dp(n);
	dp[0] = 0;

	for(int i=1;i<n;i++)
	{
		int onejump = abs(hieghts[i]-hieghts[i-1]) + dp[i-1];
		int twojump =  INT_MAX;
		if(i-2>=0){
			twojump =  abs(hieghts[i]-hieghts[i-2]) + dp[i-2];
		}
		dp[i] = min(onejump,twojump);
	}

	return dp[n-1];
}


// Space Optimised Tabulation DP
int frogATabulatedSpaceOptimised(int n, vector<int> &hieghts)
{
	int curr = INT_MAX;
	int prev = 0;
	int prev2 = INT_MAX;	 
	for(int i=1;i<n;i++)
	{
		int onejump = abs(hieghts[i]-hieghts[i-1]) + prev;
		int twojump =  INT_MAX;
		if(i-2>=0){
			twojump =  abs(hieghts[i]-hieghts[i-2]) + prev2;
		}
		curr = min(onejump,twojump);
		prev2 = prev;
		prev = curr;
	}
	return prev;
}

void printPath(int n,vector<int> &heights)
{
	vector<int> dp(n);
	dp[0] = 0;

	for(int i=1;i<n;i++)
	{
		int onejump = abs(heights[i]-heights[i-1]) + dp[i-1];
		int twojump = INT_MAX;

		if(i-2>=0){
			twojump = abs(heights[i]-heights[i-2]) + dp[i-2];
		}

		dp[i] = min(onejump,twojump);
	}
    cout<<dp[n-1]<<"\n";
	int index = 0;
	cout<<index<<" ";

	while(index<n){
		if( dp[index] - abs(heights[index]-heights[index+1]) == dp[index+1]){
			index+=1;
		}
		else{
			index+=2;
		}
		cout<<index<<" ";
	}

}

int main()
{
	int n;
	cin>>n;

	vector<int> heights(n);
	// Dp for memoisation
	vector<int> dp(n,-1);

	for(int i=0;i<n;i++){
		cin>>heights[i];
	}
    string path = "";
	// frogA(0,n,0,path,heights);
 	// cout<<minCost;

    // frogAb(n-1,0,path,heights);
    // cout<<minCost;

    cout<<frogAMemoised(0,n,heights,jumps);
    cout<<"\n";
    cout<<frogAbMemoised(n-1,heights,dp);
    cout<<"\n";
    cout<<frogATabulated(n,heights);
    cout<<"\n";
    cout<<frogATabulated2(n,heights);
    cout<<"\n";
    cout<<frogATabulatedSpaceOptimised(n,heights);
    cout<<"\n";
    printPath(n,heights);






}