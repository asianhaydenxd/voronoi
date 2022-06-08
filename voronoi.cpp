#include<iostream>
#include<stdlib.h>
#include<cmath>
#include<ctime>
#include<string>

#define DEF_WIDTH 20
#define DEF_HEIGHT 20
#define DEF_NUM_OF_POINTS 4
#define DEF_MODE Euclidean
#define DEF_CHARS "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\\|()1{}[]?-_+~<>i!lI;:,\"^`'."
#define DEF_SPREAD true

enum DistanceMode {
    Euclidean,
    Manhattan
};

struct Point {
    int x;
    int y;
};

struct Diagram {
    int width;
    int height;

    int numOfPoints;

    DistanceMode mode;

    std::string characters;
    bool spread;
};

// Manhattan distance: a + b
float manhattanDistance(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}

// Euclidean distance: sqrt(a^2 + b^2)
float euclideanDistance(int x1, int y1, int x2, int y2) {
    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

std::string drawVoronoi(DistanceMode mode, int width, int height, int numOfPoints, Point points[], std::string characters, bool spread) {
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
                            char character = characters[spread ? static_cast<int>(std::floor(characters.length() * i / numOfPoints) + 0.5) : i];

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

Diagram parseArgs(int argc, char** argv) {
    Diagram diagram;

    // Set default values
    diagram.width       = DEF_WIDTH;
    diagram.height      = DEF_HEIGHT;
    diagram.numOfPoints = DEF_NUM_OF_POINTS;
    diagram.mode        = DEF_MODE;
    diagram.characters  = DEF_CHARS;
    diagram.spread      = DEF_SPREAD;

    // Iterate through the args
    for (int i = 0; i < argc; i++) {
        // Short name for each arg's name as a string
        std::string arg = std::string(argv[i]);

        if (arg == "-w" || arg == "--width") {
            i++;
            if (i < argc) diagram.width = std::stoi(argv[i]);
            continue;
        }

        if (arg == "-h" || arg == "--height") {
            i++;
            if (i < argc) diagram.height = std::stoi(argv[i]);
            continue;
        }

        if (arg == "-n" || arg == "--num-of-points") {
            i++;
            if (i < argc) diagram.numOfPoints = std::stoi(argv[i]);
            continue;
        }

        if (arg == "-c" || arg == "--chars" || arg == "--characters") {
            i++;
            if (i < argc) diagram.characters = std::string(argv[i]);
            continue;
        }

        if (arg == "-i" || arg == "--iter" || arg == "--iterative") {
            diagram.spread = false;
            continue;
        }

        if (arg == "-e" || arg == "--euclidean") {
            diagram.mode = Euclidean;
            continue;
        }

        if (arg == "-m" || arg == "--manhattan") {
            diagram.mode = Manhattan;
            continue;
        }
    }

    return diagram;
}

int main(int argc, char** argv) {
    std::srand(std::time(0));

    const Diagram diagram = parseArgs(argc, argv);

    Point points[diagram.numOfPoints];

    // Generate randomly positioned points
    for (int i = 0; i < diagram.numOfPoints; i++) {
        points[i].x = std::rand() % diagram.width;
        points[i].y = std::rand() % diagram.height;
    }

    std::cout << drawVoronoi(diagram.mode, diagram.width, diagram.height, diagram.numOfPoints, points, diagram.characters, diagram.spread);

    return 0;
}
