#include <iostream>
#include <opencv2\opencv.hpp>
#include "Utils\utils.hpp"
#include "TSP.hpp"
#include "Evolution/Evolution.hpp"


int main(int, char**) {
    
    std::vector<std::vector<double>> data;
    if(read2DMatrix(data, "C:\\Users\\Shawn\\Documents\\GitHub\\EA_3\\Applications\\TSP\\data\\tsp.txt")){
        
    }

    // define the TSP population
    std::unordered_map<std::string,double> u = {
        {"upper", 1.0},
        {"lower", 0.0}
    };
    PopulationParam param = {
        .populationSize = 200,
        .maxPopulationSize =200,
        .maxGeneLength = 1000,
        .limits = u
    };
    auto population = new TSP(&param);

    //define the TSP evolution
    EvolutionParam eparam = {
        .crossoverType = TWOPOINT,
        .selectionType = TRUNCATION,
        .selectRate = 0.5,
        .diversityType = NONE
    };
    auto evolution = new Evolution(population, eparam);



    


    //drawing
    cv::Mat image(500, 500, CV_8UC3, cv::Scalar(0,0,0));
    if(!image.data){
        std::cout<<"could not open or find the image";
        return 0;
    }
    cv::Point p1(0,0), p2(100,0), p3(200, 0), p4(500, 500);
    int thickness = 1;
    for(int i = 0; i< data.size()-1; ++i){
        p1.x = data[i][0]*500;
        p1.y = data[i][1]*500;
        p2.x = data[i+1][0]*500;
        p2.y = data[i+1][1]*500;
        line(image, p1, p2, cv::Scalar(0, 0, 255), thickness, cv::LINE_AA);
    }
    // Show our image inside window
    cv::imshow("Output", image);
    cv::waitKey(0);
    

    
    return 0;
};
