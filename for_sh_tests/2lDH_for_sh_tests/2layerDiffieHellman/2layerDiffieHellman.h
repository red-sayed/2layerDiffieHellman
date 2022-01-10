/**
 * @file    2layerDiffieHellman.h
 * @brief   2layerDiffieHellman is a lib which implements advanced DiffieHellman's key exchange algorithm.
 *
 * Copyright (c) 2020-2021 Vladimir Rogozin (vladimir20040609@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */
#ifndef RED_2LAYERDIFFIEHELLMAN_H
#define RED_2LAYERDIFFIEHELLMAN_H

// System libs.
#include <sstream>
#include <stdlib.h>
#include <ctime>
#include <math.h>
#include <string>
#include <random>

// External libs.
#include <boost/multiprecision/cpp_int.hpp>

// RedLibrary.
#include "RedTypes.h"

#define RED2LAYERDIFFIEHELLMAN_VERSION "1.0"

// Kits.
#define RED_2lDH_140m_AUTO  "auto mode enabled 140m"
#define RED_2lDH_280m_AUTO  "auto mode enabled 280m"
#define RED_2lDH_490m_AUTO  "auto mode enabled 490m"
#define RED_2lDH_693m_AUTO  "auto mode enabled 693m"
#define RED_2lDH_1543m_AUTO "auto mode enabled 1543m"

namespace Red {
    /// Creating a template for integers, because we need it to be cross-typed.
    template<class INT_SIZE>
    class TwoLayerDiffieHellman {
        private:
            //
            // Variables.
            //

            /// x = G**a mod P

            INT_SIZE  m_G    = 2, // Base for part 1.
                      m_Pp1  = 5, // P num for part 1.
                     *m_P,        // P num.
                     *m_a1,       // Secret num for part 1.
                     *m_a2;       // Secret num for part 2.

            INT_SIZE m_base; // Base for part 2.


            ///
            /// Different modes.
            ///

            std::string m_mode; // Mode of secret key usage.

            /// 140m kit.
            const unsigned long long int m_range_140m_2  = 8366;
            const unsigned long long int m_range_140m_4  = 5916;
            const unsigned long long int m_range_140m_8  = 4582;
            const unsigned long long int m_range_140m_16 = 3741;

            /// 280m kit.
            const unsigned long long int m_range_280m_2  = 11224;
            const unsigned long long int m_range_280m_4  = 8366;
            const unsigned long long int m_range_280m_8  = 7000;
            const unsigned long long int m_range_280m_16 = 5916;

            /// 490m kit.
            const unsigned long long int m_range_490m_2  = 15427;
            const unsigned long long int m_range_490m_4  = 10908;
            const unsigned long long int m_range_490m_8  = 8774;
            const unsigned long long int m_range_490m_16 = 7483;

            /// 693m kit.
            const unsigned long long int m_range_693m_2  = 18330;
            const unsigned long long int m_range_693m_4  = 12688;
            const unsigned long long int m_range_693m_8  = 10583;
            const unsigned long long int m_range_693m_16 = 9165;

            /// 1543m kit.
            const unsigned long long int m_range_1543m_2  = 26851;
            const unsigned long long int m_range_1543m_4  = 19078;
            const unsigned long long int m_range_1543m_8  = 15427;
            const unsigned long long int m_range_1543m_16 = 13228;


            //
            // Private functions.
            //

            /**
             * @brief power
             *
             * Serves to generate a key using a, b, P.
             * Uses only in part 1.
             *
             * @param a Number which we will modificate.
             * @param b Chosen private key.
             * @param P Result number.
             *
             * @return Generated key.
             */
            inline INT_SIZE * power(const INT_SIZE *a, const INT_SIZE *b, const INT_SIZE *P) const {
                if (*b == 1) {
                    INT_SIZE *res = new INT_SIZE;
                    *res = *a;
                    return res;

                } else {
                    // Unfortunately we have to write a lot here, because there is no a good way to write it shorter.
                    // So, let's do that!

                    /// Need to get cpp_int version of base.
                    boost::multiprecision::cpp_int a_c = boost::multiprecision::cpp_int(*a);

                    /// And ui version of our exponent.
                    Red::uint_t b_int = 0;

                    {
                        std::stringstream ss;
                        ss << *b;
                        ss >> b_int;
                    }

                    /// Let's get exponented 'a'...
                    boost::multiprecision::cpp_int ab = boost::multiprecision::pow(a_c, b_int);

                    /// Now we need cpp_int version of 'P'.
                    boost::multiprecision::cpp_int p_c = 0;

                    {
                        std::stringstream ss;
                        ss << *P;
                        ss >> p_c;
                    }

                    /// Moded expenented 'a' is needed...
                    boost::multiprecision::cpp_int abp = ab % p_c;

                    /// Now we just need to convert it to the type we need.
                    INT_SIZE *res = new INT_SIZE;

                    {
                        std::stringstream ss;
                        ss << abp;
                        ss >> *res;
                    }

                    /// Yay, we finished this.
                    return res;
                }
            }

