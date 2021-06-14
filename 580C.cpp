
/*
 * @author ProfH2SO4
 * @date 14.6.2021
 * TASK: https://codeforces.com/contest/580/problem/C
 */

#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <stack>

using namespace std;

struct graph_info{
    int number_of_vertices;
    int consecutive_limit;
    vector<int> positions_of_cats;
    vector<vector<int>> edges;
};

void load_input(graph_info *struct_graph_info){
    string line;
    int x, y;
    // first line
    cin >> x >> y;
    struct_graph_info->number_of_vertices = x;
    struct_graph_info->consecutive_limit = y;
    cin.ignore();
    // second line
    getline(cin, line);
    for(int i =0; i < struct_graph_info->number_of_vertices*2; i += 2){
        struct_graph_info->positions_of_cats.push_back(line[i] - '0');
    }
    // rest
    int edges_line = struct_graph_info->number_of_vertices -1;
    struct_graph_info->edges.resize(x+1, vector<int>());
    while(edges_line > 0){
        cin >> x >> y;

        struct_graph_info->edges[x].push_back(y);
        struct_graph_info->edges[y].push_back(x);
        edges_line--;
    }

}

void inicialize_visited(graph_info *struct_graph_info, vector<bool> *visited){
    for(int i =0; i< struct_graph_info->number_of_vertices+1;i++){
        visited->emplace_back(false);
    }
}

void inicialize_leafs(graph_info *struct_graph_info, vector<bool> *leaf_nodes){
    for(int i =0; i< struct_graph_info->number_of_vertices+1;i++){
        leaf_nodes->emplace_back(false);
    }
}

void find_restaurants(graph_info *struct_graph_info, int num_vertex){
    int restaurant_counter = 0;
    stack<tuple<int, int>> stack;
    vector<bool> visited;
    vector<bool> leaf_nodes;
    inicialize_visited(struct_graph_info, &visited);
    inicialize_leafs(struct_graph_info, &leaf_nodes);
    stack.push(make_tuple(num_vertex, struct_graph_info->positions_of_cats[num_vertex - 1]));
    visited[num_vertex] = true;

    while(!stack.empty()){
        int top_node = get<0>(stack.top());
        int top_node_cat_counter = get<1>(stack.top());

        if(top_node_cat_counter > struct_graph_info->consecutive_limit){
            stack.pop();
            continue;
        }
        visited[top_node] = true;
        stack.pop();

        for(int i =0; i< struct_graph_info->edges[top_node].size();i++){ // loop via adjacent edges
            int current_node = struct_graph_info->edges[top_node][i];
            if(!visited[current_node]){
                if(struct_graph_info->positions_of_cats[current_node -1]){ //has cat
                    stack.push(make_tuple(current_node, top_node_cat_counter + 1));
                }
                else{ // has no cat
                    stack.push(make_tuple(current_node,  0));
                }
            }
        }

    }
    for(int i = 1; i < leaf_nodes.size();i++){
        if(visited[i] && struct_graph_info->edges[i].size() == 1 && i != 1){ // if leaf
            restaurant_counter++;
        }

    }
    cout << restaurant_counter << endl;
}

int main(){
    struct graph_info struct_graph_info;
    load_input(&struct_graph_info);
    find_restaurants(&struct_graph_info,1);

    return 0;
}

