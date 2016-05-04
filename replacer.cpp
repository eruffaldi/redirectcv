#include <opencv2/opencv.hpp>
#include <dlfcn.h>


namespace cv
{
	// TODO use some C++11 metaprogramming and extract it from the real imshow
	using FX = void(const std::string,InputArray);
	FX* realimshow;
	void imshow(const std::string name,InputArray p)
	{
		if(name[0] == '!')
			 realimshow(name.substr(1),p);
	}

	void entrypoint()
	{
		// nm -gU libopencv_highgui.dylib  | grep imshow
		// Linux OpenCV 2.4.12: _ZN2cv6imshowERKSsRKNS_11_InputArrayE
		// OSX OpenCV 2.4.11: __ZN2cv6imshowERKNSt3__112basic_stringIcNS0_11char_traitsIcEENS0_9allocatorIcEEEERKNS_11_InputArrayE
		#define SYMBOLOSX __ZN2cv6imshowERKNSt3__112basic_stringIcNS0_11char_traitsIcEENS0_9allocatorIcEEEERKNS_11_InputArrayE
		#define SYMBOLLINUX _ZN2cv6imshowERKSsRKNS_11_InputArrayE
		
		#define SYMBOL SYMBOLOSX
		realimshow = (FX*)dlsym(RTLD_NEXT,SYMBOL);
		
		if(!realimshow)
		{
			std::cout << "cannot find cv::imshow: use nm -gU sharedlibrary | grep imshow\n";
			exit(-1);
		}
	}

}

// preload with LD_PRELOAD=mylib
