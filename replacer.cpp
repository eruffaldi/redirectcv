#include <opencv2/opencv.hpp>
#include <dlfcn.h>


namespace cv
{
	// TODO use some C++11 metaprogramming and extract it from the real imshow
#ifdef PASSSTRING
	using FX = void(const std::string,InputArray);
	FX* realimshow;
	void imshow(const std::string name,InputArray p)
	{
		if(name[0] == '!')
			 realimshow(name.substr(1),p);
	}
#else
	using FX = void(const char *, InputArray);
	FX* realimshow;
	void imshow(const char* name,InputArray p)
	{
		if(name[0] == '!')
			realimshow(name+1,p);
	}
#endif


	void entrypoint()
	{
		// nm -gU libopencv_highgui.dylib  | grep imshow
#ifdef PASSSTRING
		realimshow = (FX*)dlsym(RTLD_NEXT,"__ZN2cv6imshowERKNSt3__112basic_stringIcNS0_11char_traitsIcEENS0_9allocatorIcEEEERKNS_11_InputArrayE");
#else
		realimshow = (FX*)dlsym(RTLD_NEXT,"_ZN2cv6imshowERKSsRKNS_11_InputArrayE");
#endif
		if(!realimshow)
		{
			std::cout << "cannot find cv::imshow: use nm -gU sharedlibrary | grep imshow\n";
			exit(-1);
		}
	}

}

// preload with LD_PRELOAD=mylib
