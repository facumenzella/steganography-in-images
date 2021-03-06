#include "../includes/reveal.h"

BYTE* revealInformation(BMPImage shadowImage, int size_to_reveal, main_error *err);
BYTE* revealImage(int* n_values, int n_size, int k, BYTE** shadows_pixels, int shadow_size, int seed);
void initializeEquations(int** equations, int* n_values, int n_size, int k);
int** gaussJordanEliminationMethod(int** equations, int dimension);
BYTE* reconstructImage(BYTE* partial_image, int partial_image_size, int n, int k);
void eliminateValuesAtColumn(int** equation, int** inverse, int dimension, int pivot);
void eliminateValues(int** equation, int** inverse, int dimension, int pivot, int direction);
BYTE* revealPartialImageWithoutLoss(BYTE* partial_image, int partial_image_size, int* permuted_image_size);
BYTE* revealPartialImageWithLoss(BYTE* partial_image, int partial_image_size);
boolean isPorterMaterial2(const int porter_image_size);

static const char* NOT_PORTER_MATERIAL = "Porter images should be divisible by 8. Read the requisites please and thank you.";

void
runReveal(Arguments arguments, main_error *err) {
    char *file_name = getSecret(arguments);

    char *directory = getDirectory(arguments);
    int min__porters_to_get_secret = getMinShadowsToRecoverSecret(arguments);
//    printf("min: %d\n", min__porters_to_get_secret);
    // printf(STARTING_REVEAL_PROCESS, min__porters_to_get_secret, directory);

    int *indexes = calloc(min__porters_to_get_secret, sizeof(int));
    if (indexes == NULL) {
        setError(err, CALLOC_ERROR);
        return;
    }
    BMPImage *porters_full_images = loadImages(directory, min__porters_to_get_secret, err);
    if (porters_full_images == NULL) {
        return;
    }
//    printf("Fetching shadows\n");
    BYTE **porter_images_shadows = calloc(min__porters_to_get_secret, sizeof(BYTE*));
    if (porter_images_shadows == NULL) {
        setError(err, CALLOC_ERROR);
    }

    if (isPorterMaterial2(getImageSize(porters_full_images[0])) == FALSE) {
      setError(err, NOT_PORTER_MATERIAL);
      return;
    }

    int shadow_size = getImageSize(porters_full_images[0]) / 8;

    porter_images_shadows[0] = revealInformation(porters_full_images[0],
                                                 shadow_size,
                                                 err);
    indexes[0] = getIndex(porters_full_images[0]);
    int seed = getSeed(porters_full_images[0]);
    for (int i = 1; i < min__porters_to_get_secret; i++) {
        int auxSeed = -1;
        indexes[i] = getIndex(porters_full_images[i]);
        auxSeed = getSeed(porters_full_images[i]);
        if (auxSeed != seed) {
            setError(err, DIFFERENT_SEEDS_FOR_PORTERS);
            return;
        }
//        printf("revealing %d \n", i);
        if (isPorterMaterial2(getImageSize(porters_full_images[i])) == FALSE) {
            setError(err, NOT_PORTER_MATERIAL);
            return;
        }
        porter_images_shadows[i] = revealInformation(porters_full_images[i],
                                                     shadow_size,
                                                     err);
    }
    BYTE *image = revealImage(indexes,
                              min__porters_to_get_secret,
                              min__porters_to_get_secret,
                              porter_images_shadows,
                              shadow_size,
                              seed);
    io_error error = NULL;
//    printf("done revealing\n");


    // this works because we said that images must be square images (aka widht = height)
    const int size_rate = 8 / min__porters_to_get_secret;

    BMPImage revealed_secret = initBMPImage("output.bmp",
                                            getFilesize(porters_full_images[0]),
                                            getOffset(porters_full_images[0]),
                                            getImageSize(porters_full_images[0]) / size_rate,
                                            getHeader(porters_full_images[0]),
                                            0,
                                            0,
                                            image,
                                            &error);
    if (revealed_secret == NULL) {
        return;
    }

    io_error save = NULL;
    saveImage(revealed_secret, file_name, size_rate, &save);
    if (save != NULL) {
        return;
    }
    printf("%s", REVEAL_SUCCESS);
}

