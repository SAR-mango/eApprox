#include <stdlib.h>
#include <stdio.h>
#include <math.h>

struct point {
    double x;
    double y;
};

void init(int* CIRC_PTS, int* TOT_PTS, double* RAD);
void quartCircAround(struct point quart_circ[], struct point* center, int* CIRC_PTS, double* RAD);
void getSlopes(double slopes[], struct point quart_circ[], struct point* center, int* CIRC_PTS);
struct point choosePoint(double slopes[], struct point quart_circ[], int* CIRC_PTS);

int main(void) {
    int CIRC_PTS = 100000;
    int TOT_PTS = 1000;
    double RAD = 0.01;

    init(&CIRC_PTS, &TOT_PTS, &RAD);

    struct point* quart_circ = malloc((CIRC_PTS - 2) * sizeof(struct point));
    double slopes[CIRC_PTS - 2];
    struct point e_approx[TOT_PTS];

    e_approx[0].x = 0.0;
    e_approx[0].y = 1.0;

    FILE* fp;
    fp = fopen("points.txt", "w+");
    // x, y, e^x, y - e^x, y^(1/x), y^(1/x) - e
    fprintf(fp, "%f %f %f %f %f %f\n", 0.0, 1.0, 1.0, 0.0, M_E, 0.0);

    for (int i = 1; i < TOT_PTS; i++) {
        quartCircAround(quart_circ, &e_approx[i - 1], &CIRC_PTS, &RAD);
        getSlopes(slopes, quart_circ, &e_approx[i - 1], &CIRC_PTS);
        e_approx[i] = choosePoint(slopes, quart_circ, &CIRC_PTS);
        // x, y, e^x, y - e^x, y^(1/x), y^(1/x) - e
        fprintf(fp, "%f %f %f %f %f %f\n", e_approx[i].x, e_approx[i].y, exp(e_approx[i].x), e_approx[i].y - exp(e_approx[i].x), pow(e_approx[i].y, 1 / e_approx[i].x), pow(e_approx[i].y, 1 / e_approx[i].x) - M_E);
    }

    fclose(fp);
    free(quart_circ);

    return 0;
}

void init(int* CIRC_PTS, int* TOT_PTS, double* RAD) {
    printf("\n---eApprox: e and e^x approximator by Erk Sampat---\n\n");
    printf("Enter the following parameters. Defaults will be used in the case of \"0\" or invalid entries.\n\n");

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

    printf("Enter a positive integer for the total number of points (1,000 default): ");
    entry = 0;
    if (!scanf("%d", &entry)) {
        fflush(stdin);
    }
    if (entry > 0) {
        *TOT_PTS = entry;
        printf("Number of total points: %d\n\n", *TOT_PTS);
    }
    else {
        printf("Using default of %d.\n\n", *TOT_PTS);
    }

    printf("Enter a positive decimal for the circle radius (0.01 default): ");
    double entry_d = 0.0;
    if (!scanf("%lf", &entry_d)) {
        fflush(stdin);
    }
    if (entry_d > 0.0) {
        *RAD = entry_d;
        printf("Radius: %lf\n\n", *RAD);
    }
    else {
        printf("Using default of %lf.\n\n", *RAD);
    }
}

void quartCircAround(struct point quart_circ[], struct point* center, int* CIRC_PTS, double* RAD) {
    double init_angle = M_PI_2 / *CIRC_PTS;
    double angle = init_angle;
    for (int i = 0; i < *CIRC_PTS - 2; i++) { // ignore horizontal and vertical lines, so CIRC_PTS - 2
        quart_circ[i].x = center->x + *RAD * cos(angle);
        quart_circ[i].y = center->y + *RAD * sin(angle);
        angle += init_angle;
    }
}

void getSlopes(double slopes[], struct point quart_circ[], struct point* center, int* CIRC_PTS) {
    for (int i = 0; i < *CIRC_PTS - 2; i++) {
        slopes[i] = (quart_circ[i].y - center->y) / (quart_circ[i].x - center->x);
    }
}

struct point choosePoint(double slopes[], struct point quart_circ[], int* CIRC_PTS) {
    double difference = fabs(slopes[0] - quart_circ[0].y);
    int index = 0;
    for (int i = 1; i < *CIRC_PTS - 2; i++) {
        double a = fabs(slopes[i] - quart_circ[i].y);
        if (a < difference) {
            difference = a;
            index = i;
        }
    }
    return quart_circ[index];
}
