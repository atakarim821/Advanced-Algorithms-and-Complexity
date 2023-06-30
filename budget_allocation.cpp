#include <ios>
#include <iostream>
#include <vector>

using namespace std;

int var(int i, int n, int q)
{ // node, number of node, quotient
    return n*q + i;
}
int main(){
    ios::sync_with_stdio(false);

    int n, m;
    cin >> n >> m;
    
    vector<bool> visited(n+1, false);
    vector<vector<int>> clause;
    for(int i=0; i<m; i++)
    {
        int u , v;
        cin >> u >> v;
        vector<int> temp;
        temp.clear();
        if(!visited[u]){
            temp.push_back(var(u, n, 0));
            temp.push_back(var(u, n, 1));
            temp.push_back(var(u, n, 2));
            clause.push_back(temp);
            temp.clear();
            visited[u] = true;
        }
        if(!visited[v]){
            temp.push_back(var(v, n, 0));
            temp.push_back(var(v, n, 1));
            temp.push_back(var(v, n, 2));
            clause.push_back(temp);
            temp.clear();
            visited[v] = true;
        }
        temp.push_back(-1*var(u, n, 0));
        temp.push_back(-1*var(v, n, 0));
        clause.push_back(temp);
        temp.clear();
        temp.push_back(-1*var(u, n, 1));
        temp.push_back(-1*var(v, n, 1));
        clause.push_back(temp);
        temp.clear();
        temp.push_back(-1*var(u, n, 2));
        temp.push_back(-1*var(v, n, 2));
        clause.push_back(temp);
        temp.clear();
    }
    cout << clause.size() << " " << 3*n << endl;
    for(auto ele : clause)
    {
        for(auto literal: ele)
        {
            cout << literal << " ";
        }
        cout << "0\n";
    }
    return 0;
}
