#include <stdio.h>
#include <string.h>

// UTF-8 as described here https://wiki.freepascal.org/UTF8_strings_and_characters
int getNbEncoding(unsigned char c) {
	if (c >= 0xF0) {
		return 4;
	} else if (c >= 0xE0) {
		return 3;
	} else if (c >= 0xC0) {
		return 2;
	} else {
		return 1;
	}
}

int getRealIndex(char* str, int idx) {
  int i = 0;
  int realIndex = 0;
  while (i < idx) {
    int nbChar = getNbEncoding(str[realIndex]);
    realIndex += nbChar;
		i++;
  }
	return realIndex;
}

void printChar(char* str, int idx) {
	if (idx >= (int) strlen(str)) return;
	int i;
	int realIndex = getRealIndex(str, idx);
	int encodingNb = getNbEncoding(str[realIndex]);
	for (i=realIndex; i < realIndex + encodingNb; i++) {
		printf("%c", str[i]);
	}
	printf("\n");
}

int main() {
	char str[50];
	unsigned int idx;
	printf("Please input your string\n");
	scanf("%50s", str);
	printf("Which character (index) would you like to show?\n");
	scanf("%d", &idx);
	printChar(str, idx);
	return 0;
}
