#include <stdlib.h>
#include "../includes/constants.h"

BYTE* reconstructImage(BYTE* partial_image, int partial_image_size, int n, int k);

BYTE*
lagrangeInterpolation(int* n_values, int k, BYTE* shadows_pixel) {
	BYTE* partial_image_section_pixels = calloc(k, sizeof(BYTE));
	BYTE** equations = declareEquations(k);
	initializeEquations(equations, n, k);
	return partial_image_section_pixels;
}

BYTE**
declareEquations(int k) {
	BYTE** equations = calloc(k, sizeof(BYTE*));
	int i;
	for (i = 0; i < k; ++i) {
		equations[i] = calloc(k, sizeof(BYTE));
	}
	return equations;
}

BYTE**
initializeEquations(BYTE** equations, int n, int k) {
	int i, j;
	for (i = 0; i < k; i++) {
		for (j = 0; j < k; j++) {
			
		}
	}
}

BYTE*
reconstructImage(BYTE* partial_image, int partial_image_size, int n, int k) {
	BYTE* image = calloc(partial_image_size, sizeof(BYTE)); //La imagen tendrá un 
	int i, j = 0;																					//tamaño k por el tamaño
	while(i < partial_image_size) {												// de la sombra, por 2,
		if (partial_image[i] < 250) {												//en el caso de que cada
			image[j++] = partial_image[i++];									// pixel sea >= a 250.
		} else {
			image[j++] = partial_image[i] + partial_image[i+1];
			i+=2;
		}
	}
	image = realloc(image, j);	//Comprimo la imagen borrando el espacio sobrante
	return image;								//allocado inicialmente como partial_image_size.
}