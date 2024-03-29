#include "Player.h"
#include "Transform.h"

#include "../Systems/InputManager.h"

Player::Player() : __move_speed(400.0f)
{
}

Player::~Player()
{
}

Player::Player(Player&& other) noexcept : __move_speed(other.__move_speed)
{
}

Player& Player::operator=(Player&& other) noexcept
{
	other;
	return *this;
}

void Player::update(double dt, Transform& tform)
{
	float float_dt = static_cast<float>(dt);

	if (InputManager::get_instance().check_key_held(GLFW_KEY_W))
		tform.translate_y(__move_speed * float_dt);
	if (InputManager::get_instance().check_key_held(GLFW_KEY_S))
		tform.translate_y(-__move_speed * float_dt);
	if (InputManager::get_instance().check_key_held(GLFW_KEY_A))
		tform.translate_x(-__move_speed * float_dt);
	if (InputManager::get_instance().check_key_held(GLFW_KEY_D))
		tform.translate_x(__move_speed * float_dt);

	if (InputManager::get_instance().check_key_pressed(GLFW_KEY_UP))
		tform.set_z_order(2.0f);
	if (InputManager::get_instance().check_key_pressed(GLFW_KEY_DOWN))
		tform.set_z_order(-2.0f);

	if (InputManager::get_instance().check_key_held(GLFW_KEY_Q))
		tform.rotate(90 * float_dt);
	if (InputManager::get_instance().check_key_held(GLFW_KEY_E))
		tform.rotate(-90 * float_dt);

	if (InputManager::get_instance().check_key_held(GLFW_KEY_LEFT))
		tform.scale(-100 * float_dt, -100 * float_dt);
	if (InputManager::get_instance().check_key_held(GLFW_KEY_RIGHT))
		tform.scale(100 * float_dt, 100 * float_dt);
}