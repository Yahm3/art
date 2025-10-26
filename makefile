TARGET = main.o 

SRC = main.c

CFALG = gcc -Wall #-std=c23

$(TARGET):
	$(CFALG) $(SRC) -o $(TARGET)

run: 
	./$(TARGET)

clean: 
	rm -v $(TARGET)

.PHONY:all clean

#Still keeping it simple and minimal
