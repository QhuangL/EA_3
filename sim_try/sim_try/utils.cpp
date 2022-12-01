#include "utils.hpp"

vector<int> argsort(vector<double> &fit){
    
    vector<int> o_fit(fit.size());
        iota(o_fit.begin(), o_fit.end(), 0);

        stable_sort(o_fit.begin(), o_fit.end(),
            [&fit](int i1, int i2) {return fit[i1] < fit[i2];});
    
    return o_fit;
};


void readRobotShape(std::vector<std::vector<int>>& robot_shape){
    ifstream fin;
    fin.open("RobotShape.csv");
    string oneline;
    robot_shape.clear();

    vector<int> xy;


    while (!fin.eof())
    {
        getline(fin, oneline);
        
        if (oneline == "")
        {
            break;
        }
        istringstream is(oneline);
        float t;
        while(is >> t){
            char ch;
            
            xy.push_back(t);
            is >> ch;
        }
        robot_shape.push_back(xy);
        
        xy.clear();
    }
    fin.close();
    std::cout<<robot_shape.size()<<std::endl;   
};