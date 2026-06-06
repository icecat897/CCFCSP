#include<iostream>
#include<vector>
#include<cstring>
#include<map>
using namespace std;
bool char_list[26];
bool my_greater(string s1,int t1,int b1,string s2,int t2,int b2){
    if(t1>t2)return true;
    else if(t1==t2){
        if(s1.size()<s2.size())return true;
        else if(s1.size()==s2.size()){
            if(t1<t2)return true;
            else if(t1==t2){
                return s1<s2;
            }
        }
    }
    return false;
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n,m;cin>>n>>m;
    vector<string> string_list(n);
    vector<int> times(n);
    vector<vector<string>> old_string(n);
    vector<string> word_list;
    for(int i=0;i<n;i++)cin>>string_list[i]>>times[i];
    int num_of_char=0;
    for(int i=0;i<n;i++){
        for(int j=0;j<string_list[i].size();j++){
            string s;
            old_string[i].push_back(s+string_list[i][j]);
            if(!char_list[string_list[i][j]-'a']){
                char_list[string_list[i][j]-'a']=true;
                num_of_char++;
            }
        }
    }
    for(int i=0;i<26;i++){
        if(char_list[i])cout<<char(i+'a')<<'\n';
    }
    int now_word=num_of_char;
    map<string,int> cut_times;
    map<string,int> pri_lengths;
    while(now_word<m){
        vector<vector<string>> new_string(n);
        for(int i=0;i<n;i++){
            if(old_string[i].size()==1){
                cut_times[old_string[i][0]]+=times[i];
                continue;
            }
            for(int j=0;j<old_string[i].size()-1;j++){
                string new_cut=old_string[i][j]+old_string[i][j+1];
                cut_times[new_cut]+=times[i];
                pri_lengths[new_cut]=old_string[i][j].length();
            }
        }
        int before_length=26;
        int max_times=-1;
        string decide_string(26,'z');
        for(pair<string,int> my_pair:cut_times){
            if(my_greater(my_pair.first,my_pair.second,pri_lengths[my_pair.first],
            decide_string,max_times,before_length)){
                max_times=my_pair.second;
                decide_string=my_pair.first;
            }
        }
        word_list.push_back(decide_string);
        now_word++;
        for(int i=0;i<n;i++){
            if(old_string[i].size()==1){
                new_string[i].push_back(old_string[i][0]);
                continue;
            }
            for(int j=0;j<old_string[i].size()-1;j++){
                string new_cut=old_string[i][j]+old_string[i][j+1];
                if(new_cut==decide_string){
                     new_string[i].push_back(decide_string);
                     j++;
                }
                else{
                     new_string[i].push_back(old_string[i][j]);
                     if(j==old_string[i].size()-2)
                     new_string[i].push_back(old_string[i][j+1]);
                }
            }
        }
        old_string=new_string;
        cut_times.clear();
    }
    for(auto s:word_list)cout<<s<<'\n';
}