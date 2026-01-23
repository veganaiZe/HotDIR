#include <windows.h>
#include "hd.h"


int
main(int argc, const char * argv[])
{
    static struct console_info console_info = {
        0, 0, 0, 0, 0
    };
    static struct search_info search_info = {
        SORT_BY_NAME, "", "", DONT_CLEAR_SCREEN
    };

    get_console_info(&console_info);
    process_command_line(&search_info, argc, argv);
    if (search_info.should_clear_screen) { system("cls"); }
    if (strncmp(search_info.pattern, "/h", 2) == 0) {
        display_help(&console_info);
        return 0;
    }

/*    char search_path[MAX_PATH] = { 0 };*/
/*    char search_string[MAX_PATH] = { 0 };*/
/*    HANDLE search_handle = 0;*/

/*    WORD original_colors;*/

/*    original_colors = (WORD)console.colors;*/

/*    build_initial_search_string(search_path, search_string);*/
/*    process_command_line(argc,*/
/*                         argv,*/
/*                         'C',*/  /** search_drive */
/*                         search_path,*/
/*                         search_string);*/
/*    display_header(search_path);*/
/*    fixup_path(search_path);*/
/*    process_files(search_handle, search_path);*/

/*    display_footer();*/
/*    restore_console(original_colors);*/
/*    restore_console();*/
    return 0;
}
