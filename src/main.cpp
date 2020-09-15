#include <opencv2/opencv.hpp>

#include <vector>

using namespace cv;

int main()
{
	//Image scale factor
	double scale = 2.0;

	CascadeClassifier face_cascade;
	CascadeClassifier eyes_cascade;
	CascadeClassifier smile_cascade;

	//Load cascades
	face_cascade.load("third_party/opencv/etc/haarcascades/haarcascade_frontalface_default.xml");
	eyes_cascade.load("third_party/opencv/etc/haarcascades/haarcascade_eye_tree_eyeglasses.xml");
	smile_cascade.load("third_party/opencv/etc/haarcascades/haarcascade_smile.xml");

	//Set capture device
	VideoCapture cap(0);

	if (!cap.isOpened())
	{
		std::cout << "--(!)Error opening video capture device\n";
		return -1;
	}

	//Infinite loop to get frames
	// termination sequence determined inside loop
	for (;;)
	{
		Mat frame;
		cap >> frame;

		//Convert color image to greyscale
		Mat gray_scale;
		cvtColor(frame, gray_scale, COLOR_BGR2GRAY);

		//Equalizes the histogram of a grayscale image.
		equalizeHist(gray_scale, gray_scale);

		//*Delete* - scaling in 'detectMultiScale'
		//resize for GPU load optimization
		//resize(gray_scale, gray_scale, Size(gray_scale.size().width / scale, gray_scale.size().height / scale));

		//Detect faces
		std::vector<Rect> faces;
		//Detects objects of different sizes in the input image. The detected objects are returned as a list of rectangles.
		face_cascade.detectMultiScale( gray_scale,      //image - Matrix of the type CV_8U containing an image
							   		   faces, 			//objects - Vector of rectangles where each rectangle contains the detected object
							   		   1.2, 			//scaleFactor - Parameter specifying how much the image size is reduced at each image scale.
							   		   3,               //minNeighbors - Parameter specifying how many neighbors each candidate rectangle should have to retain it.
							   		   0| CASCADE_SCALE_IMAGE,
							   		   Size(40, 40),    //minSize - Minimum possible object size. Objects smaller than that are ignored
			                           Size(300,300));  //maxSize - Maximum possible object size. Objects larger than that are ignored.

		for (size_t i = 0; i < faces.size(); i++)
		{
			//Color palette
			Scalar red = Scalar(255, 0, 0);
			Scalar green = Scalar(0, 255, 0);
			Scalar blue = Scalar(0, 0, 255);

			Point center(faces[i].x + faces[i].width / 2, 
						 faces[i].y + faces[i].height / 2);

			/*
			ellipse(frame,						 //image
					center, 					 //center
					Size(faces[i].width / 2, 	 //axes
						 faces[i].height / 2), 
					0, 							 //angle
					0, 							 //start angle
					360, 						 //end angle
					red, 						 //color
					3,							 //thickness
					0,							 //lineType
					0 );						 //shift
			*/

			rectangle( frame,                              //image
					   Point(faces[i].x, faces[i].y), 	   //1st vertex of rectangle
					   Point(faces[i].x + faces[i].width,  //vertex opposite to 1st
					   	  faces[i].y + faces[i].height), 
					   red, 			   //color
					   4, 								   //thickness
					   8, 								   //Type of line
					   0 );								   //shift

			Mat faceROI = gray_scale(faces[i]);

			//Detect eyes in each face
			std::vector<Rect> eyes;
			eyes_cascade.detectMultiScale(faceROI, eyes, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size(30, 30));

			for (size_t j = 0; j < eyes.size(); j++)
			{
				Point eye_center(faces[i].x + eyes[j].x + eyes[j].width / 2, 
					             faces[i].y + eyes[j].y + eyes[j].height / 2);
				
				int radius = cvRound((eyes[j].width + eyes[j].height) * 0.20);

				circle( frame, 
						eye_center, 
						radius, 
						blue,
						3 );
			}

			std::vector<Rect> smile;
			smile_cascade.detectMultiScale(faceROI, smile, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size(80, 80));

			for (int j = 0; j < smile.size(); j++)
			{
				Point smile_center( faces[i].x + smile[j].x + smile[j].width / 2, 
								    faces[i].y + smile[j].y + smile[j].height / 2);

				int radius = cvRound((smile[j].width + smile[j].height) * 0.25);
				circle( frame, 
						smile_center, 
						radius, 
						green, 
						4, 
						8, 
						0 );

			}
		}

		imshow("Capture - Face and eye detection", frame);

		if (waitKey(30) >= 0)
			break;

	}
	return 0;
}