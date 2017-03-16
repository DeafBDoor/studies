all: heap_test median_calc

median_calc: main.cpp running_median.h
	g++ -Wall -std=c++11 -o bin/$@ $<

heap_test: main_heap.cpp 
	g++ -Wall -DTESTHEAP -std=c++11 -o bin/$@ $<

clean:
	rm *.o bin/*
