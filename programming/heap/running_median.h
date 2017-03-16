#ifndef INCLUDED_RUNNING_MEDIAN_H
#define INCLUDED_RUNNING_MEDIAN_H

#include "heap.h"
using namespace std;
using namespace heap;

template <typename retType, typename valType, unsigned MaxVals>
class MedianCalculator {
    Heap<valType, MaxVals/2 + 1, std::greater<valType> > lheap;
    Heap<valType, MaxVals/2 + 1> gheap;
    valType pivot;
    unsigned size;
    retType curMedian;

    int calcSizeDiff() {
        int64_t h1,h2,ret;
        h1 = (int64_t)lheap.size();
        h2 = (int64_t)gheap.size();
        ret = h2 - h1; // pos means gheap has more

        return (int)ret;
    }
        
public:
    MedianCalculator() noexcept {
        size = 0;
    }

    valType getlHeapHead() const {
        if (lheap.size() == 0)
            return 0;
        else {
            valType tmp = lheap.peek_head();
            return tmp;
        }
    }

    valType getgHeapHead() const {
        if (gheap.size() == 0)
            return 0;
        else {
            valType tmp = gheap.peek_head();
            return tmp;
        }
    }

    valType getPivot() const {
        return pivot;
    }

    retType getCurrentMedian() {
        if (size == 0)
            throw int(-1);

        return curMedian;
    }

    retType addValue(valType val) {

        if (size == MaxVals)
            throw int(-1);

        size++;
        if (size == 1) {
            curMedian = pivot = val;
            return val;
        }


        // Insert in correct heap first.
        // Then, see if insertion will alter balance between heaps.
        // (their size must be differ by - at most - one).
        // Adjust if so.
        retType tmp;
        if (val <= pivot) {
            lheap.push(val);
            int sizediff = calcSizeDiff();
            if (sizediff < -1) {
                gheap.push(pivot);
                pivot = lheap.pop();
            }

            if (size % 2 == 0) {
                tmp = static_cast<retType>(lheap.peek_head());
                curMedian = (tmp + static_cast<retType>(pivot)) / 2.0;
            } else {
                curMedian = static_cast<retType>(pivot);
            }

        } else {
            gheap.push(val);    
            int sizediff = calcSizeDiff();
            if (sizediff > 1) {
                lheap.push(pivot);
                pivot = gheap.pop();
            } 
            
            if (size % 2 == 0) {
                tmp = static_cast<retType>(gheap.peek_head());
                curMedian = (tmp + static_cast<retType>(pivot)) / 2.0;
            } else {
                curMedian = static_cast<retType>(pivot);
            }
        }
        
        return curMedian;            
    }
};
#endif
