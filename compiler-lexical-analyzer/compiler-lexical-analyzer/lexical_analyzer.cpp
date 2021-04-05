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

	vector<string> tokens;	//�׽�Ʈ�� ��� ����� ���ڿ� �迭
	string temp_input;		//��ū ���� �޴� ���ڿ�
	char in_stream = 0;		//�Է� char
	int current_state = 0;		//start state is 0
	while ((in_stream = getchar()) != EOF) {
		int row_togo = get_transit_row(in_stream);	//�Է¿� �´� transition table�� col ��ȣ �޾ƿ�
		
		if (row_togo == UNAVAILABLE_INPUT_CHAR) {
			cout << "there is unavailable input: " << in_stream;
			break;
		}
		else {
			//�Է¿� �´� ���ο� state
			int new_state = dfa_table[current_state][row_togo];
			
			if (new_state == NO_TRANSITION_RULE) {	//���� state���� transition rule�� ���� ���
				//whitespace ����ó�� �ؾ� ��
				tokens.push_back(temp_input);


				//���� input�� �°� state �ٽ� ����
				temp_input.clear();
				temp_input.push_back(in_stream);
				current_state = dfa_table.front()[row_togo];
			}
			else {
				//���ڿ��� �Է� �߰��ϰ� ��� ����
				temp_input.push_back(in_stream);
				current_state = new_state;
			}
		}
	}

	//�׽�Ʈ ���
	for (string &s : tokens) {
		cout << s << '\n';
	}

    return 0;
}