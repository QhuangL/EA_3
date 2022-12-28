#ifndef UTILS_HPP
#define UTILS_HPP
#include <vector>
#include <cmath>
#include <algorithm> 
#include <numeric>
#include <sstream>
#include <iostream>

#include <stdio.h>
#include <string>
#include <cstring>
#include <fstream>     


std::vector<int> argsort(std::vector<double> &fit);
void readRobotShape(std::vector<std::vector<int>>& robot_shape , std::string filename);
std::vector<double> readGene(std::string filename, int index);
double distance3D(double x1, double y1, double z1, double x2, double y2, double z2);



#endif /*UTILS_HPP*/
