CC = g++
CFLAGS = -Wall -Wextra -std=c++17
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
INCLUDE = -I/usr/local/include
LIB = -L/usr/local/lib
SRC = src/main.cpp src/game.cpp src/player.cpp src/ai.cpp src/utils.cpp src/ball.cpp src/graphics/canvas.cpp
OBJ = $(SRC:.cpp=.o)
EXEC = coin-soccer-game

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC) $(LIB) $(LDFLAGS)

%.o: %.cpp
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)

run: all
	./$(EXEC)

.PHONY: package
PACKAGE_NAME := coin-soccer-game-$(shell date +%Y%m%d%H%M)
package: all
	mkdir -p dist
	cp $(EXEC) dist/ || true
	zip -r dist/$(PACKAGE_NAME).zip README.md Makefile src assets requirements.txt dist/$(EXEC)
	@echo "Packaged to dist/$(PACKAGE_NAME).zip"

.PHONY: all clean run package