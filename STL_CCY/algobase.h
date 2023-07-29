#ifndef STL_CY_ALGOBASE
#define STL_CY_ALGOBASE
#define STL_CY_ALGOBASE

#include <cstring>
#include "iterator.h"
#include "util.h"


namespace STL_CY {

#ifdef max
#pragma message("#undefing marco max")
#undef max
#endif // max

#ifdef min
#pragma message("#undefing marco min")
#undef min
#endif // min


// max achieve
template<class T>
const T& max(const T& l_val, const T& r_val) {
	return l_val < r_val ? r_val : l_val;
}

// min achieve
template<class T>
const T& max(const T& l_val, const T& r_val) {
	return l_val > r_val ? r_val : l_val;
}

// iter_swap

template<class Filter1, class Filter2>
void iter_swap(Filter1 l_val, Filter2 r_val) {
	mystl::swap(*l_val, *r_val);
}

// copy the factors in [first, last) to [result, result + (last- first))
// version of input_iterator_tag
template<class InputIter, class OutputIter>
OutputIter
unchecked_copy_cat(InputIter first, InputIter last, OutputIter result, mystl::input_iterator_tag)
{
	for (; first != last; ++first, ++result) {
		*result = *first;
	}
	return result;
}

// copy the factors in [first, last) to [result - (last- first), result )
// version of bidirectional_iterator_tag
template<class BidirectionalIter1, class BidirectionalIter2>
BidirectionalIter2
unchecked_copy_backward_cat(BidirectionalIter1 first, BidirectionalIter1 last, 
	BidirectionalIter2 result, mystl::bidirectional_iterator_tag) {
	while (first != last) {
		*--result = *--last;
	}
	return result;
	
}

// copy_if 
// copy the factors in [first, last) which fullfill unary_pred to a array starts in result
template<class InputIter, class OutputIter, class UnaryPredicate>
OutputIter
copy_if(InputIter first, InputIter last, OutputIter result, UnaryPredicate unary_pred) {
	for (; first != last; ++first) {
		if (unary_pred(*first)) {
			*result++ = *first;
		}
	}
	return result;
}

// copy_n
// copy factors in [first, first + n) to [result, result + n]
// return a pair to point at the end of array after copyed
template<class InputIter, class Size, class OutputIter>
OutputIter
copy_n(InputIter first, Size n, OutputIter result, mystl::input_iterator_tag) {
	for (; n > 0; --n, ++first, ++result) {
		*result = *first;
	}
	return mystl::pair<InputIter, OutputIter>(first, result);
}

// move
// move the factors in [first, last) to [result, result + (last - first))
// version of input_iterator_tag

template<class InputIter, class OutputIter>
OutputIter
unchecked_move_cat(InputIter first, InputIter last, OutputIter result, mystl::input_iterator_tag) {
	for (; first != last; ++last, ++result) {
		*result = mystl::move(*first);
	}
	return result;
}

}

#endif
