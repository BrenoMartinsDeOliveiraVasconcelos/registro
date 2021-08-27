import os
import subprocess
import time

filepath = os.path.dirname(os.path.realpath(__file__))
home = os.path.expanduser("~")


def main():
    print("Preparando para instalar...")
    time.sleep(1)
    while True:
        try:
            subprocess.run(["g++", "--version"], check=True, stdout=subprocess.PIPE)
            print("g++ já está instalado. Compilando...")
            try:
                subprocess.run([f"g++", f"{filepath}/main.cpp", "-o", f"{filepath}/bin/reg"], check=True)
                time.sleep(2)
                print("Compilado com sucesso.")
                print("Ultimas configurações...")
                os.mkdir(f"{home}/.reg")
                open(f"{home}/.reg/registro", "w+").closwe()
                time.sleep(1.5)
                
            except subprocess.CalledProcessError:
                print("Erro ao compilar.")
            except FileExistsError:
                print("Diretório já existe.")
            executar = input("Ok. Deseja executar agora?")
            if executar.lower() in ["sim", "s", "y", "yes"]:
                subprocess.run([f"{filepath}/bin/reg"], check=True)
            break
        except subprocess.CalledProcessError:
            conf = input("g++ não está instalado, deseja instalar? ")
            if conf.lower() in ["s", "y", "yes", "sim"]:
                try:
                    subprocess.run(["sudo apt install g++"], shell=True, check=True)
                    print("g++ instalado, continuando...")
                except subprocess.CalledProcessError:
                    print("Não foi possível instalar g++, verifique o gerenciador de pacotes para sua distro.")
                    exit(1)
            else:
                print("Okay. O arquivo main.cpp precisa ser compilado manualmente.")
                exit(0)
    print("Obrigado por instalar :D")


if __name__ == '__main__':
    main()
