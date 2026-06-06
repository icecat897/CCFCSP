#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <set>
#include <map>
#include <unordered_map>
using namespace std;
typedef long long ll;
vector<string> id_to_string;
unordered_map<string,ll> string_to_id;
ll get_id(string & s){
    if(string_to_id.count(s))return string_to_id[s];
    ll id=string_to_id.size();
    id_to_string.push_back(s);
    string_to_id[s]=id;
    return id;
}
struct word_pair
{
    ll id1,id2;
    long long times=0;
    bool operator >(const word_pair & other) const {//compare priority value
        if(this->times!=other.times){
            return this->times>other.times;
        }
        string s1=id_to_string[id1],s2=id_to_string[id2];
        string other_s1=id_to_string[other.id1],other_s2=id_to_string[other.id2];
        if(s1.size()+s2.size()!=other_s1.size()+other_s2.size()){
            return s1.size()+s2.size()<other_s1.size()+other_s2.size();
        }
        if(s1.size()!=other_s1.size()){
            return s1.size()<other_s1.size();
        }
        return (s1+s2)<(other_s1+other_s2);
    }
};
struct pair_string
{
    ll id1,id2;
    bool operator ==(const pair_string & other) const {
        return this->id1==other.id1&&this->id2==other.id2;
    }
    bool operator <(const pair_string & other) const {
        if(this->id1!=other.id1){
            return this->id1<other.id1;
        }
        else return this->id2<other.id2;
    }
};

const int MAXN=10001,MAXM=5001;
bool char_times[26];
int n,m;
list<ll> i_word[MAXN];
int i_word_show_times[MAXN]; 

void merge(pair_string & now_pair){
    ll id1=now_pair.id1,id2=now_pair.id2;
    for(int i=1;i<=n;i++){
        if(i_word[i].size()==1)continue;
        auto it=i_word[i].begin();
        while(next(it)!=i_word[i].end()){
            if(*it==id1&&*next(it)==id2){
                it=i_word[i].erase(it);
                it=i_word[i].erase(it);
                string new_word=id_to_string[id1]+id_to_string[id2];
                i_word[i].insert(it,get_id(new_word));
            }
            else {
                it++;
            }
        }
    }
}

pair_string find_string_pair(){
    bool flag=0;
    map<pair_string,long long> pair_to_times;
    for(int i=1;i<=n;i++){
        if(i_word[i].size()==1)continue;
        flag=true;
        auto it=i_word[i].begin();
        while (next(it)!=i_word[i].end())//统计所有次数
        {
            pair_string temp_pair_s={*it,*next(it)};
            pair_to_times[temp_pair_s]+=i_word_show_times[i];
            it++;
        }
    }
    if(flag==false){
        cout<<"ERROR at find_string_pair";
        pair_string s_lose={2,3};
        return s_lose;
    }
    bool find_first_flag=false;
    word_pair need_to_be_add;
    for(auto temp_map_p: pair_to_times){
        word_pair temp_word_pair={temp_map_p.first.id1,temp_map_p.first.id2,temp_map_p.second};
        if(!find_first_flag){
            find_first_flag=true;
            need_to_be_add=temp_word_pair;
            continue;
        }
        if(temp_word_pair>need_to_be_add){
            need_to_be_add=temp_word_pair;
        }
    }
    return pair_string({need_to_be_add.id1,need_to_be_add.id2});
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        string s;cin>>s;
        cin>>i_word_show_times[i];
        for(int j=0;j<int(s.size());j++){
            char_times[s[j]-'a']=true;
            string temp_s(1,s[j]);
            i_word[i].push_back(get_id(temp_s));
        }
    }
    int times=0;
    for(int i=0;i<26;i++){
        if(char_times[i]){
            times++;
            cout<<char(i+'a')<<'\n';
        }
    }
    m-=times;
    while(m--){
        pair_string now_know_pair_string=find_string_pair();
        cout<<id_to_string[now_know_pair_string.id1]+id_to_string[now_know_pair_string.id2]<<'\n';
        merge(now_know_pair_string);
    }
    return 0;
}