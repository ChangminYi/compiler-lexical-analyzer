#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "token.h"
#include "table_init.h"
#include "lexeme_mapping.h"

using namespace std;

int main(int argc, char** argv) {
	if (argc != 2) {
		cerr << "Invalid number of argument";
		exit(-1);
	}

	ifstream input_f(argv[1]);
	if (input_f.fail()) {
		cerr << "Cannot find " << argv[1];
		exit(-1);
	}

	//initializing of DFA transition table and finishing state table
	vector<vector<int>> dfa_table = getTransitionTable();
	vector<int> finish_state_match = getFinishStateReturn();

	vector<Token> tokens;	//�׽�Ʈ�� ��� ����� ���ڿ� �迭
	string temp_input;		//��ū ���� �޴� ���ڿ�
	char in_stream = 0;		//�Է� char
	int current_state = 0;		//start state is 0
	while (input_f.get(in_stream)) {		//ctrl+z ���� ������ �Է� ����
		int row_togo = get_transit_row(in_stream);	//�Է¿� �´� transition table�� column ��ȣ

		if (row_togo == UNAVAILABLE_INPUT_CHAR) {
			cerr << "there is unavailable input: " << in_stream;
			break;
		}
		else {
			//�Է¿� �´� ���ο� state
			int new_state = dfa_table[current_state][row_togo];

			//���� state���� transition rule�� ���� ���
			if (new_state == NO_TRANSITION_RULE) {	
				if (finish_state_match[current_state] == NON_FINISHING_STATE) {
					cerr << "this is not terminal state";
				}
				else {
					Token temp_token = Token(static_cast<TOKEN_TYPE>(finish_state_match[current_state]), temp_input);

					//- ����ó��: ���� ���ڳ� id�� ��� operand -�� ���ڷ� ������ �־������
					if (temp_token.type == NUMBER && temp_token.value.front() == '-') {
						if (!tokens.empty() && (tokens.back().type == NUMBER || tokens.back().type == ID)) {	
							tokens.push_back(Token(OPER, "-"));
							tokens.push_back(Token(NUMBER, temp_input.substr(1)));
						}
						else {
							tokens.push_back(temp_token);
						}
					}
					else {
						if (temp_token.type != WSPACE) {
							tokens.push_back(temp_token);
						}
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
	if (!temp_input.empty()) {	//������ ��ū �޾ƿ�: while�� ���� �ڵ�� ����
		if (finish_state_match[current_state] == NON_FINISHING_STATE) {
			cerr << "this is not terminal state";
		}
		else {
			Token temp_token = Token(static_cast<TOKEN_TYPE>(finish_state_match[current_state]), temp_input);

			if (temp_token.type == NUMBER && temp_token.value.front() == '-') {
				if (!tokens.empty() && (tokens.back().type == NUMBER || tokens.back().type == ID)) {	
					tokens.push_back(Token(OPER, "-"));
					tokens.push_back(Token(NUMBER, temp_input.substr(1)));
				}
				else {
					tokens.push_back(temp_token);
				}
			}
			else {
				if (temp_token.type != WSPACE) {
					tokens.push_back(temp_token);
				}
			}
		}
	}

	//input stream �ݱ�
	input_f.close();

	ofstream output_f("output.txt");
	for (Token &t : tokens) {
		output_f << t << '\n';
	}
	output_f.close();

	//system("pause");
	return 0;
}