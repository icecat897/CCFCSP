#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <set>
#include <map>
using namespace std;
struct word_pair
{
    string s1,s2;
    long long times=0;
    bool operator >(const word_pair & other) const {//compare priority value
        if(this->times!=other.times){
            return this->times>other.times;
        }
        if(this->s1.size()+this->s2.size()!=other.s1.size()+other.s2.size()){
            return this->s1.size()+this->s2.size()<other.s1.size()+other.s2.size();
        }
        if(this->s1.size()!=other.s1.size()){
            return this->s1.size()<other.s1.size();
        }
        return (this->s1+this->s2)<(other.s1+other.s2);
    }
};
struct pair_string
{
    string s1,s2;
    bool operator ==(const pair_string & other) const {
        return this->s1==other.s1&&this->s2==other.s2;
    }
    bool operator <(const pair_string & other) const {
        if(this->s1!=other.s1){
            return this->s1<other.s1;
        }
        else return this->s2<other.s2;
    }
};

const int MAXN=10001,MAXM=5001;
bool char_times[26];
int n,m;
list<string> i_word[MAXN];
int i_word_show_times[MAXN]; 

void merge(pair_string & now_pair){
    string s1=now_pair.s1,s2=now_pair.s2;
    for(int i=1;i<=n;i++){
        if(i_word[i].size()==1)continue;
        auto it=i_word[i].begin();
        while(next(it)!=i_word[i].end()){
            if(*it==s1&&*next(it)==s2){
                it=i_word[i].erase(it);
                it=i_word[i].erase(it);
                i_word[i].insert(it,s1+s2);
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
        pair_string s_lose={"aka","loser"};
        return s_lose;
    }
    bool find_first_flag=false;
    word_pair need_to_be_add;
    for(auto temp_map_p: pair_to_times){
        word_pair temp_word_pair={temp_map_p.first.s1,temp_map_p.first.s2,temp_map_p.second};
        if(!find_first_flag){
            find_first_flag=true;
            need_to_be_add=temp_word_pair;
            continue;
        }
        if(temp_word_pair>need_to_be_add){
            need_to_be_add=temp_word_pair;
        }
    }
    return pair_string({need_to_be_add.s1,need_to_be_add.s2});
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        string s;cin>>s;
        cin>>i_word_show_times[i];
        for(int i=0;i<int(s.size());i++){
            char_times[s[i]-'a']=true;
            i_word[i].push_back(string(1,s[i]));
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
        cout<<now_know_pair_string.s1+now_know_pair_string.s2;
        merge(now_know_pair_string);
    }
    return 0;
}
