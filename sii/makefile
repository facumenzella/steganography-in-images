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
	@gcc $(BYTE) $(MATH) $(RANDOM) $(FREE) $(ERRORS) $(IMAGES) $(ARGUMENTS) $(DISTRIBUTION) $(SII) -o sii 
	@echo "Remember the arguments"
	@echo "TODO add arguments"
