#include "XPM2.hpp"
#include <fstream>
#include <string>
#include <sstream>
namespace prog {
    //Esta função converte uma char no seu valor em int, incluindo as letras de A a F (que são valores hexadecimais)
    int calculo(char s){
        if(isdigit(s)){
            return s-'0';
        }
        if(s>='A' && s<='Z'){
            return s-'A'+10;
        }
        return s-'a'+10;
    }
    //Esta função converte uma string do tipo #000000 ou #00000 em uma cor 
    Color transforme(std::string k){
        rgb_value red=calculo(k[1])*16+calculo(k[2]);
        rgb_value green=calculo(k[3])*16+calculo(k[4]);
        rgb_value blue;
        //para o caso #00000
        if(k.size()<7){
             blue=calculo(k[5])*16;
        }else{
             blue=calculo(k[5])*16+calculo(k[6]);
        }
        return Color(red,green,blue);
    }
    //Tendo em conta a key que recebemos, esta função retorna a cor que lhe está associada
    Color help( std::vector<char> key, std::vector<Color> value,char c){
        std::string v;
        for(int i=0;i<int(key.size());i++){
            if(key[i]==c){
                return value[i];
            }
        }
        return Color(0,0,0);
    }
    Image* loadFromXPM2(const std::string& file) {
        std::ifstream in(file);
        std::string l;
        //vetor para guardar as chaves das cores
        std::vector<char> key;
        //vetor para guardar os valores das cores
        std::vector<Color> value;
        //apesar de usarmos vetores diferentes, uma key vai estar associada ao seu valor através do mesmo index
        Image* new_img;
        int xdimension ; int ydimension ; int n_of_colours=0; int n_char_perblock;
        for (int i=0;getline(in, l); i++) {
            //esta condição verifica se já passamos a parte de leitura das cores, e se estamos prontos para adicionar os valores à nossa imagem
            if(i>=2+n_of_colours){
                for(int j=0;j<xdimension;j++){
                    new_img->at(j,i-2-n_of_colours)=help(key,value,l[j]); 
                }
            }
            //esta condição verifica se estamos na 2º linha, de modo a ler os valores referentes à imagem
            else if(i==1){
                std::istringstream n(l);
                n>>xdimension>>ydimension>>n_of_colours>>n_char_perblock;
                new_img = new Image(xdimension,ydimension);
            }
            //esta condição verifica se estamos na fase de leitura de cores
            else if (i>1){
                std::istringstream n(l);
                char key_v;
                char c;
                std::string values;
                n>>key_v>>c>>values;
                key.push_back(key_v);
                //ver o significado da função transforme acima
                value.push_back(transforme(values));
            }}
            
            return new_img;
        }

    //Verificar se uma cor já se encontra no nosso vetor de cores
    bool in(std::vector<Color> values, Color value){
        for(Color k:values){
            //Caso a cor já seja uma das que temos guardadas
            if(k.blue()==value.blue() && k.red()==value.red() && k.green()==value.green()){
                return true;
            }
        }
        return false;
    }
    // auxilia a função de baixo 
    std::string intToHex(int decimalNumber) {
        std::stringstream stream;
        stream << std::hex << decimalNumber;
        std::string result(stream.str());
        if(result.size()<2){
            result+="0";
        }
        return result;
    }
    // Esta função transforma uma cor no formato #000000
    std::string to_hex(Color c){
        std::string s="#";
        s+=intToHex(int(c.red()));
        s+=intToHex(int(c.green()));
        s+=intToHex(int(c.blue()));
        return s;
    } 
    //tendo em conta a cor que passamos, retornamos a key/símbolo que lhe está associada
    char to_key(std::vector<char> a ,std::vector<Color> values, Color value){
        for(int i=0;i<int(values.size());i++){
            if(values[i].blue()==value.blue() && values[i].red()==value.red() && values[i].green()==value.green()){
                return a[i];
            }
        }
        return '0';
    }
    //Esta função serve apenas para criar símbolos aleatórios que funcionam como keys das cores
    char trans(int i){
        return '*'+i;
    }
    void saveToXPM2(const std::string& file, const Image* image) {
        std::ofstream out(file);
        //vetor para guardar as chaves das cores
        std::vector<char> key;
        //vetor para guardar os valores das cores
        std::vector<Color> values;
        //onde vamos guardar a parte que descreve a imagem através dos símbolos
        std::vector<std::string> linhas;
        //Este valor vai ser usado apenas para a função trans
        int p=0;
        //Fazemos um loop pelos pixeis da imagem
        for(int i=0;i<image->height();i++){
            std::string linha;
            for(int j=0;j<image->width();j++){
               //Se a cor que encontramos ainda não estiver guardada nas nossas keys-values
               if(!in(values,image->at(j,i))) {
                    //neste caso como ainda não está, adicionamos a cor aos values e criamos a sua key
                    values.push_back(image->at(j,i));
                    key.push_back(trans(p));
                    p++;
               }
               linha+=to_key(key,values,image->at(j,i));
            }
            linhas.push_back(linha); 
        }
        int n_of_colours=int(key.size());
        // Começamos a escrever no ficheiro
        // 1ºlinha
        out<<"! XPM 2"<<std::endl;
        // 2ºlinha
        out<<image->width()<<" "<<image->height()<<" "<<n_of_colours<<" "<<1<<std::endl;
        // Loop para adicionar as várias keys com a sua cor(no formato hexadecimal)
        for(int i=0;i<n_of_colours;i++){
            out<<key[i]<<" c "<<to_hex(values[i])<<std::endl;
        }
        // Adicionar os símbolos que foram recolhidos no loop principal
        for(std::string s:linhas){
            out<<s<<std::endl;
        }
    }
}
