#include "Snake.h"
Snake::Snake()
{
    direction = RIGHT;//khởi tạo hướng đi ban đầu của rắn
    body.push_back({ 44,10 });//tọa độ của đầu
    //tọa độ của các phần thân rắn
    body.push_back({ 24,5 });
    body.push_back({ 14,5 });
    body.push_back({ 4,5 });
    SnakeColor = { 255,0,0,255 };
    isPaused = false;//khởi tạo isPaused=false
}
void Snake::drawsnake(SDL_Renderer* RendererSnake, SDL_Texture* snakeTexture)
{
    if (checknameimage == "easy level play screen.png")
    {
        SnakeColor = YELLOW_COLOR;//gán màu của rắn thành màu vàng
    }
    else if (checknameimage == "medium level play screen.png")
    {
        SnakeColor = RED_COLOR;//gán màu của rắn thành màu đỏ
    }
    else if (checknameimage == "hard level play screen.png") {
        SnakeColor = LIGHT_SKY_BLUE_COLOR;//gán màu của rắn thành mày xanh nhạt
    }
    else {
        SnakeColor = BLUE_COLOR;//gán màu của rắn thành màu xanh đậm
    }
    //vẽ rắn
    for (long long j = (long long)body.size() - 1; j >= 0; j--)
    {
        SDL_SetRenderDrawColor(RendererSnake, SnakeColor.r, SnakeColor.g, SnakeColor.b, SnakeColor.a); // tô màu cho rắn
        if (j == 0)
        {
            DrawFilledCircle(RendererSnake, snakeTexture, body[0].x, body[0].y, SIZESNAKE);//vẽ đầu
        }
        //vẽ thân
        else {
            SDL_Rect rectdraw{};
            rectdraw.x = body[j].x;
            rectdraw.y = body[j].y;
            rectdraw.w = SIZESNAKE;
            rectdraw.h = SIZESNAKE;
            SDL_RenderFillRect(RendererSnake, &rectdraw);
        }
    }
}
void Snake::move()
{
    if (!isPaused)
    {
        //gán tạo độ của phần đằng sau bằng đoạn trước nó
        for (int i = (int)body.size() - 1; i > 0; i--)
        {
            body[i] = body[i - 1];
        }
        switch (direction)
        {
        case RIGHT://phải
        {
            body[0].x += SIZESNAKE;

            break;
        }
        case LEFT://trái
        {
            body[0].x -= SIZESNAKE;
            break;
        }
        case DOWN://xuống
        {
            body[0].y += SIZESNAKE;
            break;
        }
        case UP://lên
        {
            body[0].y -= SIZESNAKE;
            break;
        }
        default://nếu không phải các hướng di chuyển trên
        {
            break;
        }
        }
    }
}
void Snake::setDirection(Direction dir)
{
    if (isPaused && (dir == RIGHT || dir == LEFT || dir == UP || dir == DOWN))
    {
        isPaused = false; // Tiếp tục trò chơi nếu người chơi nhấn một trong các phím điều hướng
    }
    else if (!isPaused) // Chỉ thay đổi hướng nếu trò chơi không tạm dừng
    {
        switch (dir)//kiểm tra giá trị của biến dir
        {
        case RIGHT://phải
            //kiểm tra xem rắn có đang đi sang trái hay rắn chỉ có 1 đốt không
            if (direction != LEFT || body.size() == 1)
            {
                direction = dir;//di chuyển sang phải
            }
            break;
        case LEFT://trái
            //kiểm tra xem rắn có đang đi sang phải hay rắn chỉ có 1 đốt không
            if (direction != RIGHT || body.size() == 1)
            {
                direction = dir;//di chuyển sang trái
            }
            break;
        case DOWN://xuống
            //kiểm tra xem rắn có đang đi lên hay rắn chỉ có 1 đốt không
            if (direction != UP || body.size() == 1)
            {
                direction = dir;//di chuyển xuống
            }
            break;
        case UP://lên
            //kiểm tra xem rắn có đang đi xuống hay rắn chỉ có 1 đốt không
            if (direction != DOWN || body.size() == 1)
            {
                direction = dir;//di chuyển lên
            }
            break;
        case STOP://dừng lại
            isPaused = true; // Tạm dừng trò chơi
            break;
        default://nếu dir không phải một trong các giá trị trên
            break;
        }
    }
}
