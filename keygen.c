#include <stdio.h>
#include <time.h>
#include <stdlib.h>

char* addCharacter(char* str, char c, int *idx, int *sizeStr) {
	char *result = str;
	if (*sizeStr == *idx - 1) {
		*sizeStr *= 2;
		result = realloc(result, *sizeStr * sizeof(char));
	}
 	str[*idx] = c;
	*idx += 1;
	return result; 	
}

char* keygen(unsigned int sumAscii) {
	int sizeResult = 50;
	char *result = malloc(sizeof(char) * sizeResult);
	unsigned int sumTotal = 0;
	int idx = 0;
	while(sumTotal < sumAscii - 125) {
		int r = (rand() % 60) + 65;
		char c = r;
		sumTotal += r;
		result = addCharacter(result, c, &idx, &sizeResult);
	}
	char c = sumAscii - sumTotal;
	result = addCharacter(result, c, &idx, &sizeResult);
	result = addCharacter(result, '\0', &idx, &sizeResult);
	return result;
}

int main(int argc, char** argv) {
	if (argc != 2) {
		printf("Usage: %s <sumAscii>\n", *argv);
		return -1;	
	}
	unsigned int sumAscii = atoi(*(argv + 1));
	srand(time(NULL));
	char * result = keygen(sumAscii);
	printf("%s", result);
	return 0;
}

