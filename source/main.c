#include <3ds.h>
#include <citro2d.h>
#include <string.h>

#define SCREEN_W 320
#define SCREEN_H 240

// Text
static C2D_TextBuf textBuf;
static C2D_Text promptText;
static C2D_Text brewText;
static C2D_Text ninText;

// Sprites
static C2D_SpriteSheet icons;
static C2D_Sprite brewIcon;
static C2D_Sprite ninIcon;

// Render targets
static C3D_RenderTarget* top;
static C3D_RenderTarget* bot;

static int selected = 0; // 0 = Brewtendo, 1 = Nintendo

static void init_ui(void)
{
    textBuf = C2D_TextBufNew(4096);

    C2D_TextParse(&promptText, textBuf,
        "What account do you\nwant to load?");
    C2D_TextOptimize(&promptText);

    C2D_TextParse(&brewText, textBuf, "Brewtendo");
    C2D_TextOptimize(&brewText);

    C2D_TextParse(&ninText, textBuf, "Nintendo");
    C2D_TextOptimize(&ninText);

    icons = C2D_SpriteSheetLoad("romfs:/icons.t3x");

    C2D_SpriteFromSheet(&brew
