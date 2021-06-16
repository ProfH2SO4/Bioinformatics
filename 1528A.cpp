/*
 * @author ProfH2SO4
 * Task: https://codeforces.com/contest/1528/problem/A
 * hint: when you want to use cin https://www.geeksforgeeks.org/fast-io-for-competitive-programming/
 *
 */
#include <bits/stdc++.h>
using namespace std;

#define N 100005



// find beautiful number on edge  lv, rv
void find_max(long long lv, long long rv, long long lu, long long ru, long long start_node, long long end_node,
              long long node_beauty[2][N]){
    node_beauty[0][start_node] +=  max(abs(lv - lu) + node_beauty[0][end_node],
                                       abs(lv - ru) +  node_beauty[1][end_node]);
    node_beauty[1][start_node] +=  max(abs(rv - lu) + node_beauty[0][end_node],
                                       abs(rv - ru) +  node_beauty[1][end_node]);
}

struct graph_info{
    long long node_values[2][N];
    int visited[N] = {0};
    long long node_beauty[2][N];
};

void dfs(int start_node, vector<int> edges[N], struct graph_info * structgraphInfo){
    structgraphInfo->visited[start_node] = true;
    structgraphInfo->node_beauty[0][start_node] = 0;
    structgraphInfo->node_beauty[1][start_node] = 0;

    for(int end_node : edges[start_node]) { // loop adjacent edges
        if(!structgraphInfo->visited[end_node]){
            dfs(end_node, edges, structgraphInfo);

            long long lv = structgraphInfo->node_values[0][start_node];
            long long rv = structgraphInfo->node_values[1][start_node];
            long long lu = structgraphInfo->node_values[0][end_node];
            long long ru = structgraphInfo->node_values[1][end_node];

            find_max(lv, rv, lu, ru, start_node, end_node, structgraphInfo->node_beauty);


        }
    }

}

void solve(){
    int num_vertices = 0;
    cin >> num_vertices;
    struct graph_info structgraphInfo{};

    vector<int> edges[N];

    long long x, y;
    //read node values
    for (long long i = 1; i <= num_vertices; i++) {
        scanf("%lld%lld", &x, &y);
        structgraphInfo.node_values[0][i] = x;
        structgraphInfo.node_values[1][i] = y;
    }
    //undirected graph, read from both sides
    for (int j = 1; j <num_vertices; j++) {
        scanf("%lld%lld", &x, &y);
        edges[x].push_back(y);
        edges[y].push_back(x);
    }

    dfs(1, edges, &structgraphInfo);

    cout << max(structgraphInfo.node_beauty[0][1],structgraphInfo.node_beauty[1][1]) << endl;


}

int main(){
    int num_inputs = 0;
    cin >> num_inputs;
    for(int i = 0; i < num_inputs;i++){
        solve();
    }

    return 0;
}