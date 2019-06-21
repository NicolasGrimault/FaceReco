#include <iostream>
#ifdef WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif // win32
#include <time.h>

#include <opencv2/opencv.hpp>
#include "opencv2/face.hpp"

#define BLACK CV_RGB(0,0,0)
using namespace cv::face;

void sleepcp(int milliseconds) // cross-platform sleep function
{
#ifdef WIN32
    Sleep(milliseconds);
#else
    usleep(milliseconds * 1000);
#endif // win32
}

int calculationFPS(time_t *start, int count)
{
    int ret = count;
    if(count==100)
    {
        double seconds = 1;
        double fps = 0;
        time_t end;

        time(&end);
        seconds = difftime(end,*start);
        fps = count/seconds;
        std::cout << "\033[031;1mFrames per seconds : " << fps << "\033[0m" << std::endl;
        sleepcp(30);

        time(start);

        ret = 0;
    }
    return ret;
}

int main()
{
        try
        {
            cv::VideoCapture videoOpenCv;
            bool test = videoOpenCv.open(0);
            if(test==false)
            {
                throw -101;
            }

            cv::CascadeClassifier face_cascade;
            if(!face_cascade.load("/usr/share/opencv/haarcascades/haarcascade_frontalface_alt2.xml"))
            {
                throw -103;
            }

            cv::Ptr<LBPHFaceRecognizer> model = cv::face::createLBPHFaceRecognizer();
            try
            {
                model->load("trainer.yml");
            }
            catch(const std::exception& e)
            {
                std::cerr << "error : "<<e.what() << '\n';
                exit(0);
            }



            int count = 0;
            time_t start;
            time(&start);

            cv::Mat img;
            cv::Mat map;
            cv::Size sizeRect(40, 40);

            while(true)
            {
                count++;
                videoOpenCv.read(img);

                std::vector<cv::Rect> faces;

                face_cascade.detectMultiScale(img, faces, 1.1, 2, 0|CV_HAAR_FIND_BIGGEST_OBJECT, sizeRect);
                if (faces.size() > 0) {
                  CvRect r = faces.at(0);
                  cv::Rect myMat(cvPoint( r.x, r.y ), cvPoint( r.x + r.width, r.y + r.height ));
                  cv::Mat croppedImage = img(myMat);
                  cv::resize(croppedImage, map, cv::Size(400, 400), 1.0, 1.0, cv::INTER_CUBIC);
                  cvtColor(map, croppedImage, CV_RGB2GRAY);

                  int modelClass = -1;
                  double confidence = 0.0;
                  model->predict(croppedImage, modelClass, confidence);

                  if (confidence < 100)
                  {
                      std::cout << modelClass << "\n";
                  }
                }

                count = calculationFPS(&start, count);
/*
                int key = cv::waitKey(1000/25);
                if(key==(int)'q')
                {
                    break;
                }*/
            }
        }
        catch(int e)
        {
                return e;
        }

        return 0;
}
