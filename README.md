# eApprox
C program that approximates e and e^x. Examples TBA.

# Algorithm: Basic Overview
This program relies on the principle that the function e<sup>x</sup> is a graph of its own slope. That is, the derivative of e<sup>x</sup> is also e<sup>x</sup>.

With this in mind, the program's functions are broken down below:

1. Start at point (0, 1).
2. Generate evenly-spaced points that fall along a quarter circle centered at (0, 1) with some given radius.
3. Calculate the slope between each point you just generated and (0, 1).
4. Select the point whose slope between itself and (0, 1) is closest to its y value.
5. Repeat the process around the point you selected rather than (0, 1).

Here's what it looks like when points are generated around (0, 1):
![Points generated along a quarter circle centered around (0, 1)](https://github.com/SAR-mango/eApprox/blob/0e95b447df93c5f1ee3ecf1d49aabe671ce0fc6f/img_1.png = 300x)
