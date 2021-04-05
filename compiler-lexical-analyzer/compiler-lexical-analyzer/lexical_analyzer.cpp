#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "token.h"
#include "table_init.h"
#include "lexeme_mapping.h"

using namespace std;

int main(int argc, char** argv){
	/*main에서 인자 받아오기 만들어야 됨*/
	if(argc != 2){
		cerr << "Invalid number of argument";
		exit(-1);
	}

	ifstream input_f(argv[1]);
	if(input_f.fail()){
		cerr << "Cannot find " << argv[1];
		exit(-1);
	}

	//initializing of DFA transition table and finishing state table
	vector<vector<int>> dfa_table = getTransitionTable();
	vector<int> finish_state_match = getFinishStateReturn();

	vector<Token> tokens;	//테스트용 결과 저장용 문자열 배열
	string temp_input;		//토큰 내용 받는 문자열
	char in_stream = 0;		//입력 char
	int current_state = 0;		//start state is 0
	while (input_f.get(in_stream)) {		//ctrl+z 들어올 때까지 입력 받음
		int row_togo = get_transit_row(in_stream);	//입력에 맞는 transition table의 column 번호
		
		if (row_togo == UNAVAILABLE_INPUT_CHAR) {
			cerr << "there is unavailable input: " << in_stream;
			break;
		}
		else {
			//입력에 맞는 새로운 state
			int new_state = dfa_table[current_state][row_togo];
			
			if (new_state == NO_TRANSITION_RULE) {	//기존 state에서 transition rule이 없는 경우

				if (finish_state_match[current_state] == NON_FINISHING_STATE) {
					cerr << "this is not terminal state";
				}
				else {
					Token temp_token = Token(static_cast<TOKEN_TYPE>(finish_state_match[current_state]), temp_input);

					if (temp_token.type == NUMBER && temp_token.value.front() == '-') {
						if (!tokens.empty() && (tokens.back().type == NUMBER || tokens.back().type == ID)) {	//- 예외처리: 앞이 숫자나 id인 경우 operand -와 숫자로 나눠서 넣어줘야함
							tokens.push_back(Token(OPER, "-"));
							tokens.push_back(Token(NUMBER, temp_input.substr(1)));
						}
						else {
							tokens.push_back(temp_token);
						}
					}
					else {
						tokens.push_back(temp_token);
					}

					//현재 input에 맞게 state 다시 설정
					temp_input.clear();
					temp_input.push_back(in_stream);
					current_state = dfa_table.front()[row_togo];
				}
			}
			else {
				//문자열에 입력 추가하고 계속 진행
				temp_input.push_back(in_stream);
				current_state = new_state;
			}
		}
	}
	input_f.close();

	ofstream output_f("output.txt");
	for (Token &t : tokens) {
		if (t.type != WSPACE) {
			output_f << t << '\n';
		}
	}
	output_f.close();

	system("pause");
    return 0;
}