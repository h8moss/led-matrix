commonObjects = bin/common/util/array_to_vector.o bin/common/util/split_string.o bin/common/models/color.o bin/common/canvas/drawLine.o bin/common/canvas/textDrawer.o bin/common/util/padZeros.cpp
colorsObjects = bin/modules/colors/colors_configuration.o bin/modules/colors/main.o bin/modules/colors/parse_arguments.o
golObjects = bin/modules/game-of-life/game_of_life_configuration.o bin/modules/game-of-life/main.o bin/modules/game-of-life/parse_arguments.o
timeDateObjects = bin/modules/time-date/main.o

all: bin/modules/colors/colors.out bin/modules/game-of-life/game_of_life.out bin/modules/time-date/time_date.out

bin/modules/colors/colors.out: $(colorsObjects) $(commonObjects) rpi-rgb-led-matrix/Makefile
	cd rpi-rgb-led-matrix && $(MAKE)
	cd ..

	g++ $(commonObjects) $(colorsObjects) -L rpi-rgb-led-matrix/lib -Wall -Weffc++ -Wextra -Wconversion -Wsign-conversion -lrgbmatrix -lrt -lm -lpthread -o bin/modules/colors/colors.out

bin/modules/game-of-life/game_of_life.out: $(golObjects) $(commonObjects) rpi-rgb-led-matrix/Makefile
	cd rpi-rgb-led-matrix && $(MAKE)
	cd ..

	g++ $(commonObjects) $(golObjects) -L rpi-rgb-led-matrix/lib -Wall -Weffc++ -Wextra -Wconversion -Wsign-conversion -lrgbmatrix -lrt -lm -lpthread -o bin/modules/game-of-life/game_of_life.out

bin/modules/time-date/time_date.out: $(timeDateObjects) $(commonObjects) rpi-rgb-led-matrix/Makefile
	cd rpi-rgb-led-matrix && $(MAKE) && cd ..

	g++ $(commonObjects) $(timeDateObjects) -L rpi-rgb-led-matrix/lib -Wall -Weffc++ -Wextra -Wconversion -Wsign-conversion -lrgbmatrix -lrt -lm -lpthread -o bin/modules/time-date/time_date.out

$(commonObjects) $(colorsObjects) $(golObjects) $(timeDateObjects): bin/%.o: src/%.cpp rpi-rgb-led-matrix/Makefile
	mkdir -p $(@D)
	g++ -c $< -I rpi-rgb-led-matrix/include -o $@

rpi-rgb-led-matrix/Makefile:
	git clone "https://github.com/hzeller/rpi-rgb-led-matrix" rpi-rgb-led-matrix

clean:
	rm -rf bin

.PHONY: all clean
