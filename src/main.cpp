#include <opencv2/opencv.hpp>

#include <vector>

///TODO Segmentation for eyes is off-center.

using namespace cv;

int main()
{
	//Image scale factor
	double scale = 2.0;

	CascadeClassifier face_cascade;
	CascadeClassifier eyes_cascade;

	face_cascade.load("third_party/opencv/etc/haarcascades/haarcascade_frontalface_default.xml");
	eyes_cascade.load("third_party/opencv/etc/haarcascades/haarcascade_eye_tree_eyeglasses.xml");

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
		face_cascade.detectMultiScale(grayscale, faces, 1.1, 3, 0, Size(30, 30));

		
		//-- In each face, detect eyes
		std::vector<Rect> eyes;
		eyes_cascade.detectMultiScale(grayscale, eyes);

		for (size_t i = 0; i < faces.size(); i++)
		{
			//set rectangle color
			Scalar drawColor = Scalar(255, 0, 0);

			//Rectangle X,Y with vertex @ X + width, Y + height
			rectangle(frame, 
				Point(cvRound(faces[i].x * scale), 
					cvRound(faces[i].y * scale)),
				Point(cvRound((faces[i].x + faces[i].width - 1) * scale), 
					cvRound((faces[i].y + faces[i].height - 1) * scale)), 
				drawColor);

			for (size_t j = 0; j < eyes.size(); j++)
			{
				Point eye_center(faces[i].x + eyes[j].x + eyes[j].width ,
					faces[i].y + eyes[j].y + eyes[j].height );
				
				int radius = cvRound((eyes[j].width + eyes[j].height) * 0.25);

				circle(frame, eye_center, radius, Scalar(255, 0, 0), 4);
			}
		}

		imshow("Webcam Frame", frame);

		if (waitKey(30) >= 0)
			break;

	}
	return 0;
}