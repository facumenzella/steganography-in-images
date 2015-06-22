#include <stdlib.h>
#include "../includes/free.h"

void
freeSquareMatrix(void** matrix, int dimension) {
	int i;
	for (i = 0; i < dimension; i++) { 
	  free(matrix[i]);
	}
	free(matrix);
}