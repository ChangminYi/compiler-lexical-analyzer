
#ifndef CHARACTER_MAPPING
#define CHARACTER_MAPPING

#include <cctype>

// �Ұ����� �Է��� ������ ���� ��ȯ��
#define UNAVAILABLE_INPUT_CHAR -1


// �Է� ������ �����̸� transition table�� column ��ȣ ��ȯ, ���� �����̸� UNAVAILABLE_INPUT_CHAR ��ȯ.
int get_transit_row(char input_character);


#endif