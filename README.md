# Steganography in images #
> Hiding Data Within Data
>>  By Alderete, De la Puerta, Menzella & Romarion.
## Criptography & security ##
### ITBA ###

You may be wondering...how do I run this amazing app?
Well, it's easy.

SSIApp -d | -r [-dir <DIRECTORY>] [-h] -k <NUMBER> [-n <NUMBER>]  -s <IMAGE>

 -d,--distribute                Distribute a source image into other shadow images
 -dir,--directory <DIRECTORY>   Either he directory where the images where the secret will be
                                distributed (in case you have chosen the option (-d)), or where
                                images containing hidden secret (in case they are chosen option
                                (-r)). If not used, the program will search the images in the
                                current directory.
 -h,--help                      Print help
 -k,--mshadows <NUMBER>         Minimum amount of shadows needed to recover the secret image
 -n,--fshadows <NUMBER>         Final amount of shadows where the image will be distributed
 -r,--recover                   Recover a secret image from k source images
 -s,--secret <IMAGE>            Either source image to distribute (in case you have chosen the
                                option (d)) or recovered image (in case they are chosen option (-r))

All rights reserved
