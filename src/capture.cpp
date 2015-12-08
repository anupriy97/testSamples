#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include<bits/stdc++.h>

using namespace cv;
using namespace std;

int main(int argc, char* argv[])
{
	int n;
	printf("Enter camera number : ");
	scanf("%d",&n);
	char address[500];

	VideoCapture cap(n); // open the video camera no. 0
	
	if (!cap.isOpened())  // if not success, exit program
	{
        	cout << "ERROR: Cannot open the video file" << endl;
		return -1;
	}

	namedWindow("MyVideo",CV_WINDOW_AUTOSIZE); //create a window called "MyVideo"

	double dWidth = cap.get(CV_CAP_PROP_FRAME_WIDTH); //get the width of frames of the video
	double dHeight = cap.get(CV_CAP_PROP_FRAME_HEIGHT); //get the height of frames of the video

	cout << "Frame Size = " << dWidth << "x" << dHeight << endl;

	Size frameSize(static_cast<int>(dWidth), static_cast<int>(dHeight));

	while(1)
	{
		int a=0,check=0;
		
		printf("Write the location to store video(including file_name) : ");
		scanf("%s",address);
		VideoWriter record1 (address, CV_FOURCC('P','I','M','1'), 20, frameSize, true);
		if ( !record1.isOpened() ) //if not initialize the VideoWriter successfully, exit the program
		{
			cout << "ERROR: Failed to write the video" << endl;
			return -1;
		}
		
		while(1)
		{
			char space=waitKey(10);
			if(space==32) {
				check=!check;
				if(a==0)
				{
					printf("Recording started..");
					a++;
				}
				else if(a==1)
				{
					printf("Recording stopped.");
					break;
				}
			}
			Mat frame;
		
			bool bSuccess = cap.read(frame); // read a new frame from video
			
			if (!bSuccess) //if not success, break loop
			{
				cout << "ERROR: Cannot read a frame from video file" << endl;
				break;
		        }
			
			if(check)
			{
				record1.write(frame);
			}
			
			imshow("MyVideo",frame);
			
			char key=waitKey(10);
			if (key == 27) //wait for 'esc' key press for 10ms. If 'esc' key is pressed, break loop
	        	{
				cout << "esc key is pressed by user" << endl;
	        	        return 0;
	        	}
		}		
	}

	return 0;

}
