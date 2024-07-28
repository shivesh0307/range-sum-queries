// Program to show segment tree to demonstrate lazy
// propagation
#include<bits/stdc++.h>
using namespace std;
#define MAX 800000+5
#define ll long long
ll tree[MAX] = {0}; 
ll lazy[MAX] = {0};
 
void updateRangeUtil(int si, int ss, int se, int us,
					int ue, int diff)
{
	if (lazy[si] != 0)
	{
		tree[si] += (se-ss+1)*lazy[si];
 
		if (ss != se)
		{
			lazy[si*2 + 1] += lazy[si];
			lazy[si*2 + 2] += lazy[si];
		}
 
		lazy[si] = 0;
	}
 
	//no overlap
	if (ss>se || ss>ue || se<us)
		return ;
 
	// full overlap
	if (ss>=us && se<=ue)
	{
		tree[si] += (se-ss+1)*diff;
		if (ss != se)
		{
			lazy[si*2 + 1] += diff;
			lazy[si*2 + 2] += diff;
		}
		return;
	}
 
    //partial overlap
	int mid = (ss+se)/2;
	updateRangeUtil(si*2+1, ss, mid, us, ue, diff);
	updateRangeUtil(si*2+2, mid+1, se, us, ue, diff);
	tree[si] = tree[si*2+1] + tree[si*2+2];
}
 
void updateRange(int n, int us, int ue, int diff)
{
updateRangeUtil(0, 0, n-1, us, ue, diff);
}
 
ll getSumUtil(int ss, int se, int qs, int qe, int si)
{
 
	/*if (lazy[si] != 0)
	{
		tree[si] += (se-ss+1)*lazy[si];
 
		if (ss != se)
		{
			lazy[si*2+1] += lazy[si];
			lazy[si*2+2] += lazy[si];
		}
		lazy[si] = 0;
	}*/
 
	// No overlap
	if (ss>se || ss>qe || se<qs)
		return 0;
 
    //full overlap
	if (ss>=qs && se<=qe)
		return tree[si];
 
	//partial overlap
	int mid = (ss + se)/2;
	return getSumUtil(ss, mid, qs, qe, 2*si+1) ^
		getSumUtil(mid+1, se, qs, qe, 2*si+2);
}
ll getSum(int n, int qs, int qe)
{
	if (qs < 0 || qe > n-1 || qs > qe)
	{
		cout <<"Invalid Input";
		return -1;
	}
 
	return getSumUtil(0, n-1, qs, qe, 0);
}
 
 
void constructSTUtil(int arr[], int ss, int se, int si)
{
		if (ss > se)
		return ;
 
	if (ss == se)
	{
		tree[si] = arr[ss];
		return;
	}
 
	int mid = (ss + se)/2;
	constructSTUtil(arr, ss, mid, si*2+1);
	constructSTUtil(arr, mid+1, se, si*2+2);
 
	tree[si] = tree[si*2 + 1] ^ tree[si*2 + 2];
}
 
void constructST(int arr[], int n)
{
	constructSTUtil(arr, 0, n-1, 0);
}
 
int solve()
{
    int n , q; cin>>n>>q;
    int arr[n];
    for(int i=0;i<n;i++) cin>>arr[i];
    constructST(arr,n);
    while(q--)
    {
        int a,b; cin>>a>>b;
        a--; b--;
        cout<<getSum(n,a,b)<<"\n";
    }
    return 0 ;
}
int main()
{
	solve();
 
	return 0;
}
