TARGET = main.o 

SRCDIR = src
INCLUDEDIR = include
#BUILDIR = build

CFLAG = gcc -Wall #-std=c23
CFLAG_EXTRA = -lncurses -g
SRC_MAIN_PROJECT = $(SRCDIR)/main.c\
									$(SRCDIR)/car_patterns.c\
									$(SRCDIR)/help.c

#$(BUILDIR):
#@mkdir -p $(BUILDIR)

$(TARGET):
	$(CFLAG) $(SRC_MAIN_PROJECT) -o $(TARGET) $(CFLAG_EXTRA)

run: 
	./$(TARGET)

clean: 
	rm -v $(TARGET)

.PHONY:all clean

#Still keeping it simple and minimal
