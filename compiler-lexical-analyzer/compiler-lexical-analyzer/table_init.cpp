#include "table_init.h"
#include <fstream>

#define ROW 85
#define COL 83

std::vector<std::vector<int>> getTransitionTable() {
	std::vector<std::vector<int>> table(ROW, std::vector<int>(COL));
	std::ifstream f_in("dfa_transition_table.txt");
	
	if (f_in.is_open()) {
		for (std::vector<int> &i : table) {
			for (int &j : i) {
				f_in >> j;
			}
		}
	}
	
	f_in.close();
	return table;
}
