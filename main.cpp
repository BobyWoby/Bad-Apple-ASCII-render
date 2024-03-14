#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <SDL2/SDL.h>
#include <thread>
#include <chrono>

std::string matToASCII(cv::Mat src);


int main() {
//
//    if(SDL_Init(SDL_INIT_VIDEO) < 0)
//    {
//        std::cout << "Failed to initialize the SDL2 library\n";
//        return -1;
//    }
//
//    SDL_Window *window = SDL_CreateWindow("Bad Apple", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 320, 320, 0);
//    if(!window)
//    {
//        std::cout << "Failed to create window\n";
//        return -1;
//    }
//    SDL_Surface *window_surface = SDL_GetWindowSurface(window);
//
//    if(!window_surface)
//    {
//        std::cout << "Failed to get the surface from the window\n";
//        return -1;
//    }
//
//    SDL_Event e;
//    bool keep_window_open = true;
//    while(keep_window_open){
//        while(SDL_PollEvent(&e) > 0){
//            switch(e.type){
//            case SDL_QUIT:
//                keep_window_open = false;
//                break;
//            }
//        }
//        SDL_UpdateWindowSurface(window);
//    }


    cv::VideoCapture cap("BadApple.mp4");
    if(!cap.isOpened()){
        std::cout << "Can't open the video file. \n";
        return -1;
    }
    cv::Mat frame, grayFrame, smFrame;
    while(1){
        if(!cap.read(frame)){
            std::cout << "Can't read the file\n";
            break;
        }
        cv::cvtColor(frame, grayFrame, cv::COLOR_BGR2GRAY);
        cv::imshow("frame", grayFrame);
//        cv::resize(grayFrame, smFrame, cv::Size(64, 48), 1, 1);
        cv::resize(grayFrame, smFrame, cv::Size(48, 36), 1, 1);
        std::cout << matToASCII(smFrame);
        if(cv::waitKey(30) == 27)
        {
            break;
        }
//        std::this_thread::sleep_for(std::chrono::milliseconds (50));
    }
    return 0;
}
std::string matToASCII(cv::Mat src){
    std::string ramp = " .:=+@";
    std::string outStr;
    int _stride = src.step;
    uint8_t *myData = src.data;
    std::string tmp;
    for (int i = 0; i < src.rows; i++){
        for (int j = 0; j < src.cols; j++){
            tmp = ramp[(int)((myData[ i * _stride + j]) / 51)];
            outStr.append(tmp + tmp);
        }
        outStr.append("\n");
    }
    return outStr;
}