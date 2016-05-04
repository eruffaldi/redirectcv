#include <opencv2/opencv.hpp>
#include <dlfcn.h>

namespace cv
{
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
		realimshow = (FX*)dlsym(RTLD_NEXT,"__ZN2cv6imshowERKNSt3__112basic_stringIcNS0_11char_traitsIcEENS0_9allocatorIcEEEERKNS_11_InputArrayE");
		if(!realimshow)
		{
			std::cout << "cannot find cv::imshow: use nm -gU sharedlibrary | grep imshow\n";
			exit(-1);
		}
	}

}

// preload with LD_PRELOAD=mylib
