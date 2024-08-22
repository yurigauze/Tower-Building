CC = g++
CFLAGS = -g -Wall -std=c++23 -I./src/include
LIBS = -lSDL2 -lSDL2_image -lSDL2_ttf -lbox2d
SRCDIR = ./src
OBJDIR = ./obj

# Arquivos fonte no diretório src e Main.cpp
SRCS = $(wildcard $(SRCDIR)/**/*.cpp) $(wildcard ./Main.cpp)
OBJS = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRCS))

all: clear game 
	./game 

game: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)
	
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.o: %.cpp | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

clear:
	rm -f game $(OBJDIR)/*.o
