import {
  InitWindow,
  SetTargetFPS,
  WindowShouldClose,
  BeginDrawing,
  EndDrawing,
  CloseWindow,
  ClearBackground,
  DrawText,
  DrawFPS,
  RAYWHITE,
  LIGHTGRAY
} from './build/raylibqjs.so'

InitWindow(800, 450, 'raylib [core] example - basic window')
// SetTargetFPS(60)

while (!WindowShouldClose()) {
  BeginDrawing()
  ClearBackground(RAYWHITE)
  DrawFPS(10, 10)
  DrawText('Congrats! You created your first raylibqjs window!', 140, 200, 20, LIGHTGRAY)
  EndDrawing()
}

CloseWindow()
