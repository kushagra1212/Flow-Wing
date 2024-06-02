#include "raylib.h"
#include <stdio.h>
int main() {
  printf("Hello, World!\n");

  InitWindow(800, 600, "Snake Game");
  SetTargetFPS(60);
  Texture2D texture = LoadTexture("../bird.png");

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawTexturePro(texture, {0.0, 0.0, 1080.0, 1080.0},
                   {0.0, 0.0, 1080.0, 1080.0}, {0.0, 0.0}, 0.0, WHITE);
    EndDrawing();
  }

  printf("Texure Id%d\n", texture.id);
  return 0;
}