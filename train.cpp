#include "opencv2/core.hpp"
#include "opencv2/face.hpp"
#include "opencv2/highgui.hpp"
#include <opencv2/objdetect.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace cv;
using namespace cv::face;
using namespace std;


static void read_csv(const string& filename, vector<Mat>& images, vector<int>& labels, char separator = ';') {
    std::ifstream file(filename.c_str(), ifstream::in);
    if (!file) {
        string error_message = "No valid input file was given, please check the given filename.";
        CV_Error(CV_StsBadArg, error_message);
    }
    string line, path, classlabel;
    while (getline(file, line)) {
        stringstream liness(line);
        getline(liness, path, separator);
        getline(liness, classlabel);
        if(!path.empty() && !classlabel.empty()) {
            images.push_back(imread(path, 0));
            labels.push_back(atoi(classlabel.c_str()));
        }
    }
}

int main(int argc, const char *argv[]) {
    if (argc != 2) {
        cout << "usage: " << argv[0] << "  </path/to/csv.ext>" << endl;
        cout << "\t </path/to/csv.ext> -- Path to the CSV file with the face database." << endl;
        exit(1);
    }
    string fn_csv = string(argv[1]);
    vector<Mat> images;
    vector<int> labels;
    try {
        read_csv(fn_csv, images, labels);
    } catch (cv::Exception& e) {
        cerr << "Error opening file \"" << fn_csv << "\". Reason: " << e.msg << endl;
        exit(1);
    }
    Ptr<LBPHFaceRecognizer> model = cv::face::createLBPHFaceRecognizer();
    cout << "Start training.." << endl;
    model->train(images, labels);
    FileStorage train =FileStorage("trainer.yml",1);
    model ->save(train);
    cout << "Finish training" << endl;
    return 0;
}
