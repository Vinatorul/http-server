cmake-server:
	@-cmake -B build -S . 

build-server: 
	@-if [ ! -d "build" ]; then \
		cmake -B build -S . ; \
	fi
	@-cmake --build build

run-server:
	@-build/http-server 

clean:
	@-rm -rf build

format:
	@-find . -iname *.h -o -iname *.?pp | xargs clang-format -i
