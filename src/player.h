#pragma once
#include "../raylib/include/raylib.h"

struct Player
{
	float gravity = 32.0f;
	float jumpForce = 12.0f;
	float maxSpeed = 50.0f;
	bool isGrounded = false;

	Vector2 velocity = { 0, 0 };
	Vector2 position = { GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f };

	Player(Vector2 startPos);

	void jump(float& deltaTime);
	void move(float& deltaTime);
	void update();
};