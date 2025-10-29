TARGET = main.o 

SRCDIR = src
INCLUDEDIR = include
#BUILDIR = build

CFLAG = gcc -Wall #-std=c23
SRC_MAIN_PROJECT = $(SRCDIR)/main.c\
									$(SRCDIR)/animation.c\
									$(SRCDIR)/argparse.c\
									$(SRCDIR)/car_patterns.c\
									$(SRCDIR)/help.c

#$(BUILDIR):
#@mkdir -p $(BUILDIR)

$(TARGET):
	$(CFLAG) $(SRC_MAIN_PROJECT) -o $(TARGET)

run: 
	./$(TARGET)

clean: 
	rm -v $(TARGET)

.PHONY:all clean

#Still keeping it simple and minimal
