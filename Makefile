cmake:
	@-cmake -B build -S . 

build: src/*
	@-if [ ! -d "build" ]; then \
		cmake -B build -S . ; \
	fi
	@-cmake --build build

run:
	@-build/http-server 

clean:
	@-rm -rf build

format:
	@-find src/ -iname *.h -o -iname *.?pp | xargs clang-format -i
