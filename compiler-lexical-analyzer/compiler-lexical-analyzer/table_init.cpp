#include "table_init.h"
#include <fstream>

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

std::vector<int> getFinishStateReturn(){
	std::vector<int> finish_type(ROW);
	std::ifstream f_in("finish_state_return.txt");
	if (f_in.is_open()) {
		for (int &i : finish_type) {
			f_in >> i;
		}
	}
	return finish_type;
}