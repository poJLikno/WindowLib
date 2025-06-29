#include <iostream>
#include <windows.h>
#include <thread>

#define WINDOWLIB_USE_MANIFEST
//#define WINDOWLIB_NO_CONSOLE

#include "WindowLib/Window.h"
#include "WindowLib/NormalFont.h"

int main(int argc, const char **argv) {
    int result = 0;

    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    try
    {
        Window wnd("TestApp", { CW_USEDEFAULT, CW_USEDEFAULT }, { 400, 300 });//, -1, WS_OVERLAPPED | WS_SYSMENU);
        std::unique_ptr<Window> wnd2;//("Русс класс", { CW_USEDEFAULT, CW_USEDEFAULT }, { 800, 600 });//, -1, WS_OVERLAPPED | WS_SYSMENU);
        std::unique_ptr<Button> b2;
        //wnd.SetWndText("Programm");

        wnd.SetWndText("Русский Язык ya!");
        wnd.EnableControlsDialogMessages(true);

        long long j = 0;

        //wnd.AddCallback("AsyncLoopCallback", [&j](void *ptr) {
        //  
        //  Window *wnd = GetControl(Window, ptr);
        //  wnd->SetWndText(std::string(std::to_string(j)).c_str());
        //  std::cout << "It's work!\n";
        //});

        Button btn("Русская кнопка ya!", { 100, 100 }, { 50, 25 });
        //Button btn("First button", { 100, 100 }, { 50, 25 });
        Button btn_t("Second button", { 350, 100 }, { 200, 100 });
        RadioButton radio_btn("Radio button 1", true, { 10, 10 }, { 100, 17 });
        RadioButton radio_btn_t("Radio button 2", false, { 10, 30 }, { 100, 17 });
        RadioButton radio_btn_u("Radio button 3", true, { 10, 50 }, { 100, 17 });
        RadioButton radio_btn_f("Radio button 4", false, { 10, 70 }, { 100, 17 });
        CheckBox chk_box("Check box 1", { 10, 100 }, { 100, 17 });
        ComboBox cmb_bx({ 100, 350 }, { 140, 200 });
        Label lbl("govnar_pes Рус", { 300, 350 }, { 140, 20 });
        Menu menu;
        Edit edit;

        // Button 1
        btn.AddCallback("MainCallback", [&j, &wnd2, &b2, &wnd/*, &lbl*/](void *ptr) {

            Button *btn = GetControl(Button, ptr);

            {
                wnd2 = std::unique_ptr<Window>(new Window("Русс класс", { 10, 200 }, { 200, 200 }));//, -1, WS_POPUP));
                wnd2->ShowWnd(false);
                wnd2->EnableControlsDialogMessages(true);

                auto size = wnd2->GetWndSize();
                b2 = std::unique_ptr<Button>(new Button("би 2", { size.first / 6, size.second / 6 }, { 100, 100 }));

                b2->AddCallback("MainCallback", [](void *ptr) {

                    Button *btn = GetControl(Button, ptr);

                    btn->SetWndText("Руссишь text!");
                });
                b2->AddCallback("ParentResizeCallback", [](void *ptr) {

                    Button *btn = GetControlForParentResize(Button, ptr);
                    GetMiscForParentResize(ptr);

                    std::unique_ptr<char[]> btn_text(btn->GetWndText(64));

                    if (strcmp(btn_text.get(), "би 2") != 0)
                    {
                        btn->SetWndText(std::to_string(new_parent_wnd_size.first).c_str());
                    }

                    btn->SetWndPos({ new_parent_wnd_size.first / 6, new_parent_wnd_size.second / 6 });
                });

                wnd2->AttachChildControl(b2.get());

                wnd2->SetWndParent(&wnd);

                wnd2->ShowWnd(true);
            }

            //lbl.SetWndText("");

            btn->SetWndText(std::to_string(j++).c_str());
            std::cout << "Button 1 was pressed!\n";
        });

        btn.AddCallback("ParentResizeCallback", [](void *ptr) {

            Button *btn = GetControlForParentResize(Button, ptr);
            GetMiscForParentResize(ptr);
            /*Expands to:
            * Window *parent_wnd = ...
            * const  &old_parent_wnd_size = ...
            * const  &new_parent_wnd_size = ...
            */

            if (parent_wnd == nullptr) {
                return;
            }
            btn->SetWndSize({ new_parent_wnd_size.first / 4, new_parent_wnd_size.second / 6 });
        });

        //Button 2
        btn_t.AddCallback("MainCallback", [&j](void *ptr) {

            Button *btn = GetControl(Button, ptr);

            btn->SetWndText(std::to_string(-(j++)).c_str());
            std::cout << "Button 2 was pressed!\n";
        });

        btn_t.AddCallback("ParentResizeCallback", [](void *ptr) {

            Button *btn = GetControlForParentResize(Button, ptr);
            GetMiscForParentResize(ptr);

            if (parent_wnd == nullptr) {
                return;
            }
            btn->SetWndPos({ new_parent_wnd_size.first / 4, new_parent_wnd_size.second / 6 });
        });

        /* RadioButton 1 */
        radio_btn.AddCallback("MainCallback", [&j, &btn](void *ptr) {

            RadioButton *rbtn = GetControl(RadioButton, ptr);
            /* Prevent false activation */
            if (rbtn->GetState())
            {
                std::cout << "RadioButton 1 was pressed!\n";

                btn.SetInputState(j % 2 ? false : true);
            }
        });

        /* RadioButton 2 */
        radio_btn_t.AddCallback("MainCallback", [&j, &radio_btn](void *ptr) {

            RadioButton *rbtn = GetControl(RadioButton, ptr);
            /* Prevent false activation */
            if (rbtn->GetState())
            {
                std::cout << (rbtn->GetState() ? "true - " : "\0") << "RadioButton 2 was pressed!\n";
                std::cout << (radio_btn.GetState() ? "true - " : "false - ") << "RadioButton 1\n";
                radio_btn.SetState(true);
                std::cout << (radio_btn.GetState() ? "true - " : "false - ") << "RadioButton 1\n";
            }
        });

        /* RadioButton 3 */
        radio_btn_u.AddCallback("MainCallback", [&j](void *ptr) {

            RadioButton *rbtn = GetControl(RadioButton, ptr);
            /* Prevent false activation */
            if (rbtn->GetState())
            {
                std::cout << "RadioButton 3 was pressed!\n";
            }
        });

        /* RadioButton 4 */
        radio_btn_f.AddCallback("MainCallback", [&j](void *ptr) {

            RadioButton *rbtn = GetControl(RadioButton, ptr);
            /* Prevent false activation */
            if (rbtn->GetState())
            {
                std::cout << "RadioButton 4 was pressed!\n";
            }
        });

        /* CheckBox 1 */
        chk_box.AddCallback("MainCallback", [&j](void *ptr) {

            CheckBox *box = GetControl(CheckBox, ptr);

            box->SetState(!box->GetState());
            std::cout << "CheckBox 1 was pressed!\n";
        });

        // ComboBox 1
        cmb_bx.AddCallback("MainCallback", [](void *ptr) {

            ComboBox *cmb_bx = GetControl(ComboBox, ptr);

            std::unique_ptr<char[]> str(cmb_bx->GetItem());

            std::cout << cmb_bx->GetItemId() << " |----| " << str.get() << '\n';
        });

        cmb_bx.AddCallback("ParentResizeCallback", [](void *ptr) {

            ComboBox *cmb_bx = GetControlForParentResize(ComboBox, ptr);
            GetMiscForParentResize(ptr);

            if (parent_wnd == nullptr) {
                return;
            }
            cmb_bx->SetWndSize({ new_parent_wnd_size.first / 4, new_parent_wnd_size.second / 6 });
            cmb_bx->SetWndPos({ new_parent_wnd_size.first / 2, new_parent_wnd_size.second / 4 });
        });

        // Label 1
        lbl.AddCallback("ParentResizeCallback", [](void *ptr) {

            Label *lbl = GetControlForParentResize(Label, ptr);
            GetMiscForParentResize(ptr);

            if (parent_wnd == nullptr) {
                return;
            }

            lbl->SetWndPos({ new_parent_wnd_size.first / 2, new_parent_wnd_size.second / 3 });
        });

        // Edit 1
        edit.AddCallback("MainCallback", [](void *ptr) {

            try
            {
                Edit *edit = GetControl(Edit, ptr);

                std::unique_ptr<char[]> str(edit->GetWndText(64));

                std::cout << str << '\n';
            }
            catch (const std::string &/*error*/)
            {
                std::cout << "None\n";
            }
        });

        edit.AddCallback("ParentResizeCallback", [](void *ptr) {

            Edit *edit = GetControlForParentResize(Edit, ptr);
            GetMiscForParentResize(ptr);

            if (parent_wnd == nullptr) {
                return;
            }

            edit->SetWndPos({ new_parent_wnd_size.first / 4, new_parent_wnd_size.second / 6 });
        });

        // Menu & menu points
        MenuPoint p_f("First");
        MenuPoint p_s("Second");
        p_f.AddCallback("MainCallback", [&p_s, &wnd](void *ptr) {

            MenuPoint *menu_point = GetControl(MenuPoint, ptr);

            p_s.SetState(!p_s.GetState());

            std::cout << "First is work!\n";
        });

        p_s.AddCallback("MainCallback", [&btn_t, &wnd, &j](void *ptr) {

            btn_t.ShowWnd(j % 2);

            std::cout << "Second is work!\n";
        });

        PopupMenu pop_s("Second popup");
        pop_s.AttachMenuPoint(&p_f);

        PopupMenu pop_f("First popup");
        pop_f.AttachMenuPoint(&p_s);
        pop_f.AppendSeparator();
        pop_f.AttachPopupMenu(&pop_s);

        menu.AttachMenuPoint(&p_f);
        menu.AttachPopupMenu(&pop_f);
        //menu.AttachMenuPoint(&p_t);
        // -----

        // Attach controls
        wnd.AttachChildControl(&btn);
        wnd.AttachChildControl(&btn_t);
        wnd.AttachChildControl(&radio_btn);
        wnd.AttachChildControl(&radio_btn_t);
        wnd.AttachChildControl(&radio_btn_u);
        wnd.AttachChildControl(&radio_btn_f);
        wnd.AttachChildControl(&chk_box);
        wnd.AttachChildControl(&cmb_bx);
        wnd.AttachChildControl(&lbl);
        wnd.AttachChildControl(&edit);
        wnd.AttachMenu(&menu);

        // Settings
        edit.SetWndText("Русский текст pozalusta");
        cmb_bx.AddItem("pososi 1");
        //cmb_bx.AddItem("pososi 2");
        cmb_bx.AddItem("Рус строчка!");
        cmb_bx.AddItem("pososi 3");
        cmb_bx.SelectItem(0);
        //cmb_bx.SetInputState(false);
        //btn.SetInputState(false);
        radio_btn.SetState(true);

        // Font
        NormalFont good_font;
        {
            good_font.SetFont(&btn);
            good_font.SetFont(&btn_t);
            good_font.SetFont(&radio_btn);
            good_font.SetFont(&radio_btn_t);
            good_font.SetFont(&radio_btn_u);
            good_font.SetFont(&radio_btn_f);
            good_font.SetFont(&chk_box);
            good_font.SetFont(&cmb_bx);
            good_font.SetFont(&lbl);
            good_font.SetFont(&edit);
        }

        // Show window
        wnd.ShowWnd(true);

        result = wnd.Run();
    }
    catch (const std::string &error)
    {
        int str_size = (int)error.length() + 1;
        wchar_t *w_error = new wchar_t[str_size] { 0 };
        MultiByteToWideChar(CP_UTF8, 0, error.c_str(), str_size, w_error, str_size);

        MessageBoxW(NULL, w_error, L"Error", MB_OK);

        delete[] w_error;
        w_error = nullptr;
    }

    // Run message loop
    return result;
}
