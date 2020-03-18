//
// Created by ptl on 2020-03-10.
//

#include "utils.h"
#include <cmath>
#define REAL double

void displayImage(const cv::Mat &image){
    namedWindow( "Display window", cv::WINDOW_AUTOSIZE);
    cv::imshow( "Display window", image);
    cv::waitKey(0);
}

void printCV8UImage(const cv::Mat& image){
    if (image.depth() != 0)throw exception();
    int count255 = 0;
    int countOther = 0;
    for (int i=0; i<image.rows; i++){
        for (int j=0; j<image.cols; j++){
            int pixel = image.at<uchar>(i,j);
            if (pixel == 0){}
            else if (pixel == 255){count255++;}
            else {countOther++;}
            cout << setw(4) << pixel << " ";
        }
        cout << endl;
    }
    cout << "255 count: "<< count255 << endl;
    cout << "0 count: " << countOther << endl;
}


inline static REAL sqr(REAL x) {
    return x*x;
}

// from Mark Lakata (https://stackoverflow.com/questions/5083465/fast-efficient-least-squares-fit-algorithm-in-c)
void linearReg(int n, vector<double> x, vector<double> y, REAL* b, REAL* m, REAL* r){
    REAL sumx = 0.0;                      /* sum of x     */
    REAL sumx2 = 0.0;                     /* sum of x**2  */
    REAL sumxy = 0.0;                     /* sum of x * y */
    REAL sumy = 0.0;                      /* sum of y     */
    REAL sumy2 = 0.0;                     /* sum of y**2  */

    for (int i=0;i<n;i++){
        sumx  += x[i];
        sumx2 += sqr(x[i]);
        sumxy += x[i] * y[i];
        sumy  += y[i];
        sumy2 += sqr(y[i]);
    }

    REAL denom = (n * sumx2 - sqr(sumx));
    if (denom == 0) {
        // singular matrix. can't solve the problem.
        *m = 0;
        *b = 0;
        if (r) *r = 0;
        return;
    }

    *m = (n * sumxy  -  sumx * sumy) / denom;
    *b = (sumy * sumx2  -  sumx * sumxy) / denom;
    if (r!=nullptr) {
        *r = (sumxy - sumx * sumy / n) /    /* compute correlation coeff */
             sqrt((sumx2 - sqr(sumx)/n) *
                  (sumy2 - sqr(sumy)/n));
    }
}
