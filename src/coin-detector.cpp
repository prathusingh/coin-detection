#include "coin-detector.h"

#include <iostream>
#include <opencv2/opencv.hpp>
#include <utility>

using namespace cv;

namespace coindetector {
CoinDetector::CoinDetector(std::string coin_img_path) {
    coin = imread(coin_img_path);
    imshow("coin", coin);
    waitKey(0);
}
}  // namespace coindetector

int main() {
    std::string coin_img_path = "./src/images/CoinsA.png";
    coindetector::CoinDetector coin_detector{coin_img_path};
}
