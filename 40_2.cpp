#include<iostream>
using namespace std;
const int MAXN=5e5+13,MAXM=1e3+7;
int a[MAXN],k[MAXM];
int my_map[(1<<9)+10];
int n,m;
inline int f(int x,int k){
    return ((x*x+k*k)%(1<<3))^k;
}
inline int g(int x,int k){
    int a,b,c;
    a=x/(1<<6);
    c=x%(1<<3);
    b=(x/(1<<3))%(1<<3);
    int ans=b;
    ans=(ans<<3);
    ans+=(c^f(b,k));
    ans=(ans<<3);
    ans+=(a^f(c,k));
    return ans;
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        cin>>k[i];
    }
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    for(int i=0;i<(1<<9);i++){
        int temp=i;
        for(int j=1;j<=m;j++){
            temp=g(temp,k[j]);
        }
        my_map[temp]=i;
    }
    for(int i=1;i<=n;i++){
        cout<<my_map[a[i]]<<" ";
    }
}