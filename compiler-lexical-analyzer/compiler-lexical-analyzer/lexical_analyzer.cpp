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
	vector<int> finish_state_match = getFinishStateReturn();

	vector<Token> tokens;	//테스트용 결과 저장용 문자열 배열
	string temp_input;		//토큰 내용 받는 문자열
	char in_stream = 0;		//입력 char
	int current_state = 0;		//start state is 0
	while ((in_stream = getchar()) != EOF) {
		int row_togo = get_transit_row(in_stream);	//입력에 맞는 transition table의 col 번호 받아옴
		
		if (row_togo == UNAVAILABLE_INPUT_CHAR) {
			cerr << "there is unavailable input: " << in_stream;
			break;
		}
		else {
			//입력에 맞는 새로운 state
			int new_state = dfa_table[current_state][row_togo];
			
			if (new_state == NO_TRANSITION_RULE) {	//기존 state에서 transition rule이 없는 경우
				//whitespace 예외처리 해야 함

				if (finish_state_match[current_state] == NO_TRANSITION_RULE) {
					cerr << "this is not terminal state";
				}
				else {
					tokens.push_back(Token(static_cast<TOKEN_TYPE>(finish_state_match[current_state]), temp_input));

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

	//테스트
	for (Token &t : tokens) {
		cout << t << '\n';
	}

    return 0;
}