all: heap_test median_calc

.PHONY: bindir
bindir:
	if [ ! -d bin ]; then \
		mkdir bin; \
	fi

median_calc: main.cpp running_median.h bindir
	g++ -Wall -std=c++11 -o bin/$@ $<

heap_test: main_heap.cpp bindir
	g++ -Wall -DTESTHEAP -std=c++11 -o bin/$@ $<

.PHONY: clean
clean:
	rm -f *.o bin/*

