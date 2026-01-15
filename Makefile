.PHONY: build configure rebuild clean run

configure:
	cmake -S . -B build

build:
	cmake --build build

rebuild: clean configure build

clean:
	rm -rf build

run: build
	./build/ecs_sdl_example

