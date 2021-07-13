

#include <bits/stdc++.h>
#include "deque"

/**
 *  Problem can be found at
 *  https://codeforces.com/problemset/problem/1523/C
 */
using namespace std;

typedef long long ll;

void print_stack(deque<int> remains){
    for(auto item  =0; item< remains.size(); ++item){
        cout << remains[item];
        if(item +1 != remains.size()){
            cout<< ".";
        }
    }
    cout<< endl;
}


void solve(int number_of_lines){
    deque<int> remains;
    int remain;
    for(auto i = 0; i< number_of_lines;++i) {
        scanf("%d", &remain);

        if (remain == 1) { // if one than add
            remains.push_back(remain);
            print_stack(remains);
            continue;
        } else {
            // if last one is different, pop until first subsequence
            while (!remains.empty() && remains.back() +1 != remain) {
                remains.pop_back();
            }
            remains.pop_back();
            remains.push_back(remain);

        }
        print_stack(remains);
    }
}
int main(){

    int number_of_test;
    int number_of_lines;
    scanf("%d", &number_of_test);
    while(number_of_test != 0){
        scanf("%d", &number_of_lines);
        solve(number_of_lines);
        number_of_test--;
    }


    return 0;
}
