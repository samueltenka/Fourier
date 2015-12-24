# Fourier

Goal
====
Let's translate voices! 


Method
======
Cepstrum transforms.

(Q: what happens under repeated cepstrum transforms?)


Algorithm Notes
===============
Phase-randomization perceptibly changes sounds: oooh's, at least, sound like they're being made in a tunnel.
By phase-randomization we mean multiplication of each of the fourier components by a random phase, independent of the other components.

This doesn't bode well for our Cepstrum approach, since, at least according to our we will lose phase information.


Implementation Notes
====================
*	Why is there a linker problem when we separate SigProc.h into .h & .cpp's?!?!
*	Learned how to make templated, partially-specialized Array struct with maximum const-correctness. Wow, that was more complicated than expected.
*	TODO: draw poset of #includes.
