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
lib = $(libG3X) $(libG3XPP)
# fichiers *.c locaux
src = src/
Inc = include/
# fichiers *.h locaux et lib.
inc = -I./include $(incG3X) $(incG3XPP) 

exec = main

all : $(exec)

main: main.o PMat.o Particle.o FixedPoint.o Link.o HookSpring.o GlobalAction.o Damper.o Wind.o

Link.o: $(src)Link.cpp $(Inc)Link.h PMat.o

HookSpring.o: $(src)HookSpring.cpp $(Inc)HookSpring.h Link.o

GlobalAction.o: $(src)GlobalAction.cpp $(Inc)GlobalAction.h Link.o

Damper.o: $(src)Damper.cpp $(Inc)Damper.h Link.o

PMat.o: $(src)PMat.cpp $(Inc)PMat.h

Particle.o: $(src)Particle.cpp $(Inc)Particle.h PMat.o

FixedPoint.o: $(src)FixedPoint.cpp $(Inc)FixedPoint.h PMat.o

Wind.o: $(src)Wind.cpp $(Inc)Wind.h GlobalAction.o

main.o: $(src)main.cpp

# règle générique de création de xxx.o à partir de src/xxx.c
%.o : $(src)%.cpp
	@echo "module $@"
	@$(CC) $(CFLAGS) $(inc) -c $< -o $@
	@echo "------------------------"

# règle générique de création de l'executable xxx à partir de src/xxx.c (1 seul module)
% : %.o
	@echo "assemblage [$^]->$@"
	@$(CC) $^ $(lib) -o $@
	@echo "------------------------"
	
.PHONY : clean cleanall ?

# informations sur les paramètres de compilation       
? :
	@echo "---------compilation informations----------"
	@echo "  processor      : $(PROCBIT)"
	@echo "  compiler       : $(CC)"
	@echo "  options        : $(CFLAGS)"
	@echo "  lib g3x/OpenGl : $(libG3X)$(COMP)"
	@echo "  headers        : $(incG3X)"
clean : 
	@rm -f *.o
cleanall :
	@rm -f *.o $(exec)
	
