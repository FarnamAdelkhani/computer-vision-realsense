#include <opencv2/opencv.hpp>

#include <vector>

using namespace cv;

int main()
{
	//Image scale factor
	double scale = 1.5;

	CascadeClassifier faceCascade;
	faceCascade.load("third_party/opencv/etc/haarcascades/haarcascade_frontalface_default.xml");

	VideoCapture cap(0);

	if (!cap.isOpened())
		return -1;

	//Infinite loop to get frames
	// termination sequence determined inside loop
	for (;;)
	{
		Mat frame;
		cap >> frame;

		//convert color image to greyscale
		Mat grayscale;
		cvtColor(frame, grayscale, COLOR_BGR2GRAY);

		//resize for GPU load optimization
		resize(grayscale, grayscale, Size(grayscale.size().width / scale, grayscale.size().height / scale));

		//Detect faces
		std::vector<Rect> faces;
		faceCascade.detectMultiScale(grayscale, faces, 1.1, 3, 0, Size(30, 30));

		for (Rect area : faces)
		{
			//set rectangle color
			Scalar drawColor = Scalar(255, 0, 0);

			//Rectangle X,Y with vertex @ X + width, Y + height
			rectangle(frame, Point(cvRound(area.x * scale), cvRound(area.y * scale)),
				Point(cvRound((area.x + area.width - 1) * scale), cvRound((area.y + area.height - 1) * scale)), drawColor);

		}

		imshow("Webcam Frame", frame);

		if (waitKey(30) >= 0)
			break;

	}
	return 0;
}