#include "pch.h"
#include "Input.h"
#include "Window/Window.h"
#include "Game/Player.h"

Input* Input::instance = nullptr;

std::shared_ptr<Input> Input::GetInstance(bool enableMouse, float mouseSensitivity)
{
	static std::shared_ptr<Input> InputInstance(new Input(enableMouse, mouseSensitivity));
	return InputInstance;
}

Input::Input(bool enableMouse, float mouseSensitivity)
{
	this->mouseSensitivity = mouseSensitivity;
	this->lastMousePosition = glm::vec2(0);
	this->mouseInWindow = false;
	this->mouseFirstTime = true;
	this->rotX = 0;
	this->rotY = 0;
	Setup(enableMouse, Window::GetInstance()->GetGLFWwindow());
}

void Input::Setup(bool enableMouse, GLFWwindow* window)
{
	glfwSetKeyCallback(window, KeyCallback);
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_TRUE);
	if (enableMouse)
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		glfwSetCursorEnterCallback(window, CursorEnterCallback);
		glfwSetCursorPosCallback(window, CursorPosCallback);
		glfwSetMouseButtonCallback(window, MouseButtonCallback);
		glfwSetScrollCallback(window, ScrollCallback);
	}
}

void Input::Key(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	auto player = Player::GetInstance();
	if (mods == GLFW_MOD_SHIFT) player->SetState(Player::State::Sprint);
	else if (mods == GLFW_MOD_CONTROL) player->SetState(Player::State::Crouch);
	else player->SetState(Player::State::Walk);

	if (action == GLFW_PRESS) {
		switch (key) {
		case GLFW_KEY_W:		Player::SetVelocity(true, 0, 1);	break;
		case GLFW_KEY_S:		Player::SetVelocity(true, 0, -1);	break;
		case GLFW_KEY_A:		Player::SetVelocity(true, 1, 0);	break;
		case GLFW_KEY_D:		Player::SetVelocity(true, -1, 0);	break;

		case GLFW_KEY_LEFT:		Player::SetAngularVelocity(true, 0, 1);	break;
		case GLFW_KEY_RIGHT:	Player::SetAngularVelocity(true, 0, -1);	break;
		case GLFW_KEY_UP:		Player::Jump();	break;

		case GLFW_KEY_SPACE:    Player::Shoot(); break;
		}
	}

	if (action == GLFW_REPEAT)
	{
		switch (key) {
		case GLFW_KEY_SPACE:    Player::Shoot(); break;
		}
	}


	if (action == GLFW_RELEASE) {
		switch (key) {
		case GLFW_KEY_W:
		case GLFW_KEY_S:		Player::SetVelocity(false, 0, 1); break;
		case GLFW_KEY_A:
		case GLFW_KEY_D:		Player::SetVelocity(false, 1, 0); break;

		case GLFW_KEY_LEFT:
		case GLFW_KEY_RIGHT:	Player::SetAngularVelocity(false, 0, 1); break;
		}
	}
	/*
	if (action == GLFW_PRESS) {
		switch (key) {
		case GLFW_KEY_W:		player->SetVelocity(true,  0,  1);	break;
		case GLFW_KEY_S:		player->SetVelocity(true,  0, -1);	break;
		case GLFW_KEY_A:		player->SetVelocity(true,  1,  0);	break;
		case GLFW_KEY_D:		player->SetVelocity(true, -1,  0);	break;

		case GLFW_KEY_LEFT:		player->SetAngularVelocity(true,  0,  1);	break;
		case GLFW_KEY_RIGHT:	player->SetAngularVelocity(true,  0, -1);	break;
		case GLFW_KEY_UP:		player->SetAngularVelocity(true, -1,  0);	break;
		case GLFW_KEY_DOWN:		player->SetAngularVelocity(true,  1,  0);	break;

		case GLFW_KEY_SPACE:    player->Jump(); break;
		}
	}
	if (action == GLFW_RELEASE) {
		switch (key) {
		case GLFW_KEY_W: 
		case GLFW_KEY_S:		player->SetVelocity(false, 0, 1); break;
		case GLFW_KEY_A: 
		case GLFW_KEY_D:		player->SetVelocity(false, 1, 0); break;

		case GLFW_KEY_LEFT:
		case GLFW_KEY_RIGHT:	player->SetAngularVelocity(false, 0, 1); break;

		case GLFW_KEY_UP:
		case GLFW_KEY_DOWN:		player->SetAngularVelocity(false, 1, 0); break;
		}
	}
	*/
}

void Input::CursorEnter(GLFWwindow* window, int entered)
{
	mouseInWindow = entered;
}

void Input::CursorPos(GLFWwindow* window, double x, double y)
{
	if (!mouseInWindow) return;

	if (mouseFirstTime) {
		lastMousePosition = glm::vec2(x, y);
		mouseFirstTime = false;
	}

	float xOffset = (x - lastMousePosition.x) * mouseSensitivity;
	float yOffset = (lastMousePosition.y - y) * mouseSensitivity;
	lastMousePosition = glm::vec2(x, y);
	
	rotY += xOffset;
	rotX += yOffset;

	rotX = glm::clamp(rotX, -80.0f, 80.0f);

	glm::vec3 direction;
	direction.x = cos(glm::radians(rotY)) * cos(glm::radians(rotX));
	direction.y = sin(glm::radians(rotX));
	direction.z = sin(glm::radians(rotY)) * cos(glm::radians(rotX));


	//std::cout << rotY << " " << rotX + 45 << std::endl;

	Player::GetInstance()->LookAt(glm::normalize(direction));
}

void Input::MouseButton(GLFWwindow* window, int button, int action, int mods)
{
	if (action == GLFW_PRESS) {
		switch (button) {}
	}
	if (action == GLFW_RELEASE) {
		switch (button) {}
	}
}

void Input::Scroll(GLFWwindow* window, double xOffset, double yOffset)
{
	if (!mouseInWindow) return;
}
