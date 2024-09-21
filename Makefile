all: prepare
	cd build && cmake .. && cmake --build . -j16

dependency:
	cd build && cmake .. --graphviz=graph.dot && dot -Tpng graph.dot -o graph_image.png

prepare:
	rm -rf build
	mkdir build

install:
	sudo apt-get install gcc g++ cmake make doxygen git llvm pkg-config curl zip unzip tar python3-dev clang-format clang-tidy
