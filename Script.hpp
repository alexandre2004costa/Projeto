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
    Script(const std::string &filename);
    ~Script();
    void run();
    void invert();
    void to_gray_scale();
    void replace(Color fst ,Color sec);
    void fill(int x,int y,int w,int h,Color k);
    void rotate_right();
    void rotate_left();
    void v_mirror();
    void h_mirror();
    void add();
    void crop(int x,int y,int w,int h);
    void median_filter(int ws);
  private:
    // Current image.
    Image *image;
    // Input stream for reading script commands.
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
