#ifndef HD_H
#define HD_H

#ifndef ARRAYSIZE
    #define ARRAYSIZE(a) (sizeof(a) / sizeof(*(a)))
#endif

#define BLACK 0
#define BLUE 1
#define GREEN 2
#define AQUA 3
#define RED 4
#define PURPLE 5
#define YELLOW 6
#define WHITE 7
#define GRAY 8
#define LIGHT_BLUE 9
#define LIGHT_GREEN 10
#define LIGHT_AQUA 11
#define LIGHT_RED 12
#define LIGHT_PURPLE 13
#define LIGHT_YELLOW 14
#define BRIGHT_WHITE 15

#define FG_GREEN()        SetConsoleTextAttribute(console_info->console_handle, 0x02)
#define FG_AQUA()         SetConsoleTextAttribute(console_info->console_handle, 0x03)
#define FG_RED()          SetConsoleTextAttribute(console_info->console_handle, 0x04)
#define FG_PURPLE()       SetConsoleTextAttribute(console_info->console_handle, 0x05)
#define FG_YELLOW()       SetConsoleTextAttribute(console_info->console_handle, 0x06)
#define FG_WHITE()        SetConsoleTextAttribute(console_info->console_handle, 0x07)
#define FG_GRAY()         SetConsoleTextAttribute(console_info->console_handle, 0x08)
#define FG_LIGHT_GREEN()  SetConsoleTextAttribute(console_info->console_handle, 0x0A)
#define FG_LIGHT_AQUA()   SetConsoleTextAttribute(console_info->console_handle, 0x0B)
#define FG_LIGHT_RED()    SetConsoleTextAttribute(console_info->console_handle, 0x0C)
#define FG_LIGHT_PURPLE() SetConsoleTextAttribute(console_info->console_handle, 0x0D)
#define FG_LIGHT_YELLOW() SetConsoleTextAttribute(console_info->console_handle, 0x0E)
#define FG_BRIGHT_WHITE() SetConsoleTextAttribute(console_info->console_handle, 0x0F)

#define AQUA_FG "\033[96;40m"
#define RESET_COLORS "\033[0m"


enum sort_by {
    SORT_BY_NAME,
    SORT_BY_EXTENSION,
    SORT_BY_DATE,
    SORT_BY_SIZE
};


enum should_clear_screen {
    DONT_CLEAR_SCREEN,
    CLEAR_SCREEN
};


struct console_info {
        HANDLE console_handle;
        int colors;
        int colors_original;
        int width;
        int height;
};


struct search_info {
    enum sort_by sort_by;
    char path[4096];
    char pattern[4096];
    enum should_clear_screen should_clear_screen;
};


int append_horizontal_line(char[], unsigned int);
int build_initial_search_string(char * search_path, char * search_string);
char * compact_size_with_suffix(double, char *);
int create_footer(char *, int, char *, char);
char * create_horizontal_line(char *,  struct console_info *);
int display_footer(struct console_info *);
int display_header(struct console_info *, struct search_info *);
int display_help(struct console_info *);
int fixup_path(char * search_path);
struct console_info * get_console_info(struct console_info *);
int get_console_width(void);
/*int process_command_line(int argc, char * argv[], char search_drive, char * search_path, char * search_string);*/
int process_command_line(struct search_info *, int argc, const char * argv[]);
int process_files(struct console_info *, HANDLE search_handle, char * search_path);
int restore_console(void);

#endif  /** HD_H */
