OBJDIR := bin
OPTIONS := -Wall -std=c++11

all: $(OBJDIR)/heap_test $(OBJDIR)/median_calc


$(OBJDIR)/median_calc: main.cpp heap.h running_median.h | $(OBJDIR)
	$(CXX) $(OPTIONS) -o $@ $<

$(OBJDIR)/heap_test: main_heap.cpp heap.h | $(OBJDIR)
	$(CXX) $(OPTIONS) -DTESTHEAP -o $@ $<

$(OBJDIR):
	mkdir $(OBJDIR)

.PHONY: clean
clean:
	rm -f *.o $(OBJDIR)/*

