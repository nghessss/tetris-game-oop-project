# Tetris game

## Introduction

This is our one-week project for the Object-Oriented Programming (OOP) course in our class, based on the famous Tetris game. We used the C language, the SDL2 library, and some object-oriented programming techniques to build the program.

## Requirement
1. Windows 10/11
2. MingW32 installed

## Set up

1. Clone this repository
```
git clone https://github.com/voasd00/tetris-game-oop-project.git
```
2. Download SDL2 library in this [link](https://drive.google.com/file/d/1oJ6m3ef4LZRmI3TnkEb2RPmchnVGuCUb/view?usp=drive_link)

3. Then copy the downloaded library in step 2 into the main folder.

4. Run Makefie to build program, if you didn't install ``make`` before, you can run this command:
```
g++ -Isrc/include -Lsrc/lib -o main code/*.cpp code/menu/*.cpp -lmingw32 -lSDL2_image -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_mixer && start main
```

5. Enjoy the game!

## Authors

- **Nguyen Ngoc Manh Cuong** - [ManhCuong110907](https://github.com/ManhCuong110907)
- **Trieu Gia Huy** - [huyg](https://github.com/huyg1108)
- **Nguyen Quang Minh** - [mJota666](https://github.com/mJota666)
- **Vo Thanh Nghia** - [voasd00](https://github.com/voasd00)
