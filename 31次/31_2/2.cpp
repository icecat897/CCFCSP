#include<iostream>
#include<vector>
#include<cmath>
#include<iomanip>
using namespace std;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n,m;cin>>n>>m;
    vector<double> stretch(1,1);
    vector<double> rotation(1,0);
    for(int i=1;i<=n;i++){
        int idx;cin>>idx;
        double x;cin>>x;
        if(idx==1){
            stretch.push_back(stretch[i-1]*x);
            rotation.push_back(rotation[i-1]);
        }
        if(idx==2){
            rotation.push_back(rotation[i-1]+x);
            stretch.push_back(stretch[i-1]);
        }
    }
    // cout<<"\n\n\n\n\n";
    // for(int i=1;i<=n;i++)cout<<stretch[i]<<" "<<rotation[i]<<'\n';
    // cout<<"\n\n\n\n\n";
    while(m--){
        int i,j;cin>>i>>j;
        double x,y;cin>>x>>y;
        double k=stretch[j]/stretch[i-1];
        double zita=rotation[j]-rotation[i-1];
        double changed_x,changed_y;
        changed_x=x*cos(zita)-y*sin(zita);
        changed_y=x*sin(zita)+y*cos(zita);
        changed_x*=k;
        changed_y*=k;
        cout<<fixed<<setprecision(3)<<changed_x<<' '<<changed_y<<'\n';
    }
}