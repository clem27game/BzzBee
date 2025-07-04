
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -lm
TARGET = main
SOURCE = main.c

.PHONY: all clean test

all: $(TARGET)

$(TARGET): $(SOURCE)
	$(CC) -o $(TARGET) $(SOURCE) $(CFLAGS)

clean:
	rm -f $(TARGET) *.out /tmp/bzzbee_*

test: $(TARGET)
	./$(TARGET) run exemple.bzz

install:
	@echo "BzzBee installé! Utilisez ./main run fichier.bzz"

help:
	@echo "Commandes disponibles:"
	@echo "  make        - Compiler BzzBee"
	@echo "  make test   - Tester avec exemple.bzz"
	@echo "  make clean  - Nettoyer les fichiers temporaires"
	@echo "  make help   - Afficher cette aide"

.DEFAULT_GOAL := all
