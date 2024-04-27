#pragma once
#include "Snake.h"
#include "Food.h"
#include"Functions.h"
class Game
{
public:
    Snake snake;//khai báo snake trong class game
    Food food;//khai báo food trong class game
    bool GameStatus;//dùng để kiểm tra trạng thái của game
    int score;//dùng để lấy điểm trong suốt quá trình chơi game
public:
    Game();//hàm khởi tạo game
    void grow();//hàm dùng để rắn dài ra
    void run(SDL_Renderer* RendererGame, SDL_Texture* texturegame);//hàm chạy của game
    void Draw(SDL_Renderer* RendererGame, SDL_Texture* texturegame);//hàm vẽ rắn và mồi
    bool eat();//hàm kiểm tra rắn có ăn mồi không
    bool collisioncheck();//hàm kiểm tra rắn có va chạm tường không
    bool snakecheck();//hàm kiểm tra rắn có cắn mình không
    void createFood(SDL_Renderer* RendererGame, SDL_Texture* texturegame);//hàm tạo thức ăn
    //hàm in giao diện trước khi vào màn hình chơi và bắt đầu chơi game
    void display(SDL_Window*& window, SDL_Surface*& imageGame, SDL_Renderer*& RendrerGame, SDL_Texture*& texturegame, SDL_Event& event);
};
