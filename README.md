<img src="https://github.com/vladimirrogozin/2layerDiffieHellman/blob/main/KeyExchange_logo.png?raw=true" style="object-fit:contain;
            width:auto;
            height:250px;">

# 2x🔑🔑 2-layer DiffieHellman [![](https://img.shields.io/apm/l/vim-mode)](https://github.com/Red-company/RES_Implementation/blob/main/LICENSE.md)

## What is it?

This is my conception, implementation and tests of advanced(2-layer) _DiifieHellman_(_'2lDH'_ if abbreviated) key exchange _protocol_ that works with _very long inegers_(like 19.729 chars long, can work with bigger ones if needed without any problems). You can find an _example file(main.cpp)_ at this repository with it's description. It is also a part of [_RedLibrary_](https://github.com/Red-company/RedLibrary).

## Why I decided to concept that?

I was understanding how _DiffieHellman_ works and some time later I thought, _DH_ is really good for making _secure client-server messaging channels_, but _I did have an idea_ how to make the algorithm longer but get an opportunity _to hide the base number_ you use. That makes it _more difficult to calculate the shared key_.

## How it works by DH colors?

Basically, _it is the DH_, but 2lDH firstly calculates _the base number_, and _the shared key_ after that. So, that is why it was named _"2-layer DiffieHellman"_. <br/>

So, here you can see the standard _DiffieHellman_ algorithm:

```C
Diffie-Hellman(colors)
======================
 ___            ___
/ m \          / m \ - // 1 Step. We have the same values at the beginning.
\___/          \___/
 _|_            _|_
/m*a\          /m*b\ - // 2 Step. We're getting mixed keys.
\___/\___     /\___/
 ___  __|____/  ___
/m*b\/  |______/m*a\ - // 3 Step. We're exchanging them.
\___/          \___/
 _|_            _|_
/mab\          /mab\ - // 4 Step. Mixing again with secret keys and that will be -THE SHARED KEY-.
\___/          \___/
```

I'm sure you know it, so, I wrote it here to make it easier to compare with my _2-layer DH_. <br/>
Let's have a look of _2-layer DiffieHellman_:

```C
2-layer DiffieHellman(colors)
=============================

Part 1(getting the base)
------------------------
 ___            ___
/ m \          / m \ - // 1 Step. We have the same values at the beginning.
\___/          \___/
 _|_            _|_
/m*x\          /m*y\ - // 2 Step. We're getting mixed keys.
\___/\___     /\___/
 ___  __|____/  ___
/m*y\/  |______/m*x\ - // 3 Step. We're exchanging them.
\___/          \___/
 _|_            _|_
/mxy\          /mxy\ - // 4 Step. Mixing again with secret keys and that will be -THE BASE NUM-.
\___/          \___/


Part 2(getting the shared secret)
---------------------------------

h = mxy    // 'h' is our base num(wrote this just to make it easier).

 ___            ___
/ h \          / h \ - // 1 Step. We have the same base, which is hidden for the Man-In-The-Middle(MITM).
\___/          \___/
 _|_            _|_
/h*a\          /h*b\ - // 2 Step. We're mixing the base with secret keys.
\___/\___     /\___/
 ___  __|____/  ___
/h*b\/  |______/h*a\ - // 3 Step. We're exchanging them.
\___/          \___/
 _|_            _|_
/hab\          /hab\ - // 4 Step. Mixing again with secret keys and that will be -THE SHARED SECRET-.
\___/          \___/

Shared key = hab
----------
```

So, as you can see, that looks like a doubled _DiffieHellman_, and yeah, it is, but, first of all, our _Base Num_ is hidden now, secondly, this _DH_ is ~x2 more secure(check out standards and tests), and, thirdly, we spend _reasonable time_ to get well secured. In fact, there are some _difficulcy modes_ in this library, which gives it an _ability_ to it to be rather _wide-usable_.

## Math behind it

It looks like this:

```C
2-layer DiffieHellman(math scheme)
==================================

P = -1 // The max value of data type.

Part 1(getting a base)
----------------------

1) Public keys.
~~~~~~~~~~~~~~~

/// Getting a public keys.
AlicePublic1 = 2 ** AliceKey1 mod P

BobPublic1 = 2 ** BobKey1 mod P


2) Symmetric base.
~~~~~~~~~~~~~~~~~~

/// Getting the same reminder.
AliceShared = BobPublic1 ** AliceKey1 mod 5

BobShared = AlicePublic1 ** BobKey1 mod 5

/// Getting a base.
if (*u == 1) {
    m_base = 2;
    
} else if (*u == 2) {
    m_base = 4;

} else if (*u == 3) {
    m_base = 8;

} else if (*u == 4) {
    m_base = 16;
}


Part 2(getting the shared secret)
---------------------------------

SharedBase = m_base // Just copied, let's abbreviate.

1) Public keys.
~~~~~~~~~~~~~~~

/// Getting a public keys.
AlicePublic2 = SharedBase ** AliceKey2 mod P

BobPublic2 = SharedBase ** BobKey2 mod P


2) Symmetric Secret.
~~~~~~~~~~~~~~~~~~~~

/// Getting the symmetric pair.
AliceSymmetric = BobPublic2 ** AliceKey2 mod P

BobSymmetric = AlicePublic2 ** BobKey2 mod P


/// Finally.
AliceSymmetric = BobSymmetric
--------------   ------------
```

I am using _Prime number_ equal to _1_, because I want the algorithm _to be un-cutted in range_ in all operations, at the end especially.
