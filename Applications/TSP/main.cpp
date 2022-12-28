#include <iostream>
#include <opencv2\opencv.hpp>

int main(int, char**) {
    std::cout << "Hello, world!\n";
    cv::Mat img = cv::imread("C:\\Users\\Shawn\\Documents\\GitHub\\EA_3\\Applications\\TSP\\data\\cakerecipte.png",0);
    // cv::imshow("img",img);
    
    // cv::waitKey(0);
    return 0;
}
