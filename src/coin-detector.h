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
    void SplitIntoChannels(Mat* coin_channels);
    void PerformThresholding(Mat& img, Mat& thresholded_img);
    void PerformOpening(Mat& img, Mat& morphologicaled_img);
    void DetectCoinsUsingBlobDetector(Mat& img);
    void DisplayConnectedComponents(Mat& img);
    void DisplayContours();
};
}  // namespace coindetector

#endif  // COIN_DETECTOR_H