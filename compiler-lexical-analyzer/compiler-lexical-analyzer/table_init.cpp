#include "table_init.h"
#include <fstream>
#include <iostream>

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
	else {
		std::cerr << "there is no dfa_transition_table.txt in directory";
		exit(-1);
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
	else {
		std::cerr << "there is no finish_state_return.txt in directory";
		exit(-1);
	}
	return finish_type;
}