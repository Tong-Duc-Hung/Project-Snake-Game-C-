#pragma once
//các thư viện cần dùng trong chương trình game trừ các thư viện tự lập
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include<iostream>
#include<string>
#include<ctime>
#include<cmath>
#include<cstdlib>
#include<vector>
#include<fstream>
using namespace std;//khai báo không gian tên std
const int SCREEN_WIDTH = 960;//chiều rộng của cửa sổ game
const int SCREEN_HEIGHT = 600;//chiều dài của cửa sổ game
const int SIZEFOOD = 8;//kích thước của mồi
const int SIZESNAKE = 10;//kích thước của rắn 
extern string checknameimage;//dùng để kiểm tra đang ở bức ảnh tên là gì
extern bool checklevelselection;//dùng để kiểm tra có chọn level hay không
extern bool checkinstruction;//dùng để kiểm tra đang ở hướng dẫn của màn hình chính hay là cửa level nào
extern int choice;//kiểm tra lựa chọn in ra màn hình chơi ở level nào
const SDL_Color RED_COLOR = { 255, 0, 0,255 };
const SDL_Color YELLOW_COLOR = { 255, 255, 0,255 };
const SDL_Color LIGHT_SKY_BLUE_COLOR = { 135, 206, 235,235 };
const SDL_Color BLUE_COLOR = { 0,0,255,255 };
const SDL_Color WHITE_COLOR = { 255,255,255,255 };
const SDL_Color PURPLE_COLOR = { 128,0,128,255 };
const SDL_Color ORANGE_COLOR = { 255,165,0,1 };
bool InitializationSDL();//hàm khởi tạo SDL
SDL_Window* createWindow();//hàm khởi tạo cửa sổ game
SDL_Renderer* createRenderer(SDL_Window* window);//hàm khởi tạo renderer
SDL_Surface* LoadImage(SDL_Window* window, const string& imagePath);//hàm khởi tạo surface
SDL_Texture* createTexture(SDL_Renderer* renderer, SDL_Surface* imageGame);//hàm khởi tạo texture
void DrawFilledCircle(SDL_Renderer* renderer, SDL_Texture* texturegame, int x0, int y0, int radius);//hàm vẽ hình tròn
void printTimer(SDL_Renderer* renderer, TTF_Font* font, SDL_Texture* timerTexture, Uint32 startTime, SDL_Color color);//hàm in ra timer
void printScore(SDL_Renderer* renderer, SDL_Texture* scoreTexture, TTF_Font* font, int score, SDL_Color color);//hàm in ra score
void printpaused(SDL_Renderer* rendererpaused, SDL_Texture* texturepaused, TTF_Font* font, SDL_Color colorpaused);//hàm in ra paused
bool check_color(SDL_Color color1, SDL_Color color2);//hàm so sánh hai màu