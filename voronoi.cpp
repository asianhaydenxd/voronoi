#include<iostream>
#include<stdlib.h>
#include<cmath>

float distance(int x1, int y1, int x2, int y2) {
    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

int main(int argc, char** argv) {
    int width  = 10;
    int height = 10;

    int points[4][2];

    for (int i = 0; i < sizeof(points)/sizeof(points[0]); i++) {
        points[i][0] = rand() % width;
        points[i][1] = rand() % height;
    }

    for (int ix = 0; ix < width; ix++) {
        for (int iy = 0; iy < height; iy++) {
            if (points[0][0] == ix && points[0][1] == iy) {
                std::cout << "1";
            } else if (points[1][0] == ix && points[1][1] == iy) {
                std::cout << "2";
            } else if (points[2][0] == ix && points[2][1] == iy) {
                std::cout << "3";
            } else if (points[3][0] == ix && points[3][1] == iy) {
                std::cout << "4";
            } else {
                // Find distance
            }
        }
        std::cout << "\n";
    }

    return 0;
}
