#include "Image.hpp"

namespace prog
{
  Image::Image(int w, int h, const Color &fill){
    w_=w; // largura da imagem
    h_=h; // altura da imagem
    array.resize(w_, std::vector<Color>(h_)); // redimensionar a matriz de pixels
    for(int i=0;i<w_;i++){
      for(int j=0;j<h_;j++){
        array[i][j]=fill; // preencher a matriz de pixels com a cor especificada
      }
    }
  }
  Image::~Image(){}
  int Image::width() const 
  {
    return w_; // obter a largura da imagem
  }
  int Image::height() const
  {
    return h_; // obter a altura da imagem
  }
  Color& Image::at(int x, int y)
  {
    return array[x][y]; // obter uma referência para o pixel na posição (x, y)
  }
  const Color& Image::at(int x, int y) const
  {
    return array[x][y]; // obter uma referência constante para o pixel na posição (x, y)
  }
  
}
