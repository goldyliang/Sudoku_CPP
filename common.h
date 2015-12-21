/*
 * common.h
 *
 *  Created on: Apr 22, 2015
 *      Author: gordon
 */

#ifndef COMMON_H_
#define COMMON_H_

#define COUNT_NUMCANDSTEPS (9*9)  // 9*9
#define COUNT_POSCANDSTEPS (3*9*9)

#define NUMLIST_STL_
#define AREA_STL_
#define RESOLVER_STL_
#define BOARD_STL_
#define RESOLVER_FAST_REVERSE_
#define RESOLVER_FAST_REVERSE_FILLSTEPS_
//#define FILLSTEP_DYNAMIC_SORT_

//#define INLINE_CONF __attribute__((always_inline))
#define INLINE_CONF

#include <array>

typedef  unsigned int NUM_T;

template <class etyp_>
using ARRAY_9_9_T = std::array <std::array<etyp_,10>,10>;

#endif /* COMMON_H_ */
