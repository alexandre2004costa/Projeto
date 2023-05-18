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
    int w_; // largura da imagem
    int h_; // altura da imagem
    std::vector<std::vector<Color>> array; //matriz dos pixels
  public:
    Image(int w, int h, const Color &fill = {255, 255, 255}); // constructor da imagem
    ~Image(); // distructor da imagem
    int width() const; //obter a largura da imagem
    int height() const; //obter a altura da imagem
    Color &at(int x, int y); // obter uma referência para o pixel na posição (x, y)
    const Color &at(int x, int y) const; // obter uma referência constante para o pixel na posição (x, y)
  };
}
#endif
