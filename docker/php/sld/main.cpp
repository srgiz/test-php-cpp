#include <iostream>
#include <phpcpp.h>
#include <opencv2/opencv.hpp>

void sld_func()
{
    Php::out << "Hello PHP-CPP!" << std::endl;
}

class sld_opencv : public Php::Base {
private:
    Php::Value _path;
    cv::Mat _image;
public:
    /**
     *  C++ constructor and destructor
     */
    sld_opencv() = default;
    virtual ~sld_opencv() = default;

    void __construct(Php::Parameters &params)
    {
        _path = params[0];
        _image = cv::imread(_path);
        // https://docs.opencv.org/3.4/d4/da8/group__imgcodecs.html#ga288b8b3da0892bd651fce07b3bbd3a56
    }

    Php::Value getPath()
    {
        return _path;
    }

    Php::Value getWidth()
    {
        return _image.size().width;
    }

    Php::Value getHeight()
    {
        return _image.size().height;
    }

    Php::Value thumbnail(Php::Parameters &params)
    {
        Php::Value path = params[0];
        int width = params[1];
        int height = params[2];
        double factor = 1.0;

        if (width >= height) {
            factor = 1.0 / _image.size().width * width;
        } else {
            factor = 1.0 / _image.size().height * height;
        }

        // https://docs.opencv.org/4.x/da/d54/group__imgproc__transform.html#ga47a974309e9102f5f08231edc7e7529d
        cv::Mat r;
        cv::resize(_image, r, cv::Size(), factor, factor, cv::INTER_AREA);
        imwrite(path, r);

        return Php::Object("Srgiz\\OpenCV", path);
        // https://www.php-cpp.com/documentation/variables
    }
};

/**
 *  tell the compiler that the get_module is a pure C function
 */
extern "C" {

    /**
     *  Function that is called by PHP right after the PHP process
     *  has started, and that returns an address of an internal PHP
     *  strucure with all the details and features of your extension
     *
     *  @return void*   a pointer to an address that is understood by PHP
     */
    PHPCPP_EXPORT void *get_module()
    {
        // static(!) Php::Extension object that should stay in memory
        // for the entire duration of the process (that's why it's static)
        static Php::Extension extension("sld", "1.0");

        // create namespace
        Php::Namespace space("Srgiz");

        // add sld_func() to namespace
        space.add<sld_func>("func");

        // description of the class so that PHP knows which methods are accessible,
        // the __construct method is private because PHP scripts are not allowed
        // to create Counter instances
        Php::Class<sld_opencv> sld_opencv_class("OpenCV");
        sld_opencv_class.method<&sld_opencv::__construct>("__construct");
        sld_opencv_class.method<&sld_opencv::getPath>("getPath");
        sld_opencv_class.method<&sld_opencv::getWidth>("getWidth");
        sld_opencv_class.method<&sld_opencv::getHeight>("getHeight");
        sld_opencv_class.method<&sld_opencv::thumbnail>("thumbnail");

        space.add(std::move(sld_opencv_class));

        // add namespace to extension
        extension.add(std::move(space));

        return extension;
    }
}
