## Compiler
CC = x86_64-w64-mingw32-g++
CC32 = i686-w64-mingw32-g++

## Delete Commmand
DC = del

## Standard
STD = c++11

## Executables Name
EXE = $(notdir $(CURDIR))

## Project Directories
INCDIR = include
LIBDIR = lib
OBJDIR = obj
SRCDIR = src

## Define Source
SOURCE = Application.cpp ESN.cpp
OBJECT = $(SOURCE:.cpp=.o)
LIBS = 

## Define File
SRC = $(addprefix $(SRCDIR)/, $(SOURCE))
OBJ = $(addprefix $(OBJDIR)/, $(OBJECT))
LIB = $(addprefix -l/, $(LIBS))

## Define Flags
CFLAGS = -c -g3 -Wall -std=$(STD) -I$(INCDIR)
LFLAGS = -L$(LIBDIR) $(LIB)


## Define Scope
all : $(SRC) $(EXE)

## Compile C++ Files
$(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	$(CC) $< $(CFLAGS) -o $@


## Link Object Files
$(EXE) : $(OBJ)
	$(CC) $^ $(LFLAGS) -o $@

## Clean Object Files
clean : $(subst /,\,$(OBJ))
	$(DC) $^
