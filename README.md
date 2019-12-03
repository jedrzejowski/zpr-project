# ZprCraft - projekt na przedmiot ZPR

Gra jest wynikiem projektu na przedmiot ZPR

## Podgląd gry

![](res/preview1.png)
![](res/preview2.png)

## Budowanie

### Biblioteki

Do kompilacji potrzebne są następujące programy/biblioteki: cmake, boost, OpenGL, GLM, GLEW, glfw3 i git.
Każda dystrybucja Linuxa zawiera te biblioteki i najczęściej są one już w systemie po instalacji systemu

Poniżej przedstawiono kilka przykładowe komendy do instalacji na wybranych systemach operacyjnych:

| System | Komenda |
| ------ | ------- |
| Ubuntu | `# apt-get install git cmake libboost-filesystem-dev libglm-dev libglew-dev libglfw3-dev g++` |
| ArchLinux | `# pacman -S git cmake glew glm boost glfw-x11 g++` |

### Kompilacja

Poniżej przedstawiono skrypt do kompilacji na systemie Linux

```
cd /tmp # tu można zmienić wedle upodobania

git clone https://github.com/jedrzejowski/zpr-project --branch szkielet_aplikacji zpr-craft-jedrzejowski-kretkowski
cd zpr-craft-jedrzejowski-kretkowski

mkdir bin
cmake -S . -B bin

cd bin
make

cd test
ctest

cd ..
./src/zpr_app

```


## Autorzy

Adam Jędrzejowski <[adam@jedrzejowski.pl](mailto:adam@jedrzejowski.pl)>

Marcin Kretkowski
