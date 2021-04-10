#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "token.h"
#include "table_init.h"
#include "character_mapping.h"

using namespace std;

//인식한 토큰 분류하여 저장하는 함수
void recognizeToken(Token &token, vector<Token> &token_set);

//lexical analysis를 실행하여 토큰 리스트 반환
vector<Token> lexicalAnalyze(char *argv);

//파일 출력
void writeOutputFile(vector<Token> &argt);

int main(int argc, char** argv) {
	if (argc != 2) {
		std::cerr << "Invalid number of argument" << '\n';
		exit(-1);
	}

	vector<Token> tokens = lexicalAnalyze(argv[1]);
	
	writeOutputFile(tokens);

	return 0;
}

void recognizeToken(Token &token, vector<Token> &token_set) {
	//- 예외처리: 앞이 숫자나 id인 경우 operand -와 숫자로 나눠서 넣어줘야함
	if (token.type == NUMBER && token.value.front() == '-') {
		if (!token_set.empty() && (token_set.back().type == NUMBER || token_set.back().type == ID)) {
			token_set.push_back(Token(OPER, "-"));
			token_set.push_back(Token(NUMBER, token.value.substr(1)));
		}
		else {
			token_set.push_back(token);
		}
	}
	else {
		if (token.type != WSPACE) {
			token_set.push_back(token);
		}
	}

	return;
}

vector<Token> lexicalAnalyze(char *argv) {
	ifstream input_f(argv);
	if (input_f.fail()) {
		std::cerr << "Cannot find " << argv << '\n';
		exit(-1);
	}

	//initializing of DFA transition table and finishing state table
	vector<vector<int>> dfa_table = getTransitionTable();
	vector<int> finish_state_match = getFinishStateReturn();

	vector<Token> tokens;	//테스트용 결과 저장용 문자열 배열
	string temp_input;		//토큰 내용 받는 문자열
	char in_stream = 0;
	int current_state = 0;		//start state is 0
	unsigned int line_cnt = 1;	//몇 번째 줄인지 표시
	while (input_f.get(in_stream)) {
		if (in_stream == '\n') {	//줄 번호 업데이트
			line_cnt++;
		}
		int row_togo = get_transit_row(in_stream);	//입력에 맞는 transition table의 column 번호

		if (row_togo == UNAVAILABLE_INPUT_CHAR) {	//인식 불가능한 문자를 받았을 때: 에러 출력 후 종료
			std::cerr << "line " << line_cnt << ") there is unavailable input: \'" << in_stream << '\'' << '\n';
			exit(-1);
		}
		else {
			//입력에 맞는 새로운 state
			int new_state = dfa_table[current_state][row_togo];

			if (new_state == NO_TRANSITION_RULE) {
				//기존 state에서 transition rule이 없는 경우: 에러 출력 후 종료 (ex: "hello;)
				if (finish_state_match[current_state] == NON_FINISHING_STATE) {
					std::cerr << "line " << line_cnt << ") this is not terminal state: " << temp_input << '\n';
					exit(-1);
				}
				//terminal state에서 끝난 경우: 토큰 분류하고 다시 진행
				else {
					//토큰 분류
					Token token = Token(static_cast<TOKEN_TYPE>(finish_state_match[current_state]), temp_input);
					recognizeToken(token, tokens);

					//현재 input에 맞게 state 다시 설정
					temp_input.clear();
					temp_input.push_back(in_stream);
					current_state = dfa_table.front()[row_togo];
				}
			}
			//아직 토큰 인식이 끝나지 않음
			else {
				temp_input.push_back(in_stream);
				current_state = new_state;
			}
		}
	}
	if (!temp_input.empty()) {	//마지막 토큰 받아옴: while문 안의 코드와 같음
		if (finish_state_match[current_state] == NON_FINISHING_STATE) {
			std::cerr << "line " << line_cnt << ") this is not terminal state: " << temp_input << '\n';
			exit(-1);
		}
		else {
			Token token = Token(static_cast<TOKEN_TYPE>(finish_state_match[current_state]), temp_input);
			recognizeToken(token, tokens);
		}
	}
	//input stream 닫기
	input_f.close();

	return tokens;
}

void writeOutputFile(vector<Token>& argt) {
	ofstream output_f("output.txt");
	for (Token &t : argt) {
		output_f << t << '\n';
	}
	output_f.close();

	std::cout << "lexical analysis completed." << '\n';

	return;
}
