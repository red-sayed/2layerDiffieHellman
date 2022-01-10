/**
 * @file    Randomizer.h
 * @brief   Randomizer is a lib which contains a 'Randomize' function.
 *
 * Copyright (c) 2020-2021 Vladimir Rogozin (vladimir20040609@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */
#ifndef RED_RANDOMIZER_H
#define RED_RANDOMIZER_H

#include <stdlib.h>
#include <time.h>
#include <math.h>

#define REDRANDOMIZER_VERSION "1.0"

namespace Red {
    /**
     * @brief Randomize
     *
     * Used to generate a long random number.
     *
     * @return Long random number.
     */
    inline unsigned long long int Randomize() {
        srand(time(NULL));

        unsigned long long randnumber = 0;
        int digits[20];

        for (int i = 19; i >= 1; i--) {
          digits[i] = rand() % 10;
        }

        for (int i = 19; i >= 1; i--) {
           unsigned long long power = pow(10, i - 1);

            if (power % 2 != 0 && power != 1) {
                power++;
            }

            randnumber += power * digits[i];
        }

        return randnumber;
    }
}

#endif // RED_RANDOMIZER_H
