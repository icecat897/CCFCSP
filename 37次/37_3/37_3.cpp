#include<iostream>
#include<vector>
#include<map>
#include<unordered_map>
#include<sstream>
using namespace std;
const long long MOD=1000000007ll;
struct Val
{
    int flag=1;//1 means has been figure out,2 means it is changed
    vector<string> cal;// for 2
    long long has_been_know_length=0;
};
unordered_map<string,long long> memo;
unordered_map<string,Val> my_map;
long long count_length(string s){
    if(memo.count(s))return memo[s];
    Val & now_val=my_map[s];
    if(now_val.flag==1)return memo[s]=now_val.has_been_know_length;
    else {
        long long ans=now_val.has_been_know_length;
        for(string son_s :now_val.cal){
            ans=(ans+count_length(son_s))%MOD;
        }
        return memo[s]=ans;   
    }
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;cin>>n;
    stringstream ss;
    while(n--){
        memo.clear();
        ss.str("");
        ss.clear();
        int id;cin>>id;
        cin.ignore();
        string input;
        getline(cin,input);
        ss.str(input);
        //cout<<input<<'\n';
        //cout<<"-------------------------------\n";
        if(id==1){
            Val temp_val;
            string now_word;
            ss>>now_word;
            string son_string;
            while(ss>>son_string){
                if(son_string.front()!='$'){
                    temp_val.has_been_know_length=
                    (temp_val.has_been_know_length+son_string.size())%MOD;
                }
                else {
                    son_string=son_string.substr(1);
                    temp_val.has_been_know_length=
                    (temp_val.has_been_know_length+count_length(son_string))%MOD;
                }
            }
            my_map[now_word]=temp_val;
        }
        else if(id==2){
            string now_word;
            ss>>now_word;
            string son_string;
            Val temp_val;
            temp_val.flag=2;
            while(ss>>son_string){
                if(son_string.front()!='$'){
                    temp_val.has_been_know_length=
                    (temp_val.has_been_know_length+son_string.size())%MOD;
                }
                else {
                    son_string=son_string.substr(1);
                    temp_val.cal.push_back(son_string);
                }
            }
            my_map[now_word]=temp_val;
        }
        else if(id==3){
            string now_word;
            ss>>now_word;
            cout<<count_length(now_word)<<'\n';
        }
        else {
            cout<<"ERROR at get id";
        }
    }
}