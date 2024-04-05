#include "star.h"

Star::Star(const std::string& n, std::vector<double>& pos, std::vector<double>& spd,
std::vector<double>& acc, double m) : Object(n, pos, spd, acc, m) {}