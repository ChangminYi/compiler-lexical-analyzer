#include "lexeme_mapping.h"

int get_transit_row(char input_lexeme) {
	// 0 ~ 9: 10개 (return 0 ~ 9)
	if (isdigit(input_lexeme)) {
		return input_lexeme - '0';
	}
	// a ~ z: 26개 (returns 10 ~ 35)
	else if (islower(input_lexeme)) {
		return 10 + (input_lexeme - 'a');
	}
	// A ~ Z: 26개 (returns 36 ~ 61)
	else if (isupper(input_lexeme)) {
		return 36 + (input_lexeme - 'A');
	}
	// 62 ~ : 나머지 연산자 및 기호들
	else {
		switch (input_lexeme) {
		case '_': return 62;
		case '+': return 63;
		case '-': return 64;
		case '*': return 65;
		case '/': return 66;
		case '\t': return 67;
		case '\r':
		case '\n': return 68;
		case ' ': return 69;
		case '\'': return 70;
		case '"': return 71;
		case '=': return 72;
		case '<': return 73;
		case '>': return 74;
		case '(': return 75;
		case ')': return 76;
		case '{': return 77;
		case '}': return 78;
		case '[': return 79;
		case ']': return 80;
		case ',': return 81;
		case ';': return 82;
		default: return UNAVAILABLE_INPUT_CHAR;
		}
	}
	return UNAVAILABLE_INPUT_CHAR;
}
