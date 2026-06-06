#include<iostream>
using namespace std;
const int MAXN=10001,MAXM=101,MAX_SIZE=1001;
int a[MAXN];
int s[MAXM][MAX_SIZE],t[MAXM][MAX_SIZE];
int n,m;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>n>>m;
    for(int i=1;i<=n;i++)cin>>a[i];
    for(int i=1;i<=m;i++){
        cin>>s[i][0];
        for(int j=1;j<=s[i][0];j++){
            cin>>s[i][j];
        }
    }
    for(int i=1;i<=m;i++){
        cin>>t[i][0];
        for(int j=1;j<=t[i][0];j++){
            cin>>t[i][j];
        }
    }
    for(int i=1;i<=m;i++){
        bool flag_same=true,flag_check_ok;
        if(s[i][0]!=t[i][0])flag_same=false;
        if(flag_same){
            for(int j=1;j<=s[i][0];j++){
                if(s[i][j]!=t[i][j]){
                    flag_same=false;
                    break;
                }
            }
        }
        int ans_s=0,ans_t=0;
        for(int j=1;j<=s[i][0];j++){
            ans_s^=a[s[i][j]];
        }
        for(int j=1;j<=t[i][0];j++){
            ans_t^=a[t[i][j]];
        }
        flag_check_ok=(ans_s==ans_t);
        if(flag_check_ok^flag_same){
            cout<<"wrong\n";
        }
        else cout<<"correct\n";
    }
}