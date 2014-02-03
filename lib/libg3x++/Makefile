#
# Les variables d'environnement libG3X, incG3X
# sont definies dans le fichier ~/.bashrc par le script ../install.sh
#
#compilateur
CC = g++

#compil en mode 'debug' ou optmisée (-O2)
DBG = no

ifeq ($(DBG),yes) #en mode debug
  CFLAGS = -g -Wpointer-arith -Wall -ansi
else               #en mode normal
  CFLAGS = -O2 -ansi
endif

# assemblage des infos de lib. et inc.
lib = $(libG3X)
# fichiers *.c locaux
src = src/
Inc = include/
# fichiers *.h locaux et lib.
inc = -I./include $(incG3X) 

exec = main

all : libg3x++.so

libg3x++.so: G3Xcoord.o
	@echo "Compile lib $@"
	@$(CC) -shared $(CFLAGS) $(inc) $^ -o $@

G3Xcoord.o: $(src)G3Xcoord.cpp $(Inc)G3Xcoord.h	

%.o : $(src)%.cpp
	@echo "Compile module $@"
	@$(CC) $(CFLAGS) $(inc) -c $< -o $@
	@echo "------------------------"
