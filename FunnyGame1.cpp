/*************************************************************************
  > File Name   : FunnyGame1.cpp
  > Author      : liudy
  > Mail        : 787896130@qq.com
  > Created Time: 2016年08月04日 星期四 10时02分04秒
 ************************************************************************/

#include<iostream>
#include<list>
using namespace std;

list<int>Map[1005];
bool SG[1005], visited[1005];
int leaf[1005];     //当leaf[i]等于1是表示其为叶子节点,但要注意当起始airport只连接一个airport时其leaf = 1, 所以要排除这种情况 
void SetSG(int node, int start){
    //排除起始airport 为叶子的情况
    if(leaf[node] == 1 && node != start){
        SG[node] = false;
        return;
    }
    SG[node] = false;
    visited[node] = true;
    for(list<int>::iterator it = Map[node].begin(); it != Map[node].end(); it++){
        if(!visited[*it]){
            SetSG(*it, start);
            if(!SG[*it])
                SG[node] = true;
        }

    }
}
void PrintAns(int start){
    int ans = 99999;
    if(!SG[start]){
        cout << "First player loses" << endl;
        return;
    }else
        for(list<int>::iterator it = Map[start].begin(); it != Map[start].end(); it++){
            if(!SG[*it] && *it < ans){
                ans = *it;
            }
        }
    cout << "First player wins flying to airport " << ans << endl;
}
int main(){
    int n, k;
    cin >> n >> k;
    for(int i = 1; i < n; i++){
        int n1, n2;
        cin >> n1 >> n2;
        Map[n1].push_back(n2);
        Map[n2].push_back(n1);
        leaf[n1]++;
        leaf[n2]++;
    } 
    SetSG(k, k);
    PrintAns(k);
    return 0;
}

