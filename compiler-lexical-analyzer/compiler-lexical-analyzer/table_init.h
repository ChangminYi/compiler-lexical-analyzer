#include <vector>
#include "token.h"

#ifndef TABLE_INIT
#define TABLE_INIT

#define ROW 85
#define COL 83
#define NO_TRANSITION_RULE -1

using namespace std;

vector<vector<int>> getTransitionTable();


#endif