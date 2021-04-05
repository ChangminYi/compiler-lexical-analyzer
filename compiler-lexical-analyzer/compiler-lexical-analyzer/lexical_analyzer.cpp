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

	//initializing of DFA transition table and finishing state table
	vector<vector<int>> dfa_table = getTransitionTable();
	vector<int> finish_state_match = getFinishStateReturn();

	vector<Token> tokens;	//�׽�Ʈ�� ��� ����� ���ڿ� �迭
	string temp_input;		//��ū ���� �޴� ���ڿ�
	char in_stream = 0;		//�Է� char
	int current_state = 0;		//start state is 0
	while ((in_stream = getchar()) != EOF) {		//ctrl+z ���� ������ �Է� ����
		int row_togo = get_transit_row(in_stream);	//�Է¿� �´� transition table�� column ��ȣ
		
		if (row_togo == UNAVAILABLE_INPUT_CHAR) {
			cerr << "there is unavailable input: " << in_stream;
			break;
		}
		else {
			//�Է¿� �´� ���ο� state
			int new_state = dfa_table[current_state][row_togo];
			
			if (new_state == NO_TRANSITION_RULE) {	//���� state���� transition rule�� ���� ���

				if (finish_state_match[current_state] == NON_FINISHING_STATE) {
					cerr << "this is not terminal state";
				}
				else {
					Token temp_token = Token(static_cast<TOKEN_TYPE>(finish_state_match[current_state]), temp_input);

					if (temp_token.type == NUMBER && temp_token.value.front() == '-') {
						if (!tokens.empty() && (tokens.back().type == NUMBER || tokens.back().type == ID)) {	//- ����ó��: ���� ���ڳ� id�� ��� operand -�� ���ڷ� ������ �־������
							tokens.push_back(Token(OPER, "-"));
							tokens.push_back(Token(NUMBER, temp_input.substr(1)));
						}
					}
					else {
						tokens.push_back(temp_token);
					}

					//���� input�� �°� state �ٽ� ����
					temp_input.clear();
					temp_input.push_back(in_stream);
					current_state = dfa_table.front()[row_togo];
				}
			}
			else {
				//���ڿ��� �Է� �߰��ϰ� ��� ����
				temp_input.push_back(in_stream);
				current_state = new_state;
			}
		}
	}

	//�׽�Ʈ
	for (Token &t : tokens) {
		if (t.type != WSPACE) {
			cout << t << '\n';
		}
	}

    return 0;
}