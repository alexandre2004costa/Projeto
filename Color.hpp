#ifndef __prog_Color_hpp__
#define __prog_Color_hpp__

namespace prog
{
  typedef unsigned char rgb_value;
  class Color
  {
    private:
      rgb_value red_; // componente da cor vermelha
      rgb_value green_;  // componente da cor verde
      rgb_value blue_;  // componente da cor azul 
    public:
      Color();
      Color(const Color& c); // constructor de cópia
      Color(rgb_value r, rgb_value g, rgb_value b); // construtor com parametros
      rgb_value red() const; //getter para a componente da cor vermelha
      rgb_value& red(); //getter e setter para a componente da cor vermelha
      rgb_value green() const; //getter para a componente da cor verde
      rgb_value& green(); //getter e setter para a componente da cor verde
      rgb_value blue() const; //getter para a componente da cor azul
      rgb_value& blue(); //getter e setter para a componente da cor azul
  };
}
#endif
