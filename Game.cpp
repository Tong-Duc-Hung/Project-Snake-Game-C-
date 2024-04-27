#include "Game.h"
Game::Game()
{
	snake = Snake();//khởi tạo snake
	food = Food();//khởi tạo food
	GameStatus = true;//gán GameStatus=true
	score = 0;//gán score =0
}
void Game::run(SDL_Renderer* RendererGame, SDL_Texture* texturegame)
{
	const Uint8* state = SDL_GetKeyboardState(nullptr);//trả về 1 mảng chứa trạng thái của tất cả các phím
	//kiểm tra phím UP có được nhấn không
	if (state[SDL_SCANCODE_UP]) {
		snake.setDirection(UP);
	}
	//kiểm tra phím DOWN có được nhấn không
	else if (state[SDL_SCANCODE_DOWN]) {
		snake.setDirection(DOWN);
	}
	//kiểm tra phím LEFT có được nhấn không
	else if (state[SDL_SCANCODE_LEFT]) {
		snake.setDirection(LEFT);
	}
	//kiểm tra phím RIGHT có được nhấn không
	else if (state[SDL_SCANCODE_RIGHT]) {
		snake.setDirection(RIGHT);
	}
	//kiểm tra phím 0 có được nhấn không
	else if (state[SDL_SCANCODE_0])
	{
		snake.setDirection(STOP);
	}
	snake.move(); // Di chuyển rắn trước khi vẽ
	if (eat())//nếu hàm ăn trả về true
	{
		if (check_color(food.Color_Food, snake.SnakeColor))//nếu ăn mồi cùng màu với rắn
		{
			grow();
			score++;
		}
		else if (check_color(food.Color_Food, ORANGE_COLOR))//nếu ăn mồi màu cam
		{
			for (int i = 0; i < 2; i++)
			{
				grow();
			}
			score += 2;
		}
		else if (check_color(food.Color_Food, PURPLE_COLOR))//nếu ăn mồi màu tím
		{
			for (int i = 0; i < 3; i++)
			{
				grow();
			}
			score += 3;
		}
		//nếu ăn mồi màu trắng
		else {
			for (int i = 0; i < 4; i++)
			{
				grow();
			}
			score += 4;
		}
		food.SetRandomColor();//lấy màu cho thức ăn
		createFood(RendererGame, texturegame);//tọa thức ăn
	}
	if (collisioncheck() == false || snakecheck() == false)//nếu rắn chạm tường hoặc cắn vào thân
	{
		if (checknameimage == "easy level play screen.png")
		{
			if (score >= 20)//nếu thõa màn điều kiện thắng của level easy
			{
				cout << "YOU WIN" << endl;
			}
			else {
				cout << "YOU LOSE" << endl;
			}
		}
		else if (checknameimage == "medium level play screen.png")
		{
			if (score >= 50)//nếu thõa màn điều kiện thắng của level medium
			{
				cout << "YOU WIN" << endl;
			}
			else {
				cout << "YOU LOSE" << endl;
			}
		}
		else if (checknameimage == "hard level play screen.png")
		{
			if (score >= 80)//nếu thõa màn điều kiện thắng của level hard
			{
				cout << "YOU WIN" << endl;
			}
			else {
				cout << "YOU LOSE" << endl;
			}
		}
		else if (checknameimage == "hardest level play screen.png") {
			if (score >= 100)//nếu thõa màn điều kiện thắng của level hardest
			{
				cout << "YOU WIN" << endl;
			}
			else {
				cout << "YOU LOSE" << endl;
			}
		}
		GameStatus = false;//cập nhật trạng thái game
	}
	Draw(RendererGame, texturegame); // Vẽ sau khi rắn đã di chuyển
}
void Game::grow() {
	SDL_Rect tail = snake.body.back();
	snake.body.push_back(tail);
}
void Game::Draw(SDL_Renderer* RendererGame, SDL_Texture* texturegame) {
	// Vẽ rắn và thức ăn lên màn hình
	food.DrawFood(RendererGame, texturegame);
	snake.drawsnake(RendererGame, texturegame);
}
bool Game::eat()
{
	//nếu khoảng cách của rắn và mồi nhỏ hơn khoảng cách của SIZEFOOOD+SIZESNAKE
	if (sqrt(pow((snake.body[0].x - food.x), 2) + pow((snake.body[0].y - food.y), 2)) < 18)
	{
		return true;
	}
	return false;
}
bool Game::collisioncheck()
{
	//nếu đầu rắn chạm vào tọa độ của tường
	if ((snake.body[0].x<14 || snake.body[0].x>SCREEN_WIDTH - 14) || (snake.body[0].y<10 || snake.body[0].y>SCREEN_HEIGHT - 50))
	{
		return false;
	}
	return true;
}
bool Game::snakecheck()
{
	for (int i = 1; i < (int)snake.body.size(); i++)
	{
		//nếu có phần nào của thân rắn trùng với đầu rắn
		if (snake.body[0].x == snake.body[i].x && snake.body[0].y == snake.body[i].y)
		{
			return false;
		}
	}
	return true;
}
void Game::createFood(SDL_Renderer* RendererGame, SDL_Texture* texturegame)
{
	bool check = false;//khởi tạo biến kiểm tra
	do {
		check = false;
		food.x = rand() % 937 + 12;//khởi tạo ngẫu nhiên tọa độ x của mồi
		food.y = rand() % 545 + 8;//khởi tạo ngẫu nhiên tọa độ y của mồi
		for (int i = 0; i < (int)snake.body.size(); i++)
		{
			//nếu khoảng cách của rắn và mồi nhỏ hơn khoảng cách của SIZEFOOOD+SIZESNAKE
			if (sqrt(pow((snake.body[i].x - food.x), 2) + pow((snake.body[i].y - food.y), 2)) < 18)
			{
				check = true;
			}
			else {
				check = false;
				break;
			}
		}
		if (check == false)//nếu thõa màn không phần nào của rắn trùng với mồi
		{
			food.DrawFood(RendererGame, texturegame);//vẽ mồi
		}
	} while (check);
}
void Game::display(SDL_Window*& window, SDL_Surface*& imageGame, SDL_Renderer*& RendrerGame, SDL_Texture*& texturegame, SDL_Event& event)
{
	if (event.type == SDL_QUIT)//nếu event.type=SDL_Quit
	{
		SDL_Quit();//đóng SDL
	}
	int mouseX = event.motion.x;//lấy tọa độ x của chuột
	int mouseY = event.motion.y;//lấy tọa độ y của chuột
	if (event.type == SDL_MOUSEBUTTONDOWN)
	{
		// in ảnh levels
		if (((mouseX >= 55 && mouseX <= 428) && (mouseY >= 466 && mouseY <= 561) && checknameimage == "interface image.png") || ((mouseX >= 368 && mouseX <= 607) && (mouseY >= 464 && mouseY <= 570) && (checknameimage == "level easy.png" || checknameimage == "level medium.png" || checknameimage == "level hard.png" || checknameimage == "level hardest.png")))
		{
			imageGame = LoadImage(window, "levels.png");
			texturegame = SDL_CreateTextureFromSurface(RendrerGame, imageGame);
			checknameimage = "levels.png";
		}
		//in ảnh hướng dẫn chung của trò chơi
		else if ((mouseX >= 521 && mouseX <= 910) && (mouseY >= 466 && mouseY <= 558) && checknameimage == "interface image.png")
		{
			imageGame = LoadImage(window, "instruction interface image.png");
			texturegame = SDL_CreateTextureFromSurface(RendrerGame, imageGame);
			checknameimage = "instruction interface image.png";
			checkinstruction = true;
		}
		else if ((mouseX >= 626 && mouseX <= 945) && (mouseY >= 462 && mouseY <= 559) && checknameimage == "level easy.png")
		{
			imageGame = LoadImage(window, "instruction level easy.png");
			texturegame = SDL_CreateTextureFromSurface(RendrerGame, imageGame);
			checknameimage = "instruction level easy.png";
			checkinstruction = true;
		}
		//in ảnh hướng dẫn của level medium
		else if ((mouseX >= 626 && mouseX <= 945) && (mouseY >= 462 && mouseY <= 559) && checknameimage == "level medium.png")
		{
			imageGame = LoadImage(window, "instruction level medium.png");
			texturegame = SDL_CreateTextureFromSurface(RendrerGame, imageGame);
			checknameimage = "instruction level medium.png";
			checkinstruction = true;
		}
		//in ảnh hướng dẫn của level hard
		else if ((mouseX >= 626 && mouseX <= 945) && (mouseY >= 462 && mouseY <= 559) && checknameimage == "level hard.png")
		{
			imageGame = LoadImage(window, "instruction level hard.png");
			texturegame = SDL_CreateTextureFromSurface(RendrerGame, imageGame);
			checknameimage = "instruction level hard.png";
			checkinstruction = true;
		}
		//in ảnh hướng dẫn của level harest
		else if ((mouseX >= 626 && mouseX <= 945) && (mouseY >= 462 && mouseY <= 559) && checknameimage == "level hardest.png")
		{
			imageGame = LoadImage(window, "instruction level hardest.png");
			texturegame = SDL_CreateTextureFromSurface(RendrerGame, imageGame);
			checknameimage = "instruction level hardest.png";
			checkinstruction = true;
		}
	}
	// tu instruction trở về màn hình game
	if (event.type == SDL_MOUSEBUTTONDOWN && checkinstruction == true)//dung checkinstruction để kiểm tra xem có phải là màn hình đang ở hướng dẫn không
	{
		//in ra màn hình chính của game
		if ((mouseX >= 354 && mouseX <= 534 && mouseY >= 526 && mouseY <= 578) && checknameimage == "instruction interface image.png")
		{
			imageGame = LoadImage(window, "interface image.png");
			texturegame = SDL_CreateTextureFromSurface(RendrerGame, imageGame);
			checknameimage = "interface image.png";
		}
		//in ra màn hình chính của level easy
		else if ((mouseX >= 379 && mouseX <= 571 && mouseY >= 497 && mouseY <= 571) && checknameimage == "instruction level easy.png")
		{
			imageGame = LoadImage(window, "level easy.png");
			texturegame = SDL_CreateTextureFromSurface(RendrerGame, imageGame);
			checknameimage = "level easy.png";
		}
		//in ra màn hình chính của level medium
		else if ((mouseX >= 383 && mouseX <= 574 && mouseY >= 490 && mouseY <= 569) && checknameimage == "instruction level medium.png")
		{
			imageGame = LoadImage(window, "level medium.png");
			texturegame = SDL_CreateTextureFromSurface(RendrerGame, imageGame);
			checknameimage = "level medium.png";
		}
		//in ra màn hình chính của level hard
		else if ((mouseX >= 376 && mouseX <= 574 && mouseY >= 490 && mouseY <= 569) && checknameimage == "instruction level hard.png")
		{
			imageGame = LoadImage(window, "level hard.png");
			texturegame = SDL_CreateTextureFromSurface(RendrerGame, imageGame);
			checknameimage = "level hard.png";
		}
		//in ra màn hình chính của level hardest
		else if ((mouseX >= 385 && mouseX <= 573 && mouseY >= 493 && mouseY <= 571) && checknameimage == "instruction level hardest.png")
		{
			imageGame = LoadImage(window, "level hardest.png");
			texturegame = SDL_CreateTextureFromSurface(RendrerGame, imageGame);
			checknameimage = "level hardest.png";
		}
	}
	//in ra màn hình level
	if (event.type == SDL_MOUSEBUTTONDOWN && checknameimage == "levels.png")//dùng checknameimage để kiểm tra xem có phải đang ở màn hình chọn level không
	{
		//in ra level easy
		if (mouseX >= 81 && mouseX <= 402 && mouseY >= 95 && mouseY <= 227)
		{
			imageGame = LoadImage(window, "level easy.png");
			texturegame = SDL_CreateTextureFromSurface(RendrerGame, imageGame);
			choice = 1;
			checknameimage = "level easy.png";
		}
		//in ra level medium
		else if (mouseX >= 560 && mouseX <= 882 && mouseY >= 94 && mouseY <= 220)
		{
			imageGame = LoadImage(window, "level medium.png");
			texturegame = SDL_CreateTextureFromSurface(RendrerGame, imageGame);
			choice = 2;
			checknameimage = "level medium.png";
		}
		//in ra level hard
		else if (mouseX >= 81 && mouseX <= 402 && mouseY >= 294 && mouseY <= 426)
		{
			imageGame = LoadImage(window, "level hard.png");
			texturegame = SDL_CreateTextureFromSurface(RendrerGame, imageGame);
			choice = 3;
			checknameimage = "level hard.png";
		}
		//in ra level hardest
		else if (mouseX >= 559 && mouseX <= 882 && mouseY >= 290 && mouseY <= 426)
		{
			imageGame = LoadImage(window, "level hardest.png");
			texturegame = SDL_CreateTextureFromSurface(RendrerGame, imageGame);
			choice = 4;
			checknameimage = "level hardest.png";
		}
	}
	//in ra màn hình chơi
	if (event.type == SDL_MOUSEBUTTONDOWN && (checknameimage == "level easy.png" || checknameimage == "level medium.png" || checknameimage == "level hard.png" || checknameimage == "level hardest.png"))//kiểm tra xem có đang ở màn hình chính của level không
	{
		if ((mouseX >= 20 && mouseX <= 346) && (mouseY >= 464 && mouseY <= 562))//bắt đầu màn chơi
		{

			switch (choice)//choice dùng để cập nhật màn chơi
			{
			case 1://in ra màn hình chơi của màn easy
			{
				imageGame = LoadImage(window, "easy level play screen.png");
				texturegame = SDL_CreateTextureFromSurface(RendrerGame, imageGame);
				checknameimage = "easy level play screen.png";
				break;
			}
			case 2://in ra màn hình chơi của màn medium
			{
				imageGame = LoadImage(window, "medium level play screen.png");
				texturegame = SDL_CreateTextureFromSurface(RendrerGame, imageGame);
				checknameimage = "medium level play screen.png";
				break;
			}
			case 3://in ra màn hình chơi của màn hard
			{
				imageGame = LoadImage(window, "hard level play screen.png");
				texturegame = SDL_CreateTextureFromSurface(RendrerGame, imageGame);
				checknameimage = "hard level play screen.png";
				break;
			}
			case 4://in ra màn hình chơi của màn hardest
			{
				imageGame = LoadImage(window, "hardest level play screen.png");
				texturegame = SDL_CreateTextureFromSurface(RendrerGame, imageGame);
				checknameimage = "hardest level play screen.png";
				break;
			}
			default://nếu không có chọn nào phù hợp thì in ra Error
			{
				cerr << "Error" << endl;
			}
			}
		}
	}
}
