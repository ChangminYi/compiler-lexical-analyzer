#include <iostream>
#include <fstream>
#include <vector>
#include "token.h"
#include "table_init.h"

using namespace std;

int main(int argc, char *argv[]){
	//initializing of DFA transition table
	vector<vector<int>> dfa_table = getTransitionTable();


    return 0;
}