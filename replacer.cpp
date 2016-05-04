#include <opencv2/opencv.hpp>
#include <dlfcn.h>

// TODO use some C++11 metaprogramming and extract it from the real imshow
using FX = void(std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> > const&, cv::_InputArray const&);
FX* realimshow;

namespace cv
{
	void imshow(std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> > const& name, cv::_InputArray const& p)
	{
		std::cout << "imshow " << name << std::endl;
		if(name[0] == '!')
			 realimshow(name.substr(1),p);
	}
}

struct Entrypoint
{
	Entrypoint()
	{
		// nm -gU libopencv_highgui.dylib  | grep imshow
		// nm -g  test | grep imshow 
		// Linux OpenCV 2.4.12: _ZN2cv6imshowERKSsRKNS_11_InputArrayE
		// OSX OpenCV 2.4.11: __ZN2cv6imshowERKNSt3__112basic_stringIcNS0_11char_traitsIcEENS0_9allocatorIcEEEERKNS_11_InputArrayE
		//
		// VERIFY
		// MY:                __ZN2cv6imshowERKNSt3__112basic_stringIcNS0_11char_traitsIcEENS0_9allocatorIcEEEERKNS_11_InputArrayE
		// EXE:               __ZN2cv6imshowERKNSt3__112basic_stringIcNS0_11char_traitsIcEENS0_9allocatorIcEEEERKNS_11_InputArrayE
		// 
		#define SYMBOLOSX "_ZN2cv6imshowERKNSt3__112basic_stringIcNS0_11char_traitsIcEENS0_9allocatorIcEEEERKNS_11_InputArrayE"
		#define SYMBOLLINUX "_ZN2cv6imshowERKSsRKNS_11_InputArrayE"
		
		#define SYMBOL SYMBOLOSX
		realimshow = (FX*)dlsym(RTLD_NEXT,SYMBOL);
		
		if(!realimshow)
		{
			std::cout << "cannot find cv::imshow: use nm -gU sharedlibrary | grep imshow\n";
			exit(-1);
		}
	}
};

Entrypoint entry;