            /**
             * @brief power_2_pub
             *
             * Serves to generate a key using a, b, P.
             * Used only in part 2.
             *
             * @param a Number which we will modificate.
             * @param b Chosen private key.
             * @param P Result number.
             *
             * @return Generated key.
             */
            inline INT_SIZE * power_2_pub(const INT_SIZE *a, const unsigned long long int& b, const INT_SIZE *P) const {
                // Unfortunately we have to write a lot here, because there is no a good way to write it shorter.
                // So, let's do that (again)!

                /// Need to get cpp_int version of base.
                boost::multiprecision::cpp_int a_c = boost::multiprecision::cpp_int(*a);

                /// And ui version of a random(if needed) exponent.
                srand(time(0));
                Red::uint_t b_int;

                *m_a2 = (unsigned int) rand() % b;

                if ((b - *m_a2) >= 2) {
                    *m_a2 += 2;
                }

                {
                   std::stringstream ss;
                   ss << *m_a2;
                   ss >> b_int;
                }

                /// Let's get exponented 'a'...
                boost::multiprecision::cpp_int ab = boost::multiprecision::pow(a_c, b_int);

                /// Now we need cpp_int version of 'P'.
                boost::multiprecision::cpp_int p_c = 0;

                {
                    std::stringstream ss;
                    ss << *P;
                    ss >> p_c;
                }

                /// Moded expenented 'a' is needed...
                boost::multiprecision::cpp_int abp = ab % p_c;

                /// Now we just need to convert it to the type we need.
                INT_SIZE *res = new INT_SIZE;

                {
                    std::stringstream ss;
                    ss << abp;
                    ss >> *res;
                }

                /// Yay, we finished this.
                return res;
            }

            /**
             * @brief power_2_sync
             *
             * Serves to generate a key using a, b, P.
             * Used only in part 2.
             *
             * @param a Number which we will modificate.
             * @param b Chosen private key.
             * @param P Result number.
             *
             * @return Generated key.
             */
            inline INT_SIZE * power_2_sync(const INT_SIZE *a, const INT_SIZE *b, const INT_SIZE *P) const {
                // Unfortunately we have to write a lot here, because there is no a good way to write it shorter.
                // So, let's do that (again)!

                /// Need to get cpp_int version of base.
                boost::multiprecision::cpp_int a_c = boost::multiprecision::cpp_int(*a);

                /// And ui version of a random(if needed) exponent.
                Red::uint_t b_int;

                {
                   std::stringstream ss;
                   ss << *b;
                   ss >> b_int;
                }

                /// Let's get exponented 'a'...
                boost::multiprecision::cpp_int ab = boost::multiprecision::pow(a_c, b_int);

                /// Now we need cpp_int version of 'P'.
                boost::multiprecision::cpp_int p_c = 0;

                {
                    std::stringstream ss;
                    ss << *P;
                    ss >> p_c;
                }

                /// Moded expenented 'a' is needed...
                boost::multiprecision::cpp_int abp = ab % p_c;

                /// Now we just need to convert it to the type we need.
                INT_SIZE *res = new INT_SIZE;

                {
                    std::stringstream ss;
                    ss << abp;
                    ss >> *res;
                }

                /// Yay, we finished this.
                return res;
            }

        public:
            /**
             * @brief TwoLayerDiffieHellman
             *
             * GeneratedKey = G**a mod P
             *
             * Where,
             * @param ModificatedNum P number.
             * @param SecretNum1 Secret number 1.
             * @param SecretNum2 Secret number 2.
             * @param Mode Mode of secret key usage.
             */
            TwoLayerDiffieHellman(INT_SIZE *ModificatedNum = 0,
                                  INT_SIZE *SecretNum1 = 0,
                                  INT_SIZE *SecretNum2 = 0,
                                  std::string_view Mode = "manual")
                : m_P(ModificatedNum), m_a1(SecretNum1), m_a2(SecretNum2), m_mode(Mode) {}

            /**
             * @brief Set
             *
             * GeneratedKey = G**a mod P
             *
             * Where,
             * @param ModificatedNum P number.
             * @param SecretNum1 Secret number 1.
             * @param SecretNum2 Secret number 2.
             * @param Mode Mode of secret key usage.
             */
            void Set(INT_SIZE *ModificatedNum,
                     INT_SIZE *SecretNum1,
                     INT_SIZE *SecretNum2,
                     std::string_view Mode = "manual") {

                m_P    = ModificatedNum;
                m_a1   = SecretNum1;
                m_a2   = SecretNum2;
                m_mode = Mode;
            }

            /**
             * @brief Part1_GetPublicValue
             *
             * Serves to calculate a value for partner.
             *
             * @return Value for public exchange.
             */
            INT_SIZE * Part1_GetPublicValue() const {
                return power(&this->m_G, this->m_a1, this->m_P);
            }

