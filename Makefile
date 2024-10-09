CC = g++
CFLAGS = -g -Wall -std=c++23 -I./src/include
LIBS = -L. -lbox2d -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
SRCDIR = ./src
OBJDIR = ./obj

SRCS = $(shell find $(SRCDIR) -name '*.cpp')
OBJS = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRCS))

OBJDIRS = $(sort $(dir $(OBJS)))

all: clear game 
	./game 

game: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)
	
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIRS)
	$(CC) $(CFLAGS) -c $< -o $@
	
$(OBJDIRS):
	mkdir -p $@

clear:
	rm -f game $(OBJS)
	rm -rf $(OBJDIR)
