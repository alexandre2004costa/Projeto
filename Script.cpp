#include <iostream>
#include <fstream>
#include<algorithm>
#include "Script.hpp"
#include "PNG.hpp"
#include "XPM2.hpp"

using namespace std;

namespace prog {
    // Use to read color values from a script file.
    istream& operator>>(istream& input, Color& c) {
        int r, g, b;
        input >> r >> g >> b;
        c.red() = r;
        c.green() = g;
        c.blue() = b;
        return input;
    }

    Script::Script(const string& filename) :
            image(nullptr), input(filename) {

    }
    void Script::clear_image_if_any() {
        if (image != nullptr) {
            delete image;
            image = nullptr;
        }
    }
    Script::~Script() {
        clear_image_if_any();
    }

    void Script::run() {
        string command;
        while (input >> command) {
            cout << "Executing command '" << command << "' ..." << endl;
            if (command == "open") {
                open();
                continue;
            }
            if (command == "blank") {
                blank();
                continue;
            }
            // Other commands require an image to be previously loaded.
            if (command == "save") {
                save();
                continue;
            }
            if(command == "invert"){
                invert();
                continue;
            }
            if(command == "to_gray_scale"){
                to_gray_scale();
                continue;
            }
            if(command == "replace"){
                Color fst;Color sec;
                input >> fst>>sec;
                replace(fst,sec);
                continue;
            }
            if(command == "fill"){
                int x;int y;int w;int h;Color k;
                input >> x>> y>> w>>h>>k;
                fill( x, y, w, h,k);
                continue;
            }
            if(command == "rotate_right"){
                rotate_right();
                continue;
            }
             if(command == "rotate_left"){
                rotate_left();
                continue;
            }
            if(command == "h_mirror"){
                h_mirror();
                continue;
            }
            if(command == "v_mirror"){
                v_mirror();
                continue;
            }
            if(command == "crop"){
                int x;int y;int w;int h;
                input >> x>> y>> w>>h;
                crop(x,y,w,h);
                continue;
            }
            if(command == "add"){
                add();
                continue;
            }
            if(command == "median_filter"){
                int ws;
                input >> ws;
                median_filter(ws);
                continue;
            }
            if(command == "xpm2_open"){
                clear_image_if_any();
                string filename;
                input >> filename;
                image=loadFromXPM2(filename);
                continue;
            }
            if(command == "xpm2_save"){
                string filename;
                input >> filename;
                saveToXPM2(filename,image);
                continue;
            }   
            } 
            // TODO ...

        }
    void Script::open() {
        // Replace current image (if any) with image read from PNG file.
        clear_image_if_any();
        string filename;
        input >> filename;
        image = loadFromPNG(filename);
    }
    void Script::blank() {
        // Replace current image (if any) with blank image.
        clear_image_if_any();
        int w, h;
        Color fill;
        input >> w >> h >> fill;
        image = new Image(w, h, fill);
    }
    void Script::save() {
        // Save current image to PNG file.
        string filename;
        input >> filename;
        saveToPNG(filename, image);
    }
void Script::invert() {
    for (int i = 0; i < image->width(); i++) {
        for (int j = 0; j < image->height(); j++) {
            image->at(i, j)=Color(255-image->at(i, j).red(),255-image->at(i, j).green(),255-image->at(i, j).blue());
        }
    }
}
void Script::to_gray_scale(){
for(int i=0;i<image->width();i++){
      for(int j=0;j<image->height();j++){
        rgb_value v =int((image->at(i, j).red()+image->at(i, j).green()+image->at(i, j).blue())/3);
        image->at(i, j)=Color(v,v,v);
      }
    }
  }
    void Script::replace(Color fst ,Color sec){  
        for(int i=0;i<image->width();i++){
            for(int j=0;j<image->height();j++){
                if(image->at(i, j).red()==fst.red() && image->at(i, j).green()==fst.green() && image->at(i, j).blue()==fst.blue()){
                    image->at(i, j)=sec;
                }
            }
        }
    }
        void Script::fill(int x, int y, int w, int h,Color k) {
            for (int i = x; i < x + w; i++) {
                for (int j = y; j < y + h; j++) {
                    image->at(i, j) =k;
                }
            }
        }

