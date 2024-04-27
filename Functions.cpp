#include"Functions.h"
string checknameimage;
bool checklevelselection = false;//gán giá trị cho checklevelselection
bool checkinstruction = false;//gán giá trị cho checkinstruction
int choice;
bool InitializationSDL()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		SDL_Log("SDL_Init Error %s\n", SDL_GetError());
		return false;
	}
	return true;
}
SDL_Window* createWindow()
{
	SDL_Window* Window = SDL_CreateWindow("Snake Game",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		SDL_WINDOW_SHOWN
	);

	if (Window == nullptr)
	{
		SDL_Log("window could not be created %s\n", SDL_GetError());
		SDL_Quit();
	}
	return Window;
}
SDL_Renderer* createRenderer(SDL_Window* window)
{
	SDL_Renderer* Renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (Renderer == nullptr)
	{
		SDL_Log("renderer could not be created %s\n", SDL_GetError());
		SDL_DestroyWindow(window);
		SDL_Quit();
	}
	return Renderer;
}
SDL_Surface* LoadImage(SDL_Window* window, const std::string& imagePath)
{
	SDL_Surface* loadedSurface = IMG_Load(imagePath.c_str());
	if (loadedSurface == nullptr)
	{
		SDL_Log("loadedSurface Error %s\n", SDL_GetError());
		return nullptr;
	}
	SDL_Surface* optimizedSurface = SDL_ConvertSurfaceFormat(loadedSurface,
		SDL_GetWindowPixelFormat(window),
		0);
	SDL_FreeSurface(loadedSurface);
	return optimizedSurface;
}
SDL_Texture* createTexture(SDL_Renderer* renderer, SDL_Surface* imageGame)
{
	SDL_Texture* Texture = SDL_CreateTextureFromSurface(renderer, imageGame);
	if (Texture == nullptr)
	{
		SDL_Log("SDL_CreateTextureFromSurface Error %s", SDL_GetError());
		SDL_FreeSurface(imageGame);
		SDL_DestroyRenderer(renderer);
		IMG_Quit();
		SDL_Quit();
		return nullptr;
	}
	return Texture;
}
void DrawFilledCircle(SDL_Renderer* renderer, SDL_Texture* texturegame, int x0, int y0, int radius) {
	int x = radius;
	int y = 0;
	int err = 0;
	while (x >= y) {
		for (int i = y0 - y; i <= y0 + y; i++) {
			SDL_RenderDrawPoint(renderer, x0 + x, i);
			SDL_RenderDrawPoint(renderer, x0 - x, i);
		}
		for (int i = y0 - x; i <= y0 + x; i++) {
			SDL_RenderDrawPoint(renderer, x0 + y, i);
			SDL_RenderDrawPoint(renderer, x0 - y, i);
		}
		if (err <= 0) {
			y += 1;
			err += 2 * y + 1;
		}
		if (err > 0) {
			x -= 1;
			err -= 2 * x + 1;
		}
	}
}
void printTimer(SDL_Renderer* renderer, TTF_Font* font, SDL_Texture* timerTexture, Uint32 startTime, SDL_Color color) {
	// Kiểm tra và giải phóng texture cũ
	if (timerTexture != nullptr) {
		SDL_DestroyTexture(timerTexture);
	}
	// Tính thời gian đã trôi qua từ startTime đến hiện tại
	Uint32 currentTime = SDL_GetTicks();
	Uint32 elapsedTime = (currentTime - startTime) / 1000; // chuyển đơn vị thành giây
	// Tạo chuỗi timerText để hiển thị thời gian
	string timerText = "Time: " + to_string(elapsedTime) + " seconds";
	// Tạo một surface từ chuỗi timerText
	SDL_Surface* surface = TTF_RenderText_Solid(font, timerText.c_str(), color);
	// Tạo một texture từ surface
	timerTexture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_Rect dsttimer{};
	dsttimer.x = 110;
	dsttimer.y = 570;
	dsttimer.w = 0;
	dsttimer.h = 0;
	//truy vấn các thuộc tính của textture
	SDL_QueryTexture(timerTexture, nullptr, nullptr, &dsttimer.w, &dsttimer.h);
	// Vẽ texture lên cửa sổ game
	SDL_RenderCopy(renderer, timerTexture, nullptr, &dsttimer);
	// Giải phóng surface
	SDL_FreeSurface(surface);
}
void printScore(SDL_Renderer* renderer, SDL_Texture* scoreTexture, TTF_Font* font, int score, SDL_Color color) {
	// Kiểm tra và giải phóng texture cũ
	if (scoreTexture != nullptr) {
		SDL_DestroyTexture(scoreTexture); // free the old texture
	}
	// Tạo chuỗi scoreText để hiển thị điểm số
	string scoreText = "Score: " + to_string(score);
	// Tạo một surface từ chuỗi scoreText
	SDL_Surface* surface = TTF_RenderText_Solid(font, scoreText.c_str(), color);
	// Tạo một texture từ surface
	scoreTexture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_Rect dstscore{};
	dstscore.x = 574;
	dstscore.y = 570;
	dstscore.w = 0;
	dstscore.h = 0;
	//truy vấn các thuộc tính của texture
	SDL_QueryTexture(scoreTexture, nullptr, nullptr, &dstscore.w, &dstscore.h);
	// Vẽ texture lên cửa sổ game
	SDL_RenderCopy(renderer, scoreTexture, nullptr, &dstscore);
	// Giải phóng surface
	SDL_FreeSurface(surface);
}
void printpaused(SDL_Renderer* rendererpaused, SDL_Texture* texturepaused, TTF_Font* font, SDL_Color colorpaused) {
	// Kiểm tra và giải phóng texture cũ
	if (texturepaused == nullptr)
	{
		SDL_DestroyTexture(texturepaused);
	}
	// Tạo chuỗi scoreText để hiển thị điểm số
	SDL_Surface* surfacepaused = TTF_RenderText_Solid(font, "PAUSED IS 0", colorpaused);
	// Tạo một texture từ surface
	texturepaused = SDL_CreateTextureFromSurface(rendererpaused, surfacepaused);
	// Lấy kích thước của texture
	SDL_Rect dstpaused{};
	dstpaused.x = 750;
	dstpaused.y = 570;
	dstpaused.w = 0;
	dstpaused.h = 0;
	SDL_QueryTexture(texturepaused, nullptr, nullptr, &dstpaused.w, &dstpaused.h);
	SDL_RenderCopy(rendererpaused, texturepaused, nullptr, &dstpaused);// Vẽ texture lên cửa sổ game
	// Giải phóng surface
	SDL_FreeSurface(surfacepaused);
}
bool check_color(SDL_Color color1, SDL_Color color2)
{
	//so sánh các thuộc tính của 2 màu
	if (color1.r == color2.r && color1.g == color2.g && color1.b == color2.b && color1.a == color2.a)
	{
		return true;
	}
	return false;
}
