#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <string>
#include <stdio.h>
#include <time.h>
#include <bits/stdc++.h>

using namespace std;
using namespace cv;

// Get current date/time, format is YYYY-MM-DD.HH:mm:ss
const string currentDateTime() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
    // for more information about date/time format
    strftime(buf, sizeof(buf), "%Y-%m-%d-%X", &tstruct);

    return buf;
}

int cap_index=0;
bool display_index=false;

int main(int argc,const char** argv){

	if(argc<3){
		cout<<"USAGE: "<<endl<<"First Argument : Capturing Index 0/1 "<<endl<<"Second Argument : Display Screen 0 for no 1 for yes"<<endl;
		return 0;
	}

	if(*argv[1]=='1') cap_index=1;
	if(*argv[2]=='1') display_index=true;

	//VideoCapture cap("sample.mp4");
	VideoCapture cap(cap_index);
	
	if(!cap.isOpened()){
		cout<<"could not load video";
		return -1;
	}
	//to get fps of video
	/*double fps= cap.get(CV_CAP_PROP_FPS);
	cout<<"FPS: "<<fps<<endl;*/ 
	
	namedWindow("VIDCAP",CV_WINDOW_AUTOSIZE);
	
	
   //Size size=cvSize(640,480);
	
   double dWidth = cap.get(CV_CAP_PROP_FRAME_WIDTH); //get the width of frames of the video
   double dHeight = cap.get(CV_CAP_PROP_FRAME_HEIGHT); //get the height of frames of the video

   Size size(static_cast<int>(dWidth), static_cast<int>(dHeight));
   
   int frames_ps=20;

   string date_time=currentDateTime();  
   /*char path[50];
   snprintf(path, 50,"%s.avi", date_time );	;
*/
   VideoWriter vidcap(" "+date_time+".avi", CV_FOURCC('P','I','M','1'), frames_ps, size, true); //initialize the VideoWriter object 
   //VideoWriter vidcap(filename, CV_FOURCC('X','V','I','D'), frames_ps, size,false);	

   if ( !vidcap.isOpened() ) //if not initialize the VideoWriter successfully, exit the program
   {
        cout << "ERROR: Failed to write the video" << endl;
        return -1;
   }
	
	while(1){
		Mat frame;
		bool isopen=cap.read(frame);
		if(!isopen){
			cout<<"cannot read video";
			break;
		}

		vidcap.write(frame);
		
		if(display_index) imshow("VIDCAP",frame);

		char key=cvWaitKey(30);
		if((key) == 27){
			break;
		}
		
	}
    destroyWindow("VIDCAP"); //Destroy Window
	return 0;
	
	
}
