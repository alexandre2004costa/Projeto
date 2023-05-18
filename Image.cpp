#include "Image.hpp"

namespace prog
{
  Image::Image(int w, int h, const Color &fill){
    w_=w;
    h_=h;
    array.resize(w_, std::vector<Color>(h_));
    for(int i=0;i<w_;i++){
      for(int j=0;j<h_;j++){
        array[i][j]=fill;
      }
    }
  }
  Image::~Image(){}
  int Image::width() const
  {
    return w_;
  }
  int Image::height() const
  {
    return h_;
  }
  Color& Image::at(int x, int y)
  {
    return array[x][y];
  }
  const Color& Image::at(int x, int y) const
  {
    return array[x][y];
  }
  
}
