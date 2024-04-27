#include"Functions.h"
#include"Game.h"
using namespace std;
int main(int argc, char* argv[])
{
	srand(time(0));//khởi tạo bộ sinh số ngẫu nhiên 
	if (!InitializationSDL())//kiểm tra khởi tạo SDL
	{
		return -1;
	}
	SDL_Window* window = createWindow();//khởi tạo cửa sổ game
	if (window == nullptr)//kiểm tra khởi tạo cửa sổ game
	{
		SDL_Quit();
		return -1;
	}
	SDL_Renderer* RendrerGame = createRenderer(window);//khởi tạo renderer
	if (RendrerGame == nullptr)//kiểm tra khởi tạo renderer
	{
		SDL_DestroyWindow(window);
		SDL_Quit();
		return -1;
	}
	TTF_Init();//khởi tạo TTF
	TTF_Font* font = TTF_OpenFont("SSWB.ttf", 26);//tạo font
	SDL_Color color_ttf = { 255,255,255 };//khởi tạo và khai báo màu ban đầu cho color_ttf
	SDL_Color colorPaused = { 0,255,0,255 };//khởi tạo và khai báo màu bạn đầu cho colorpaused
	Uint32 startTime = SDL_GetTicks() / 1000;//khởi tạo biến thời gian ban đầu đơn vị là giây
	int score_texture = 0;//khởi tạo điểm khi in lên màn hình chơi game
	SDL_Texture* timerTexture = nullptr;//khởi tạo texture cho hàm in timer
	SDL_Texture* scoreTexture = nullptr;//khởi tạo texture cho hàm in score
	SDL_Texture* paused = nullptr;//khởi tạo texture cho hàm in paused
	IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);//khởi tạo hỗ trợ cho các định dạng ảnh
	SDL_Surface* imageGame = LoadImage(window, "interface image.png");//khởi tạo surface lưu ảnh
	checknameimage = "interface image.png";//gán giá trị cho checknameimage
	SDL_Texture* texturegame = SDL_CreateTextureFromSurface(RendrerGame, imageGame);//khởi tạo texturegame
	bool isRunning = true;//kiểm tra trạng thái vòng lặp game
	SDL_Event event;//khởi tạo sự kiện
	Game game;//khởi tạo game trong class Game
	while (isRunning)//bắt đầu chạy game
	{
		while (SDL_PollEvent(&event))//dùng để lấy sự kiện game
		{
			game.display(window, imageGame, RendrerGame, texturegame, event);//in giao diện trước khi vào màn hình chơi và bắt đầu chơi game
		}
		SDL_RenderClear(RendrerGame);//xóa toàn bộ nội dung hiện tại của bộ đệm đồ họa
		SDL_RenderCopy(RendrerGame, texturegame, nullptr, nullptr);//sao chép 1 phần của 1 texture
		if (checknameimage == "easy level play screen.png" || checknameimage == "medium level play screen.png" || checknameimage == "hard level play screen.png" || checknameimage == "hardest level play screen.png")//nếu là màn hình chơi
		{
			//các hoạt động khi đang ở màn hinh chơi
			if (checknameimage == "easy level play screen.png")
			{
				color_ttf = YELLOW_COLOR;//gán màu của ttf là màu vàng
			}
			else if (checknameimage == "medium level play screen.png")
			{
				color_ttf = RED_COLOR;//gán màu của ttf là màu đỏ
			}
			else if (checknameimage == "hard level play screen.png") {
				color_ttf = LIGHT_SKY_BLUE_COLOR;//gán màu của ttf là màu xanh nhạt
			}
			else {
				color_ttf = BLUE_COLOR;//gán màu của ttf là màu xanh đậm
			}
			printTimer(RendrerGame, font, timerTexture, startTime, color_ttf);//in timer
			printScore(RendrerGame, scoreTexture, font, score_texture, color_ttf);//in score
			printpaused(RendrerGame, paused, font, colorPaused);//in chữ "PAUSED IS 0"
			game.run(RendrerGame, texturegame);
			if (checknameimage == "easy level play screen.png")
			{
				SDL_Delay(40);//trì hoãn 40 mili giây
			}
			else if (checknameimage == "medium level play screen.png")
			{
				SDL_Delay(30);//trì hoãn 30 mili giây
			}
			else if (checknameimage == "hard level play screen.png")
			{
				SDL_Delay(25);//trì hoãn 25 mili giây
			}
			else {
				SDL_Delay(18);//trì hoãn 18 mili giây
			}

		}
		SDL_RenderPresent(RendrerGame);//cập nhật màn hình
		score_texture = game.score;//lấy điểm in lên màn hình chơi
		isRunning = game.GameStatus;//gán trạng thái của game để dừng
	}
	SDL_DestroyWindow(window);//hủy window
	SDL_FreeSurface(imageGame);//giải phóng surface
	SDL_DestroyTexture(texturegame);//hủy texturegame
	SDL_DestroyRenderer(RendrerGame);//hủy rendrergame
	SDL_DestroyTexture(timerTexture);//hủy timertexture
	SDL_DestroyTexture(scoreTexture);//hủy scoretexture
	SDL_DestroyTexture(paused);//hủy texture paused
	TTF_CloseFont(font);//xóa font
	TTF_Quit();//đóng TTF
	SDL_Quit();//đóng SDL
	return 0;
}
