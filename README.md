# eApprox
C program that approximates e and e<sup>x</sup>. Specifically, it generates a text file containing the approximations as well as some other interesting data. A python program then reads the data from the text file and graphs the results beautifully using Matplotlib. Here's what that looks like:

<img src="img_3.png" height="600">

# Algorithm: Basic Overview
This program relies on the principle that the function e<sup>x</sup> is a graph of its own slope. That is, the derivative of e<sup>x</sup> is also e<sup>x</sup>.

With this in mind, the program's functions are broken down below:

1. Start at point (0, 1).
2. Generate evenly-spaced points that fall along a quarter circle centered at (0, 1) with some given radius.
3. Calculate the slope between each point you just generated and (0, 1).
4. Select the point whose slope between itself and (0, 1) is closest to its y value. Save this point.
5. Repeat the process around that point. Now, slopes are calculated between points on the new quarter circle and the point selected in the previous step.

Here's what it looks like when points are generated around (0, 1). The orange line connects (0, 1) to the point that was selected.

<img src="img_1.png" width="300">

And here's what the process looks like when it is repeated. The circles don't look entirely circular because the graph's scale is not perfectly even between both axes.

<img src="img_2.png" width="300">

Essentially, the program generates very small line segments between points, where the slope of each segment matches the y value of its right-side point as closely as possible. As an approximation for e<sup>x</sup>, this works surprisingly well. However, experimenting with the program and evaluating its performance will be left to the reader.

# How the Code Works
I have left comments out of the code because it is – in my humble opinion – fairly easy to read and understand for those who want to challenge themselves. To make up for this, the entire program is documented in detail below. Comments will always be BELOW their respective code segments.

```
#include <stdio.h>
#include <math.h>
```
Includes the necessary libraries. ``stdio.h`` (standard input/output) is needed for the program to prompt the user for parameters and for the user to enter the parameters. ``math.h`` (the math library) is needed for the ``fabs()`` (float absolute value) function. This allows the program to calculate the absolute value between decimal values.
