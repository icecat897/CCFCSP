#include<iostream>
#include<vector>
using namespace std;
const long long MOD=998244353;
int jinghao[1000001];
int n,m;
vector<int> my_choice;
long long ans=0;
inline long long get_power(int exp){
    int base=26,ans=1;
    while(exp){
        if(exp&1)ans=ans*base%MOD;
        base=base*base%MOD;
        exp>>=1;
    }
    return ans;
}
void  cal(int pos,int next_jinghao){
    //cout<<pos<<" "<<next_jinghao<<'\n';
    if(pos>n){
        int first3=n+1;int last6=-1;
        int total_decide=m;
        for(int i=0;i<int(my_choice.size());i++){
            if(my_choice[i]==3){
                first3=i;
                break;
            }
        }
        for(int i=int(my_choice.size()-1);i>=0;i--){
            if(my_choice[i]==6){
                last6=i;
                break;
            }
        }
        if(first3>last6)return;
        for(int i=0;i<int(my_choice.size());i++){
            total_decide+=my_choice[i];
        }
        //cout<<"find!";
        ans=ans+get_power(n-total_decide);
        return;
    }
    if(jinghao[next_jinghao]==pos){
        cal(pos+1,next_jinghao+1);
    }
    int left_length=jinghao[next_jinghao]-pos;
    if(left_length>=6){
        my_choice.push_back(6);
        cal(pos+6,next_jinghao);
        my_choice.pop_back();
    }
    if(left_length>=3){
        my_choice.push_back(3);
        cal(pos+3,next_jinghao);
        my_choice.pop_back();
    }
    if(left_length>0){
        cal(pos+1,next_jinghao);
    }
}
int main(){
    cin>>n>>m;
    for(int i=1;i<=m;i++)cin>>jinghao[i];
    jinghao[m+1]=n+1;
    cal(1,1);
    cout<<ans;
}