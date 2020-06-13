#include "pch.h"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include "pch.h"
#include <utility>
#include <limits.h>
#include"templateMatching.h"
#include <chrono>

static int match_method;

using namespace std;
using namespace cv;
using namespace std::chrono;
Mat img; Mat temp; Mat result;
//int match_method;
//string a;
//string b;
void res(char* a, char* b, int* x, int* y) {
    auto start = high_resolution_clock::now(); 
    Mat img = imread(a);
    cout << a << endl;
    //cout << img;
    Mat temp = imread(b);
    cout << b <<endl;
    //cout << temp;
    namedWindow("image_window", WINDOW_AUTOSIZE);
    namedWindow("result_window", WINDOW_AUTOSIZE);
    Mat img_display;
    img.copyTo(img_display);
    Mat result;
    /// Creating the result matrix
    int result_cols = img.cols + temp.cols - 1;
    int result_rows = img.rows + temp.rows - 1;
    result.create( result_cols, result_rows, CV_32FC1);
    matchTemplate(img, temp, result, TM_CCOEFF_NORMED);
    normalize(result, result, 0, 1, NORM_MINMAX, -1, Mat());

    /// Localizing the best match with minMaxLoc
    double minVal; double maxVal; Point minLoc; Point maxLoc;
    static Point matchLoc;

    minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc, Mat());

    if (match_method == TM_SQDIFF || match_method == TM_SQDIFF_NORMED)
    {
        matchLoc = maxLoc;
    }
    else
    {
        matchLoc = minLoc;
    }

    rectangle(img_display, matchLoc, Point(matchLoc.x + temp.cols, matchLoc.y + temp.rows), Scalar(0, 0, 0), 2, 8, 0);
    rectangle(result, matchLoc, Point(matchLoc.x + temp.cols, matchLoc.y + temp.rows), Scalar(0, 0, 0), 2, 8, 0);
    *x = matchLoc.x;
    *y = matchLoc.y;
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by function: "
        << duration.count() << " microseconds" << endl;
    imshow("image_window", img_display);
    imshow("result_window", result);
    //cout << matchLoc;
    //cout << img;
    //cout << temp;
    waitKey(0);
}