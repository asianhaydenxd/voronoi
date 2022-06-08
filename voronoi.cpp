#include<iostream>
#include<stdlib.h>
#include<cmath>
#include<ctime>

float euclidDistance(int x1, int y1, int x2, int y2) {
    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

int main(int argc, char** argv) {
    std::srand(std::time(0));

    int width  = 20;
    int height = 10;

    int points[4][2];

    for (int i = 0; i < sizeof(points)/sizeof(points[0]); i++) {
        points[i][0] = std::rand() % width;
        points[i][1] = std::rand() % height;

        std::cout << std::to_string(points[i][0]) << "\n" << std::to_string(points[i][1]) << "\n";
    }

    for (int iy = 0; iy < height; iy++) {
        for (int ix = 0; ix < width; ix++) {
            if (points[0][0] == ix && points[0][1] == iy) {
                std::cout << "@";
            } else if (points[1][0] == ix && points[1][1] == iy) {
                std::cout << "@";
            } else if (points[2][0] == ix && points[2][1] == iy) {
                std::cout << "@";
            } else if (points[3][0] == ix && points[3][1] == iy) {
                std::cout << "@";
            } else {
                float d1 = euclidDistance(ix, iy, points[0][0], points[0][1]);
                float d2 = euclidDistance(ix, iy, points[1][0], points[1][1]);
                float d3 = euclidDistance(ix, iy, points[2][0], points[2][1]);
                float d4 = euclidDistance(ix, iy, points[3][0], points[3][1]);

                float min = d1;
                if (d2 < min) {
                    min = d2;
                }
                if (d3 < min) {
                    min = d3;
                }
                if (d4 < min) {
                    min = d4;
                }

                if (min == d1) {
                    std::cout << ".";
                } else if (min == d2) {
                    std::cout << "+";
                } else if (min == d3) {
                    std::cout << "/";
                } else if (min == d4) {
                    std::cout << ":";
                }
            }
        }
        std::cout << "\n";
    }

    return 0;
}
