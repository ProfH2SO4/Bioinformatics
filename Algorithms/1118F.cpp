#include <bits/stdc++.h>

using namespace std;

/*
 * Date: 27.7.2021
 * problem can be found at https://codeforces.com/contest/1118/problem/F1
 */
struct counter{
    int blue;
    int red;
    int count;
};

tuple <int, int> dfs(struct counter *struct_counter, vector<vector<int>> &edges, vector<int> &v_colors, int vertex, int parent){
    int sum_red_vertex_sofar = 0;
    int sum_blue_vertex_sofar = 0;

    if(v_colors[vertex] == 1){
        sum_red_vertex_sofar = 1;
    }
    if(v_colors[vertex] == 2){
        sum_blue_vertex_sofar = 1;
    }

    tuple<int, int> sub_tree;
    for(auto adj_vertex: edges[vertex]){
        if(adj_vertex == parent){ continue; }
        sub_tree = dfs(struct_counter, edges, v_colors, adj_vertex, vertex);
        // all red found in a subtree and no blue
        if(get<0>(sub_tree) == struct_counter->red && get<1>(sub_tree) == 0){
            struct_counter->count ++;
        }
        // all blue found and no red
        if(get<0>(sub_tree) == 0 && get<1>(sub_tree) == struct_counter->blue){
            struct_counter->count ++;
        }
        sum_red_vertex_sofar += get<0>(sub_tree);
        sum_blue_vertex_sofar += get<1>(sub_tree);
    }


    return make_tuple(sum_red_vertex_sofar, sum_blue_vertex_sofar);
}

int main(){
    int num_vertices;
    scanf("%d", &num_vertices);

    vector<int> v_colors(num_vertices+1);
    struct counter struct_counter;
    struct_counter.blue = 0;
    struct_counter.red = 0;
    struct_counter.count = 0;

    int c;
    for(auto i = 1; i<= num_vertices; ++i){
        scanf("%d", &c);
        if(c == 1){
            struct_counter.red++;
        }
        if(c == 2){
            struct_counter.blue++;
        }
        v_colors[i] = c;
    }

    vector<vector<int>> edges(num_vertices + 1) ;
    int x,y;
    for(auto i = 0; i< num_vertices-1; ++i){
        scanf("%d %d", &x, &y);
        edges[x].push_back(y);
        edges[y].push_back(x);
    }

    dfs(&struct_counter , edges, v_colors, 1, -1);


    cout << struct_counter.count << endl;


    return 0;
}



