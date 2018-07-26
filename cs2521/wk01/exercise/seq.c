#include <stdio.h>
#include <stdlib.h>

void seq(int, int, int);

int main(int argc, char *argv[]) {
	int start, step, finish;
	switch(argc) {
	case 2:
		start = 1;
		finish = atoi(argv[1]);
		step = (start < finish) ? 1 : -1;
		break;
	case 3:
		start = atoi(argv[1]);
		finish = atoi(argv[2]);
		step = (start < finish) ? 1 : -1;
		break;
	case 4:
		start = atoi(argv[1]);
		step = atoi(argv[2]);
		finish = atoi(argv[3]);
		break;
	}
	seq(start, step, finish);
	return EXIT_SUCCESS;
}

void seq(int start, int step, int finish) {
	int i;
	for (i = start; (start < finish)? i <= finish : i >= finish; i+=step) {
		printf("%d ", i);
	}
	printf("\n");
}

