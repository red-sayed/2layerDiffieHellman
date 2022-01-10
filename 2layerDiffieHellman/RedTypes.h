/**
 * @file    RedTypes.h
 * @brief   RedTypes is a lib which serves to compress int and char definitions.
 * Copyright (c) 2020-2021 Vladimir Rogozin (vladimir20040609@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */
#ifndef RED_TYPES_H
#define RED_TYPES_H

#include <boost/multiprecision/cpp_int.hpp>

#define REDTYPES_VERSION "1.2"

namespace Red {
    // Standart size.
    typedef unsigned char           uint8_t;
    typedef unsigned short      int uint16_t;
    typedef unsigned            int uint_t;
    typedef unsigned long  long int uint32_t;
    typedef signed   char           int8_t;
    typedef signed   short      int int16_t;
    typedef signed              int int_t;
    typedef signed   long  long int int32_t;

    // Long size.
    using uint512_t  = boost::multiprecision::number<boost::multiprecision::cpp_int_backend<512,  512,  boost::multiprecision::unsigned_magnitude, boost::multiprecision::unchecked, void>, boost::multiprecision::et_off>;
    using uint1024_t = boost::multiprecision::number<boost::multiprecision::cpp_int_backend<1024, 1024, boost::multiprecision::unsigned_magnitude, boost::multiprecision::unchecked, void>, boost::multiprecision::et_off>;
    using uint2048_t = boost::multiprecision::number<boost::multiprecision::cpp_int_backend<2048, 2048, boost::multiprecision::unsigned_magnitude, boost::multiprecision::unchecked, void>, boost::multiprecision::et_off>;
    using uint4096_t = boost::multiprecision::number<boost::multiprecision::cpp_int_backend<4096, 4096, boost::multiprecision::unsigned_magnitude, boost::multiprecision::unchecked, void>, boost::multiprecision::et_off>;
    using uint8192_t = boost::multiprecision::number<boost::multiprecision::cpp_int_backend<8192, 8192, boost::multiprecision::unsigned_magnitude, boost::multiprecision::unchecked, void>, boost::multiprecision::et_off>;
    using uint16384_t = boost::multiprecision::number<boost::multiprecision::cpp_int_backend<16384, 16384, boost::multiprecision::unsigned_magnitude, boost::multiprecision::unchecked, void>, boost::multiprecision::et_off>;
    using uint32768_t = boost::multiprecision::number<boost::multiprecision::cpp_int_backend<32768, 32768, boost::multiprecision::unsigned_magnitude, boost::multiprecision::unchecked, void>, boost::multiprecision::et_off>;
    using uint65536_t = boost::multiprecision::number<boost::multiprecision::cpp_int_backend<65536, 65536, boost::multiprecision::unsigned_magnitude, boost::multiprecision::unchecked, void>, boost::multiprecision::et_off>;
    using uint131072_t = boost::multiprecision::number<boost::multiprecision::cpp_int_backend<131072, 131072, boost::multiprecision::unsigned_magnitude, boost::multiprecision::unchecked, void>, boost::multiprecision::et_off>;
    using uint262144_t = boost::multiprecision::number<boost::multiprecision::cpp_int_backend<262144, 262144, boost::multiprecision::unsigned_magnitude, boost::multiprecision::unchecked, void>, boost::multiprecision::et_off>;
    using uint524288_t = boost::multiprecision::number<boost::multiprecision::cpp_int_backend<524288, 524288, boost::multiprecision::unsigned_magnitude, boost::multiprecision::unchecked, void>, boost::multiprecision::et_off>;

}

#endif // RED_TYPES_H
