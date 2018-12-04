#include <3ds.h>
#include <string>
#include <citro2d.h>
#include <algorithm>
#include "CTRFont.hpp"
#include "gfx.h"
#include "save.h"
#include "e_utils.h"
#include "utils.h"
#include "InputManager.h"
#include "imagebutton.h"
#include "menus.h"
#include "gui/MainMenu.hpp"
#include "gui/PlayerMenu.hpp"
#include "gui/AcreMenu.hpp"
#include "gui/ShopsMenu.hpp"

extern InputManager *input;

ImageButton *TownButton = new ImageButton(15.f, 110.f, 70.f, 55.f, 0, KEY_A|KEY_TOUCH, BUTTON_MAIN, Editor_ss);
ImageButton *AcreButton = new ImageButton(89.f, 110.f, 70.f, 55.f, 0, KEY_A|KEY_TOUCH, BUTTON_MAIN, Editor_ss);
ImageButton *PlayerButton = new ImageButton(163.f, 110.f, 70.f, 55.f, 0, KEY_A|KEY_TOUCH, BUTTON_MAIN, Editor_ss);
ImageButton *VillagerButton = new ImageButton(237.f, 110.f, 70.f, 55.f, 0, KEY_A|KEY_TOUCH, BUTTON_MAIN, Editor_ss);
ImageButton *PWPButton = new ImageButton(15.f, 180.f, 70.f, 55.f, 0, KEY_A|KEY_TOUCH, BUTTON_MAIN, Editor_ss);
ImageButton *IslandButton = new ImageButton(89.f, 180.f, 70.f, 55.f, 0, KEY_A|KEY_TOUCH, BUTTON_MAIN, Editor_ss);
ImageButton *MainStreetButton = new ImageButton(163.f, 180.f, 70.f, 55.f, 0, KEY_A|KEY_TOUCH, BUTTON_MAIN, Editor_ss);
ImageButton *AboutButton = new ImageButton(237.f, 180.f, 70.f, 55.f, 0, KEY_A|KEY_TOUCH, BUTTON_MAIN, Editor_ss);

ImageButton *SaveButton = new ImageButton(220.f, 10.f, 80.f, 33.f, 0, KEY_A|KEY_TOUCH, BUTTON_MAIN, Editor_ss);
ImageButton *OptionsButton = new ImageButton(220.f, 60.f, 80.f, 33.f, 0, KEY_A|KEY_TOUCH, BUTTON_MAIN, Editor_ss);
ImageButton *GameSelectButton = new ImageButton(20.f, 10.f, 80.f, 33.f, 0, KEY_A|KEY_TOUCH, BUTTON_MAIN, Editor_ss);
ImageButton *TownManagerButton = new ImageButton(20.f, 60.f, 80.f, 33.f, 0, KEY_A|KEY_TOUCH, BUTTON_MAIN, Editor_ss);

bool Editor::SaveCheck(void) {
    return MsgDisp(top, "Would you like to save changes\nmade to your save?", MsgTypeConfirm);
}

