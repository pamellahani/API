
# utilisation des règles implicites connues par Make
# pour compiler de nombreux langages
# Ces règles (et les variables utilisée) sont visibles en lançant "make -p"

# Nésitez pas à ajuster ces variables si nécessaires
CC=gcc
# "-MMD -MF .$*.d" permet de faire générer un fichier
# de dépendance qui sera inclus par Make (cf 'include' plus bas)
CFLAGS=-O2 -g -MMD -MF .$*.d
CPPFLAGS=-I. -Wall -Werror #-Wextra
LDLIBS=-lm

# Liste des implémentations
# Une implémentation de nom NAME doit être placée dans le dossier
# implementations/NAME/
# On doit y trouver :
# - un fichier "public.h" : déclarations publiques
# - un fichier "code.c" : code de l'implémentation
IMPLEMENTATIONS=double # double circ-simple circ-double

# Liste des programmes à compiler avec les différentes implémentations
PROGS=test-API-liste test-queue test-API-maillon

# test-queue a plusieurs fichiers sources, on peut l'indiquer ici.
# chacun de ces fichiers sera compilé avec chacune des implémentations
# pour produire autant de binaires que d'implémentations.
test-queue_SOURCES=test-queue.c queue.c

test-API-maillon_SOURCES = test-API-maillon.c 

# cible 'all' par défaut (la première du fichier)
all:

#############################################################
# Fin de la configuration utilisateur
#############################################################

test: all

# Liste des binaires construits
BINARIES=

# mettre DEBUG à 1 pour débogguer les règles générées
DEBUG=


#############################################################
# règles générées pour chaque implémentation
define add-impl # $1: implementation
$$(if $$(DEBUG),$$(warning "Ajout de l'implémentation $1"))

$1-code.o: implementations/$1/code.c
	$$(COMPILE.c) $$(OUTPUT_OPTION) $$<
$1-code.o: CPPFLAGS+=-Iimplementations/$1

$1-common.o: implementations/common.c
	$$(COMPILE.c) $$(OUTPUT_OPTION) $$<
$1-common.o: CPPFLAGS+=-Iimplementations/$1

%-$1.o: %.c
	$$(COMPILE.c) $$(OUTPUT_OPTION) $$<
%-$1.o: CPPFLAGS+=-Iimplementations/$1

endef
#############################################################

#############################################################
# règles générées pour chaque couple programme/implémentation
define add-program-impl # $1: program $2: implementation
$$(if $$(DEBUG),$$(warning "Ajout du programme $1 avec l'implémentation $2"))

$1-$2: $$(patsubst %.c,%-$2.o,$$(if $$($1_SOURCES),$$($1_SOURCES),$1.c)) \
	$2-code.o $2-common.o

.PHONY: $1 run-$1-$2 run-$1
$1: $1-$2

run-$1-$2: $1-$2
	@printf "\nExécution du programme $1 avec l'implémentation $2\n"
	./$1-$2

run-$1: run-$1-$2

test: run-$1

BINARIES += $1-$2
endef
#############################################################

#############################################################
# génération dynamique des règles
$(foreach i,$(IMPLEMENTATIONS), \
	$(eval $(call add-impl,$i)) \
	$(foreach p,$(PROGS), \
		$(eval $(call add-program-impl,$p,$i))))
#############################################################

# on contruit tous les programmes 
all: $(BINARIES)

# on inclut les fichiers de dépendance autogénérés
include $(wildcard .*.d)

# cibles qui ne sont pas réellement à construire
# (pas de fichier nommés 'all' ou 'clean')
.PHONY: all clean all test

clean:
	$(RM) $(BINARIES) *.o .*.d

archive: clean
	tar cvzf archive.tar.gz --exclude "*.tar.gz" --exclude ".*" --exclude "*~" *
