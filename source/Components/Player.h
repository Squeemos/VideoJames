#pragma once

class Transform;

class Player
{
public:
	Player();
	~Player();
	Player(Player&& other) noexcept;
	Player& operator=(Player&& other) noexcept;

	void update(double dt, Transform& tform);

private:
	float __move_speed;
};