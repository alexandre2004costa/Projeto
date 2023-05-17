#include "Image.hpp"

namespace prog
{
  Image::Image(int w, int h, const Color &fill){
    w_=w; // largura da imagem
    h_=h; // altura da imagem
    array.resize(w_, std::vector<Color>(h_)); // redimensionar a matriz de pixels
    color_=fill; // cor do preenchimento
    for(int i=0;i<int(w_);i++){
      for(int j=0;j<int(h_);j++){
        array[i][j]=color_; // preencher a matriz de pixels com a cor do preenchimento
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
  void Image:: invert(){
    for(int i=0;i<int(w_);i++){
      for(int j=0;j<int(h_);j++){
        array[i][j]=Color(255-array[i][j].red(), 255-array[i][j].green() , 255-array[i][j].blue()); // inverter a cor do pixel
      }
    }
  }
  void Image::to_gray_scale(){
    for(int i=0;i<int(w_);i++){
      for(int j=0;j<int(h_);j++){
        rgb_value v =int((array[i][j].red()+array[i][j].green()+array[i][j].blue())/3); // calcular a média dos componentes da cor para converter em escala de cinza
        array[i][j]=Color(v,v,v); // definir o pixel para a cor em escala de cinza
      }
    }
  }
  void Image::replace(rgb_value red1,rgb_value green1,rgb_value blue1,rgb_value red2,rgb_value green2,rgb_value blue2){
    for(int i=0;i<int(w_);i++){
      for(int j=0;j<int(h_);j++){
        if(array[i][j].red()==red1&&array[i][j].green()==green1&&array[i][j].blue()==blue1){
          array[i][j]=Color(red2, green2 , blue2); // substituir a cor do pixel pela nova cor especificada
        }
      }
    }
  }
  void Image::fill(int x,int y,int w,int h,rgb_value red,rgb_value green,rgb_value blue){
   for(int i=x;i<=w;i++){
      for(int j=y;j<=h;j++){
          array[i][j]=Color(red,green,blue); // preencher uma região retangular com a cor especificada
        }
      }
    }
  void Image::h_mirror(){
    int k=1; //variável de controlo 
    for(int i=w_/2;i<=w_;i++){
      for(int j=0;j<=h_;j++){
          array[i][j]=array[i-k][j]; // espelhar horizontalmente a metade direita da imagem para a metade esquerda
        }
      }
      k++;
      k++;
    }
  
}
