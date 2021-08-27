#ifndef ARQUIVO_H_INCLUDED
#define ARQUIVO_H_INCLUDED
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <filesystem>
#include <string>

std::fstream registro;

void adicionar(std::string nome, std::string estado, std::string files, std::string idade,
                std::string genero){
    std::fstream arquivo;

    arquivo.open(files+"/registro", std::fstream::app);
    arquivo << nome << ":" << estado << ":" << idade 
            << ":" << genero << ":" << "\n";
    arquivo.close();
    
    return;
}

void remover(std::string nome, std::string files){
    std::string linha;
    std::vector<std::string> linhas;
    registro.open(files+"/registro", std::fstream::in);
    std::string s;
    std::string token;
    
    while (std::getline(registro, linha)){
        linhas.push_back(linha);
    }

    registro.close(); registro.open(files+"/registro", std::fstream::out);

    for (int i = 0; i<linhas.size(); i++){
        token = linhas[i].substr(0, linhas[i].find(":"));
        if (token == nome){
            linhas[i] = "";
        }
    }
    
    for (const auto &piece : linhas){
        if (piece != ""){
            s += piece+"\n";
        }
    }
    registro << s;
    registro.close();
}

void listar(std::string files){
    std::vector<std::string> linha;
    std::string l;
    std::string token;
    std::string del = ":";
    std::string input;
    size_t pos = 0;

    registro.open(files+"/registro", std::fstream::in);

    std::cout << "Nome       Estado      Idade       Genero" << "\n"
                << "-----------------------------------------";

    while (std::getline(registro, l)){
        std::cout << "\n";
        while ((pos = l.find(del)) != std::string::npos){
            token = l.substr(0, l.find(del));
            linha.push_back(token);
            l.erase(0, l.find(del) + del.length());
        }
        for (int i=0; i<linha.size(); i++){
            std::cout << linha[i] << "      ";
        }
        linha.clear();
    }

    registro.close();
    std::cin >> input;

}

void modificar(std::string files, std::string nome, std::string val, std::string nval){
    std::vector<std::string> linha;
    std::vector<std::string> linhas;
    std::string l;
    std::string token;
    std::string del = ":";
    size_t pos = 0;
    std::string input;
    std::stringstream valor;
    int numvalor;
    std::string formlinha;
    std::string textofin;
    int contador = -1;

    valor << val;
    valor >> numvalor;

    registro.open(files+"/registro", std::fstream::in);

    while (std::getline(registro, l)){
        contador++;
        linhas.push_back(l);
         while ((pos = l.find(del)) != std::string::npos){
            token = l.substr(0, l.find(del));
            linha.push_back(token);
            l.erase(0, l.find(del) + del.length());
        }
        if(numvalor < linha.size() && numvalor > -1){
            if(nome == linha[0]){
                linha[numvalor] = nval;
                for (auto it:linha){
                    formlinha += it + ":";
                }
                linhas[contador] = formlinha;
                break;
            }else{
                linha.clear();
            }
        }
    }
    
    registro.close(); registro.open(files+"/registro", std::fstream::out);
    for (auto it:linhas){
        textofin += it + "\n";
    }

    registro << textofin; registro.close();
}

void limpar(std::string files){
    registro.open(files+"/registro", std::fstream::out);
    registro << "";
    registro.close();
}

#endif