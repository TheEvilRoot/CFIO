#include <stdio.h>
#include <stdlib.h>

#define sint sizeof(int) * 8

struct binary_mask {
	unsigned int first : 1;
	unsigned int : sint - 2;
	unsigned int last: 1;
};

struct hex_mask {
	unsigned int first : 8;
	unsigned int : sint - (8 * 2);
	unsigned int last : 8;
};

int enterInt(const char *msg, int *ret) {
	if (!ret) return 0;

	rewind(stdin);
	fseek(stdin, 0, SEEK_END);
	if (msg) printf("%s", msg);

	return scanf("%d", ret);
}

char enterChar(const char *msg) {
	rewind(stdin);
	fseek(stdin, 0, SEEK_END);
	if (msg) printf("%s", msg);

	return getchar();
}

void stop(FILE *file) {
	if (file) fclose(file);
	puts("Goodby");
	exit(0);
}

void writeFile(FILE **filePtr) {
	if (!filePtr) return;

	if (!(*filePtr)) (*filePtr) = fopen("binary", "a+b");

	while (1) {
		int number = 0;
		if (!enterInt("> ", &number)) {
			char confirm = enterChar("Stop?");
			if (confirm != 'n') break;
		} else {
			fwrite(&number, sizeof(int), 1, (*filePtr));
		}
	}

	fclose((*filePtr));
	(*filePtr) = fopen("binary", "r+b");
}

void readFile(FILE *file) {
	if (!file) {
		puts("File not opened");
		stop(file);
	}
	fseek(file, 0, 0);

	while (!feof(file)) {
		int number = 0;
		size_t res = fread(&number, sizeof(int), 1, file);
		if (!res) break;
		printf("%d\n", number);
	}

}

void binaryReadFile(FILE *file) {
	if (!file) {
		puts("File not opened");
		stop(file);
	}
	fseek(file, 0, 0);
	while (!feof(file)) {
		int number = 0;
		size_t res = fread(&number, sizeof(int), 1, file);
		if (!res) break;
		
		printf("%d\t-> ", number);
		int x = 0;
		for (int i = 0; i < sizeof(int) * 8; i++) {
			struct binary_mask *mask = (struct binary_mask*) &number;
			printf("%u", mask->last);
			number = number << 1;
			x++;
			if (x > 1) {
				printf(" ");
				x = 0;
			}
		}
		printf("\n");
	}

}

void hexReadFile(FILE *file) {
	if (!file) {
		puts("File not opened");
		stop(file);
	}
	fseek(file, 0, 0);

	while (!feof(file)) {
		int number = 0;
		size_t res = fread(&number, sizeof(int), 1, file);
		if (!res) break;
		
		printf("%d\t-> ", number);
		for (int i = 0; i < (sizeof(int) * 8) / 8; i++) {
			struct hex_mask *mask = (struct hex_mask*) &number;
			printf("%02x ", mask->first);
			number = number >> 8;
		}
		printf("\n");
	}
}

int main() {
	FILE *file = fopen("binary", "r+b");
	if (!file) {
		puts("Cannot open file 'binary'");
		return 1;
	}

	while (1) {
		// puts("[W]rite the file");
		// puts("[R]ead the file");
		// puts("[B]inary read the file");
		// puts("[H]exadecimal read the file");
		// puts("[Q]uit");

		while (1) {
			char choice = enterChar("[W, R, B, H, Q]: ");
			switch(choice) {
				case 'W': case 'w': {
					writeFile(&file);
					break;
				}
				case 'R': case 'r': {
					readFile(file);
					break;
				}
				case 'B': case 'b': {
					binaryReadFile(file);
					break;
				}
				case 'H': case 'h': {
					hexReadFile(file);
					break;
				}
				case 'Q': case 'q': {
					stop(file);
				}
				default: continue;
			}
			break;
		}
	}
	return 0;
}