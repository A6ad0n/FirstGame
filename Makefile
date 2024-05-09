TARGET = project
CC = clang++
CCFLAGS = -std=c++14 -Wall -Wextra

SFML_INCLUDE = -I./dependecies/include/
SFML_LIB = -L./dependecies/lib/ -lsfml-graphics -lsfml-window -lsfml-system

PREF_SRC = ./src/
PREF_OBJ = ./obj/

SRC = $(wildcard $(PREF_SRC)*.cpp)
OBJ = $(patsubst $(PREF_SRC)%.cpp, $(PREF_OBJ)%.o, $(SRC))

$(TARGET) : $(OBJ)
	$(CC) $(CCFLAGS) $(SFML_INCLUDE) -o $(TARGET) $(OBJ) $(SFML_LIB)

$(PREF_OBJ)%.o : $(PREF_SRC)%.cpp
	$(CC) $(CCFLAGS) $(SFML_INCLUDE) -c $< -o $@

open : $(TARGET)
	./$(TARGET)
	rm $(TARGET) $(PREF_OBJ)*.o

clean :
	rm $(PREF_OBJ)*.o