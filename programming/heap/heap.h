#ifndef INCLUDED_HEAP_H
#define INCLUDED_HEAP_H

#include <array>
#include <assert.h>
#include <iterator>
#include <exception>

using namespace std;

namespace heap {
    enum REASON {EMPTY_HEAP = 0, FULL_HEAP = 1, OOB_ACCESS = 2, UNKNOWN = 999};

    class HeapException : exception {
        enum REASON reason;
        public:
        const char * reason_str[4] = {"Tried to remove item from empty heap!",
            "Tried to insert item into a heap with max elements!",
            "Out-of-bounds access to underlying heap container!",
            "Unknown error!"};

        HeapException(REASON r) noexcept {
            reason = r;
        }

        virtual const char * what() const noexcept override {
            switch(reason) {
                case EMPTY_HEAP:
                    return reason_str[EMPTY_HEAP];
                case FULL_HEAP:
                    return reason_str[FULL_HEAP];
                case OOB_ACCESS:
                    return reason_str[OOB_ACCESS];
                default:
                    return reason_str[UNKNOWN];
            }
        }
    };

    template <typename T, unsigned Max, typename Compare>
        class HeapIterator;

    template <typename T, unsigned Max, 
             typename Compare = std::less<T> >
                 class Heap {
                     array<T, Max> base_arr;
                     unsigned heapsize;
                     Compare c;

                     friend class HeapIterator<T,Max,Compare>;

                     inline int parent_idx(int idx) {
                         if (idx == 0)
                             return -1;

                         return (idx - 1)/2;
                     }

                     inline int lchild_idx(int idx) {
                         int i = 2 * idx + 1;
                         return (i < (int)heapsize)?i:-1;
                     }

                     inline int rchild_idx(int idx) {
                         int i = 2 * idx + 2;
                         return (i < (int)heapsize)?i:-1;
                     }

                     inline void swap_on_idx(int idx1, int idx2) {
                         T tmp = base_arr[idx1];
                         base_arr[idx1] = base_arr[idx2];
                         base_arr[idx2] = tmp;
                     }

                     void heapify_up() noexcept {
                         int idx = heapsize-1;
                         int pidx;

                         assert(heapsize <= Max);

                         while((pidx = parent_idx(idx)) != -1) {
                             if (c(base_arr[pidx], base_arr[idx]))
                                 break;
                             else {
                                 swap_on_idx(pidx, idx);
                             }
                             idx = pidx;
                         }
                     }

                     void sift_down() noexcept {
                         int idx = 0;
                         int lcidx, rcidx; // left and right children indexes 
                         int chosenidx;

                         assert(heapsize >= 2 && heapsize <= Max);

                         while ((idx < (int)(heapsize - 1))) {
                             lcidx = lchild_idx(idx);
                             rcidx = rchild_idx(idx);

                             if (lcidx != -1) {
                                 chosenidx = 
                                     c(base_arr[lcidx], base_arr[idx])?lcidx:idx;
                                 if (rcidx != -1)
                                     chosenidx = 
                                         c(base_arr[rcidx], base_arr[chosenidx])?rcidx:chosenidx;
                             }

                             if (chosenidx == idx)
                                 break;

                             swap_on_idx(idx, chosenidx);

                             idx = chosenidx;    
                         }

                     }

                     public:
                     Heap() {
                         heapsize = 0;
                     }

                     T pop() {
                         T retval;
                         if (heapsize == 0) {
                             throw HeapException(EMPTY_HEAP);
                         }

                         heapsize--;
                         retval = base_arr[0];
                         if (heapsize == 0) // No elements 
                             return retval;

                         swap_on_idx(0, heapsize);

                         if (heapsize == 1)
                             return retval;

                         sift_down();

                         return retval;
                     }

                     Heap &push(T val) {
                         if (heapsize == Max)
                             throw HeapException(FULL_HEAP);

                         base_arr[heapsize] = val;
                         heapsize++;
                         if (heapsize == 1) {
                             return *this;
                         }

                         heapify_up();

                         return *this;
                     }

                     T peek_head() const {
                         if (heapsize == 0) {
                             throw HeapException(EMPTY_HEAP); 
                         }

                         return base_arr[0];
                     }

                     inline const array<T,Max> & get_base_array() {
                         return base_arr;
                     }

                     HeapIterator<T,Max,Compare> begin() {
                         HeapIterator<T,Max,Compare> hi(*this, 0);

                         return hi;
                     }

                     HeapIterator<T,Max,Compare> end() {
                         HeapIterator<T,Max,Compare> hi(*this, heapsize);

                         return hi;
                     }

                     unsigned size() const {
                         return heapsize;
                     }
                 };

    template <typename T, unsigned Max, typename Compare = std::less<T> >
        class HeapIterator : public std::iterator<std::forward_iterator_tag, T> {
            Heap<T,Max,Compare> heap;
            int idx;
            public:
            HeapIterator(Heap<T,Max,Compare>& h, int i): heap(h), idx(i) {}
            HeapIterator& operator++() {++idx; return *this;}
            bool operator==(const HeapIterator& rhs) {return rhs.idx == idx;}
            bool operator!=(const HeapIterator& rhs) {return rhs.idx != idx;}
            T& operator*() {
                if (idx < 0 || idx > (int)heap.heapsize)
                    throw HeapException(OOB_ACCESS);

                return heap.base_arr[idx]; 
            }
        };

}

#endif
