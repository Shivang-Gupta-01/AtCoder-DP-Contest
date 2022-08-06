#include<bits/stdc++.h>
using namespace std;
int minCost = INT_MAX;
void frogBRecursive(int index,int n,int k,int cost,string path,vector<int> &heights)
{

	if(index==n-1)
	{
        // cout<<path<<" "<<cost<<" "<<minCost<<"\n";
		minCost = min(cost,minCost);
		return;
	}

	for(int i=1;i<=k;i++)
	{
		if(index+i<n){
			frogBRecursive(index+i,n,k,cost + abs(heights[index+i]-heights[index]),path+to_string(index),heights);
		}
	}
}

void frogBRecursiveBottomUp(int n,int k,int cost,vector<int> &heights)
{
    if(n==0)
    {
        minCost = min(cost,minCost);
    }

    for(int i=1;i<=k;i++)
    {
        if(n-i>=0)
        {
            frogBRecursiveBottomUp(n-i,k,cost + abs(heights[n-i]-heights[n]) , heights);
        }
    }
}


int frogBMemoised(int index,int n,int k,vector<int> &heights,vector<int> &dp)
{
    if(index==n-1)
	{
		return 0;
	}
    if(dp[index]!=-1){
        return dp[index];
    }
    int cost = INT_MAX;
	for(int i=1;i<=k;i++)
	{
		if(index+i<n){
			cost = min(cost,abs(heights[index+i]-heights[index]) + frogBMemoised(index+i,n,k,heights,dp));
		}
	}
    return dp[index] = cost;
}

int frogBMemoisedBottomUp(int n,int k,vector<int> &heights,vector<int> &dp)
{
	if(n==0)
	{
		return dp[0] = 0;
	}
	if(dp[n]!=-1){
		return dp[n];
	}
	int cost = INT_MAX;
	for(int i=1;i<=k;i++)
	{
        // cout<<i<<"\n";
		if(n-i>=0)
		{

			cost = min(cost,abs(heights[n-i] - heights[n]) + frogBMemoisedBottomUp(n-i,k,heights,dp));
            // cout<<cost<<" "<<n<<" "<<n-i<<"\n";
		}
		
	}
	return dp[n] = cost;
}

int frogBTabulatedTD(int n,int k,vector<int> &heights)
{
	vector<int> dp(n,0);

	for(int i=1;i<n;i++)
	{
		int cost = INT_MAX;
		for(int j=1;j<=k;j++)
		{
			if(i-j>=0){
				cost = min(cost,abs(heights[i-j]-heights[i]) + dp[i-j]);
			}
		}
		dp[i] = cost;
	}

	return dp[n-1];
}
int frogBTabulatedBU(int n,int k,vector<int> &heights)
{
	vector<int> dp(n,0);

	for(int i=n-2;i>=0;i--)
    {
        int cost = INT_MAX;
        for(int j=1;j<=k;j++){
            if(i+j<n)
            {
                cost = min(cost,abs(heights[i+j]-heights[i]) + dp[i+j]);
            }
        }
        dp[i] = cost;
    }
    return dp[0];
}

int main()
{

	int n,k;
	cin>>n>>k;
	vector<int> heights(n);
	vector<int> dp(n,-1);
	for(int i=0;i<n;i++){
		cin>>heights[i];
	}
	int cost = 0;
    string path ;
	// frogBRecursive(0,n,k,cost,path,heights);
    // frogBRecursiveBottomUp(n,k,cost,heights);
    cout<<frogBMemoised(0,n,k,heights,dp);
	// cout<<minCost;

}