#include<stdio.h>
#include<math.h>
#include <random>

#include "2layerDiffieHellman/2layerDiffieHellman.h"
#include "2layerDiffieHellman/RedTypes.h"

int main() {
    Red::uint65536_t P, a1, a2, b1, b2;
    srand(time(0));

    P = -1; // A prime number P is taken
    std::cout << "The value of P : " << P << std::endl;

    // Generating secrets.
    a1 = rand() % RED_2lDH_RANDOM_A1_KEY_336m + 2; // also there're _70m, _105m, _126m, _238m, _336.
    a2 = 5;

    b1 = 126; // rand() % RED_2lDH_RANDOM_A1_KEY_336m + 2;
    b2 = 20;

    Red::TwoLayerDiffieHellman<Red::uint65536_t> Alice(&P, &a1, &a2, RED_2lDH_1543m_AUTO); // Also there're _140m_, _280m_, _490m_, _693m_.
    Red::TwoLayerDiffieHellman<Red::uint65536_t> Bob(&P, &b1, &b2); // Or use a custum one.

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

    // Generating a num.
    Red::uint65536_t *ValueA = Alice.Part2_GetPublicValue();
    Red::uint65536_t *ValueB = Bob.Part2_GetPublicValue();

    // Getting the result pair.
    Red::uint65536_t *Sa = Alice.Part2_GetSymmetricSecret(ValueB);
    Red::uint65536_t *Sb = Bob.Part2_GetSymmetricSecret(ValueA);

    std::cout << "Secret key for the Alice is : " << *Sa << std::endl << std::endl << std::endl;
    std::cout << "Secret Key for the Bob is   : " << *Sb << std::endl;
    std::cout << std::endl << std::endl;

    // Freeing up memory.
    delete Pa;
    delete Pb;
    delete ValueA;
    delete ValueB;
    delete Sa;
    delete Sb;

    return 0;
}