            /**
             * @brief Part1_GetSymmetricBaseNum
             *
             * Serves to to calculate symmetric value.
             *
             * @param x Partner's key, which we got after exchange part.
             */
            void Part1_GetSymmetricBaseNum(INT_SIZE *x) {
                INT_SIZE *u;

                u = power(x, this->m_a1, &this->m_Pp1);

                std::cout << *u << " - after power function" << std::endl;

                /// Getting a base num.
                if (*u == 1) {
                    m_base = 2;

                } else if (*u == 2) {
                    m_base = 4;

                } else if (*u == 3) {
                    m_base = 8;

                } else if (*u == 4) {
                    m_base = 16;

                } else {
                    throw "[\033[91m2layerDiffieHellman\033[0m]: hello from here!";
                }

                std::cout << m_base<< " - base num" << std::endl << std::endl;
            }

            /**
             * @brief Part2_GetPublicValue
             *
             * Serves to calculate a value for partner.
             *
             * @return Value for public exchange.
             */
            INT_SIZE * Part2_GetPublicValue() const {
                if (m_mode == "manual") {
                    return power(&this->m_base, this->m_a2, this->m_P);

                } else { // auto mode enabled && wrong usage.
                    if (m_mode == "auto mode enabled 140m") {
                        if (m_base == 2) {
                            return power_2_pub(&this->m_base, this->m_range_140m_2, this->m_P);

                        } else if (m_base == 4) {
                            return power_2_pub(&this->m_base, this->m_range_140m_4, this->m_P);

                        } else if (m_base == 8) {
                            return power_2_pub(&this->m_base, this->m_range_140m_8, this->m_P);

                        } else if (m_base == 16) {
                            return power_2_pub(&this->m_base, this->m_range_140m_16, this->m_P);
                        }

                    } else if (m_mode == "auto mode enabled 280m") {
                        if (m_base == 2) {
                            return power_2_pub(&this->m_base, this->m_range_280m_2, this->m_P);

                        } else if (m_base == 4) {
                            return power_2_pub(&this->m_base, this->m_range_280m_4, this->m_P);

                        } else if (m_base == 8) {
                            return power_2_pub(&this->m_base, this->m_range_280m_8, this->m_P);

                        } else if (m_base == 16) {
                            return power_2_pub(&this->m_base, this->m_range_280m_16, this->m_P);
                        }

                    } else if (m_mode == "auto mode enabled 490m") {
                        if (m_base == 2) {
                            return power_2_pub(&this->m_base, this->m_range_490m_2, this->m_P);

                        } else if (m_base == 4) {
                            return power_2_pub(&this->m_base, this->m_range_490m_4, this->m_P);

                        } else if (m_base == 8) {
                            return power_2_pub(&this->m_base, this->m_range_490m_8, this->m_P);

                        } else if (m_base == 16) {
                            return power_2_pub(&this->m_base, this->m_range_490m_16, this->m_P);
                        }

                    } else if (m_mode == "auto mode enabled 693m") {
                        if (m_base == 2) {
                            return power_2_pub(&this->m_base, this->m_range_693m_2, this->m_P);

                        } else if (m_base == 4) {
                            return power_2_pub(&this->m_base, this->m_range_693m_4, this->m_P);

                        } else if (m_base == 8) {
                            return power_2_pub(&this->m_base, this->m_range_693m_8, this->m_P);

                        } else if (m_base == 16) {
                            return power_2_pub(&this->m_base, this->m_range_693m_16, this->m_P);
                        }

                    } else if (m_mode == "auto mode enabled 1543m") {
                        if (m_base == 2) {
                            return power_2_pub(&this->m_base, this->m_range_1543m_2, this->m_P);

                        } else if (m_base == 4) {
                            return power_2_pub(&this->m_base, this->m_range_1543m_4, this->m_P);

                        } else if (m_base == 8) {
                            return power_2_pub(&this->m_base, this->m_range_1543m_8, this->m_P);

                        } else if (m_base == 16) {
                            return power_2_pub(&this->m_base, this->m_range_1543m_16, this->m_P);
                        }

                    } else { // As 140m mode.
                        if (m_base == 2) {
                            return power_2_pub(&this->m_base, this->m_range_140m_2, this->m_P);

                        } else if (m_base == 4) {
                            return power_2_pub(&this->m_base, this->m_range_140m_4, this->m_P);

                        } else if (m_base == 8) {
                            return power_2_pub(&this->m_base, this->m_range_140m_8, this->m_P);

                        } else if (m_base == 16) {
                            return power_2_pub(&this->m_base, this->m_range_140m_16, this->m_P);
                        }
                    }
                }
            }

            /**
             * @brief Part2_GetSymmetricSecret
             *
             * Serves to to calculate the final value.
             *
             * @param x Partner's key, which we got after exchange operation.
             *
             * @return Final num
             */
            INT_SIZE * Part2_GetSymmetricSecret(INT_SIZE *x) const {
                return power(x, this->m_a2, this->m_P);
            }

            // Base dtor.
            ~TwoLayerDiffieHellman() {}
    };
}

#endif // RED_2LAYERDIFFIEHELLMAN_H
