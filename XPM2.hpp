#ifndef __prog_XPM2_hpp__
#define __prog_XPM2_hpp__

#include <string>
#include "Image.hpp"

namespace prog {
    // Função para carregar uma imagem no formato XPM2 a partir de um arquivo
    Image* loadFromXPM2(const std::string &file);
    
    // Função para salvar uma imagem no formato XPM2 em um arquivo
    void saveToXPM2(const std::string& file, const Image* img);
}
#endif
