#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

void solve(){

    int num_trampolines;
    scanf("%d", &num_trampolines);

    vector<ll> trampolines;
    int temp_trampolines[5005] = {0};
    ll trampoline;
    trampolines.push_back(0);
    for(auto i = 0; i < num_trampolines; ++i){
        scanf("%lld", &trampoline);
        trampolines.push_back(trampoline);
    }
    ll count_rounds = 0;

    for(auto i = 1; i < num_trampolines; ++i){
        if(trampolines[i] == 1){ continue;} // if 1 skip

        if(i + trampolines[i] > trampolines.size()){ // end of the trampolines
                for(auto j = i + 2; j < trampolines.size();++j){
                    temp_trampolines[j]++;
                }
            }
        // count position where can rabbit jump
        // + 2  = minimum jump
        else{
            for(auto j = i + 2; j < i + trampolines[i] + 1; ++j){
                if(j >= trampolines.size()) { break; }
                temp_trampolines[j]++;

            }
        }
    }

    for(auto i = 1; i<trampolines.size(); ++i){
        // beginning of jump
        if( trampolines[i] - temp_trampolines[i] - 1 > 0){ // -1 cuz if 1 then skip
            count_rounds += trampolines[i] - temp_trampolines[i] - 1;
        }
        else{ // move rabbits ahead
            temp_trampolines[i+1] += temp_trampolines[i] -  trampolines[i]  + 1;
        }
    }
    cout << count_rounds  <<endl;



}


int main(){
    int num_tests;
    scanf("%d", &num_tests);

    while(num_tests > 0){
        solve();
        num_tests--;
    }


    return 0;
}