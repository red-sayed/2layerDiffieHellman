#include <stdio.h>
#include <math.h>
#include <random>
#include <chrono>

#include "2layerDiffieHellman/2layerDiffieHellman.h"
#include "2layerDiffieHellman/RedTypes.h"

int main() {
    Red::uint65536_t P = -1, a1, a2, b1, b2;
    srand(time(0));

    // Generating secrets.
    a1 = rand() % RED_2lDH_RANDOM_A1_KEY_70m; //rand() % RED_2lDH_RANDOM_A1_KEY_70m + 2; // also there're _105m, _126m, _238m, _336m.
    a2 = 6000;

    b1 = 2; // rand() % RED_2lDH_RANDOM_A1_KEY_70m + 2;
    b2 = 6000;

    Red::TwoLayerDiffieHellman<Red::uint65536_t> Alice(&P, &a1, &a2/*, RED_2lDH_6k_AUTO*/); // Also there're _8k_, _11k_, _16k_, _20k_.
    Red::TwoLayerDiffieHellman<Red::uint65536_t> Bob(&P, &b1, &b2); // Will set 8k automatically.

    std::cout << std::endl;
    std::cout << "The private keys('a1 : a2') for Alice : " << a1 << " : " << a2 << std::endl;
    std::cout << "The private keys('b1 : b2') for Bob   : " << b1 << " : " << b2 << std::endl << std::endl;

    // Generating public keys.
    Red::uint65536_t *Pa = Alice.Part1_GetPublicValue();
    Red::uint65536_t *Pb = Bob.Part1_GetPublicValue();

    std::cout << "Pa: " << *Pa << std::endl << std::endl;
    std::cout << "Pb: " << *Pb << std::endl << std::endl;

    // Generating a pair of a base num.
    Alice.Part1_GetSymmetricBaseNum(Pb);
    Bob.Part1_GetSymmetricBaseNum(Pa);

    auto start = std::chrono::system_clock::now();

    // Generating a num.
    Red::uint65536_t *ValueA = Alice.Part2_GetPublicValue();
    Red::uint65536_t *ValueB = Bob.Part2_GetPublicValue();

    // Getting the result pair.
    Red::uint65536_t *Sa = Alice.Part2_GetSymmetricSecret(ValueB);
    Red::uint65536_t *Sb = Bob.Part2_GetSymmetricSecret(ValueA);

    auto duration = (std::chrono::system_clock::now() - start) * 0.000001;

    std::cout << "Secret key for the Alice is : " << *Sa << std::endl << std::endl << std::endl;
    std::cout << "Secret Key for the Bob is   : " << *Sb << std::endl;
    std::cout << std::endl << std::endl;

    std::cout << "Time spent: " << duration.count() << " seconds, ~" << 1 / float(duration.count()) << " cycles/sec" << std::endl;

    // How to use one more time the 2lDH object?
    //
    // Like this:
    //
    // Alice.Set(-newP-,-newA1-,-newA2-,-mode-);

    // Freeing up memory.
    delete Pa;
    delete Pb;
    delete ValueA;
    delete ValueB;
    delete Sa;
    delete Sb;

    return 0;
}
