#include "Food.h"
Food::Food() {
    x = rand() % 937 + 12;//khởi tạo x của food
    y = rand() % 545 + 8;//khởi tạo y của food
    SetRandomColor();//lấy màu ngẫu nhiên của food
}
void Food::DrawFood(SDL_Renderer* RendererFood, SDL_Texture* foodTexture)
{
    SDL_SetRenderDrawColor(RendererFood, Color_Food.r, Color_Food.g, Color_Food.b, Color_Food.a);//tô màu cho food
    DrawFilledCircle(RendererFood, foodTexture, x, y, SIZEFOOD);//vẽ food
}
void Food::SetRandomColor()//xét màu ngẫu nhiên cho food
{
    if (checknameimage == "easy level play screen.png")
    {
        Colors_Food = { WHITE_COLOR, PURPLE_COLOR,ORANGE_COLOR,YELLOW_COLOR };//danh sách các màu của level easy
        Color_Food = Colors_Food[rand() % Colors_Food.size()];//chọn màu ngẫu nhiên
    }
    else if (checknameimage == "medium level play screen.png")
    {
        Colors_Food = { WHITE_COLOR, PURPLE_COLOR,ORANGE_COLOR,RED_COLOR };//danh sách các màu của level medium
        Color_Food = Colors_Food[rand() % Colors_Food.size()];//chọn màu ngẫu nhiên
    }
    else if (checknameimage == "hard level play screen.png")
    {
        Colors_Food = { WHITE_COLOR, PURPLE_COLOR,ORANGE_COLOR,LIGHT_SKY_BLUE_COLOR };//danh sách các màu của level hard
        Color_Food = Colors_Food[rand() % Colors_Food.size()];//chọn màu ngẫu nhiên
    }
    else {
        Colors_Food = { WHITE_COLOR, PURPLE_COLOR,ORANGE_COLOR,BLUE_COLOR };//danh sách các màu của level hardest
        Color_Food = Colors_Food[rand() % Colors_Food.size()];//chọn màu ngẫu nhiên
    }
}
