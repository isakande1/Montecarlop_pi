#include<stdio.h>
#include<omp.h>
#include<time.h>
#include<stdlib.h>
#include<math.h>

int main(void) {
    int  npoint = 2500000;
    double pi = 0.0, npcircle = 0;
    srand(time(0));
#pragma omp parallel
    {
        int i, tnum = 0, numt = 0,
                lnpcircle = 0;
        double x =0.0, y = 0.0, radius = 5.0, distance = 0.0;
        tnum = omp_get_thread_num(); numt = omp_get_num_threads();
        for( i = tnum; i < npoint; i+= numt) {
            x = ((double) rand() /  RAND_MAX ) * (2.0 *radius) - radius;
            y = ((double) rand() /  RAND_MAX ) * (2.0 * radius) - radius;
            distance = sqrt((x * x) + (y *y));
            if(distance <= radius)
                lnpcircle +=1;

        }
#pragma omp critical
        {
            npcircle += lnpcircle;
        }

    }
    pi = 4 * (npcircle / npoint);
    printf("%f \n", pi);

    return 0;
}