void Editor::Draw_MainMenu(void)
{
    static bool TextInit = false;
    static const float TextSize = 0.6f;
    static std::vector<Text> ButtonText;
    static std::vector<Text> ColumnText;
    static int ButtonIcon[] = {TOWN_ICON, ACRES_ICON, PROFILE_ICON, VILLAGERS_ICON,
                               PWP_ICON, ISLAND_ICON, SHOPS_ICON, ABOUT_ICON};

    if (!TextInit) {
        ButtonText.push_back(Text(COLOR_GREY, "Town", TextSize, TextSize, 37.f, 147.f));
        ButtonText.push_back(Text(COLOR_GREY, "Acres", TextSize, TextSize, 110.f, 147.f));
        ButtonText.push_back(Text(COLOR_GREY, "Players", TextSize, TextSize, 178.f, 147.f));
        ButtonText.push_back(Text(COLOR_GREY, "Villagers", TextSize, TextSize, 248.f, 147.f));
        ButtonText.push_back(Text(COLOR_GREY, "PWPs", TextSize, TextSize, 37.f, 217.f));
        ButtonText.push_back(Text(COLOR_GREY, "Island", TextSize, TextSize, 110.f, 217.f));
        ButtonText.push_back(Text(COLOR_GREY, "Shops", TextSize, TextSize, 182.f, 217.f));
        ButtonText.push_back(Text(COLOR_GREY, "About", TextSize, TextSize, 256.f, 217.f));

        ColumnText.push_back(Text(COLOR_GREY, "Game\nSelect", TextSize, TextSize, 44.f, 12.f));
        ColumnText.push_back(Text(COLOR_GREY, "  Town\nManager", TextSize, TextSize, 40.f, 60.f));
        ColumnText.push_back(Text(COLOR_GREY, "Save", TextSize, TextSize, 248.f, 18.f));
        ColumnText.push_back(Text(COLOR_GREY, "Options", TextSize, TextSize, 240.f, 67.f));
        TextInit = true;
    }

    draw_base_interface();
    C2D_SceneBegin(bottom);
    DrawSprite(Common_ss, NLTK_ICON, 126, 10); //NLTK's Icon

    for (int i = 0; i < 2; i++)
    {
        DrawSprite(Editor_ss, BUTTON_MAIN, 20,  10+(50*i), nullptr, 1.15, 0.6);  //w = 80, h = 33
        DrawSprite(Editor_ss, BUTTON_MAIN, 220, 10+(50*i), nullptr, 1.15, 0.6);  //w = 80, h = 33
        ColumnText[i].Draw(); //Column 1 Text
        ColumnText[2+i].Draw(); //Column 2 Text
    }

    TownButton->Draw();
    AcreButton->Draw();
    PlayerButton->Draw();
    VillagerButton->Draw();
    PWPButton->Draw();
    IslandButton->Draw();
    MainStreetButton->Draw();
    AboutButton->Draw();

    for (int i = 0; i < 4; i++)
    {
        DrawSprite(Editor_ss, ButtonIcon[i], 39+(74*i), 114, GreenFilter); //Row 1 Icons
        DrawSprite(Editor_ss, ButtonIcon[4+i], 39+(74*i), 184, GreenFilter); //Row 2 Icons
        ButtonText[i].Draw(); //Row 1 Text
        ButtonText[i+4].Draw(); //Row 2 Text
    }

    C2D_SceneBegin(top);
    draw_centered_text(0, 400, 80, 0, 1.1, 1.1, COLOR_GREY, "Editor Main Menu!");
    input->DrawCursor();
    C3D_FrameEnd(0);
}

int Editor::Spawn_MainMenu(Save *saveFile)
{
    while (aptMainLoop())
    {
        checkIfCardInserted();

        Editor::Draw_MainMenu();
        input->RefreshInput();

        if (hidKeysDown() & KEY_START)
        {
            return MODE_EXIT;
        }

        else if (hidKeysDown() & KEY_B)
        {
            return MODE_MAINMENU;
        }

        if (input->IsActive(TownButton->GetActiveArea())) //Town Menu
            MsgDisp(top, "Town Menu Coming Soon!");

        else if (input->IsActive(AcreButton->GetActiveArea())) //Acres Menu
            Editor::Spawn_AcresMenu(saveFile);

        else if (input->IsActive(PlayerButton->GetActiveArea())) //Player Menu
            Editor::Spawn_PlayerMenu(saveFile);

        else if (input->IsActive(VillagerButton->GetActiveArea())) //Villagers Menu
            MsgDisp(top, "Villagers Menu Coming Soon!");

        else if (input->IsActive(PWPButton->GetActiveArea())) //Pwp Menu
            MsgDisp(top, "PWP Menu Coming Soon!");

        else if (input->IsActive(IslandButton->GetActiveArea())) //Island Menu
            MsgDisp(top, "Island Menu Coming Soon!");

        else if (input->IsActive(MainStreetButton->GetActiveArea())) //Main Street Menu
            Editor::Spawn_ShopsMenu(saveFile);

        else if (input->IsActive(AboutButton->GetActiveArea())) //About Menu
            spawn_about_menu();

        /* Menu Columns */
        else if (input->IsActive(OptionsButton->GetActiveArea())) //Options Column
            spawn_config_menu();

        else if (input->IsActive(GameSelectButton->GetActiveArea())) //Game Select Column
            return MODE_GAMESELECT;

        else if (input->IsActive(TownManagerButton->GetActiveArea())) //Town Manager Column
            return MODE_MANAGER;

        else if (input->IsActive(SaveButton->GetActiveArea())) //Save Column
        {
            if (SaveCheck())
            {
                if (saveFile->Commit(false))
                    MsgDisp(top, "Save Succeeded!");

                else
                    MsgDisp(top, "Save Failed!");
            }
        }
    }
    return 0;
}
