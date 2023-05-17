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
    int w_;  // largura da imagem
    int h_;  // altura da imagem
    Color color_; // cor padrão
    std::vector<std::vector<Color>> array; // matriz de pixels
  public:
    Image(int w, int h, const Color &fill = {255, 255, 255}); // constructor da imagem
    ~Image(); // destructor da imagem
    int width() const;
    int height() const;
    Color &at(int x, int y); // obter uma referência para o pixel na posição (x, y)
    const Color &at(int x, int y) const;
    void invert(); // inverter as cores da imagem
    void to_gray_scale(); // converter a imagem para escala de cinzento
    void replace(rgb_value red1,rgb_value green1,rgb_value blue1,rgb_value red2,rgb_value green2,rgb_value blue2);  // substituir uma cor por outra
    void fill(int x,int y,int w,int h,rgb_value red,rgb_value green,rgb_value blue); // preencher uma região retangular com uma cor
    void h_mirror(); // espelhar a imagem horizontalmente
    void l_mirror(); // espelhar a imagem verticalmente
    void add_filename(rgb_value r,rgb_value g,rgb_value b,int x,int y); // adicionar um filename na posição (x, y)
  };
}
#endif
