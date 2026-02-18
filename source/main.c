#include <3ds.h>
#include <citro2d.h>

static int selected = 0; // 0 = Nintendo, 1 = Brewtendo

int main(int argc, char* argv[])
{
    gfxInitDefault();
    romfsInit();

    C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
    C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
    C2D_Prepare();

    C2D_ScreenTarget top = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);
    C2D_ScreenTarget bottom = C2D_CreateScreenTarget(GFX_BOTTOM, GFX_LEFT);

    C2D_TextBuf buf = C2D_TextBufNew(4096);
    C2D_Text title, subtitle, nintendo, brewtendo;

    C2D_TextParse(&title, buf, "Brewtendo Network");
    C2D_TextParse(&subtitle, buf, "eShop Replacement Servers");
    C2D_TextParse(&nintendo, buf, "Nintendo");
    C2D_TextParse(&brewtendo, buf, "Brewtendo");

    C2D_TextOptimize(&title);
    C2D_TextOptimize(&subtitle);
    C2D_TextOptimize(&nintendo);
    C2D_TextOptimize(&brewtendo);

    while (aptMainLoop())
    {
        hidScanInput();
        u32 kDown = hidKeysDown();

        if (kDown & KEY_START) break;
        if (kDown & KEY_LEFT) selected = 0;
        if (kDown & KEY_RIGHT) selected = 1;

        C3D_FrameBegin(C3D_FRAME_SYNCDRAW);

        // TOP SCREEN
        C2D_TargetClear(top, C2D_Color32(20, 20, 20, 255));
        C2D_SceneBegin(top);

        C2D_DrawText(&title, C2D_AtBaseline | C2D_WithColor,
                     200, 60, 0, 0.8f, 0.8f,
                     C2D_Color32(255, 255, 255, 255));

        C2D_DrawText(&subtitle, C2D_AtBaseline | C2D_WithColor,
                     200, 90, 0, 0.5f, 0.5f,
                     C2D_Color32(180, 180, 180, 255));

        // BOTTOM SCREEN
        C2D_TargetClear(bottom, C2D_Color32(15, 15, 15, 255));
        C2D_SceneBegin(bottom);

        u32 colN = selected == 0 ? C2D_Color32(100, 200, 255, 255) : C2D_Color32(255, 255, 255, 255);
        u32 colB = selected == 1 ? C2D_Color32(100, 200, 255, 255) : C2D_Color32(255, 255, 255, 255);

        C2D_DrawText(&nintendo, C2D_AtBaseline | C2D_WithColor,
                     80, 120, 0, 0.6f, 0.6f, colN);

        C2D_DrawText(&brewtendo, C2D_AtBaseline | C2D_WithColor,
                     220, 120, 0, 0.6f, 0.6f, colB);

        C3D_FrameEnd(0);
    }

    C2D_TextBufDelete(buf);
    C2D_Fini();
    C3D_Fini();
    romfsExit();
    gfxExit();
    return 0;
}
