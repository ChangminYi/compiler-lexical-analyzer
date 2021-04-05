#include <iostream>
//#include <fstream>
#include <vector>
#include <string>
#include "token.h"
#include "table_init.h"
#include "lexeme_mapping.h"

using namespace std;

int main(int argc, char *argv[]){
	/*main���� ���� �޾ƿ��� ������ ��*/

	//initializing of DFA transition table
	vector<vector<int>> dfa_table = getTransitionTable();

	char in_stream = 0;
	int current_state = 0;		//start state is 0
	while (in_stream = getchar()) {
		int row_togo = get_transit_row(in_stream);	//�Է¿� �´� transition table�� col ��ȣ �޾ƿ�
		
		if (row_togo == UNAVAILABLE_INPUT_CHAR) {
			cout << "there is unavailable input: " << in_stream;
			break;
		}
		else {
			current_state = dfa_table[current_state][row_togo];	//�Է¿� �´� ���ο� state

			if (current_state == NO_TRANSITION_RULE) {	//���� state���� transition rule�� ���� ���
				
			}
			else {
				//coutinue?
			}
		}
	}

    return 0;
}