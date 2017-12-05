#include <iostream>
#include <vector>
#include <stdio.h>
#include <cerrno>
#include <cstring>
#include "Frame.h"
#include "Object.h"
#include "Image.h"
#include "Rectangle.h"
#include "Clock.h"

typedef unsigned char byte;

using namespace std;

const double frames_per_second = 30; 
const int duration_in_seconds = 11;

Frame frame(720, 480);

int main(int argc, char * argv[]) {
	// Construct the ffmpeg command to run.
	const char * cmd = 
		"ffmpeg              "
		"-y                  "
		"-hide_banner        "
		"-f rawvideo         " // input to be raw video data
		"-pixel_format rgb24 "
		"-video_size 720x480 "
		"-r 30               " // frames per second
		"-i -                " // read data from the standard input stream
		"-pix_fmt yuv420p    " // to render with Quicktime
		"-vcodec mpeg4       "
		"-an                 " // no audio
		"-q:v 5              " // quality level; 1 <= q <= 32
		"output.mp4          ";

	// Run the ffmpeg command and get pipe to write into its standard input stream.
#ifdef _WIN32
	FILE * pipe = _popen(cmd, "wb");
#else
	FILE * pipe = popen(cmd, "w");
#endif
	if (pipe == 0) {
		cout << "error: " << strerror(errno) << endl;
		return 1;
	}

	vector<Object *> objects;

	Clock clock;
	Rectangle rec1(10,20);
	Rectangle rec2(30,50);
	Rectangle rec3(50,25);
	Image img;

	clock.setX(150.0);
	clock.setY(200.0);

	img.setX(300.0);
	img.setY(150.0);
	img.setVelocity(0,-100);
	img.load("duck.bmp", 150, 150);

	rec1.setX(0.0);
	rec1.setY(0.0);
	rec1.setVelocity(80,80);
	rec1.setColor(0xFF, 0x00, 0x00);

	rec2.setX(300.0);
	rec2.setY(250.0);
	rec2.setVelocity(100,-100);
	rec2.setColor(0xFF, 0x00, 0xFF);

	rec3.setX(500.0);
	rec3.setY(400.0);
	rec3.setVelocity(-150,-150);
	rec3.setColor(0xFF, 0xFF, 0x00);


	objects.push_back(&clock);
	objects.push_back(&rec1);
	objects.push_back(&rec2);
	objects.push_back(&rec3);
	objects.push_back(&img);

	int num_frames = duration_in_seconds * frames_per_second;
	for (int i = 0; i < num_frames; ++i) {
		double dt = 1.0 / frames_per_second;
		frame.clear();

		for (int j = 0; j < objects.size(); j++) {
			objects[j]->update(dt);
			objects[j]->draw();
		}
		frame.write(pipe);
	}

	fflush(pipe);
#ifdef _WIN32
	_pclose(pipe);
#else
	pclose(pipe);
#endif

	cout << "num_frames: " << num_frames << endl;
	cout << "Done." << endl;

	return 0;
}
