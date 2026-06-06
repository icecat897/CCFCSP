#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <unordered_map>
using namespace std;
const int MAXN=2001;
bool is_deleted[MAXN];
int fa[MAXN];
vector<int> adj[MAXN];
unordered_map<int,bool> is_son[MAXN];
long long w[MAXN];
int n,m;
long long total;
long long my_index[MAXN];
long long min_idx=1e15;
int min_number;
int visited_num=0;
long long son_and_his_w[MAXN];//表明他与他的子树都被删掉了
void add_son(int root){
    for(int & son :adj[root]){
        add_son(son);
        for(auto  son_son :is_son[son]){
            is_son[root][son_son.first]=true;
        }
    }
}
void dfs(int root){
    visited_num++;
    total+=w[root];
    son_and_his_w[root]+=w[root];
    for(int & son:adj[root]){
        if(is_deleted[son])continue;
        dfs(son);
        son_and_his_w[root]+=son_and_his_w[son];
    }
}
void count_idx(int root){
    my_index[root]=abs(total-(son_and_his_w[root]<<1));
    if(my_index[root]<min_idx||(my_index[root]==min_idx&&root<min_number))
    min_idx=my_index[root],min_number=root;
    for(int & son:adj[root]){
        if(is_deleted[son]==true)continue;
        count_idx(son);
    }
}
void process(int x){
    memset(is_deleted,0,sizeof(is_deleted));
    int root=1;
    int round=1;
    while(true){
        //getchar();
        memset(son_and_his_w,0,sizeof(son_and_his_w));
        total=0;
        min_idx=1e15;
        visited_num=0;
        // cout<<"round "<<round++<<'\n';
        // cout<<"the root is "<<root<<'\n';
        dfs(root);
        //cout<<"the visited_num is "<<visited_num<<'\n';
        if(visited_num==1)break;
        count_idx(root);
        //for(int i=1;i<=n;i++)cout<<son_and_his_w[i]<<' ';
        //cout<<'\n';
        //for(int i=1;i<=n;i++)cout<<index[i]<<' ';
        //cout<<'\n';
        //cout<<"the min number is "<<min_number<<'\n';
        cout<<min_number<<' ';
        if(is_son[min_number].count(x)){
            root=min_number;
            //cout<<"find\n";
        }
        else {
            //cout<<"no"<<'\n';
            is_deleted[min_number]=true;
        }
        //cout<<'\n'<<'\n'<<'\n';
    }
    cout<<'\n';
}
int main() {
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);
    cin>>n>>m;
    for(int i=1;i<=n;i++)cin>>w[i];
    is_son[1][1]=true;
    for(int i=2;i<=n;i++){
        int fa;cin>>fa;
        adj[fa].push_back(i);
        is_son[fa][i]=true;
        is_son[i][i]=true;
    }
    add_son(1);
    for(int i=1;i<=m;i++){
        //cout<<i<<i<<i<<i<<i<<i<<'\n';
        int find_node;
        cin>>find_node;
        process(find_node);
        //cout<<'\n';
    }
    return 0;
}