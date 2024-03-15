#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <SDL2/SDL.h>
#include <thread>
#include <chrono>
#include <SFML/Audio.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>


std::string matToASCII(cv::Mat src);


int main() {
    sf::SoundBuffer buffer;
    if(!buffer.loadFromFile("BadApple.wav")){
        std::cout << "Can't load the audio file\n";
        return -1;
    }
    sf::Sound sound;
    sound.setBuffer(buffer);
    cv::VideoCapture cap("BadApple.mp4");
    if(!cap.isOpened()){
        std::cout << "Can't open the video file. \n";
        return -1;
    }
    cv::Mat frame, grayFrame, smFrame;
    sound.play();
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
        std::this_thread::sleep_for(std::chrono::milliseconds (1));
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