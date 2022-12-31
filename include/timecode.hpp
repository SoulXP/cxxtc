// Copyright (C) Stefan Olivier
// <https://stefanolivier.com>
// ----------------------------
// Description: Header for cxxtc timecode library

#pragma once

///////////////////////////////////////////////////////////////////////////

// Library headers
#include "timecode_common.hpp"
#include "timecode_basic.hpp"
#include <type_traits>

///////////////////////////////////////////////////////////////////////////

#ifndef VTM_TIMECODE_MACROS
#define VTM_TIMECODE_MACROS

#endif // @END OF VTM_TIMECODE_MACROS

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////
//
//           -- @SECTION Public Interface cxxtc::chrono --
//
///////////////////////////////////////////////////////////////////////////

namespace cxxtc::chrono {

using fps = internal::__FPSFormat<float64_t, int64_t>;

using timecode = internal::__BasicTimecodeInt<int64_t,
                                              float64_t,
                                              std::string,
                                              std::string_view,
                                              fps>;

} // @END OF namespace cxxtc::chrono

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////
//
//           -- @SECTION Public Interface cxxtc --
//
///////////////////////////////////////////////////////////////////////////

namespace cxxtc {

// @SECTION: VTM timecode object aliases
using timecode = chrono::timecode;

// @SECTION: VTM FPS factory object aliases
using fps = chrono::fps;
using fpsfloat_t = typename chrono::fps::float_type;
using fpsint_t = typename chrono::fps::signed_type;
using fpsuint_t = typename chrono::fps::unsigned_type;

} // @END OF namespace cxxtc

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////
//
//           -- @SECTION Extensions to namespace std --
//
///////////////////////////////////////////////////////////////////////////

namespace std {
// @SECTION: __BasicTimecodeInt std::tuplee specialization
template<>
struct tuple_size<cxxtc::timecode> : std::integral_constant<std::size_t, 6>{}; // TODO: constant for magic number

template<std::size_t Index>
struct tuple_element<Index, cxxtc::timecode>
    : tuple_element<Index,
                    tuple<typename cxxtc::timecode::__element1_type,
                          typename cxxtc::timecode::__element2_type,
                          typename cxxtc::timecode::__element3_type,
                          typename cxxtc::timecode::__element4_type,
                          typename cxxtc::timecode::__element5_type,
                          typename cxxtc::timecode::__element6_type >>
{};

} // @END OF namespace std

///////////////////////////////////////////////////////////////////////////
