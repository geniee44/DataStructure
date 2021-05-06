#include <time.h>
#include <stdlib.h>
#include <stdio.h>

int median_of_three(int* list, int a, int b, int c) {
	printf("\n%d %d %d", a, b, c);
	if (((list[b] < list[a]) && (list[a] < list[c])) || (list[c] < list[a]) && (list[a] < list[b])) {
		printf("%d\n", list[a]);
		return a;
	}
	else if (((list[a] < list[b]) && (list[b] < list[c])) || (list[c] < list[b]) && (list[b] < list[a])) {
		printf("%d\n", list[b]);
		return b;
	}
	else if (((list[a] < list[c]) && (list[c] < list[b])) || (list[b] < list[c]) && (list[c] < list[a])) {
		printf("%d\n", list[c]);
		return c;
	}
}

int main(void) {
	int list[5];
	for (int i = 0; i < 5; i++) {
		scanf("%d", &list[i]);
	}

	printf("%d", median_of_three(list, 0, 2, 4));

	return 0;
}