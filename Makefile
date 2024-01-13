build-project:
	mkdir -p build
	cmake -B build -DGEN_DOCS=OFF
	cmake --build build
