#include "coin-detector.h"

#include <iostream>
#include <opencv2/opencv.hpp>
#include <utility>

using namespace cv;

namespace coindetector {
CoinDetector::CoinDetector(std::string coin_img_path) { coin = imread(coin_img_path); }

void CoinDetector::SplitIntoChannels(Mat* channels) {
    Mat coin_grey_scale;
    cvtColor(coin, coin_grey_scale, cv::COLOR_BGR2GRAY);

    split(coin, channels);
    Mat img_r;
    Mat img_g;
    Mat img_b;

    img_b = channels[0];
    img_g = channels[1];
    img_r = channels[2];
}

void CoinDetector::PerformThresholding(Mat& img, Mat& thresholded_img) {
    threshold(img, thresholded_img, 40, 90, 1);
}
}  // namespace coindetector

int main() {
    std::string coin_img_path = "./src/images/CoinsA.png";
    coindetector::CoinDetector coin_detector{coin_img_path};
    Mat coin_channels[3];
    coin_detector.SplitIntoChannels(coin_channels);
    Mat thresholded_image;
    coin_detector.PerformThresholding(coin_channels[1], thresholded_image);
}
