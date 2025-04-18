#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void draw_graph(int (*func)(double *, double, const char *), char *polish_str) {
    char graph[25][80];

    for (int i = 0; i < 25; i++) {
        for (int j = 0; j < 80; j++) {
            graph[i][j] = '.';
        }
    }

    for (int x = 0; x < 80; x++) {
        double arg = (x / 80.0) * (4 * M_PI);
        double y;
        func(&y, arg, polish_str);
        int y_pos = (int)((y + 1) / 2 * 24);

        if (y_pos >= 0 && y_pos < 25) {
            graph[y_pos][x] = '*';
        }
    }

    for (int i = 0; i < 25; i++) {
        for (int j = 0; j < 80; j++) {
            printf("%c", graph[i][j]);
        }
        printf("\n");
    }
}
