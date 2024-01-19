commonObjects = bin/common/util/array_to_vector.o bin/common/util/split_string.o
colorsObjects = bin/modules/colors/models/color.o bin/modules/colors/colors_configuration.o bin/modules/colors/main.o bin/modules/colors/parse_arguments.o

bin/modules/colors/colors.out: $(colorsObjects) $(commonObjects) rpi-rgb-led-matrix/Makefile
	cd rpi-rgb-led-matrix && $(MAKE)
	cd ..

	g++ $(commonObjects) $(colorsObjects) -L rpi-rgb-led-matrix/lib -Wall -Weffc++ -Wextra -Wconversion -Wsign-conversion -lrgbmatrix -lrt -lm -lpthread -o bin/modules/colors/colors.out

$(commonObjects) $(colorsObjects): bin/%.o: src/%.cpp rpi-rgb-led-matrix/Makefile
	mkdir -p $(@D)
	g++ -c $< -I rpi-rgb-led-matrix/include -o $@

rpi-rgb-led-matrix/Makefile:
	git clone "https://github.com/hzeller/rpi-rgb-led-matrix" rpi-rgb-led-matrix

clean:
	rm -rf bin/