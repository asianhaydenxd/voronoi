#include<iostream>
#include<stdlib.h>
#include<cmath>
#include<ctime>
#include<string>

#define DEF_WIDTH         20
#define DEF_HEIGHT        20
#define DEF_NUM_OF_POINTS 4
#define DEF_MODE          Euclidean
#define DEF_DISPLAY       Double
#define DEF_POINT_STR     "()"
#define DEF_CHARS         "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\\|()1{}[]?-_+~<>i!lI;:,\"^`'."
#define DEF_SPREAD        true

#define MAX_POINTS 1000

enum DistanceMode {
    Euclidean,
    Manhattan
};

enum DisplayStyle {
    Single,
    SingleSpace,
    Double
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
    DisplayStyle display;

    std::string pointStr;
    std::string characters;
    bool spread;

    Point points[MAX_POINTS];
};

// Manhattan distance: a + b
float manhattanDistance(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}

// Euclidean distance: sqrt(a^2 + b^2)
float euclideanDistance(int x1, int y1, int x2, int y2) {
    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

std::string drawVoronoi(Diagram diagram) {
    // Starting output for procedural generation
    std::string output = "";

    // Iterate through rows
    for (int iy = 0; iy < diagram.height; iy++) {
        // Iterate through individual grid slots
        for (int ix = 0; ix < diagram.width; ix++) {
            // Iterate through each point
            for (int i = 0; i < diagram.numOfPoints; i++){
                if (diagram.points[i].x == ix && diagram.points[i].y == iy) {
                    output.append(diagram.pointStr);
                    break;
                }
                // If the loop is over and the current slot still isn't any of the points
                if (i + 1 == diagram.numOfPoints) {
                    float distances[diagram.numOfPoints];

                    // Generate array of distances to each point
                    for (int i = 0; i < diagram.numOfPoints; i++) {
                        if (diagram.mode == Euclidean) distances[i] = euclideanDistance(ix, iy, diagram.points[i].x, diagram.points[i].y);
                        if (diagram.mode == Manhattan) distances[i] = manhattanDistance(ix, iy, diagram.points[i].x, diagram.points[i].y);
                    }

                    // Find the distance of the with the closest (minimum) distance
                    float min = distances[0];

                    for (int i = 0; i < diagram.numOfPoints; i++) {
                        if (distances[i] < min) {
                            min = distances[i];
                        }
                    }

                    // Find the point with the target distance and print the appropriate character
                    for (int i = 0; i < diagram.numOfPoints; i++) {
                        if (min == distances[i]) {
                            // If spread is true, take i and evenly distribute it across the character array
                            // Otherwise, just index the characters with i
                            char character = diagram.characters[diagram.spread ? static_cast<int>(std::floor(diagram.characters.length() * i / diagram.numOfPoints) + 0.5) : i];

                            // Append the new character onto the output based on the diagram's character display style
                            if (diagram.display == Single) {
                                output += character;
                            } else if (diagram.display == SingleSpace) {
                                output += character;
                                output += " ";
                            } else if (diagram.display == Double) {
                                output += character;
                                output += character;
                            }
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
    diagram.display     = DEF_DISPLAY;
    diagram.pointStr    = DEF_POINT_STR;
    diagram.characters  = DEF_CHARS;
    diagram.spread      = DEF_SPREAD;

    int definedPoints = 0;

    // Iterate through the args
    for (int i = 0; i < argc; i++) {
        // Short name for each arg's name as a string
        std::string arg = std::string(argv[i]);

        if (arg == "-p" || arg == "--point") {
            i++;
            if (i < argc) diagram.points[definedPoints].x = std::stoi(argv[i]);
            i++;
            if (i < argc) diagram.points[definedPoints].y = std::stoi(argv[i]);
            definedPoints++;
            diagram.numOfPoints = definedPoints;
            continue;
        }

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

        if (arg == "-P" || arg == "--pc" || arg == "--point-char") {
            i++;
            if (i < argc) diagram.pointStr = std::string(argv[i]);
            continue;
        }

        if (arg == "-i" || arg == "--iter" || arg == "--iterative") {
            diagram.spread = false;
            continue;
        }

        if (arg == "-s" || arg == "--spread") {
            diagram.spread = true;
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

        if (arg == "-1" || arg == "--single") {
            diagram.display = Single;
            continue;
        }

        if (arg == "-S" || arg == "--single-space") {
            diagram.display = SingleSpace;
            continue;
        }

        if (arg == "-2" || arg == "--double") {
            diagram.display = Double;
            continue;
        }
    }

    // Generate randomly positioned points
    for (int i = 0; i < diagram.numOfPoints; i++) {
        if (i >= definedPoints) {
            diagram.points[i].x = std::rand() % diagram.width;
            diagram.points[i].y = std::rand() % diagram.height;
        }
    }

    return diagram;
}

int main(int argc, char** argv) {
    std::srand(std::time(0));

    Diagram diagram = parseArgs(argc, argv);

    std::cout << drawVoronoi(diagram);

    return 0;
}
