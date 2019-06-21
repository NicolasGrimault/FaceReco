#include <iostream>
#ifdef WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif // win32
#include <time.h>

//g++ -o photo photo.cpp `pkg-config  --cflags --libs opencv`

#define BLACK CV_RGB(0,0,0)

#include <opencv2/opencv.hpp>

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
            cv::Mat img;
            cv::Size sizeRect(40, 40);


            cv::namedWindow("Window3", cv::WINDOW_AUTOSIZE);
            int count = 0;
            while(true)
            {
                videoOpenCv.read(img);
                cvtColor(img, img, CV_RGB2GRAY);

                std::vector<cv::Rect> faces;
                std::vector<std::string> names;



                face_cascade.detectMultiScale(img, faces, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, sizeRect);
                for( size_t i = 0; i < faces.size(); i++ )
                {
                    names.push_back("Human being");
                }

                for( size_t i = 0; i < faces.size(); i++ )
                {
                  CvRect r = faces.at(i);
                  rectangle(img, cvPoint( r.x, r.y ), cvPoint( r.x + r.width, r.y + r.height ), BLACK, 1, 8, 0);
                  putText(img,names.at(i), cvPoint(r.x + r.width + 10, r.y + r.height + 10), cv::FONT_HERSHEY_PLAIN, 1.0, BLACK, 2.0);
                }
                cv::imshow("Window3", img);
                int key = cv::waitKey(1000/25);
                if(key==(int)'q')
                {
                    break;
                }
                if(key==(int)'p')
                {
                  std::string fname;
                  for( size_t i = 0; i < faces.size(); i++ ){
                    CvRect r = faces.at(i);
                    cv::Rect myROI(cvPoint( r.x, r.y ), cvPoint( r.x + r.width, r.y + r.height ));
                    cv::Mat croppedImage = img(myROI);
                    cv::Mat face_resized;
                    cv::resize(croppedImage, face_resized, cv::Size(400, 400), 1.0, 1.0, cv::INTER_CUBIC);
                    count++;
                    fname="./Photo"+std::to_string(count)+".png";
                    cv::imwrite(fname,face_resized);
                }
              }

            }
        }
        catch(int e)
        {
                return e;
        }

        return 0;
}
