objects = bin/main.o bin/models/image.o bin/util/hex_to_rgb.o bin/util/image_from_csv.o bin/util/read_file.o bin/visual_modules/image_visual_module.o

bin/led-matrix.out: $(objects) rpi-rgb-led-matrix/Makefile
# Build dependencies
	cd rpi-rgb-led-matrix && $(MAKE)
	cd ..

	g++ bin/*.o bin/**/*.o -L rpi-rgb-led-matrix/lib -Wall -lrgbmatrix -lrt -lm -lpthread -o bin/led-matrix.out

$(objects): bin/%.o: src/%.cpp rpi-rgb-led-matrix/Makefile
	mkdir -p $(@D)
	g++ -c $^ -I rpi-rgb-led-matrix/include -o $@

rpi-rgb-led-matrix/Makefile:
	git clone "https://github.com/hzeller/rpi-rgb-led-matrix" rpi-rgb-led-matrix

clean:
	rm -rf bin/