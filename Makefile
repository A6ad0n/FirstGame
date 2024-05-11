TARGET = project
CC = clang++
CCFLAGS = -std=c++14 -Wall -Wextra

SFML_INCLUDE = -I./dependecies/include/
SFML_LIB = -L./dependecies/lib/ -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

PREF_SRC = ./src/

$(TARGET) :
	$(CC) -o $(TARGET) $(PREF_SRC)*.cpp $(CCFLAGS) $(SFML_INCLUDE) $(SFML_LIB)

open : $(TARGET)
	./$(TARGET)
	rm $(TARGET)

clean : $(TARGET)
	rm $(TARGET);