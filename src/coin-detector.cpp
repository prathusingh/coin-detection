#include "coin-detector.h"

#include <iostream>
#include <opencv2/opencv.hpp>
#include <utility>

using namespace cv;

namespace coindetector {
CoinDetector::CoinDetector(std::string coin_img_path) { coin = imread(coin_img_path); }

void CoinDetector::SplitIntoChannels() {
    Mat coin_grey_scale;
    cvtColor(coin, coin_grey_scale, cv::COLOR_BGR2GRAY);

    Mat coin_channels[3];
    split(coin, coin_channels);
    Mat img_r;
    Mat img_g;
    Mat img_b;

    img_b = coin_channels[0];
    img_g = coin_channels[1];
    img_r = coin_channels[2];
}
}  // namespace coindetector

int main() {
    std::string coin_img_path = "./src/images/CoinsA.png";
    coindetector::CoinDetector coin_detector{coin_img_path};
    coin_detector.SplitIntoChannels();
}
