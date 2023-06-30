#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;


int var(int i, int j, int n) // ith position, jth node
{
    return (i-1)*n + j;
}

int main() {
    ios::sync_with_stdio(false);

    int n, m;
    cin >> n >> m;
    vector<vector<int>> clauses;
    map<pair<int, int>, bool> visit;
    vector<vector<int>> adj(n+1);
    // Preprocessing graph.
    for(int i=0; i<m;i++)
    {
        int u, v; cin >> u >> v;
        if(!visit[{u, v}])
        {
            visit[{u, v}] = true;
            visit[{v, u}] = true;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
    }
    // all pos contains atleast one node. It will ensure that none of the positions are empty.
    for(int i=1; i<=n; i++)
    {
        vector<int> temp;
        for(int j = 1; j<=n; j++)
        {
            temp.push_back(var(i, j, n));
        }
        clauses.push_back(temp);
    }
    // each pos contains atmost one node.  It ensures that each position contains exactly node.
    for(int i=1; i<=n; i++)
    {
        for(int j=1; j<=n; j++){
            for(int k=j+1; k<=n; k++)
            {
                vector<int> temp;
                temp.push_back(-1*var(i, j, n));
                temp.push_back(-1*var(i, k, n));
                clauses.push_back(temp);
            }
        }
    }
    // all node occur exactly once in path. 
    for(int j=1; j<=n ;j++)
    {
        for(int i=1; i<=n ;i++)
        {
            for(int k= i+1; k<=n; k++)
            {
                vector<int> temp;
                temp.push_back(-1*var(i, j, n));
                temp.push_back(-1*var(k, j, n));
                clauses.push_back(temp);
            }
        }
    }
    // non adjacent node j and k can't be in the adjacent path.
    for(int i=1; i<n; i++)
    {
        for(int j=1; j<=n; j++)
        {
            for(int k = 1; k<=n; k++)
            {
                if(k!=j)
                {
                    auto it = find(adj[j].begin(), adj[j].end(), k);
                    if(it==adj[j].end())
                    {
                        vector<int> temp;
                        temp.push_back(-1*var(i, j, n));
                        temp.push_back(-1*var(i+1, k, n));
                        clauses.push_back(temp);
                    }
                }
            }
        }
    }
    
    std::cout << clauses.size() << " " << n*n << endl;
    for(auto clause : clauses)
    {
        for(auto literal: clause) std::cout << literal << " ";
        std::cout << "0\n";
    }
    return 0;
}
