#include <stdlib.h>
#include <stdio.h>

void extend(void **array, int length, size_t bytes) {
	if (!array) return;

	(*array) = realloc((*array), (length * bytes));
	if (!(*array)) printf("[extend] %p failed to realloc. Length: %d, Bytes: %lu\n", array, length, bytes);
}

int enterInt(const char *msg, int *num) {
	if (!num) return 0;
	printf("%s", msg);
	rewind(stdin);
	fseek(stdin, 0, SEEK_END);
	return scanf("%d", num);
}

char confirm() {
	rewind(stdin);
	fseek(stdin, 0, SEEK_END);
	printf("Exit? ");
	char ret = 0;
	char c = 0;
	while ((c = getchar()) != -1) {
		if (c == '\n') {
			return ret;
		} else {
			ret = c;
		}
	}
	return ret;
}

int main() {

	printf("int: %lu\n", sizeof(int));

	FILE *file = fopen("binary", "w+b");
	int *i = (int*) calloc(1, sizeof(int));
	int index = 0;

	while (1) {
		int number = 0;
		if (!enterInt("> ", &number)) {
			if (confirm() == 'y') break;
		} else {
			i[index++] = number;
			extend(&i, index + 1, sizeof(int));
		}
	}

	for (int x = 0; x < index; x++) {
		printf("[%d] -> %d, 0x%x\n", x, i[x], i[x]);
	}

	fwrite(i, sizeof(int), index, file);
	fclose(file);

	return 0;
}
