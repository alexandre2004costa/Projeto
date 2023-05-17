#include "Color.hpp"

namespace prog {
    Color::Color() { //default color
        red_=0;
        green_=0;
        blue_=0;
    }
    Color::Color(const Color& other) { //constructor copy
        red_=other.red();
        green_=other.green();
        blue_=other.blue();
    }
    Color::Color(rgb_value red, rgb_value green, rgb_value blue) { // construtor com parâmetros
        red_=red;
        green_=green;
        blue_=blue;
    }
    rgb_value Color::red() const {  //getter para a componente da cor vermelha
        return red_;
    }
    rgb_value Color::green() const { //getter para a componente da cor verde
        return green_;
    }
    rgb_value Color::blue() const { //getter para a componente da cor azul
        return blue_;
    }

    rgb_value& Color::red()  {  //getter e setter para a componente da cor vermelha
        return red_;
    }
    rgb_value& Color::green()  {    //getter e setter para a componente da cor verde
      return green_;
    }
    rgb_value& Color::blue()  { //getter e setter para a componente da cor azul
      return blue_;
    }
}
