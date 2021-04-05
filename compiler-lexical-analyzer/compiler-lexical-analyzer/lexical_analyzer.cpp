#include <iostream>
//#include <fstream>
#include <vector>
#include <string>
#include "token.h"
#include "table_init.h"
#include "lexeme_mapping.h"

using namespace std;

int main(int argc, char *argv[]){
	/*main에서 인자 받아오기 만들어야 됨*/

	//initializing of DFA transition table
	vector<vector<int>> dfa_table = getTransitionTable();

	char in_stream = 0;
	int current_state = 0;		//start state is 0
	while (in_stream = getchar()) {
		int row_togo = get_transit_row(in_stream);	//입력에 맞는 transition table의 col 번호 받아옴
		
		if (row_togo == UNAVAILABLE_INPUT_CHAR) {
			cout << "there is unavailable input: " << in_stream;
			break;
		}
		else {
			current_state = dfa_table[current_state][row_togo];	//입력에 맞는 새로운 state

			if (current_state == NO_TRANSITION_RULE) {	//기존 state에서 transition rule이 없는 경우
				
			}
			else {
				//coutinue?
			}
		}
	}

    return 0;
}