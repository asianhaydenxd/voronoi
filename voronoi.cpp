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
            for (int i = 0; i < numOfPoints; i++) {
                if (points[i].x == ix && points[i].y == iy) {
                    std::cout << "()";
                    break;
                }
                if (i + 1 == numOfPoints) {
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
                            char character = characters[static_cast<int>(std::floor(69 * i / numOfPoints) + 0.5)];
                            std::cout << character << character;
                            break;
                        }
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

    const char characters[] = "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\\|()1{}[]?-_+~<>i!lI;:,\"^`'.";

    Point points[numOfPoints];

    for (int i = 0; i < numOfPoints; i++) {
        points[i].x = std::rand() % width;
        points[i].y = std::rand() % height;
    }

    drawVoronoi(Euclidian, width, height, numOfPoints, points, characters);

    return 0;
}
