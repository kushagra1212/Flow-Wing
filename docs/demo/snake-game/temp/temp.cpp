/*
 * FlowWing Compiler
 * Copyright (C) 2023-2025 Kushagra Rathore
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */


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
