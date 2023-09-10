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

```
struct point {
    double x;
    double y;
};
```
Because the entire program deals with points, we might as well abstract them now into a ``struct``. A ``point`` object simply contains two decimal values: ``x`` and ``y``.

```
void init(int* CIRC_PTS, int* TOT_PTS, double* RAD);
void quartCircAround(struct point quart_circ[], struct point* center, int* CIRC_PTS, double* RAD);
void getSlopes(double slopes[], struct point quart_circ[], struct point* center, int* CIRC_PTS);
struct point choosePoint(double slopes[], struct point quart_circ[], int* CIRC_PTS);
```
Prototypes (or declarations) for functions defined later. These will be explained in depth later.

```
int main(void) {
    int CIRC_PTS = 100000;
    int TOT_PTS = 1000;
    double RAD = 0.01;

    init(&CIRC_PTS, &TOT_PTS, &RAD);
```
We are now in the main() function. First, we initialize the three parameters – number of circle points, total number of points, and radius – to their default values. We then pass the addresses (indicated by the &) of these variables to the init() function, which is explained below.

```
void init(int* CIRC_PTS, int* TOT_PTS, double* RAD) {
    printf("\n---eApprox: e and e^x approximator by Erk Sampat---\n\n");
    printf("Enter the following parameters. Defaults will be used in the case of \"0\" or invalid entries.\n\n");
```
The init() function takes three arguments, all of which are pointers to the parameter variables in the main() function. First, init() prints the title of the program and some basic instructions. This is accomplished with simple ``printf()`` statements.

```
    printf("Enter a positive integer for the number of circle points (100,000 default): ");
    int entry = 0;
    if (!scanf("%d", &entry)) {
        fflush(stdin);
    }
    if (entry > 0) {
        *CIRC_PTS = entry;
        printf("Number of circle points: %d\n\n", *CIRC_PTS);
    }
    else {
        printf("Using default of %d.\n\n", *CIRC_PTS);
    }
```
It then prompts the user to enter the number of circle points. It scans the user input, and if the user enters an integer, the value will be assigned to the variable ``entry``. ``scanf("%d", &entry)`` is responsible for this. ``%d`` tells it to look for decimal-value integers, and ``&entry`` is the address of ``entry``
