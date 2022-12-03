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
using namespace std;

vector<int> argsort(vector<double> &fit);
void readRobotShape(std::vector<std::vector<int>>& robot_shape , string filename);
std::vector<double> readGene(string filename, int index);
double distance3D(double x1, double y1, double z1, double x2, double y2, double z2);



#endif /*UTILS_HPP*/
