#pragma once
#include"Functions.h"
enum  Direction { STOP = 0, LEFT, RIGHT, UP, DOWN };//tập hợp các kí hiệu của hướng đi của rắn và stop
class Snake
{
public:
    vector<SDL_Rect> body; // Vector chứa các phần của rắn
    Direction direction; // Hướng di chuyển cửa 
    SDL_Color SnakeColor;//màu của rắn
    bool isPaused;//kiểm tra người chơi có dùng stop hay không
public:
    Snake();///khởi tạo rắn 
    void drawsnake(SDL_Renderer* RendererSnake, SDL_Texture* snakeTexture);//hàm vẽ rắn
    void move(); //hàm dùng để di chuyển rắn
    void setDirection(Direction dir);//hàm lấy hướng đi của rắn
};
