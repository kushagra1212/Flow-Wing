/*
 * FlowWing Compiler
 * Copyright (C) 2023-2026 Kushagra Rathore
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


/*
 * FlowWing Compiler - Raylib Module Bridge
 */

#include "raylib.h"
#include <cstdint>
#include <cstring>
#include <string>

// Dynamic Tags from your runtime
#define DYN_TAG_INT8 0
#define DYN_TAG_INT32 1
#define DYN_TAG_INT64 2
#define DYN_TAG_FLOAT32 3
#define DYN_TAG_FLOAT64 4
#define DYN_TAG_STRING 5
#define DYN_TAG_BOOLEAN 6
#define DYN_TAG_NIRAST 7
#define DYN_TAG_CHAR 8

extern "C" {
struct DynamicValue {
  int32_t tag;
  int64_t value;
};
}

// Helper to unpack Color from int64
Color unpackColor(int64_t packed) {
  return Color{(unsigned char)(packed & 0xFF),
               (unsigned char)((packed >> 8) & 0xFF),
               (unsigned char)((packed >> 16) & 0xFF),
               (unsigned char)((packed >> 24) & 0xFF)};
}

// Helper to unpack Vec2 from int64
Vector2 unpackVec2(int64_t packed) {
  float x, y;

  // Extract the lower 32 bits and upper 32 bits as values
  uint32_t x_bits = static_cast<uint32_t>(packed & 0xFFFFFFFF);
  uint32_t y_bits = static_cast<uint32_t>(packed >> 32);

  // Copy the bit patterns into the floats
  std::memcpy(&x, &x_bits, sizeof(float));
  std::memcpy(&y, &y_bits, sizeof(float));

  return {x, y};
}
extern "C" {

void _ray_init_window(int width, int height, const char *title) {
  InitWindow(width, height, title);
}

bool _ray_window_should_close() { return WindowShouldClose(); }

void _ray_begin_drawing() { BeginDrawing(); }

void _ray_end_drawing() { EndDrawing(); }

void _ray_clear_background(int64_t color_packed) {
  ClearBackground(unpackColor(color_packed));
}

void _ray_draw_circle(float centerX, float centerY, float radius,
                      int64_t color_packed) {
  DrawCircle((int)centerX, (int)centerY, radius, unpackColor(color_packed));
}

void _ray_draw_rectangle(float posX, float posY, float width, float height,
                         int64_t color_packed) {
  DrawRectangle((int)posX, (int)posY, (int)width, (int)height,
                unpackColor(color_packed));
}

void _ray_draw_text(const char *text, int32_t posX, int32_t posY,
                    int32_t fontSize, int64_t color_packed) {
  DrawText(text, posX, posY, fontSize, unpackColor(color_packed));
}

bool _ray_is_key_pressed(int32_t key) { return IsKeyPressed((KeyboardKey)key); }

bool _ray_is_mouse_button_pressed(int32_t button) {
  return IsMouseButtonPressed((MouseButton)button);
}
}