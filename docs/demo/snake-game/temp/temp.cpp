#include "raylib.h"

int main() {
  InitWindow(800, 600, "Mouse Position Example");

  while (!WindowShouldClose()) {
    // Get the mouse position
    Vector2 mousePosition = GetMousePosition();

    // Check if the mouse is within certain bounds
    if (mousePosition.x > 100 && mousePosition.x < 200 &&
        mousePosition.y > 100 && mousePosition.y < 200) {
      // Do something if the mouse is over a specific area
    }

    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawText("Move the mouse to see its position", 10, 10, 20, DARKGRAY);
    EndDrawing();
  }

  CloseWindow();
  return 0;
}
