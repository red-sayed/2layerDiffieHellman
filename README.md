<img src="https://github.com/vladimirrogozin/2layerDiffieHellman/blob/main/KeyExchange_logo.png?raw=true" style="object-fit:contain;
            width:auto;
            height:250px;">

# 2x🔑🔑 2-layer DiffieHellman [![](https://img.shields.io/apm/l/vim-mode)](https://github.com/Red-company/RES_Implementation/blob/main/LICENSE.md)

## What is it?

This is my conception, implementation and tests of advanced(2-layer) _DiifieHellman_(2lDH) key exchange _protocol_ that works with _very long inegers_(like 19.729 chars long, can work with bigger ones without any problems). You can find an _example file(main.cpp)_ at this repository with it's description. It is also a part of [_RedLibrary_](https://github.com/Red-company/RedLibrary).

## Why I decided to concept that?

I was understanding how _DiffieHellman_ works and some time later I thought, _DH_ is really good for making _secure server-client messaging channels_, but _I did have an idea_ how to make the algorithm longer but get an opportunity _to hide the base number_ you use. That makes it _more difficult to calculate the shared key_.

## How it works by DH colors?

Basically, _it is the DH_ but where that firstly calculates _the base number_, and _the shared key_ after that. <br/>

So, here you can see the standard DiffieHellman algorithm:

```
Diffie-Hellman(colors)
 ___            ___
/ m \          / m \ - 1 Step. We have the same values at the beginning.
\___/          \___/
 _|_            _|_
/m*a\          /m*b\ - 3 Step. We're getting mixed keys.
\___/\____    /\___/
 ___  ___|___/  ___
/m*b \/  |_____/m*a\ - 4 Step. We're exchanging them.
\___/          \___/
 _|_            _|_
/mab\          /mab\ - 5 Step. Mixing again with secret keys and that will be THE SHARED KEY.
\___/          \___/
```

I'm sure you know it, so, I wrote it here to make it easier to compare with my 2-layer DH. <br/>
Let's have a look of 2-layer DiffieHellman:

```
2-layer DiffieHellman(colors)
=============================

Part 1(getting the base)
------------------------
 ___            ___
/ m \          / m \ - 1 Step. We have the same values at the beginning.
\___/          \___/
 _|_            _|_
/m*a\          /m*b\ - 3 Step. We're getting mixed keys.
\___/\____    /\___/
 ___  ___|___/  ___
/m*b \/  |_____/m*a\ - 4 Step. We're exchanging them.
\___/          \___/
 _|_            _|_
/mab\          /mab\ - 5 Step. Mixing again with secret keys and that will be THE BASE NUM.
\___/          \___/

Part 2(getting the shared secret)
---------------------------------

h = mab    // 'h' is our base num(just to make easier).

 ___            ___
/ h \          / h \ - 1 Step. We have the same base, which is hidden for the Man-In-The-Middle(MITM).
\___/          \___/
 _|_            _|_
/h*a\          /h*b\ - 3 Step. We're mixing the base with secret keys.
\___/\____    /\___/
 ___  ___|___/  ___
/h*b \/  |_____/h*a\ - 4 Step. We're exchanging them.
\___/          \___/
 _|_            _|_
/hab\          /hab\ - 5 Step. Mixing again with secret keys and that will be THE BASE NUM.
\___/          \___/

Shared key = hab
----------
```
