#include "../includes/distribution.h"
#include "../includes/imageUtils.h"

boolean isValidKAgainstImageSize(const int k, const int image_size);
void distribute(BYTE *image,
                int image_size,
                BYTE **shadow_images,
                char* directory,
                int n,
                int k,
                int bits_to_hide,
                int seed,
                main_error *err);
BYTE* convertImageToArrayWithoutLoss(BYTE* image, int image_size, int* new_image_size);
BYTE* convertImageToArrayWithLoss(BYTE* image, int image_size);
BYTE** createShadows(unsigned char* image, int image_size, int n, int k);
void evaluateSection(BYTE* section, BYTE** shadows, int shadow_pixel_index, int n, int k);
BYTE ** initializeShadows(int image_size, int n, int k);
void hideInformation(BYTE *shadowImage_bytes, BYTE *toHide, int size_to_hide, main_error *err);
void int2bin(int number);

void
runDistribution(Arguments arguments, main_error *err) {
    int seed = 10; // TODO check this out
    char *file_name = getSecret(arguments);
    BMPImage bmp = loadImage(file_name, err);
    if (bmp == NULL) {
        // we fucked up
        setError(err, "We could not open the secret image\n");
        return;
    }
    printf("Secret image %s was succesfully loaded\n", file_name);
    
    BYTE *image = getBMPImage(bmp);
    char *directory = getDirectory(arguments);
    int image_size = getImageSize(bmp);
    int n = getTotalAmountOfShadowsToDistributeSecret(arguments);
    int k = getMinShadowsToRecoverSecret(arguments);
    
    if (isValidKAgainstImageSize(k, image_size) == FALSE) {
        setError(err, IMAGE_SIZE_NOT_DIVISIBLE_BY_K_ERROR);
        return;
    }
    
    BMPImage *porter_full_images = loadImages(directory, n, err);
    if (porter_full_images == NULL) {
        return; // we fucked up.
    }
    for (int i = 0; i < n; i++) {
        if (isValidKAgainstImageSize(k, getImageSize(porter_full_images[i])) == FALSE) {
            setError(err, IMAGE_SIZE_NOT_DIVISIBLE_BY_K_ERROR);
            return;
        }
    }
    printf("We have loaded the %d full porters\n", n);
    
    int bits_to_hide = 1;
    if (k < 8) {
        bits_to_hide = 2;
    }
    
    BYTE **porter_images = calloc(n, sizeof(BYTE*));
    for (int i = 0; i < n ; i++) {
        porter_images[i] = getBMPImage(porter_full_images[i]);
    }
    printf("We have loaded the %d porter images\n", n);
    
    distribute(image, image_size, porter_images, directory, n, k, bits_to_hide, seed, err);
    
    printf("We now save the images with the hidden data\n");
    for (int i = 0; i < n; i++) {
        io_error error = NULL;
        BMPImage image = porter_full_images[i];
        setIndex(image, i+1);
        setSeed(image, seed);
        saveImage(image, PORTERS_DIRECTORY, &error);
        if (error != NULL) {
            printf("error: %s\n", error);
            return;
        }
    }
    printf("We are done here\n");
}

boolean
isValidKAgainstImageSize(const int k, const int image_size) {
    if (image_size % k == 0) {
        return TRUE;
    }
    return FALSE;
}

void
distribute(BYTE *image, int image_size, BYTE **shadow_images, char* directory, int n, int k,
           int bits_to_hide,
           int seed, main_error *err) {
    /* step 1 - Use a key to generate a permutation sequence to permute the pixels
     of the secret image.
     */
    //    randomize(seed);
    //    shufflePixels(n, image);
    
    /* step 2 - Sequentially read in gray values of D* and then store in E according to the rule below.
     For each read-in gray value pi of D* :
     2.1. If pi<=250; then store pi in E:
     2.2. If pi>250; then split pi into two values 250 and (pi - 250).
     Store these two values in E (first 250, then pi - 250).
     */
    BYTE *E = convertImageToArrayWithLoss(image, image_size);
    
    // we are cool, so we continue
    BYTE **shadows = createShadows(E, image_size, n, k);
    
    for (int i = 0; i < n; i++) {
        hideInformation(shadow_images[i], shadows[i], image_size/k, err);
    }
}

