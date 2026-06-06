#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <stack>
#include <sstream>
#include <set>
#include <map>
using namespace std;
const long long MOD=1e9+7;
inline long long get_mod(long long x){
    return (x%MOD+MOD)%MOD;
}
struct Yixiang{

    map<long long,long long> xi_to_mi;//x0表示常数
    bool operator <(const Yixiang & other)const{
        if(this->xi_to_mi.size()!=other.xi_to_mi.size()){
            return this->xi_to_mi.size()<other.xi_to_mi.size();
        }
        auto it_this=this->xi_to_mi.begin(),it_other=other.xi_to_mi.begin();
        while(it_this!=xi_to_mi.end()){
            if(it_this->first!=it_other->first){
                return it_this->first<it_other->first;
            }
            if(it_this->second!=it_other->second){
                return it_this->second<it_other->second;
            }
            it_other++,it_this++;
        }
        return false;
    }
    Yixiang operator *(const Yixiang & other) const{
        Yixiang ans_yixiang;
        auto it_other=other.xi_to_mi.begin();
        while(it_other!=other.xi_to_mi.end()){
            ans_yixiang.xi_to_mi[it_other->first]+=it_other->second;
            it_other++;
        }
        auto it_this=this->xi_to_mi.begin();
        while(it_this!=this->xi_to_mi.end()){
            ans_yixiang.xi_to_mi[it_this->first]+=it_this->second;
            it_this++;
        }
        return ans_yixiang;
    }
};
struct Shizi{
    map<Yixiang,long long> xiang_to_xishu;
    Shizi operator + (const Shizi & other){
        auto it_other=other.xiang_to_xishu.begin();
        while(it_other!=other.xiang_to_xishu.end()){
            if(this->xiang_to_xishu.count(it_other->first)){
                this->xiang_to_xishu[it_other->first]=
                get_mod(this->xiang_to_xishu[it_other->first]+it_other->second);
            }
            else {
                this->xiang_to_xishu[it_other->first]=it_other->second;
            }
            it_other++;
        }
        return *this;
    }
    Shizi operator - (const Shizi & other){
        auto it_other=other.xiang_to_xishu.begin();
        while(it_other!=other.xiang_to_xishu.end()){
            if(this->xiang_to_xishu.count(it_other->first)){
                this->xiang_to_xishu[it_other->first]=
                get_mod(this->xiang_to_xishu[it_other->first]-it_other->second);
            }
            else {
                this->xiang_to_xishu[it_other->first]=-it_other->second;
            }
            it_other++;
        }

        return *this;
    }
    Shizi operator * (const Shizi & other){
        Shizi ans_shizi;
        auto it_this=this->xiang_to_xishu.begin();
        while(it_this!=this->xiang_to_xishu.end()){
            auto it_other=other.xiang_to_xishu.begin();
            while(it_other!=other.xiang_to_xishu.end()){
                Yixiang ans_xiang=(it_other->first)*(it_this->first);
                long ans_xishu=get_mod(it_other->second*it_this->second);
                ans_shizi.xiang_to_xishu[ans_xiang]=
                get_mod(ans_shizi.xiang_to_xishu[ans_xiang]+ans_xishu);
                it_other++;
            }
            it_this++;
        }
        return ans_shizi;
    }
};
long long get_power(long long base,long long exp){
    long long ans=1;
    while(exp){
        if(exp&1)ans=get_mod(ans*base);
        base=get_mod(base*base);
        exp>>1;
    }
    return ans;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n,m;cin>>n>>m;
    stack<Shizi> my_stack;
    string s;
    getline(cin,s);
    stringstream ss;
    ss.str(s);
    while(ss>>s){
        if(s[0]=='x'){
            int idx=stoi(s.substr(1));
            Yixiang temp_yixiang;
            temp_yixiang.xi_to_mi[idx]=1;
            Shizi temp_shizi;
            temp_shizi.xiang_to_xishu[temp_yixiang]=1;
            my_stack.push(temp_shizi);
        }
        else if(s.size()==1){
            auto right_shizi=my_stack.top();my_stack.pop();
            auto left_shizi=my_stack.top();my_stack.pop();
            Shizi new_shizi;
            if(s[0]=='+')new_shizi=left_shizi+right_shizi;
            else if(s[0]=='-')new_shizi=left_shizi-right_shizi;
            else if(s[0]=='*')new_shizi=left_shizi*right_shizi;
            my_stack.push(new_shizi);
        }
        else {
            long long temp_i=stoi(s);
            Yixiang temp_yixiang;
            temp_yixiang.xi_to_mi[0]=0;//x0的系数设置为0
            Shizi temp_shizi;
            temp_shizi.xiang_to_xishu[temp_yixiang]=temp_i;
            my_stack.push(temp_shizi);
        }
    }
    if(my_stack.size()!=1)cout<<"ERROR";
    Shizi fx=my_stack.top();
    long long a[101];
    while(m--){
        long long xi;
        cin>>xi;
        for (size_t i = 1; i <=n; i++)
        {
            cin>>a[i];
        }
        int ans=0;
        for(auto & xiang :fx.xiang_to_xishu){
            long long xishu=xiang.second;
            Yixiang yixiang=xiang.first;
            int temp_ans=xishu;
            if(yixiang.xi_to_mi.count(xi)==0)continue;
            else {
                temp_ans=get_mod(temp_ans*yixiang.xi_to_mi[xi]);
                for(auto & xi_and_mi :yixiang.xi_to_mi){
                    if(xi_and_mi.first==xi)
                    temp_ans=get_mod(temp_ans*get_power(a[xi],xi_and_mi.second-1));
                    else{
                        temp_ans=get_mod
                        (temp_ans*get_power(a[xi_and_mi.first],xi_and_mi.second));
                    }
                }
            }
            ans=get_mod(ans+temp_ans);
        }
        cout<<ans;
    }
    return 0;
}