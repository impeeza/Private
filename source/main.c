
#include <3ds.h>
#include <citro2d.h>

static C3D_RenderTarget *top, *bot;
static C2D_TextBuf textBuf;
static C2D_Text title, subtitle, prompt, brewTxt, ninTxt;
static C2D_SpriteSheet sheet;
static C2D_Sprite brewIcon, ninIcon;
static int sel = 0;

void init_ui() {
    textBuf = C2D_TextBufNew(4096);

    C2D_TextParse(&title, textBuf, "Brewtendo Network");
    C2D_TextParse(&subtitle, textBuf, "eShop Replacement Servers");
    C2D_TextParse(&prompt, textBuf, "What account do you want to load?");
    C2D_TextParse(&brewTxt, textBuf, "Brewtendo");
    C2D_TextParse(&ninTxt, textBuf, "Nintendo");

    C2D_TextOptimize(&title);
    C2D_TextOptimize(&subtitle);
    C2D_TextOptimize(&prompt);
    C2D_TextOptimize(&brewTxt);
    C2D_TextOptimize(&ninTxt);

    sheet = C2D_SpriteSheetLoad("romfs:/icons.t3x");
    C2D_SpriteFromSheet(&brewIcon, sheet, 0);
    C2D_SpriteFromSheet(&ninIcon, sheet, 1);

    C2D_SpriteSetScale(&brewIcon, 0.75f, 0.75f);
    C2D_SpriteSetScale(&ninIcon, 0.75f, 0.75f);
}

int main() {
    gfxInitDefault();
    C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
    C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
    C2D_Prepare();
    romfsInit();

    top = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);
    bot = C2D_CreateScreenTarget(GFX_BOTTOM, GFX_LEFT);
    init_ui();

    while (aptMainLoop()) {
        hidScanInput();
        u32 kDown = hidKeysDown();
        if (kDown & KEY_LEFT) sel = 0;
        if (kDown & KEY_RIGHT) sel = 1;
        if (kDown & KEY_A || kDown & KEY_START) break;

        C2D_TargetClear(top, C2D_Color32(18,18,22,255));
        C2D_SceneBegin(top);
        C2D_DrawText(&title, C2D_WithColor, 80, 80, 0, 0.8f, 0.8f, C2D_Color32(255,255,255,255));
        C2D_DrawText(&subtitle, C2D_WithColor, 80, 120, 0, 0.6f, 0.6f, C2D_Color32(200,200,200,255));

        C2D_TargetClear(bot, C2D_Color32(20,20,24,255));
        C2D_SceneBegin(bot);
        C2D_DrawText(&prompt, C2D_WithColor, 40, 30, 0, 0.6f, 0.6f, C2D_Color32(220,220,220,255));

        C2D_SpriteSetPos(&brewIcon, 40, 80);
        C2D_DrawSprite(&brewIcon);
        C2D_DrawText(&brewTxt, C2D_WithColor, 40, 150, 0, 0.55f, 0.55f, C2D_Color32(255,255,255,255));

        C2D_SpriteSetPos(&ninIcon, 180, 80);
        C2D_DrawSprite(&ninIcon);
        C2D_DrawText(&ninTxt, C2D_WithColor, 180, 150, 0, 0.55f, 0.55f, C2D_Color32(255,255,255,255));

        gfxSwapBuffers();
        gspWaitForVBlank();
    }

    C2D_SpriteSheetFree(sheet);
    C2D_TextBufDelete(textBuf);
    romfsExit();
    C2D_Fini();
    C3D_Fini();
    gfxExit();
    return 0;
}
