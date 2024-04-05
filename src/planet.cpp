#include "planet.h"

Planet::Planet(const std::string& n, std::vector<double>& pos, std::vector<double>& spd,
std::vector<double>& acc, double m) : Object(n, pos, spd, acc, m) {}


double Planet::area() {
    double area = 0.5 * sqrt(1);
}