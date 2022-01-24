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

I am using _Prime number_ equal to _-1_, because I want the algorithm _to be un-cutted in range_ in all operations, at the end especially.

## Standards

I made some _standards_ for each part to use _2lDH_ in way you need. *Let's check them out.* <br/>

> :warning: Also need to say that these ***standards*** were calculated on ***MacBook Air 2017 with Intel Core I5*** processor, that means that on typical anybody's calculator all of these operations ***will be made much faster*** or at least it will be spent +- not more time than I shown.

> ✏️: _sqrt(max) was placed there to show the nums each side need to use as max value to get a private key and if they will equal to each other, to spend not more time than I shown._
<br/><br/>

### Part 1 (getting a base)

| Standard(num of possible variations, millions)| sqrt(max) | base | Time spent(in seconds) |
|-----------------------------------------------|-----------|------|------------------------|
| 70m | 8.366 | 2 | 4,127 |
| 105m | 10.246 | 2 | 8,525 |
| 126m | 11.224 | 2 | 11,799 |
| 238m | 15.427 | 2 | 38,475 |
| 336m | 18.330 | 2 | 71,926 |

5 Standards for _Part 1_. I think that's enough to start, but maybe will add more later. *Let's continue with _Part 2_*.
<br/><br/>

### Part 2 (getting the shared secret)

As it can use different bases, I've separated these tables.

#### 140m

| base | num of possible variations, millions | sqrt(max) | Time spent(in seconds) |
|------|--------------------------------------|-----------|------------------------|
| 2 | 70m | 8.366 | 2,577 |
| 4 | 35m | 5.916 | 2,671 |
| 8 | 21m | 4.582 | 2,394 |
| 16 | 14m | 3.741 | 2,117 |

#### 280m

| base | num of possible variations, millions | sqrt(max) | Time spent(in seconds) |
|------|--------------------------------------|-----------|------------------------|
| 2 | 126m | 11.224 | 7,556 |
| 4 | 70m | 8.366 | 8,081 |
| 8 | 49m | 7.000 | 8,849 |
| 16 | 35m | 5.916 | 8,435 |

#### 490m

| base | num of possible variations, millions | sqrt(max) | Time spent(in seconds) |
|------|--------------------------------------|-----------|------------------------|
| 2 | 238m | 15.427 | 20,362 |
| 4 | 119m | 10.908 | 20,686 |
| 8 | 77m | 8.774 | 19,613 |
| 16 | 56m | 7.483 | 19,165 |

#### 693m

| base | num of possible variations, millions | sqrt(max) | Time spent(in seconds) |
|------|--------------------------------------|-----------|------------------------|
| 2 | 336m | 18.330 | 40,834 |
| 4 | 161m | 12.688 | 41,172 |
| 8 | 112m | 10.583 | 41,572 |
| 16 | 84m | 9.165 | 39,664 |

#### 1543m

| base | num of possible variations, millions | sqrt(max) | Time spent(in seconds) |
|------|--------------------------------------|-----------|------------------------|
| 2 | 721m | 26.851 | 197,268 |
| 4 | 364m | 19.078 | 199,839 |
| 8 | 283m | 15.427 | 196,951 |
| 16 | 175m | 13.228 | 221,794 |
