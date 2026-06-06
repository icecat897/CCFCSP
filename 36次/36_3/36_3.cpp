#include<iostream>
#include<list>
#include<vector>
#include<map>
using namespace std;
struct state
{
    bool should_be_write;// need to be write(==1),else ==0;
    long long pos;// memo id;    
};
const int MAXN=65540;
int cache_size[MAXN];
list<state> cache[MAXN];//队首最新，队尾最旧
map<long long,decltype(cache[0].begin())> group_pos_map[MAXN];
int n,N;
inline int get_memo_group(long long & pos){
    return (pos/n)%N;
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int q;cin>>n>>N>>q;
    while(q--){
        bool  io_order;//==0 means read, ==1 means write;
        long long pos;
        cin>>io_order>>pos;
        int memo_group=get_memo_group(pos);
        if(group_pos_map[memo_group].count(pos)){//命中
            auto it=group_pos_map[memo_group][pos];
            if(io_order==1){//需要写
                it->should_be_write=1;
            }
            //移动到队首
            cache[memo_group].splice(cache[memo_group].begin(),cache[memo_group],it);
        }
        else {//没有命中
            if(cache_size[memo_group]<n){//没满
                //获取pos到cache迭代器的映射
                //push 当前缓存行的状态
                cache[memo_group].push_front({io_order,pos});
                group_pos_map[memo_group][pos]=cache[memo_group].begin();
                cache_size[memo_group]++;
                cout<<0<<' '<<pos<<'\n';
            }       
            else if(cache_size[memo_group]==n){//满了
                auto it=cache[memo_group].rbegin();
                if(it->should_be_write==1){
                    cout<<1<<' '<<it->pos<<'\n';
                }
                cache[memo_group].pop_back();
                cache[memo_group].push_front({io_order,pos});
                cout<<0<<' '<<pos<<'\n';
            }
            else {
                cout<<"ERROT AT MISSING";
            }
        }
        cout<<"now ";
        if(io_order==1)cout<<"write ";
        else cout<<"read ";
        cout<<pos<<" pos\n";
        cout<<"now memo_group is "<<memo_group<<'\n';
        for(auto & s:cache[memo_group]){
            cout<<s.pos<<' '<<s.should_be_write<<'\n';
         }
        cout<<"------------------\n";
    }
}