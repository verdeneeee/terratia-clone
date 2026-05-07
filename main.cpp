#include "raylib/include/raylib.h"
#include "src/player.h"

int main()
{
    InitWindow(800, 450, "hello world");

    Player player({ GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f });

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(SKYBLUE);

        float deltaTime = GetFrameTime();

        DrawRectangle(0, (450 + 80) / 2, 800, 450/2, GREEN);

        player.update();
        player.move(deltaTime);
        player.jump(deltaTime);

        EndDrawing();
    }

    CloseWindow();

	return 0;
}