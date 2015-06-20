CC = gcc
HELP_CMD = help

# C files
BYTE = src/byte/byte.c
MATH = src/math.c
RANDOM = src/random/random.c
FREE = src/free.c
ERRORS = src/errors/errors.c
IMAGES = src/image/*
ARGUMENTS = src/arguments/*
DISTRIBUTION = src/distribution.c
REVEAL = src/reveal.c
SII = sii.c
SII_EXE = sii

help:
	@echo "Available commands:"
	@echo "1) help: Prints this help!! But I guess you already know that"
	@echo "2) sii: Compiles Stenography in Images into sii and leaves it in the current directory"
	@echo "3) clean: Removes sii if exists from current directory"

# clean
clean: 
	@-rm -f $(SII_EXE)
	@echo "sii.c was successfully removed"
	@exit
# sii
# gcc src/byte/byte.c src/math.c src/random/random.c src/free.c src/errors/errors.c src/image/image* src/arguments/* src/distribution.c sii.c -o sii
sii: 
	@-rm -f $(SII_EXE)
	@gcc $(BYTE) $(MATH) $(RANDOM) $(FREE) $(ERRORS) $(IMAGES) $(ARGUMENTS) $(DISTRIBUTION) $(REVEAL) $(SII) -o sii 
	@echo "Remember the arguments:"
	@echo -d[--distribution] Distribution mode.
	@echo -r[--recover] Recover mode.
	@echo -s[--secret] Name of an image of with bmp extension. If you choose distribution mode, its the image to hide. If you choose recover mode, its the output file.
	@echo -k[--minShadows] Minimum amount of shadows to recover secret.
	@echo -n[--totalShadows] Total amount of shadows where the secret will be distributed.
	@echo -dir[--directory] If you choose distribution mode, its the folder where the porter images will be. If you choose recover mode, its the folder where the actual porter images are.

# gcc for debugging mode with lldb or gdb
gcc:
	@gcc -g $(BYTE) $(MATH) $(RANDOM) $(FREE) $(ERRORS) $(IMAGES) $(ARGUMENTS) $(DISTRIBUTION) $(REAVEAL) $(SII) -o sii 
