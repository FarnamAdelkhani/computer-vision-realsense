#include <opencv2/dnn.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core/utils/trace.hpp>

using namespace cv;
using namespace cv::dnn;

#include <fstream>
#include <iostream>
#include <cstdlib>


using namespace std;


/* Find best class for the blob (i. e. class with maximal probability) */
static void getMaxClass(const Mat& probBlob, int* classId, double* classProb)
{
    Mat probMat = probBlob.reshape(1, 1); //reshape the blob to 1x1000 matrix
    Point classNumber;
    minMaxLoc(probMat, NULL, classProb, NULL, &classNumber);
    *classId = classNumber.x;
}


static std::vector<String> readClassNames(const char* filename = "synset_words.txt")
{
    std::vector<String> classNames;
    std::ifstream fp(filename);
    if (!fp.is_open())
    {
        std::cerr << "File with classes labels not found: " << filename << std::endl;
        exit(-1);
    }
    std::string name;
    while (!fp.eof())
    {
        std::getline(fp, name);
        if (name.length())
            classNames.push_back(name.substr(name.find(' ') + 1));
    }
    fp.close();
    return classNames;
}


int main(int argc, char** argv)
{
    cout << "OpenCV version : " << CV_VERSION << endl;
    cout << "Major version : " << CV_MAJOR_VERSION << endl;
    cout << "Minor version : " << CV_MINOR_VERSION << endl;
    cout << "Subminor version : " << CV_SUBMINOR_VERSION << endl;

    if (CV_MAJOR_VERSION < 3)
    {
        // Old OpenCV 2 code goes here. 
    }
    else
    {
        // New OpenCV 3 code goes here. 
    }

    CV_TRACE_FUNCTION();
    String modelTxt = "C:/Users/Farnam/Desktop/GIT/computer_vision_realsense/third_party/opencv_extra/testdata/dnn/bvlc_googlenet.prototxt";
    String modelBin = "C:/Users/Farnam/Desktop/GIT/computer_vision_realsense/third_party/opencv_extra/testdata/dnn/bvlc_googlenet.caffemodel";
    // add the following lines
    if (modelTxt.empty() || modelBin.empty())
        std::cout << "failed to open modelTxt or modelBin" << std::endl;
    else
        std::cout << "modelTxt and modelBin loaded OK" << std::endl;

    String imageFile = (argc > 1) ? argv[1] : "C:/Users/Farnam/Desktop/GIT/computer_vision_realsense/third_party/opencv_extra/testdata/dnn/space_shuttle.jpg";

    // add the following lines
    if (imageFile.empty())
        std::cout << "failed to open space_shuttle.jpg" << std::endl;
    else
        std::cout << "space_shuttle.jpg loaded OK" << std::endl;

    Net net = dnn::readNetFromCaffe(modelTxt, modelBin);
    if (net.empty())
    {
        std::cerr << "Can't load network by using the following files: " << std::endl;
        std::cerr << "prototxt:   " << modelTxt << std::endl;
        std::cerr << "caffemodel: " << modelBin << std::endl;
        std::cerr << "bvlc_googlenet.caffemodel can be downloaded here:" << std::endl;
        std::cerr << "http://dl.caffe.berkeleyvision.org/bvlc_googlenet.caffemodel" << std::endl;
        exit(-1);
    }
    Mat img = imread(imageFile);
    if (img.empty())
    {
        std::cerr << "Can't read image from the file: " << imageFile << std::endl;
        exit(-1);
    }
    //GoogLeNet accepts only 224x224 RGB-images
    Mat inputBlob = blobFromImage(img, 1, Size(224, 224),
        Scalar(104, 117, 123));   //Convert Mat to batch of images
    Mat prob;
    cv::TickMeter t;
    for (int i = 0; i < 10; i++)
    {
        CV_TRACE_REGION("forward");
        net.setInput(inputBlob, "data");        //set the network input
        t.start();
        prob = net.forward("prob");                          //compute output
        t.stop();
    }
    int classId;
    double classProb;
    getMaxClass(prob, &classId, &classProb);//find the best class
    std::vector<String> classNames = readClassNames();
    std::cout << "Best class: #" << classId << " '" << classNames.at(classId) << "'" << std::endl;
    std::cout << "Probability: " << classProb * 100 << "%" << std::endl;
    std::cout << "Time: " << (double)t.getTimeMilli() / t.getCounter() << " ms (average from " << t.getCounter() << " iterations)" << std::endl;
    return 0;
} //main