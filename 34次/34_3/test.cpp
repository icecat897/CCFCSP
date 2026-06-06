#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include<list>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    list<int> my_list={1,2,3,4,5};
    auto it=my_list.begin();
    while (it!=my_list.end())
    {
        if(*it==2){
            it=my_list.erase(it);
            it=my_list.erase(it);
            cout<<*it;
        }
        else it++;
    }
    
    return 0;
}