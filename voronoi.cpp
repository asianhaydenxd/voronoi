#include<iostream>
#include<stdlib.h>
#include<cmath>
#include<ctime>
#include<string>

enum DistanceMode {
    Euclidean,
    Manhattan
};

struct Point {
    int x;
    int y;
};

// Manhattan distance: a + b
float manhattanDistance(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}

// Euclidean distance: sqrt(a^2 + b^2)
float euclideanDistance(int x1, int y1, int x2, int y2) {
    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

std::string drawVoronoi(DistanceMode mode, int width, int height, int numOfPoints, Point points[], const char characters[], bool spread) {
    // Starting output for procedural generation
    std::string output = "";

    // Iterate through rows
    for (int iy = 0; iy < height; iy++) {
        // Iterate through individual grid slots
        for (int ix = 0; ix < width; ix++) {
            // Iterate through each point
            for (int i = 0; i < numOfPoints; i++){
                if (points[i].x == ix && points[i].y == iy) {
                    output.append("()");
                    break;
                }
                // If the loop is over and the current slot still isn't any of the points
                if (i + 1 == numOfPoints) {
                    float distances[numOfPoints];

                    // Generate array of distances to each point
                    for (int i = 0; i < numOfPoints; i++) {
                        if (mode == Euclidean) distances[i] = euclideanDistance(ix, iy, points[i].x, points[i].y);
                        if (mode == Manhattan) distances[i] = manhattanDistance(ix, iy, points[i].x, points[i].y);
                    }

                    // Find the distance of the with the closest (minimum) distance
                    float min = distances[0];

                    for (int i = 0; i < numOfPoints; i++) {
                        if (distances[i] < min) {
                            min = distances[i];
                        }
                    }

                    // Find the point with the target distance and print the appropriate character
                    for (int i = 0; i < numOfPoints; i++) {
                        if (min == distances[i]) {
                            // If spread is true, take i and evenly distribute it across the character array
                            // Otherwise, just index the characters with i
                            char character = characters[spread ? static_cast<int>(std::floor(69 * i / numOfPoints) + 0.5) : i];

                            output.append({character, character});
                            break;
                        }
                    }
                }
            }
        }
        output.append("\n");
    }
    return output;
}

int main(int argc, char** argv) {
    std::srand(std::time(0));

    int width  = 50;
    int height = 50;

    int numOfPoints = 4;

    DistanceMode mode = Euclidean;

    std::string characters = "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\\|()1{}[]?-_+~<>i!lI;:,\"^`'.";

    for (int i = 0; i < argc; i++) {
        std::string arg = std::string(argv[i]);

        if (arg == "-w" || arg == "--width") {
            i++;
            if (i < argc) {
                width = std::stoi(argv[i]);
            }
            continue;
        }

        if (arg == "-h" || arg == "--height") {
            i++;
            if (i < argc) {
                height = std::stoi(argv[i]);
            }
            continue;
        }

        if (arg == "-n" || arg == "--num-of-points") {
            i++;
            if (i < argc) {
                numOfPoints = std::stoi(argv[i]);
            }
            continue;
        }

        if (arg == "-c" || arg == "--chars" || arg == "--characters") {
            i++;
            if (i < argc) {
                characters = std::string(argv[i]);
            }
            continue;
        }

        if (arg == "-e" || arg == "--euclidean") {
            mode = Euclidean;
            continue;
        }

        if (arg == "-m" || arg == "--manhattan") {
            mode = Manhattan;
            continue;
        }
    }

    Point points[numOfPoints];

    // Generate randomly positioned points
    for (int i = 0; i < numOfPoints; i++) {
        points[i].x = std::rand() % width;
        points[i].y = std::rand() % height;
    }

    std::cout << drawVoronoi(Euclidean, width, height, numOfPoints, points, characters.c_str(), false);

    return 0;
}
