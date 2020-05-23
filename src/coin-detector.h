#ifndef COIN_DETECTOR_H
#define COIN_DETECTOR_H

#include <opencv2/opencv.hpp>
#include <string>
#include <utility>

using namespace cv;

namespace coindetector {

class CoinDetector {
   private:
    Mat coin;

   public:
    CoinDetector(std::string coin_img_path);
    void SplitIntoChannels();
};
}  // namespace coindetector

#endif  // COIN_DETECTOR_H