#ifndef __prog_Script_hpp__
#define __prog_Script_hpp__

#include <string>
#include <fstream>
#include "Image.hpp"

namespace prog
{
  class Script
  {
  public: 
    Script(const std::string &filename);  // constructor do script
    ~Script();  // distructor do script
    void run(); // executar o script
    void invert(); // inverter as cores da imagem atual
    void to_gray_scale(); // converter a imagem atual para uma escala cinza
    void replace(Color fst ,Color sec); // substituir uma cor pela outra na imagem atual
    void fill(int x,int y,int w,int h,Color k); // preencher uma região retangular com uma cor na imagem atual
    void rotate_right();
    void rotate_left();
    void v_mirror(); // espelhar verticalmente a imagem atual
    void h_mirror(); // espelhar horizontalmente a imagem atual
    void add(); // adicionar uma nova imagem
    void crop(int x,int y,int w,int h); // recortar uma região retangular da imagem atual
    void median_filter(int ws);  // aplicar filtro da mediana na imagem atual com tamanho de janela especificado
  private:
     // Imagem atual
    Image *image;
     // Fluxo de entrada para ler comandos do script.
    std::ifstream input;
    
  private:
    // Private functions
    void clear_image_if_any();
    void open();
    void blank();
    void save();

  };
}
#endif