    void Script:: rotate_right(){
        int new_width = image->height();
        int new_height = image->width();
        Image* new_img = new Image(new_width, new_height);
        for (int i = 0; i < new_height; i++) {
            for (int j = 0; j < new_width; j++) {
                new_img->at(j, i) = image->at(i,new_width-1-j);
            }
        }
        delete image;
        image = new_img;
    }
    void Script::rotate_left() {
        int new_width = image->height();
        int new_height = image->width();
        Image* new_img = new Image(new_width, new_height);
        for (int i = 0; i < new_height; i++) {
            for (int j = 0; j < new_width; j++) {
                new_img->at(j, i) = image->at(new_height-1-i,j);
            }
        }
        delete image;
        image = new_img;
    }
    void Script::v_mirror(){
    for(int i=0;i<image->width();i++){
      for(int j=0;j<image->height()/2;j++){
          Color pixel=image->at(i,j);
          image->at(i, j) = image->at(i,image->height() - 1 - j);
          image->at(i,image->height() - 1 - j) = pixel;
        }
      }
    }
    void Script::h_mirror(){
    for(int i=0;i<image->height();i++){
      for(int j=0;j<image->width()/2;j++){
          Color pixel=image->at(j,i);
          image->at(j, i) = image->at(image->width() - 1 - j,i);
          image->at(image->width() - 1 - j,i) = pixel;
        }
      }
    }
    void Script::crop(int x,int y,int w,int h){
        Image* new_img = new Image(w, h);
        for (int i = 0; i < w; i++) {
            for (int j = 0; j < h; j++) {
                new_img->at(i, j) = image->at(x+i,y+j);
            }
        }
        delete image;
        image = new_img;
    }
    void Script::add(){
        int x;int y;Color a;string filename;
        input >>filename>> a>> x>> y;
        Image* other_img=loadFromPNG(filename);
        for (int i = 0; i < other_img->width(); i++) {
            for (int j = 0; j < other_img->height(); j++) {
                if(!(other_img->at(i,j).red()==a.red() && other_img->at(i,j).green()==a.green() && other_img->at(i,j).blue()==a.blue())){
                    image->at(i+x,j+y)= other_img->at(i,j);
                }
            }
        }
        delete other_img;
    }
    
    rgb_value median(std::vector<rgb_value> a){
        std::sort(a.begin(), a.end());
        if (a.size() % 2 == 0) {
            return (a[a.size() / 2-1]+a[a.size()/2])/2;
        }
        return a[a.size()/2];
    }

    void Script::median_filter(int ws){ 
        // Largura da borda,ou seja,tamanho que temos que andar para chegar a uma ponta a partir do centro
        ws=ws/2;
        //Criar a nossa nova imagem onde vamos guardar os valores
        Image* new_img = new Image(image->width(), image->height());
        //Percorrer a imagem
        for(int i=0;i<image->width();i++){
            for(int j=0;j<image->height();j++){
                std::vector<rgb_value> red_values;
                std::vector<rgb_value> green_values;
                std::vector<rgb_value> blue_values;
                //Vamos juntar aos vetores os valores à volta
                for(int k=-ws;k<=ws;k++){
                    for(int l=-ws;l<=ws;l++){
                        if(i+k >= 0 && i+k < image->width() && j+l >= 0 && j+l < image->height()){
                            red_values.push_back(image->at(i+k,j+l).red());
                            green_values.push_back(image->at(i+k,j+l).green());
                            blue_values.push_back(image->at(i+k,j+l).blue());
                        }}}
            //Temos agora que fazer a mediana dos vetores e adicionar a cor na nossa nova imagem
                new_img->at(i,j)=Color(median(red_values),median(green_values),median(blue_values));
            }}
            //Converter a nova imagem na nossa imagem atual
                delete image;
                image = new_img;
            }

  
}
