#include<iostream>
#include<stdlib.h>
#include<cmath>
#include<ctime>

enum DistanceMode {
    Euclidian,
    Manhattan
};

struct Point {
    int x;
    int y;
};

float manhattanDistance(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}

float euclideanDistance(int x1, int y1, int x2, int y2) {
    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

void drawVoronoi(DistanceMode mode, int width, int height, int numOfPoints, Point points[], const char characters[]) {
    for (int iy = 0; iy < height; iy++) {
        for (int ix = 0; ix < width; ix++) {
            if (points[0].x == ix && points[0].y == iy) {
                std::cout << "()";
            } else if (points[1].x == ix && points[1].y == iy) {
                std::cout << "()";
            } else if (points[2].x == ix && points[2].y == iy) {
                std::cout << "()";
            } else if (points[3].x == ix && points[3].y == iy) {
                std::cout << "()";
            } else {

                float distances[numOfPoints];

                for (int i = 0; i < numOfPoints; i++) {
                    if (mode == Euclidian) distances[i] = euclideanDistance(ix, iy, points[i].x, points[i].y);
                    if (mode == Manhattan) distances[i] = manhattanDistance(ix, iy, points[i].x, points[i].y);
                }

                float min = distances[0];

                for (int i = 0; i < numOfPoints; i++) {
                    if (distances[i] < min) {
                        min = distances[i];
                    }
                }

                for (int i = 0; i < numOfPoints; i++) {
                    if (min == distances[i]) {
                        std::cout << characters[i] << characters[i];
                        break;
                    }
                }
            }
        }
        std::cout << "\n";
    }
}

int main(int argc, char** argv) {
    std::srand(std::time(0));

    const int width  = 50;
    const int height = 50;

    const int numOfPoints = 4;

    const char characters[] = ".'`^\",:;Il!i><~+_-";

    Point points[numOfPoints];

    for (int i = 0; i < numOfPoints; i++) {
        points[i].x = std::rand() % width;
        points[i].y = std::rand() % height;
    }

    drawVoronoi(Euclidian, width, height, numOfPoints, points, characters);

    return 0;
}
