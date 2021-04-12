#include <assert.h>

#include "raylib.h"

#define RAYLIB_ASEPRITE_IMPLEMENTATION
#include "raylib-aseprite.h"

int main(int argc, char *argv[]) {
    // Initialization
    SetTraceLogLevel(LOG_ALL);
    TraceLog(LOG_INFO, "================================");
    TraceLog(LOG_INFO, "raylib-aseprite-test");
    TraceLog(LOG_INFO, "================================");

    InitWindow(640, 480, "raylib-aseprite-tests");
    assert(IsWindowReady());

    // Make sure we're running in the correct directory.
    assert(argc > 0);
    const char* dir = GetDirectoryPath(argv[0]);
    assert(ChangeDirectory(dir));

    // LoadAseprite()
    Aseprite aseprite = LoadAseprite("resources/backpacker.aseprite");
    assert(aseprite.ase != NULL);
    assert(aseprite.ase->frame_count > 5);

    // TraceAseprite()
    TraceAseprite(aseprite);

    // LoadAsepriteTag()
    AsepriteTag tag = LoadAsepriteTag(aseprite, "Walk Down");
    assert(tag.timer > 0);

    // GetAspriteTagCount()
    assert(GetAspriteTagCount(aseprite) > 2);

    // GetAsepriteTagName()
    const char* name = GetAsepriteTagName(tag);
    assert(TextIsEqual(name, "Walk Down"));

    // LoadAsepriteTagFromId()
    {
        AsepriteTag tag2 = LoadAsepriteTagFromId(aseprite, 2);
        assert(tag2.speed == 1.0f);
        assert(tag2.currentFrame == 17);
        const char* name = GetAsepriteTagName(tag2);
        assert(TextIsEqual(name, "Walk Up"));
    }

    // GetAsepriteTexture()
    Texture texture = GetAsepriteTexture(aseprite);
    assert(texture.width > 2);
    assert(texture.height > 2);

    BeginDrawing();
    {
        // DrawAseprite()
        DrawAseprite(aseprite, 3, 10, 10, WHITE);
        // DrawAsepriteV()
        DrawAsepriteV(aseprite, 5, (Vector2){10, 20}, WHITE);
        // DrawAsepriteEx()
        DrawAsepriteEx(aseprite, 6, (Vector2){10, 30}, 20, 3, WHITE);
        // DrawAsepritePro()
        DrawAsepritePro(aseprite, 7, (Rectangle){30, 30, 20, 20}, (Vector2){0, 0}, 0.5f, WHITE);

        // DrawAsepriteTag()
        DrawAsepriteTag(tag, 10, 10, WHITE);
        // DrawAsepriteTagV()
        DrawAsepriteTagV(tag, (Vector2){10, 20}, WHITE);
        // DrawAsepriteTagEx()
        DrawAsepriteTagEx(tag, (Vector2){10, 30}, 20, 3, WHITE);
        // DrawAsepriteTagPro()
        DrawAsepriteTagPro(tag, (Rectangle){30, 30, 20, 20}, (Vector2){0, 0}, 0.5f, WHITE);
    }
    EndDrawing();

    // UnloadAseprite()
    UnloadAseprite(aseprite);

    CloseWindow();
    TraceLog(LOG_INFO, "================================");
    TraceLog(LOG_INFO, "raylib-aseprite tests succesful");
    TraceLog(LOG_INFO, "================================");

    return 0;
}