BYTE*
revealImage(int* n_values, int n_size, int k, BYTE** shadows_pixels, int shadow_size, int seed) {
    int i, j, l, partial_image_index;
    BYTE** shadows_i_pixels = declareGenericByteMatrix(n_size, 1);
    long image_size = k * shadow_size;
    BYTE* partial_image = calloc(image_size, sizeof(BYTE));
    BYTE** inverseMatrix;
    BYTE** coefficients;
    int** equations = declareEquations(k);
    partial_image_index = 0;
    initializeEquations(equations, n_values, n_size, k);
    inverseMatrix = makeModularMatrix(gaussJordanEliminationMethod(equations, n_size), n_size);
    for (j = 0; j < shadow_size; j++) {
        for (i = 0; i < n_size; i++) {
            shadows_i_pixels[i][0] = shadows_pixels[i][j];
        }
        coefficients = multiplyByteMatrices(inverseMatrix, shadows_i_pixels, n_size, n_size, n_size, 1); // Se supone que a esta altura, n = k par que quede la matriz cuadrada.
        for (l = 0; l < k; l++) {
            partial_image[partial_image_index + l] = coefficients[l][0];
        }
        partial_image_index += l;
        setValuesToByteMatrix(shadows_i_pixels, n_size, 0, 0);
    }
//    printf("seed %d\n", seed);
    randomize(seed);
    unshufflePixels(image_size, partial_image);
    return partial_image;
}

void
initializeEquations(int** equations, int* n_values, int n_size, int k) {
    int i, j;
    for (i = 0; i < n_size; i++) {
        for (j = 0; j < k; j++) {
            equations[i][j] = intPow(n_values[i], j);
        }
    }
}

int**
gaussJordanEliminationMethod(int** equations, int dimension) { //AKA: Matrix inversion
    int** inverseMatrix = declareEquations(dimension);
    int** copied_equations = copySquareMatrix(equations, dimension);
    identityMatrix(inverseMatrix, dimension);
    int i;
    for (i = 0; i < dimension; i++) {
        eliminateValuesAtColumn(copied_equations, inverseMatrix, dimension, i);
    }
    return inverseMatrix;
}

void
eliminateValuesAtColumn(int** equations, int** inverse, int dimension, int pivot) {
    if (equations[pivot][pivot] != 1){
        inverse[pivot] = divideRowBy(inverse[pivot], dimension, equations[pivot][pivot]);
        equations[pivot] = divideRowBy(equations[pivot], dimension, equations[pivot][pivot]);
    }
    eliminateValues(equations, inverse, dimension, pivot, UP);
    eliminateValues(equations, inverse, dimension, pivot, DOWN);
}

void
eliminateValues(int** equations, int** inverse, int dimension, int pivot, int direction) {
    int i = pivot + direction;
    while(i >= 0 && i < dimension) {
        if (equations[i][pivot] != 0) {
            inverse[i] = addEquations(inverse[i], multiplyRowBy(inverse[pivot], dimension, equations[i][pivot]), dimension, NEGATIVE);
            equations[i] = addEquations(equations[i], multiplyRowBy(equations[pivot], dimension, equations[i][pivot]), dimension, NEGATIVE);
        }
        makeModularIntMatrix(equations, dimension);
        makeModularIntMatrix(inverse, dimension);
        i += direction;
    }
}

BYTE*
revealPartialImageWithoutLoss(BYTE* partial_image, int partial_image_size, int* permuted_image_size) {
    BYTE* result = calloc(partial_image_size*2, sizeof(BYTE));
    int i, result_index = 0;
    for (i = 0; i < partial_image_size; i++, result_index++) {
        BYTE b = partial_image[i];
        if (b == MAX_BYTE_VALUE - 1) {
            BYTE following_b = partial_image[++i];
            result[result_index] = b + following_b;
        } else {
            result[result_index] = b;
        }
    }
    *permuted_image_size = result_index;
    return realloc(result, result_index);
}


// Kill this with fire. This function is also defined in distribution.c but time is running
// and we have to finish this quickly
boolean
isPorterMaterial2(const int porter_image_size) {
//    printf ("shadow_size: %d\n", shadow_size);
    if (porter_image_size % 8 == 0) {
        return TRUE;
    }
    return FALSE;
}

BYTE*
revealInformation(BMPImage shadowImage, int size_to_reveal, main_error *err) {
    BYTE *shadow_image_bytes = getBMPImage(shadowImage);
    BYTE *revealed_shadow = calloc(size_to_reveal, sizeof(BYTE));
    int bi = 0;
    // we iterate over the bytes of the porter
    int j = 0;
    while (bi < size_to_reveal) {
        BYTE revealed_byte = 0;
        for (int i = 0; i < 8; i++) {
            revealed_byte = revealed_byte << 1;
            BYTE byte_to_reveal = shadow_image_bytes[j];
            uint8_t bit = getBit(byte_to_reveal, 0);
            revealed_byte = overrideLessSignificantBit(revealed_byte, bit);
            j++;
        }
        memcpy(&revealed_shadow[bi], &revealed_byte, sizeof(BYTE));
        bi++;
    }
    return revealed_shadow;
}
