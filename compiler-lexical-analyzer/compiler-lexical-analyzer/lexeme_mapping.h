
#ifndef LEXEME_MAPPING
#define LEXEME_MAPPING

#include <cctype>

// 불가능한 입력이 들어왔을 때의 반환값
#define UNAVAILABLE_INPUT_CHAR -1


// 입력 가능한 문자이면 transition table의 column 번호 반환, 없는 문자이면 UNAVAILABLE_INPUT_CHAR 반환.
int get_transit_row(char input_lexeme);


#endif