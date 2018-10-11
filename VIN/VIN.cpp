/*	Identify VIN code using OpenCV
	Author: zwy4896
	Date:2018/10/9
	Version:V1.0 
*/
#include<iostream>
#include"opencv2/opencv.hpp"
using namespace cv;
using namespace std;

Mat img, gauss_img, gray_img, hist_img, thres_img,
	morph_img;

//Filter
void Filter()
{
	//Mat image_filter;
	int k_width = 7;
	int k_height = 7;
	GaussianBlur(img, gauss_img, Size(k_width, k_height), 0, 0);

	imwrite("Gaussian.jpg", gauss_img);
	namedWindow("Gaussian", CV_WINDOW_AUTOSIZE);
	imshow("Gaussian", gauss_img);
	//namedWindow("1", CV_WINDOW_AUTOSIZE);
	//imshow("1", img);
	waitKey();
}
////Gray
void gray()
{
	//Mat grey;
	cvtColor(gauss_img, gray_img, CV_BGR2GRAY);
	imwrite("Grey.jpg", gray_img);
	namedWindow("grey", CV_WINDOW_AUTOSIZE);
	imshow("grey", gray_img);
	waitKey();
}
////Histogram equalization
void HistoEqu()
{
	//Mat image_hist;
	equalizeHist(gray_img, hist_img);

	imwrite("Hist.jpg", hist_img);
	namedWindow("hist", CV_WINDOW_AUTOSIZE);
	imshow("hist", hist_img);
	waitKey();
}
////Binarization
void Bin()
{
	int blockSize = 25;
	int constValue = 10;
	adaptiveThreshold(gray_img, thres_img, 255, CV_ADAPTIVE_THRESH_MEAN_C, CV_THRESH_BINARY_INV, blockSize, constValue);
	imwrite("bin.jpg", thres_img);
	namedWindow("Thres", CV_WINDOW_AUTOSIZE);
	imshow("Thres", thres_img);
	waitKey();
}

void Mopho()
{
	Mat dil_img, ero_img;
	Mat element_ero = getStructuringElement(MORPH_RECT, Size(3, 3));
	Mat element_dil = getStructuringElement(MORPH_RECT, Size(8, 8));
	dilate(thres_img, dil_img, element_dil);
	erode(dil_img, ero_img, element_ero);
	imwrite("dil.jpg", dil_img);
	namedWindow("Dilation", CV_WINDOW_AUTOSIZE);
	imshow("Dilation", dil_img);
	waitKey();
	imwrite("erode.jpg", ero_img);
	namedWindow("Erode", CV_WINDOW_AUTOSIZE);
	imshow("Erode", ero_img);
	//namedWindow("1", CV_WINDOW_AUTOSIZE);
	//imshow("1", img);
	ero_img.copyTo(morph_img);
	waitKey();
}
void Outl()
{
	vector<vector<Point>> contours;
	//vector <Vec4i> hier;
	findContours(morph_img, contours, CV_RETR_CCOMP, CV_CHAIN_APPROX_NONE);
	drawContours(img, contours, -1, Scalar(0, 255, 0), 2);
	imwrite("contours.jpg", img);
	namedWindow("con", CV_WINDOW_AUTOSIZE);
	imshow("con", img);
	waitKey();
}

int main(int argc, char** argv)
{
	//Input img!
	string path = "./test.jpg";
	img = imread(path);
	//img.copyTo(image);
	if (img.empty())
	{
		cout << "Image not found!";
		return 0;
	}
	//namedWindow(wdname);

	//Filter
	Filter();
	////Gray
	gray();
	////Histogram equalization
	HistoEqu();
	////Binarization
	Bin();
	//Morphology
	Mopho();
	//OutLine
	Outl();

	for (;;)
	{
		//imshow("image", img);
		int c = waitKey(0);
		if ((c & 255) == 27)
		{
			cout << "Exiting ...\n";
			break;
		}
		if ((char)c == 'q')
		{
			destroyAllWindows();
			break;
		}
	}

}