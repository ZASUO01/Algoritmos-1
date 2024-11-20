#include <iostream>
#include <vector>
#include <utility>
#include <string>
#include <unordered_map>

using namespace std;

#define MAX(A, B) (A > B ? A : B)


int getMaxScore(
    int tkIdx,
    int sectIdx,
    vector<pair<int, int>> &tks,
    vector<pair<int, int>> &sects,
    pair<int, int> sectAcc,
    int acc,
    int dur,
    vector<bool> used
){  
    if(tkIdx >= tks.size()){
        acc += (sectAcc.first * sectAcc.second * sects[sectIdx].first);
        sectIdx++;

        if(sectIdx >= sects.size()){
            return acc;
        }else{
            tkIdx = 0;
            sectAcc = {0, 0};
            dur = sects[sectIdx].second;
        }
    }

    int maxScore;
    int currScr = used[tkIdx] ? (tks[tkIdx].first / 2) : tks[tkIdx].first;
    int currDur = tks[tkIdx].second;

    used[tkIdx] = false;
    int notInclude = getMaxScore(tkIdx + 1, sectIdx, tks, sects, sectAcc, acc, dur, used);
    
    if(currDur > dur){
        maxScore = notInclude;
    }else{
        used[tkIdx] = true;
        int include = getMaxScore(tkIdx + 1, sectIdx, tks, sects, {sectAcc.first + currScr, sectAcc.second + 1}, acc, dur - currDur, used);

        maxScore = MAX(include, notInclude);
    }

    return maxScore;
}

int main(){
    int N, K, i;
    int acc = 0;

    cin >> N >> K;

    vector<pair<int, int>> sections;
    vector<pair<int, int>> tricks;
    vector<bool> usedBefore;

    int e, l;
    for(i = 0; i < N; i++){
        cin >> e >> l;
        sections.push_back({e, l});
        acc += l;
    }

    int p, t;
    for(i = 0; i < K; i++){
        cin >> p >> t;
        tricks.push_back({p, t});
        usedBefore.push_back(false);
    }

    cout << getMaxScore(0, 0, tricks, sections, {0, 0}, 0, sections[0].second, usedBefore) << "\n";

    return 0;
}