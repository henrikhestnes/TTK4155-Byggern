#include "menu.h"
#include "oled.h"


menu_node main_menu;
menu_node settings_menu;


void menu_init() {
    char* content[3] = {"New game", "Settings", "Quit"};
    main_menu.content = content;
    main_menu.length = 3;
    //main_menu.children = &settings_menu;
    //settings_menu.parent = &main_menu;
}


void menu_print(font_type type) {
    for (int i = 0; i < main_menu.length; i++) {
        oled_set_pos(i, 0);
        // oled_write_string(main_menu.content[i], type);
        printf("%s", main_menu.content[i]);
    }
}