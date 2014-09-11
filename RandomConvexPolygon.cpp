#include <CGAL/Cartesian.h>
#include <CGAL/point_generators_2.h>
#include <CGAL/random_convex_set_2.h>

#include <iostream>
#include <iterator>
#include <string>
#include <vector>

// Type definitions
typedef CGAL::Cartesian<double> CartesianCoordinate;
typedef CartesianCoordinate::Point_2 Point_2;
typedef CGAL::Random_points_on_circle_2< 
    Point_2,
    CGAL::Creator_uniform_2<double, Point_2> 
> Point_generator;
typedef std::vector<Point_2> Vector;

// Constants definitions
const int EXEC_ERR_CODE     = -1;
const int EXEC_SUCCESS_CODE = 0;

const std::string ERR_INVALID_USAGE = "Usage: RandomConvexPolygon <nr-of-points>";

const std::string OUTPUT_SEPARATOR = " ";

const double POINT_GENERATOR_CIRCLE_RADIUS = 250;


// Update the coordinates of the convex polygon points such that they are all within the range [0, 2 * POINT_GENERATOR_CIRCLE_RADIUS]
void updatePolygonPointsCoordinates(Vector &polygon) {
    std::size_t nrOfPoints = polygon.size();

    for (std::size_t i = 0; i < nrOfPoints; i++) {
        polygon[i] = Point_2(
                         polygon[i].x() + POINT_GENERATOR_CIRCLE_RADIUS,
                         polygon[i].y() + POINT_GENERATOR_CIRCLE_RADIUS
                     );
    }
}

// Print the polygon to standard output
void printPolygon(Vector &polygon) {
    std::cout << polygon.size() << std::endl;

    for (auto point : polygon) {
        std::cout << point.x() << OUTPUT_SEPARATOR << point.y() << std::endl;
    }
}

// Generate a random convex polygon comprising the specified number of points
void generateRandomConvexPolygon(unsigned int nrOfPoints, Vector &polygon) {
    CGAL::random_convex_set_2(
        nrOfPoints, 
        std::back_inserter(polygon),
        Point_generator(POINT_GENERATOR_CIRCLE_RADIUS)
    );    
}

// Generate a random convex polygon comprising the specified number of points
int generateRandomConvexPolygon(unsigned int nrOfPoints) {
    Vector polygon;

    generateRandomConvexPolygon(nrOfPoints, polygon);
    updatePolygonPointsCoordinates(polygon);
    printPolygon(polygon);

    return EXEC_SUCCESS_CODE;
}

// Main function
int main(int argc, char **argv) {
    if (argc != 2) {
        std::cerr << ERR_INVALID_USAGE << std::endl;

        return EXEC_ERR_CODE;
    }

    unsigned int nrOfPoints = static_cast<unsigned int>(atoi(argv[1]));

    return generateRandomConvexPolygon(nrOfPoints);
}
