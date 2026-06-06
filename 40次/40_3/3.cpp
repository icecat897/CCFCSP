#include<iostream>
#include<vector>
#include<stack>
using namespace std;
char photo[401][401];
char temp_grid[401][401];
int z;
struct Reverse_order{
    int u,d,l,r,o;
};
struct Rotate_order{
    int u,v,l,d,r;
};
int big_photo_state=0;//indicate the degree of the whole photo has been rotate(clockwise)
pair<int,int> get_true_pos(int x,int y){
    if(big_photo_state==0)return {x,y};
    else if(big_photo_state==90){
        return {z-y+1,x}; 
    }
    else if(big_photo_state==180){
        return {z-x+1,z-y+1};
    }
    else if(big_photo_state==270){
        return {y,z-x+1};
    }
    else {cout<<"ERROR at get_true_photo";return {x,y};}
}
void process_order(Reverse_order & order){
    //cout<<"in process_order reverse_order"<<'\n';
    if(order.o==1){
        int i=order.u,j=order.d;
        while(i<j){
            for(int k=order.l;k<=order.r;k++){
                pair<int,int> pos1=get_true_pos(i,k),pos2=get_true_pos(j,k);
                swap(photo[pos1.first][pos1.second],photo[pos2.first][pos2.second]);
            }
            i++,j--;
        }
    }
    else {
        int i=order.l,j=order.r;
        while (i<j)
        {
            for(int k=order.u;k<=order.d;k++){
                pair<int,int> pos1=get_true_pos(k,i),pos2=get_true_pos(k,j);
                swap(photo[pos1.first][pos1.second],photo[pos2.first][pos2.second]);
            }
            i++,j--;
        }
    }
    return ;
}
void rotate(int u,int v,int length,bool dir,int degree){//dir==1顺时针,dir==0逆时针
    //cout<<"in rotate"<<'\n';
    if(u==1&&v==1&&length==z){
        if(dir==1)big_photo_state=((big_photo_state+degree)%360+360)%360;
        else big_photo_state=((big_photo_state-degree)%360+360)%360;
        return ;
    }
    degree=(degree%360+360)%360;
    if(degree==270){
        rotate(u,v,length,!dir,90);
        return ;
    }
    else if(degree==0){
        return ;
    }
    else if(degree==90){
        if(dir==1){
            for(int i=0;i<length;i++){
                for(int j=0;j<length;j++){
                    pair<int,int> pos2=get_true_pos(u+i,v+j);
                    temp_grid[j][length-1-i]=photo[pos2.first][pos2.second];
                }
            }
        }
        if(dir==0){
            for(int i=0;i<length;i++){
                for(int j=0;j<length;j++){
                    pair<int,int> pos2=get_true_pos(u+i,v+j);
                    temp_grid[length-1-j][i]=photo[pos2.first][pos2.second];
                }
            }
        }
        for(int i=0;i<length;i++){
            for(int j=0;j<length;j++){
                pair<int,int> pos2=get_true_pos(u+i,v+j);
                photo[pos2.first][pos2.second]=temp_grid[i][j];
            }
        }
    }
    else if(degree==180){
        rotate(u,v,length,dir,90);
        rotate(u,v,length,dir,90);
    }
    else {
        cout<<"ERROR at rotate";
        return ;
    }
}
void process_order(Rotate_order & order){
    //cout<<"in process_order Rotate_order"<<'\n';
    rotate(1,1,z,1,order.r*90);
    rotate(order.u,order.v,order.l,0,order.d);
    return ;
}
void print_whole_photo(){
    for(int i=1;i<=z;i++){
        for(int j=1;j<=z;j++){
            pair<int ,int> pos=get_true_pos(i,j);
            cout<<photo[pos.first][pos.second];
        }
        cout<<"\n";
    }
    cout<<'\n';
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>z;
    for(int i=1;i<=z;i++){
        for(int j=1;j<=z;j++){
            cin>>photo[i][j];
        }
    }
    int k;cin>>k;
    int t;cin>>t;
    vector<int> order(t+1);
    stack<Reverse_order> reverse_order_stack_r;
    stack<Rotate_order> rotate_order_stack_r;
    for(int i=1;i<=t;i++){
        cin>>order[i];
        if(order[i]==2){
            int u,d,l,r,o;
            cin>>u>>d>>l>>r>>o;
            Reverse_order now_order={u,d,l,r,o};
            //Reverse_order inv_order=get_inverse(now_order);
            reverse_order_stack_r.push(now_order);
        }
        else if(order[i]==1){
            int u,v,l,d,r;
            cin>>u>>v>>l>>d>>r;
            Rotate_order now_order={u,v,l,d,r};
            //Rotate_order inv_order=get_inverse(now_order);
            rotate_order_stack_r.push(now_order);
        }
        else {
            cout<<"id="<<order[i]<<'\n';
            cout<<"ERROR at input order";
            return 0;
        }
    }
    for(int i=t;i>=1;i--){
        if(order[i]==1){
            Rotate_order now_order=rotate_order_stack_r.top();
            rotate_order_stack_r.pop();
            process_order(now_order);
        }
        else {
            Reverse_order now_order=reverse_order_stack_r.top();
            reverse_order_stack_r.pop();
            process_order(now_order);
        }
        //cout<<big_photo_state<<'\n';
        // if(order[i]==1)cout<<"rotate"<<'\n';
        // else cout<<"reverse"<<"\n";
        // print_whole_photo();
    }
    int n=z,m=z;
    for(int  i=1;i<=z;i++){
        pair<int,int> pos=get_true_pos(i,1);
        if(photo[pos.first][pos.second]=='?'){
            n=i-1;
            break;
        }
    }
    for(int i=1;i<=z;i++){
        pair<int,int> pos=get_true_pos(1,i);
        if(photo[pos.first][pos.second]=='?'){
            m=i-1;
            break;
        }
    }
    //print_whole_photo();
    cout<<n<<' '<<m<<'\n';
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            pair<int,int> pos=get_true_pos(i,j);
            cout<<photo[pos.first][pos.second];
        }
        cout<<'\n';
    }
}