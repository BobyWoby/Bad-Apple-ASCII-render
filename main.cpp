#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
std::string matToASCII(cv::Mat src);


int main(int argc, char* argv[]) {
    /*
     * args:
     * 0 = volume
     * */
    sf::RenderWindow window(sf::VideoMode(800, 600), "Display");
    sf::SoundBuffer buffer;
    sf::Font font;
    sf::Text text;
    text.setFont(font);
//    text.setString("");
    text.setCharacterSize(12);
//    text.setCharacterSize(10);
    text.setFillColor(sf::Color::White);
    text.setStyle(sf::Text::Regular);

    if(!font.loadFromFile("UbuntuMono-R.ttf")){
        std::cout << "Couldn't load font";
        exit(1);
    }
    if(!buffer.loadFromFile("BadApple.wav")){
        std::cout << "Can't load the audio file\n";
        return -1;
    }
    sf::Sound sound;
    sound.setBuffer(buffer);
    sound.setVolume(std::stoi(argv[1]));
    sound.setPitch(std::stod(argv[2]));
    cv::VideoCapture cap("BadApple.mp4");
    if(!cap.isOpened()){
        std::cout << "Can't open the video file. \n";
        return -1;
    }
    cv::Mat frame, grayFrame, smFrame;
    sound.play();
    while(window.isOpen()){
        if(!cap.read(frame)){
            std::cout << "Can't read the file\n";
            break;
        }
        cv::cvtColor(frame, grayFrame, cv::COLOR_BGR2GRAY);
        cv::imshow("Bad Apple", grayFrame);
        cv::resize(grayFrame, smFrame, cv::Size(48, 36), 1, 1, cv::INTER_NEAREST);
        text.setString(matToASCII(smFrame));
        window.clear(sf::Color::Black);
        window.draw(text);
        window.display();
        if(cv::waitKey(30) == 27){
            window.close();
            break;
        }
    }
    return 0;
}
std::string matToASCII(cv::Mat src){
    std::string ramp = "  .'^,:l!i>~+-?]}`)|tfjrxnuvcYUJQOZmpdbho*#MW&%B@@@@@@@";
    // " .:=+@"
//    ramp = " .'`^\",:;Il!i><~+_-?][}{`)(|\\/tfjrxnuvczXYUJCLQ0OZmqpdbkhao*#MW&8%B@$";
    std::string outStr;
    std::string tmp;
    cv::Scalar intensity;
    uchar* p;
    for (int i = 0; i < src.rows; i++){
        p = src.ptr<uchar>(i);
        for (int j = 0; j < src.cols; j++){
            tmp = ramp[floor(p[j] / 5.0)];
            outStr.append(tmp + tmp);
        }
        outStr.append("\n");
    }
    return outStr;
}