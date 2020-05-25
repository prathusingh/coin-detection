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

void CoinDetector::PerformOpening(Mat& img, Mat& morphologicaled_img) {
    int closing_size = 4;
    Mat element =
        getStructuringElement(MORPH_ELLIPSE, Size(2 * closing_size + 1, 2 * closing_size + 1),
                              Point(closing_size, closing_size));
    morphologyEx(img, morphologicaled_img, MORPH_CLOSE, element);
}

void CoinDetector::DetectCoinsUsingBlobDetector(Mat& img) {
    // Setup SimpleBlobDetector parameters.
    SimpleBlobDetector::Params params;

    params.blobColor = 0;

    params.minDistBetweenBlobs = 2;

    // Filter by Area
    params.filterByArea = false;

    // Filter by Circularity
    params.filterByCircularity = true;
    params.minCircularity = 0.8;

    // Filter by Convexity
    params.filterByConvexity = true;
    params.minConvexity = 0.8;

    // Filter by Inertia
    params.filterByInertia = true;
    params.minInertiaRatio = 0.8;
    SimpleBlobDetector blob_detector;
    Ptr<SimpleBlobDetector> detector = SimpleBlobDetector::create();
    std::vector<KeyPoint> key_points;
    detector->detect(img, key_points);
    std::cout << key_points.size() << std::endl;

    int x, y, radius;

    for (auto i = 0; i < key_points.size(); i++) {
        KeyPoint point = key_points[i];
        x = point.pt.x;
        y = point.pt.y;
        radius = (int)point.size / 2.0;
        circle(img, Point(x, y), 5, Scalar(0, 255, 0), -1);
        circle(img, Point(x, y), radius, Scalar(0, 255, 0), 2);
    }

    imshow("blobs", img);
    waitKey(0);
}
}  // namespace coindetector

int main() {
    std::string coin_img_path = "./src/images/CoinsA.png";
    coindetector::CoinDetector coin_detector{coin_img_path};
    Mat coin_channels[3];
    coin_detector.SplitIntoChannels(coin_channels);
    Mat thresholded_image;
    coin_detector.PerformThresholding(coin_channels[1], thresholded_image);
    Mat morphed_img;
    coin_detector.PerformOpening(thresholded_image, morphed_img);
    coin_detector.DetectCoinsUsingBlobDetector(morphed_img);
}
