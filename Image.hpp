#ifndef __prog_Image_hpp__
#define __prog_Image_hpp__
#include "Color.hpp"
#include<iostream>
#include<vector>

namespace prog
{
  class Image
  {
  private:
    int w_;
    int h_;
    Color color_;
    std::vector<std::vector<Color>> array;
  public:
    Image(int w, int h, const Color &fill = {255, 255, 255});
    ~Image();
    int width() const;
    int height() const;
    Color &at(int x, int y);
    const Color &at(int x, int y) const;
    void invert();
    void to_gray_scale();
    void replace(rgb_value red1,rgb_value green1,rgb_value blue1,rgb_value red2,rgb_value green2,rgb_value blue2);
    void fill(int x,int y,int w,int h,rgb_value red,rgb_value green,rgb_value blue);
    void h_mirror();
    void l_mirror();
    void add_filename(rgb_value r,rgb_value g,rgb_value b,int x,int y);
  };
}
#endif
