#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <exception>
#include <sstream>
#include "lib/funcs.h"

int main(){
    char *userName = getenv("LOGNAME");

    std::stringstream converter;
    std::string usuario;

    std::string files;

    converter << userName;
    converter >> usuario;

    if (userName != "root"){
        files = "/home/"+usuario+"/.reg";
    }else{
        files = "/root/.reg";
    }

    std::string opt;
    std::string nome; 
    std::string estado;
    std::string idade;
    std::string genero;

    std::string valor;
    std::string nvalor;
    
    std::string consentimento;

    while (true){
        std::system("clear");
        try{                
        std::cout << "          == REGISTRO ==          " << "\n\n";
        std::cout << "          1 - Adicionar" << "\n"
                    << "          2 - Remover" << "\n"
                    << "          3 - Listar" << "\n"
                    << "          4 - Modificar" << "\n"
                    << "          5 - Limpar registro" << "\n"
                    << "          6 - Sair" << "\n\n"
                    << "          Escolha [1-5] => ";

        std::cin >> opt;

        }catch(std::exception &e){
            std::cout << "\033[31;1mErro: " << e.what() << "\n\033[0m";    
        }
        if (opt == "1"){
            std::cout << "          Nome: "; std::getline(std::cin >> std::ws, nome);//std::cin >> nome; 
            std::cout << "          Estado: "; std::getline(std::cin >> std::ws, estado);
            std::cout << "          Idade: "; std::getline(std::cin >> std::ws, idade);
            std::cout << "          Genero: "; std::getline(std::cin >> std::ws, genero);

            adicionar(nome, estado, files, idade, genero);
        }else if(opt == "2"){
            std::cout << "          Nome: "; std::getline(std::cin >> std::ws, nome);
            remover(nome, files);
        }else if(opt == "3"){
            listar(files);
        }else if(opt == "4"){
            std::cout << "          Nome: "; std::getline(std::cin >> std::ws, nome);
            std::cout << "          Codigo do valor a modificar (apartir de 0): "; std::getline(std::cin >> std::ws, valor);
            std::cout << "          Novo valor: "; std::getline(std::cin >> std::ws, nvalor);
            modificar(files, nome, valor, nvalor);
        }else if(opt == "5"){
            std::cout << "\033[31;1mTens certeza disto? [Digite SIM para confirmar]\033[0m";
            std::cin >> consentimento;

            if (consentimento == "SIM"){
                limpar(files);
            }

        }else if(opt == "6"){
            exit(0);
        }
    }

    return 0;
}
