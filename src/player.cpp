#include "player.h"
#include "../raylib/include/raylib.h"

Player::Player(Vector2 startPos) {}

void World::placeBlock(Vector2& mousePos, Camera2D cam)
{
	if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
	{
		float gridX = (int)(GetScreenToWorld2D(mousePos, cam).x / cellSize) * cellSize;
		float gridY = (int)(GetScreenToWorld2D(mousePos, cam).y / cellSize) * cellSize;

		placedBlocks.push_back({ gridX, gridY - 30.0f });
	}
}

void World::destroyBlock(Vector2& mousePos, Camera2D cam)
{
	if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON))
	{
		for (int i = 0; i < placedBlocks.size(); i++)
		{
			if (CheckCollisionPointRec(GetScreenToWorld2D(mousePos, cam), { placedBlocks[i].x, placedBlocks[i].y + 30, cellSize, cellSize }))
			{
				placedBlocks.erase(placedBlocks.begin() + i);
				break;
			}
		}
	}
}

void Player::jump(float& deltaTime)
{	
	if(IsKeyDown(KEY_SPACE) && isGrounded) velocity.y = -jumpForce;

	position.y += velocity.y * deltaTime;
	if (!isGrounded) velocity.y += gravity * deltaTime;
}

void Player::move(float& deltaTime)
{
	velocity.x = 0;

	if (IsKeyDown(KEY_D)) velocity.x = maxSpeed;
	if (IsKeyDown(KEY_A)) velocity.x = -maxSpeed;

	position.x += velocity.x * deltaTime;
}

void Player::update(float& deltaTime, World& world)
{
	move(deltaTime);
	playerRect = { position.x, position.y, 20, 40 };

	for (Vector2 block : world.placedBlocks)
	{
		blockRect = { block.x, block.y + 30, world.cellSize, world.cellSize };

		if (CheckCollisionRecs(playerRect, blockRect))
		{
			if (velocity.x > 0) position.x = blockRect.x - playerRect.width;
			else if (velocity.x < 0) position.x = blockRect.x + blockRect.width;
		}
	}

	jump(deltaTime);
	isGrounded = false;

	playerRect = { position.x, position.y, 20, 40 };

	for (Vector2 block : world.placedBlocks)
	{
		blockRect = { block.x, block.y + 30, world.cellSize, world.cellSize };

		if (CheckCollisionRecs(playerRect, blockRect))
		{
			if (velocity.y > 0)
			{
				isGrounded = true;
				position.y = blockRect.y - playerRect.height;
				velocity.y = 0;
			}
			else if (velocity.y < 0)
			{
				position.y = blockRect.y + blockRect.height;
			}
		}
	}

	DrawRectangle(position.x, position.y, 20, 40, WHITE);
}