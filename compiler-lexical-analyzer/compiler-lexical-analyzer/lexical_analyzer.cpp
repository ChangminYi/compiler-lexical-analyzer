#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "token.h"
#include "table_init.h"
#include "character_mapping.h"

using namespace std;

//�ν��� ��ū �з��Ͽ� �����ϴ� �Լ�
void recognizeToken(int current_state, string &recog_str, vector<Token> &token_Set, vector<vector<int>> &dfa_table, vector<int> &finish_state_table);

//lexical analysis�� �����Ͽ� ��ū ����Ʈ ��ȯ
vector<Token> lexicalAnalyze(char *argv);

//���� ���
void writeOutputFile(vector<Token> &argt);

int main(int argc, char** argv) {
	if (argc != 2) {
		std::cerr << "Invalid number of argument";
		exit(-1);
	}

	vector<Token> tokens = lexicalAnalyze(argv[1]);
	
	writeOutputFile(tokens);

	return 0;
}

void recognizeToken(int current_state, string &recog_str, vector<Token> &token_Set, vector<vector<int>> &dfa_table, vector<int> &finish_state_table) {
	Token temp_token = Token(static_cast<TOKEN_TYPE>(finish_state_table[current_state]), recog_str);

	//- ����ó��: ���� ���ڳ� id�� ��� operand -�� ���ڷ� ������ �־������
	if (temp_token.type == NUMBER && temp_token.value.front() == '-') {
		if (!token_Set.empty() && (token_Set.back().type == NUMBER || token_Set.back().type == ID)) {
			token_Set.push_back(Token(OPER, "-"));
			token_Set.push_back(Token(NUMBER, recog_str.substr(1)));
		}
		else {
			token_Set.push_back(temp_token);
		}
	}
	else {
		if (temp_token.type != WSPACE) {
			token_Set.push_back(temp_token);
		}
	}

	return;
}

vector<Token> lexicalAnalyze(char *argv) {
	ifstream input_f(argv);
	if (input_f.fail()) {
		std::cerr << "Cannot find " << argv;
		exit(-1);
	}

	//initializing of DFA transition table and finishing state table
	vector<vector<int>> dfa_table = getTransitionTable();
	vector<int> finish_state_match = getFinishStateReturn();

	vector<Token> tokens;	//�׽�Ʈ�� ��� ����� ���ڿ� �迭
	string temp_input;		//��ū ���� �޴� ���ڿ�
	char in_stream = 0;
	int current_state = 0;		//start state is 0
	unsigned int line_cnt = 1;	//�� ��° ������ ǥ��
	while (input_f.get(in_stream)) {
		if (in_stream == '\n') {	//�� ��ȣ ������Ʈ
			line_cnt++;
		}
		int row_togo = get_transit_row(in_stream);	//�Է¿� �´� transition table�� column ��ȣ

		if (row_togo == UNAVAILABLE_INPUT_CHAR) {	//�ν� �Ұ����� ���ڸ� �޾��� ��: ���� ��� �� ����
			std::cerr << "line " << line_cnt << ") there is unavailable input: \'" << in_stream << '\'';
			exit(-1);
		}
		else {
			//�Է¿� �´� ���ο� state
			int new_state = dfa_table[current_state][row_togo];

			if (new_state == NO_TRANSITION_RULE) {
				//���� state���� transition rule�� ���� ���: ���� ��� �� ���� (ex: "hello;)
				if (finish_state_match[current_state] == NON_FINISHING_STATE) {
					std::cerr << "line " << line_cnt << ") this is not terminal state: " << temp_input;
					exit(-1);
				}
				//terminal state���� ���� ���: ��ū �з��ϰ� �ٽ� ����
				else {
					//��ū �з�
					recognizeToken(current_state, temp_input, tokens, dfa_table, finish_state_match);

					//���� input�� �°� state �ٽ� ����
					temp_input.clear();
					temp_input.push_back(in_stream);
					current_state = dfa_table.front()[row_togo];
				}
			}
			//���� ��ū �ν��� ������ ����
			else {
				temp_input.push_back(in_stream);
				current_state = new_state;
			}
		}
	}
	if (!temp_input.empty()) {	//������ ��ū �޾ƿ�: while�� ���� �ڵ�� ����
		if (finish_state_match[current_state] == NON_FINISHING_STATE) {
			std::cerr << "line " << line_cnt << ") this is not terminal state: " << temp_input;
			exit(-1);
		}
		else {
			recognizeToken(current_state, temp_input, tokens, dfa_table, finish_state_match);
		}
	}
	//input stream �ݱ�
	input_f.close();

	return tokens;
}

void writeOutputFile(vector<Token>& argt) {
	ofstream output_f("output.txt");
	for (Token &t : argt) {
		output_f << t << '\n';
	}
	output_f.close();

	std::cout << "lexical analysis completed.";

	return;
}
