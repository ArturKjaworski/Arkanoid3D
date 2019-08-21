#include "pch.h"

#include "Shader.h"
#include "Camera.h"

#include "Texture.h"

#include "Game.h"
#include "Renderer.h"
#include "Network.h"

#include <vector>
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void processInput(GLFWwindow *window);

void menus();

//settings
const GLuint SCR_WIDTH = 800;
const GLuint SCR_HEIGHT = 600;

Shader* shader;
Camera* camera;
Player* player;
GLFWwindow* window;

GLFWwindow* init()
{
#pragma region glfw
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Arkanoid 3D", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return nullptr;
	}
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return nullptr;
	}
#pragma endregion

	shader = new Shader("res/basicShader");

	camera = new Camera(glm::vec3(0, 23, 30), 30.0f, float(SCR_WIDTH / SCR_WIDTH), 0.01f, 1000.f);
	camera->SetBoundary(SCR_WIDTH, SCR_HEIGHT);

	return window;
}
enum EState
{
	MainMenu,
	CreateGameMenu,
	JoinMenu,
};

EState gameState = EState::MainMenu;
std::string address;

void SwitchMenu(int option)
{
	switch (option)
	{
		case 0:
		{
				glfwSetWindowShouldClose(window, true);
			//esc
			break;
		}

		case 1:
		{
			if (gameState == EState::MainMenu)
			{
				gameState = EState::CreateGameMenu;
				Network::GetInstance().InitServer();
			}

			break;
		}
		case 2:
		{
			if (gameState == EState::MainMenu)
			{
				gameState = EState::JoinMenu;
			}
			break;
		}
		case 3://enter
		{
			if (gameState == EState::CreateGameMenu && !Network::GetInstance().clients.empty() && !Game::GetInstance().IsRunning())
			{
				Network::GetInstance().sendToAll("start");
			}
			if (gameState == EState::JoinMenu && Network::GetInstance().type == Network::EConnectionType::NONE && !Game::GetInstance().IsRunning() && address.size() > 0)
			{
				Network::GetInstance().SetServerAddress(address);
				Network::GetInstance().InitClient();
			}
			break;
		}

		default:
			break;
	}
	if (!Game::GetInstance().IsRunning())
		menus();
}


void menus()
{
	switch (gameState)
	{
		case EState::MainMenu:
		{	
			std::cout << "Every key should be pressed while window is active (not in console!)\n\n";
			std::cout << "Press Q to Create game" << std::endl;
			std::cout << "Press W to Join game" << std::endl;
			break;
		}	

		case EState::CreateGameMenu:
		{
			if (!Network::GetInstance().clients.empty())
				std::cout << "Loading Game\n";
			else
				std::cout << "Wait for player...";

			break;
		}	
		case EState::JoinMenu:
		{
			if (gameState == EState::JoinMenu && Network::GetInstance().type == Network::EConnectionType::Client)
				std::cout << "Waiting for game start... " << std::endl;
			else
				std::cout << "Server address IPv4: " << std::endl << address << std::endl;

			break;
		}

		default:
			break;
	}
}

bool connected = false;
int main()
{
	window = init();

	if (!window)
		return -1;

	glfwSetKeyCallback(window, key_callback);
	menus();
	gameState = EState::MainMenu;

	Renderer renderer;
	Game& game = Game::GetInstance();

	// render loop
	double startTime = glfwGetTime();
	double endTime;
	float deltaTime;

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		renderer.Clear();

		if (!Network::GetInstance().clients.empty() && !connected)
		{
			std::cout << "\nPlayer joined\nPress Enter to start game\n";
			connected = true;
		}
		endTime = glfwGetTime();
		deltaTime = float(endTime - startTime);
		startTime = endTime;

		if (!game.IsRunning())
		{
			std::string msg = Network::GetInstance().recv().c_str();
			if (std::strcmp(msg.c_str(), "start") == 0)
			{
				game.Init();
				Network::GetInstance().sendToServer("ready");
			}
			
			if (std::strcmp(msg.c_str(), "ready") == 0)
				game.Init();
		}

		game.Update(deltaTime);

		renderer.Draw(game.GetGameObjects(), camera, *shader);

		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	delete(shader);

	glfwTerminate();
	return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (!(action == GLFW_PRESS || (action == GLFW_REPEAT && (key == GLFW_KEY_A || key == GLFW_KEY_D))))
		return;

	switch (key)
	{
		case GLFW_KEY_ESCAPE:
		{
			SwitchMenu(0);
			break;
		}

		case GLFW_KEY_Q:
		{
			SwitchMenu(1);
			break;
		}	

		case GLFW_KEY_W:
		{
			SwitchMenu(2);
			break;
		}		

		case GLFW_KEY_ENTER:
		{
			SwitchMenu(3);
			break;
		}

		default:
		{
			if (gameState == EState::JoinMenu && Network::GetInstance().type == Network::EConnectionType::NONE && !Game::GetInstance().IsRunning())
			{
				if (key == GLFW_KEY_PERIOD)
				{
					address += '.';
				}
				else if(key == GLFW_KEY_BACKSPACE)
				{
					if (!address.empty())
						address.pop_back();
				}
				else
					address += char(key);

				system("cls");
				std::cout << "Every key should be pressed while window is active (not in console!)\n\n";
				std::cout << "Server address IPv4: " << std::endl << address << std::endl;
			}
			break;
		}
	}
}

void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		if (!Game::GetInstance().IsRunning())
			return;

		if (Network::GetInstance().type == Network::EConnectionType::Client)
			Network::GetInstance().sendToServer("a");
		else
			Game::GetInstance().GetPlayer()->MoveRight(-0.2f);
	}
		
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		if (!Game::GetInstance().IsRunning())
			return;

		if (Network::GetInstance().type == Network::EConnectionType::Client)
			Network::GetInstance().sendToServer("d");
		else
			Game::GetInstance().GetPlayer()->MoveRight(0.2f);
	}

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		if (!Game::GetInstance().IsRunning())
			return;

		if (Network::GetInstance().type == Network::EConnectionType::Client)
			Network::GetInstance().sendToServer("f");
		else
			Game::GetInstance().GetPlayer()->Shoot();
	}
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}