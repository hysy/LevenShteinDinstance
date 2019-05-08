// use C++11 Compiler

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

// 削除, 挿入, 変換
using Coord = pair < int , int >; 
using State = pair < Coord, int >; 

void LevenShteinDistance(string pattern, string str) {
  vector < vector < int > > dp(pattern.size()+1, vector < int > (str.size() + 1, 1 << 27));
  vector < vector < State > > state_table(pattern.size()+1, vector < State > (str.size()+1, make_pair(make_pair(-1, -1), -1) ));

  for (int i = 0; i < pattern.size() + 1; ++i) dp[i][0] = i;
  for (int i = 0; i < str.size() + 1; ++i) dp[0][i] = i;

  for (int p = 1; p < pattern.size() + 1; ++p) {
    for (int s = 1; s < str.size() + 1; ++s) {
      // 削除, 挿入, 変換
      vector < int > choices{dp[p-1][s] + 1, dp[p][s-1] + 1, dp[p-1][s-1] + (pattern[p-1] != str[s-1])};
      dp[p][s] = *min_element(choices.begin(), choices.end());
      
      vector < Coord > prev_coords{make_pair(p-1,s), make_pair(p,s-1), make_pair(p-1, s-1)};
      int operation = min_element(choices.begin(), choices.end()) - choices.begin();
      // 変換する必要があるか
      // 変換する必要がない -> operation = 3      
      if (1 == count(choices.begin(), choices.end(), dp[p-1][s-1] + (pattern[p-1] != str[s-1])) &&
          (pattern[p-1] == str[s-1])) {
        operation = 3;
      }

      if (operation == 3) state_table[p][s] = State(prev_coords[2], 3);
      else state_table[p][s] = State(prev_coords[operation], operation);
    }
  }
  State now_state = state_table[pattern.size()][str.size()];
  vector < State > state_sequence;
  while (now_state.second != -1) {
    if (now_state.second != 3)
      state_sequence.push_back(now_state);
    Coord &prev_coord = now_state.first;
    now_state = state_table[prev_coord.first][prev_coord.second];
  }
  reverse(state_sequence.begin(), state_sequence.end());
  
  cout << "convert: " << pattern << " -> " << str << " !" << endl;
  cout << endl;

  string now_pattern = pattern;
  string operation_name[3] = {"delete", "insert", "replace"};
  int offset = 0;
  for (auto& state: state_sequence) {
    Coord& coord = state.first;
    int& pattern_coord = coord.first;
    int& str_coord = coord.second;
    int& operation = state.second;

    int now_pattern_coord = pattern_coord + offset;
    cout << "(" << pattern_coord << ", " << str_coord << ") " 
         << "operation: " << operation_name[operation] << endl;
    
    switch (operation) {
      // 削除、挿入、変換
    case 0:
      now_pattern.erase(now_pattern.begin() + now_pattern_coord);
      offset--;
      break;
    case 1:
      now_pattern.insert(now_pattern.begin() + now_pattern_coord, str[str_coord]);
      offset++;
      break;
    case 2:
      now_pattern[now_pattern_coord] = str[str_coord];
      break;
    default:
      break;
    }
    cout << "  now pattern: " << now_pattern << endl;
  }

  cout << endl;
  cout << "LevenShteinDistance: " << dp[pattern.size()][str.size()] << endl;
}


int RecursiveLevenShteinDistance(string pattern, string str, int p, int s) {
  if (p == 0) return s;
  if (s == 0) return p;

  return min({RecursiveLevenShteinDistance(pattern, str, p - 1, s) + 1,
              RecursiveLevenShteinDistance(pattern, str, p, s - 1) + 1,
              RecursiveLevenShteinDistance(pattern, str, p - 1, s - 1) + (pattern[p-1] != str[s-1]) });
}


int main(int argc, char **argv) {
  if (argc != 3) {
    cerr << "invalid input!! " << endl; 
    exit(1);
  }
  
  string pattern = argv[1], str = argv[2];
//  cin >> pattern >> str;
  LevenShteinDistance(pattern, str);
  cout << "[Confirmation] Recursive LevenShteinDistance: " << RecursiveLevenShteinDistance(pattern, str, pattern.size(), str.size()) << endl;
  return 0;
}
