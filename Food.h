#pragma once
#include"Functions.h"
class Food
{
public:
    int x;//tọa độ x của food
    int y;//tọa độ y của food
    SDL_Color Color_Food;
    vector<SDL_Color> Colors_Food;//vector chứa các màu sắc của thức ăn
public:
    Food();//hàm khởi tạo thức ăn
    void DrawFood(SDL_Renderer* rendererFood, SDL_Texture* foodTexture);//hàm vẽ thức ăn
    void SetRandomColor();//hàm dùng để lấy ngẫu nhiên màu của thức ăn
};