BYTE*
convertImageToArrayWithLoss(BYTE* image, int image_size) {
    BYTE* converted_image = calloc(image_size, sizeof(BYTE));
    int i, j = 0;
    for (i = 0; i < image_size; i++) {
        if (image[i] >= 250) {
            converted_image[j++] = 250;
        } else {
            converted_image[j++] = image[i];
        }
    }
    return converted_image;
}

BYTE*
convertImageToArrayWithoutLoss(BYTE* image, int image_size, int* new_image_size) {
    BYTE* converted_image = calloc(image_size*2, sizeof(BYTE));
    int i, j = 0;
    for (i = 0; i < image_size; i++) {
        if (image[i] >= 250) {
            converted_image[j++] = 250;
            converted_image[j++] = image[i] - 250;
        } else {
            converted_image[j++] = image[i];
        }
    }
    *new_image_size = j;
    realloc(new_image_size, *converted_image);
    return converted_image;
}

BYTE**
createShadows(BYTE* image, int image_size, int n, int k) {
    int shadow_pixel_index = 0;
    // step 3 - Sequentially, take r not-shared-yet elements of the array E to form an r-pixel section.
    BYTE* section = calloc(k, sizeof(BYTE));
    printf("Creating %d, shadows of size: %d\n with k: %d\n", n, image_size / k, k);
    BYTE** shadows = initializeShadows(image_size, n, k);
    int i;
    printf("Shadows initialized\n");
    // step 5 - Repeat Steps 3 and 4 until all elements of the array E are processed.
    for (i = 0; i < image_size; i++) {
        section[i % k] = image[i];
        if ((i + 1) % k == 0) {
            // step 4 - Generate n pixels for the n shadow images
            evaluateSection(section, shadows, shadow_pixel_index, n, k);
            shadow_pixel_index++;
            memset(section, 0, k);
        }
    }
    printf("Shadows created\n");
    return shadows;
}

void
evaluateSection(BYTE* section, BYTE** shadows, int shadow_pixel_index, int n, int k) {
    int i, j, ans;
    for (i = 1; i <= n; i++) {
        ans = 0;
        for (j = 0; j < k; j++) {
            ans += section[j] * intPow(i, j);
        }
        shadows[i-1][shadow_pixel_index] = ans % MAX_BYTE_VALUE;
    }
}

/*
 * This method assumes that image_size/k is an integer
 */
BYTE **
initializeShadows(int image_size, int n, int k) {
    BYTE** shadows = calloc(n, sizeof(BYTE *)); // aka unsigned char*
    int shadow_size = image_size/k;
    int i;
    for (i = 0; i < n; ++i) {
        shadows[i] = calloc(shadow_size, sizeof(BYTE));
    }
    return shadows;
}

void
hideInformation(BYTE *shadowImage_bytes, BYTE *toHide, int size_to_hide, main_error *err) {
    int bi = 0; // for iterating over shadowImage_bytes
    for (int i = 0; i < size_to_hide; i++) {
        // we iterate over the bytes to hide
        BYTE byte_toHide = toHide[i];
        //        printf("byte to hide: %d binary: ", byte_toHide); int2bin(byte_toHide); printf("\n");
        for (int j = 7; j >= 0; j--) {
            // we iterate over the bits of the byte to hide
            uint8_t bit = getBit(byte_toHide, j);
            //            printf("bit to hide: %d\n", bit);
            BYTE shadowImage_byte = shadowImage_bytes[bi];
            //            printf("porter byte: "); int2bin(shadowImage_byte); printf("\n");
            BYTE porter_byte = overrideLessSignificantBit(shadowImage_byte, bit);
            memcpy(&shadowImage_bytes[bi], &porter_byte, sizeof(BYTE));
            //            printf("porter byte modified: "); int2bin(shadowImage_bytes[bi]); printf("\n");
            bi++;
        }
    }
}

void int2bin(int number) {
    int binaryNumber[100],i=1,j;
    int quotient = number;
    
    while(quotient!=0){
        binaryNumber[i++]= quotient % 2;
        quotient = quotient / 2;
    }
    for(j = i -1 ;j> 0;j--)
        printf("%d",binaryNumber[j]);
    printf("\n");
}
