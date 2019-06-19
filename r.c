#include <stdio.h>
#include <stdlib.h>

int main() {
	FILE *file = fopen("binary", "rb");
	while (!feof(file)) {
		int number = 0;
		size_t res = fread(&number, sizeof(int), 1, file);
		if (!res) break;
		printf("%d\n", number);
	}
	return 0;
}