#include "character_mapping.h"

int get_transit_row(char input_character) {
	// 0 ~ 9: 10�� (return 0 ~ 9)
	if (isdigit(input_character)) {
		return input_character - '0';
	}
	// a ~ z: 26�� (returns 10 ~ 35)
	else if (islower(input_character)) {
		return 10 + (input_character - 'a');
	}
	// A ~ Z: 26�� (returns 36 ~ 61)
	else if (isupper(input_character)) {
		return 36 + (input_character - 'A');
	}
	// 62 ~ : ������ ������ �� ��ȣ��
	else {
		switch (input_character) {
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
