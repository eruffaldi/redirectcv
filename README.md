# redirectcv
Example of OpenCV redirection to hide/control imshow

Requires: https://github.com/eruffaldi/cmakego
	cmakego -DCMAKE_MODULE_PATH=...cmakegolocation .

Customize under Linux or different version of OpenCV:

	nm -gU libopencv_highui.dylib

Tested under OSX with opencv 2.4
