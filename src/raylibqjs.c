#include "raylib.h"
#include "quickjs.h"

#define countof(x) (sizeof(x) / sizeof((x)[0]))

static JSValue js_InitWindow(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv) {
  int width;
  if (JS_ToInt32(ctx, &width, argv[0])) {
    return JS_EXCEPTION;
  }

  int height;
  if (JS_ToInt32(ctx, &height, argv[1])) {
    return JS_EXCEPTION;
  }

  const char* title = JS_ToCString(ctx, argv[2]);
  if (!title){
    return JS_EXCEPTION;
  }
  
  InitWindow(width, height, title);

  return JS_UNDEFINED;
}

static JSValue js_js_raylib_exports(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv) {
  int fps;
  if (JS_ToInt32(ctx, &fps, argv[0])) {
    return JS_EXCEPTION;
  }

  SetTargetFPS(fps);

  return JS_UNDEFINED;
}

static JSValue js_WindowShouldClose(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv) {
  return JS_NewBool(ctx, WindowShouldClose());
}

static JSValue js_BeginDrawing(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv) {
  BeginDrawing();

  return JS_UNDEFINED;
}

static JSValue js_EndDrawing(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv) {
  EndDrawing();

  return JS_UNDEFINED;
}

static JSValue js_CloseWindow(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv) {
  CloseWindow();

  return JS_UNDEFINED;
}

static JSValue js_ClearBackground(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv) {
  int color;
  if (JS_ToInt32(ctx, &color, argv[0])) {
    return JS_EXCEPTION;
  }

  ClearBackground(GetColor(color));

  return JS_UNDEFINED;
}

static JSValue js_DrawText(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv) {
  const char* text = JS_ToCString(ctx, argv[0]);
  if (!text){
    return JS_EXCEPTION;
  }

  int posX;
  if (JS_ToInt32(ctx, &posX, argv[1])) {
    return JS_EXCEPTION;
  }
  
  int posY;
  if (JS_ToInt32(ctx, &posY, argv[2])) {
    return JS_EXCEPTION;
  }

  int fontSize;
  if (JS_ToInt32(ctx, &fontSize, argv[3])) {
    return JS_EXCEPTION;
  }

  int color;
  if (JS_ToInt32(ctx, &color, argv[4])) {
    return JS_EXCEPTION;
  }

  DrawText(text, posX, posY, fontSize, GetColor(color));

  return JS_UNDEFINED;
}

static JSValue js_DrawFPS(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv) {
  int posX;
  if (JS_ToInt32(ctx, &posX, argv[0])) {
    return JS_EXCEPTION;
  }
  
  int posY;
  if (JS_ToInt32(ctx, &posY, argv[1])) {
    return JS_EXCEPTION;
  }

  DrawFPS(posX, posY);

  return JS_UNDEFINED;
}

static const JSCFunctionListEntry js_raylib_exports[] = {
  JS_CFUNC_DEF("InitWindow", 3, js_InitWindow),
  JS_CFUNC_DEF("SetTargetFPS", 1, js_js_raylib_exports),
  JS_CFUNC_DEF("WindowShouldClose", 0, js_WindowShouldClose),
  JS_CFUNC_DEF("BeginDrawing", 0, js_BeginDrawing),
  JS_CFUNC_DEF("EndDrawing", 0, js_EndDrawing),
  JS_CFUNC_DEF("CloseWindow", 0, js_CloseWindow),
  JS_CFUNC_DEF("ClearBackground", 1, js_ClearBackground),
  JS_CFUNC_DEF("DrawText", 5, js_DrawText),
  JS_CFUNC_DEF("DrawFPS", 2, js_DrawFPS),

  // I am doing colors as ints to make it easy, should be struct/objects
  JS_PROP_INT32_DEF("LIGHTGRAY", -926365441, 0 ),
  JS_PROP_INT32_DEF("GRAY", -2105376001, 0 ),
  JS_PROP_INT32_DEF("DARKGRAY", 1347440895, 0 ),
  JS_PROP_INT32_DEF("YELLOW", -34012929, 0 ),
  JS_PROP_INT32_DEF("GOLD", -3473153, 0 ),
  JS_PROP_INT32_DEF("ORANGE", -6225665, 0 ),
  JS_PROP_INT32_DEF("PINK", -9583873, 0 ),
  JS_PROP_INT32_DEF("RED", -433506305, 0 ),
  JS_PROP_INT32_DEF("MAROON", -1105119233, 0 ),
  JS_PROP_INT32_DEF("GREEN", 14954751, 0 ),
  JS_PROP_INT32_DEF("LIME", 10366975, 0 ),
  JS_PROP_INT32_DEF("DARKGREEN", 7679231, 0 ),
  JS_PROP_INT32_DEF("SKYBLUE", 1723858943, 0 ),
  JS_PROP_INT32_DEF("BLUE", 7991807, 0 ),
  JS_PROP_INT32_DEF("DARKBLUE", 5418239, 0 ),
  JS_PROP_INT32_DEF("PURPLE", -931463169, 0 ),
  JS_PROP_INT32_DEF("VIOLET", -2026062081, 0 ),
  JS_PROP_INT32_DEF("DARKPURPLE", 1881112319, 0 ),
  JS_PROP_INT32_DEF("BEIGE", -743406593, 0 ),
  JS_PROP_INT32_DEF("BROWN", 2137673727, 0 ),
  JS_PROP_INT32_DEF("DARKBROWN", 1279209471, 0 ),
  JS_PROP_INT32_DEF("WHITE", -1, 0 ),
  JS_PROP_INT32_DEF("BLACK", 255, 0 ),
  JS_PROP_INT32_DEF("BLANK", 0, 0 ),
  JS_PROP_INT32_DEF("MAGENTA", -16711681, 0 ),
  JS_PROP_INT32_DEF("RAYWHITE", -168430081, 0 )
};

static int js_raylib_init(JSContext* ctx, JSModuleDef* m) {
  return JS_SetModuleExportList(ctx, m, js_raylib_exports, countof(js_raylib_exports));
}

JSModuleDef* js_init_module(JSContext* ctx, const char* module_name) {
  JSModuleDef* m;
  m = JS_NewCModule(ctx, module_name, js_raylib_init);
  if (!m) {
    return NULL;
  }
  JS_AddModuleExportList(ctx, m, js_raylib_exports, countof(js_raylib_exports));
  return m;
}