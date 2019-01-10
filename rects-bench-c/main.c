#include <raylib.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#if defined(PLATFORM_WEB)
#include <emscripten/emscripten.h>
#endif

int randInt(int max) {
  return rand() % max;
}

float randFloat() {
  return ((float) rand()) / ((float) RAND_MAX);
}

#define N 30000

typedef struct MyRect {
  float x, y;
  Color color;
  float speed;
  int w, h;
  float phase;
} MyRect;

MyRect rects[N];

static void load() {
  for (int i = 0; i < N; ++i) {
    MyRect *rect = &rects[i];
    rect->x = randInt(947);
    rect->y = randInt(781);
    rect->color.r = rand();
    rect->color.g = rand();
    rect->color.b = rand();
    rect->color.a = 255;
    rect->speed = 400 * randFloat();
    rect->w = randInt(120);
    rect->h = randInt(120);
    rect->phase = 2 * PI * randFloat();
  }
}

static void update() {
  for (int i = 0; i < N; ++i) {
    MyRect *rect = &rects[i];
    rect->x += rect->speed * sin(GetTime() + rect->phase) * GetFrameTime();
  }
}

static void draw() {
  for (int i = 0; i < N; ++i) {
    MyRect *rect = &rects[i];
    DrawRectangle(rect->x, rect->y, rect->w, rect->h, rect->color);
  }
  {
    static char buf[32];
    snprintf(buf, 32, "fps: %d", GetFPS());
    DrawText(buf, 20, 20, 14, WHITE);
  }
}

static void frame() {
  update();
  
  BeginDrawing();
  ClearBackground(BLACK);
  draw();
  EndDrawing();
  
  { // Workaround for https://github.com/glfw/glfw/issues/1334
    static bool windowPositionSet = false;
    if (!windowPositionSet) {
      SetWindowPosition(200, 200);
      windowPositionSet = true;
    }
  }
}

int main()
{
  InitWindow(947, 781, "hello, raylib!");
  
  load();
  
#if defined(PLATFORM_WEB)
  emscripten_set_main_loop(frame, 0, 1);
#else
  SetTargetFPS(120);
  
  while (!WindowShouldClose())
  {
    frame();
  }
#endif
  
  CloseWindow();
  
  return 0;
}
