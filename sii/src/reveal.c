#include <stdlib.h>
#include "../includes/constants.h"

BYTE* reconstructImage(BYTE* partial_image, int partial_image_size, int n, int k);

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