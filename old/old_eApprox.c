#include <stdio.h>
#include <math.h>

#define CIRC_PTS 100000
#define RAD 0.01
#define TOT_PTS 1000

double quart_circ[CIRC_PTS - 2][2];
double slopes[CIRC_PTS - 2];
double e_approx[TOT_PTS][2];

void quartCircAround(double* center) {
    double init_angle = M_PI_2 / CIRC_PTS;
    double angle = init_angle;
    for (int i = 0; i < CIRC_PTS - 2; i++) {
        quart_circ[i][0] = center[0] + RAD * cos(angle);
        quart_circ[i][1] = center[1] + RAD * sin(angle);
        angle += init_angle;
    }
}

void getSlopes(double* center) {
    for (int i = 0; i < CIRC_PTS - 2; i++) {
        slopes[i] = (quart_circ[i][1] - center[1]) / (quart_circ[i][0] - center[0]);
    }
}

double* choosePt(void) {
    double difference = fabs(slopes[0] - quart_circ[0][1]);
    int index = 0;
    for (int i = 1; i < CIRC_PTS - 2; i++) {
        double a = fabs(slopes[i] - quart_circ[i][1]);
        if (a < difference) {
            difference = a;
            index = i;
        }
    }
    return quart_circ[index];
}

int main (void) {
    e_approx[0][0] = 0;
    e_approx[0][1] = 1;
    double* point;
    FILE* fp;
    fp = fopen("points.txt", "w+");
    // x, y, e^x, y - e^x, y^(1/x), y^(1/x) - e
    fprintf(fp, "%f %f %f %f %f %f\n", 0.0, 1.0, 1.0, 0.0, M_E, 0.0);
    for (int i = 1; i < TOT_PTS; i++) {
        quartCircAround(e_approx[i - 1]);
        getSlopes(e_approx[i - 1]);
        point = choosePt();
        e_approx[i][0] = *point++;
        e_approx[i][1] = *point;
        // x, y, e^x, y - e^x, y^(1/x), y^(1/x) - e
        fprintf(fp, "%f %f %f %f %f %f\n", e_approx[i][0], e_approx[i][1], exp(e_approx[i][0]), e_approx[i][1] - exp(e_approx[i][0]), 
        pow(e_approx[i][1], 1 / e_approx[i][0]), pow(e_approx[i][1], 1 / e_approx[i][0]) - M_E);
    }

    fclose(fp);
    return 0;
}
