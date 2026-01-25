/** HotDIR (clone) - Public Domain by veganaiZe
 *
 * Colorful file/folder listing at the command prompt.
 *
 * NO WARRANTY WHATSOEVER!
 *
 */
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>

#include "hd.h"

#define VERSION_STRING "0.6.4 (pre-release)"  /** <-- Increment just before release. */


/*HANDLE g_hConsole;*/
/*SHORT  g_console_width;*/
/*WORD   g_original_attributes;*/
/*char   g_search_drive   = 'C';*/     /** Pre-load with C: drive */
/*//char   g_search_string[MAX_PATH];
//char   g_search_path[MAX_PATH];*/

/** Console variables: */
/*CONSOLE_SCREEN_BUFFER_INFO
       g_screen_info_t;*/
/*WIN32_FIND_DATA
       g_file_data_t;*/
/*INT    g_console_height = 24;*/
/*//HANDLE g_search_handle;*/
/*SHORT  line_count = 3;*/  /** Preload w/ num lines in header */
/*DWORD  g_dwAttrib;*/

/** File variables */
/*char * file_ext       = NULL;*/    /** Current file's extension */
/*double  g_file_size      = -1.0;*/    /** Current file's size */
/*double  g_total_size     = 0.0;*/     /** Total of all listed file sizes */
/*double  g_total_consumed = 0.0;*/     /** Total actual/compressed disk usage */
/*int    g_file_counter   = 0;*/       /** Total listed file count */

/** Args to GetVolumeInformation() */
/*TCHAR  g_volume_name[MAX_PATH + 1] = { 0 };*/
/*char g_root_path[] = "x:\\";*/


int
append_horizontal_line(char string[], unsigned int console_width)
{
    (void) string;
    (void) console_width;
    /*//unsigned int i = 0;
    //SHORT console_width = csbi.srWindow.Right + 1;
    //const char horizontal_line_character[] = { (char)196, '\0' };*/
/*//
//    sprintf(glyph, "%c", 196);
//
//    for (i=0; i <= console_width; ++i) {
//        strcat(string, glyph);
//    }
//
//    strcat(string, "\n");*/
    return 0;
}


int
build_initial_search_string(struct search_info * search_info)
{
    DWORD result = GetCurrentDirectory(MAX_PATH, search_info->pattern);
    if (result == 0) {
        puts("Error getting current directory.");
        exit(1);
    }
    strncpy(search_info->path, search_info->pattern, MAX_PATH);
    strncat(search_info->path, "\\*.*", MAX_PATH);
    return 0;
}


char *
compact_size_with_suffix(double size_bytes, char * suffixed_size)
{
    if(size_bytes >= 1024)  /** KB */
        if((size_bytes /= 1024) >= 1024)  /** MB */
            if((size_bytes /= 1024) >= 1024)  /** GB */
                if((size_bytes /= 1024) >= 1024)  /** TB */
                    sprintf(suffixed_size, "%lu TB", (unsigned long) (size_bytes/1024LU));
                else sprintf(suffixed_size, "%u GB", (unsigned) size_bytes);
            else sprintf(suffixed_size, "%u MB", (unsigned) size_bytes);
        else sprintf(suffixed_size, "%u KB", (unsigned) size_bytes);
    else sprintf(suffixed_size, "%u B", (unsigned) size_bytes);

    return suffixed_size;
}


int
create_footer(char * footer_string, int console_width, char * root_path, char search_drive)
{
    (void) footer_string;
    (void) console_width;
    (void) root_path;
    (void) search_drive;



    return 0;
}


char *
create_horizontal_line(char result[], struct console_info * console_info)
{
    int i = 0;
    const char horizontal_line_character = (char) 196;

    /** Draw line in result string */
    for(i = 0; i < console_info->width; ++i) {
        result[i] = horizontal_line_character;
    }
    result[i] = '\0';

    return result;
}


int
display_footer(struct console_info * console_info, struct search_info * search_info)
{
    char line[8192] = { 0 };
    int file_count = 0;  /*TODO*/
    int total_consumed = 0;  /*TODO*/
    double total_size = 0;  /*TODO*/
    char volume_name_buffer[1024] = { 0 };

    FG_AQUA();
    create_horizontal_line(line, console_info);
    printf("%s", line);

    FG_LIGHT_AQUA();
    printf(" %6d", file_count);
    FG_LIGHT_GREEN();
    printf(" files, totaling ");
    FG_LIGHT_AQUA();

    if(total_size > 1023.0)  /** KB */
        if((total_size /= 1024.0) > 1023.0)  /** MB */
            if((total_size /= 1024.0) > 1023.0)  /** GB */
                if((total_size /= 1024.0) > 1023.0)  /** TB */
                    printf("%.1f TB", total_size);
                else printf("%.1f GB", total_size);
            else printf("%.1f MB", total_size);
        else printf("%.1f KB", total_size);
    else printf("%d B", (int) total_size);

    FG_LIGHT_GREEN(); printf(", consuming ");
    FG_LIGHT_AQUA();  printf("%d", (int) total_consumed);
    FG_LIGHT_GREEN(); puts(" bytes of disk space.");
    FG_LIGHT_AQUA();  printf(" %d", 0);
    FG_LIGHT_GREEN(); printf(" bytes available on Drive ");
    FG_LIGHT_AQUA();  printf("%c:", search_info->drive);
    FG_LIGHT_GREEN(); printf(" \t\t Volume label: ");

/*    g_root_path[0] = g_search_drive;*/
/*//  GetVolumeInformation(g_root_path, g_volume_name, ARRAYSIZE(g_volume_name), &serial_number, &max_component_length, &filesystem_flags, filesystem_name, ARRAYSIZE(filesystem_name));*/
    GetVolumeInformation(&search_info->drive, volume_name_buffer, ARRAYSIZE(volume_name_buffer), NULL, NULL, NULL, NULL, 0);

    FG_LIGHT_RED(); printf("%s\n", volume_name_buffer);
    return 0;
}


int
display_header(struct console_info * console_info, struct search_info * search_info)
{
    char line[8192] = { 0 };

    FG_BRIGHT_WHITE();
    puts("\nHD");
    FG_AQUA();
    printf("Path: %s\n", search_info->path);

    /** Draw horizontal line across screen */
    create_horizontal_line(line, console_info);
    printf("%s", line);

    return 0;
}


int
display_help(struct console_info * console_info)
{
    int i;

    FG_BRIGHT_WHITE(); puts("\nHD " VERSION_STRING);
    FG_AQUA(); puts("Public domain by veganaiZe");

    /** Draw ------------- */
    for (i = 0; i < console_info->width; i++) { putchar(196); }

    FG_PURPLE(); printf("\nClone of ");
    FG_YELLOW(); printf("HotDIR ");
    FG_PURPLE(); puts("by Tony Overfield and Robert Woeger");
    FG_AQUA();   puts("\nUsage:");
    FG_WHITE();  puts("\tHD [options] [drive:\\][path][search-string]");
    FG_AQUA();   puts("\nOptions:");
    FG_WHITE();  printf("\t/C ");
    FG_AQUA();   puts("- Clear Screen");
    FG_WHITE();  printf("\t/# ");
    FG_AQUA();   puts("- Number of Columns (2,4,6) (Default: 1)");
    FG_WHITE();  printf("\t/L ");
    FG_AQUA();   puts("- Left to Right Ordering (Default: Top to Bottom)");
    FG_WHITE();  printf("\t/E ");
    FG_AQUA();   puts("- Sort by Extension");
    FG_WHITE();  printf("\t/D ");
    FG_AQUA();   puts("- Sort by Date");
    FG_WHITE();  printf("\t/S ");
    FG_AQUA();   puts("- Sort by Size");

    return 0;
}


int
fixup_path(struct search_info * search_info)
{
    /** Contents of directory (w/o trailing backslash) */
    DWORD attributes = GetFileAttributes((LPCTSTR) search_info->path);

    /** Valid directory ? */
    if (attributes != INVALID_FILE_ATTRIBUTES
            && (attributes & FILE_ATTRIBUTE_DIRECTORY)) {
        /** Append backslash & wildcard pattern */
        strcat(search_info->path, "\\*.*");
    }

    return 0;
}


struct console_info *
get_console_info(struct console_info * p_console_info)
{
    CONSOLE_SCREEN_BUFFER_INFO console_screen_buffer_info;
    p_console_info->console_handle = GetStdHandle(STD_OUTPUT_HANDLE);
/*    console_info->console_handle = GetStdHandle(STD_OUTPUT_HANDLE);*/
    GetConsoleScreenBufferInfo(p_console_info->console_handle,
                               &console_screen_buffer_info);

    /** Save console colors */
/*    g_original_attributes = */
    p_console_info->colors = p_console_info->colors_original =
            console_screen_buffer_info.wAttributes;
/*    p_console_info->colors = g_screen_info_t.wAttributes;*/

    /** Get console width */
/*    g_console_width = console_screen_buffer_info.srWindow.Right;*/
    p_console_info->width = console_screen_buffer_info.srWindow.Right + 1;

    /** Get console height */
/*    g_console_height = */
    p_console_info->height =
            console_screen_buffer_info.srWindow.Bottom
            - console_screen_buffer_info.srWindow.Top;
/*    p_console_info->height =
            g_screen_info_t.srWindow.Bottom - g_screen_info_t.srWindow.Top;*/

    return p_console_info;
}


int
get_console_width(void)
{
    HANDLE console_output_handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO console_screen_buffer_info;
    GetConsoleScreenBufferInfo(console_output_handle,
                               &console_screen_buffer_info);

    return console_screen_buffer_info.srWindow.Right + 1;
}


int
process_command_line(struct search_info * search_info, int argc, const char * argv[])
{
    while (--argc > 0) {
        if (*(argv[argc]) == '/') {
            switch ((int) *(argv[argc]+1)) {
                case 'h' : case 'H' : case '?':
                    strcpy(search_info->pattern, "/h");
                    break;
                case 'c' : case 'C':
                    search_info->should_clear_screen = CLEAR_SCREEN;
                    break;
                case 'n' : case 'N' :
                    puts("\nSORT_NAME -- not implemented (default)");
                    break;
                case 'e' : case 'E' :
                    puts("\nSORT_EXT -- not implemented");
                    break;
                case 'd' : case 'D' :
                    puts("\nSORT_DATE -- not implemented");
                    break;
                case 's' : case 'S' :
                    puts("\nSORT_SIZE -- not implemented");
                    break;
            }
        /** Process any drive, folder, and file arguments */
        } else {
            /** Drive indicator ? */
            if (strchr(argv[argc], ':') != NULL) {
               /** Get current drive letter */
               search_info->drive = (char) toupper(*(strchr(argv[argc], ':')-1));
               /** Drop drive letter */
               argv[argc] = argv[argc] + 2;
            } else {
               /** Fallback to current drive letter */
               search_info->drive = *search_info->pattern;
            }

            /** Drop drive letter no matter what */
            strcpy(search_info->pattern, search_info->pattern + 2);

            /** Arg has more than just drive letter ? */
            if (argv[argc][0]) {
                if (argv[argc][0] != '\\') {
                    sprintf(search_info->path, "%c:%s\\%s", search_info->drive,
                            search_info->pattern, argv[argc]);
                } else {
                    sprintf(search_info->path, "%c:%s", search_info->drive, argv[argc]);
                }
            } else {
                sprintf(search_info->path, "%c:\\", search_info->drive);
            }

            if (search_info->path[strlen(search_info->path)-1] == '\\') {
                strcat(search_info->path, "*.*");
            }
        }  /** End if */
    }  /** End while */

    return 0;
}


/** Returns file count */
int
process_files(struct console_info * console_info,
              struct search_info * search_info)
{
    int i = 0;
    int file_count = 0;
    SHORT  line_count = 3;  /** Preload w/ num lines in header */
    double file_size = 0.0;
    double total_size = 0.0;
    char * file_ext;
    char * search_path = search_info->path;
    CONSOLE_SCREEN_BUFFER_INFO console_screen_buffer_info;
    WORD attributes = 0;
    LPWIN32_FIND_DATA lpFindFileData = NULL;
    HANDLE search_handle = FindFirstFile((LPCTSTR) search_path, lpFindFileData);

    if (search_handle == INVALID_HANDLE_VALUE) {
        puts("\nNo file or folder found.");
        restore_console(console_info);
        return -1;
    }
/*//    else if (search_handle == ERROR_FILE_NOT_FOUND) {
//        puts("\nNo file or folder found.");
//
//        restore_console();
//        return -1;
//    }*/

    do {
        /** File is directory ? */
        if (lpFindFileData->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            FG_LIGHT_PURPLE();
        } else {
            ++file_count;

            /** Get file extension */
            file_ext = strrchr(lpFindFileData->cFileName, '.');

            /** Convert file extension to lowercase */
            if (file_ext != NULL) {
                for (i = 0; file_ext[i]; i++) {
                    file_ext[i] = (char) tolower(file_ext[i]);
                }

                /** Set color based on file extension */
                if (strcmp(file_ext, ".exe") == 0 || strcmp(file_ext, ".msi") == 0 )
                    FG_LIGHT_AQUA();
                else if(strcmp(file_ext, ".txt") == 0 || strcmp(file_ext, ".doc") == 0 || strcmp(file_ext, ".c") == 0
                            || strcmp(file_ext, ".rtf") == 0 || strcmp(file_ext, ".cc") == 0 || strcmp(file_ext, ".asm") == 0
                            || strcmp(file_ext, ".docx") == 0 || strcmp(file_ext, ".xml") == 0 || strcmp(file_ext, ".odt") == 0
                            || strcmp(file_ext, ".fodt") == 0 || strcmp(file_ext, ".ods") == 0 || strcmp(file_ext, ".fods") == 0
                            || strcmp(file_ext, ".odp") == 0 || strcmp(file_ext, ".fodp") == 0 || strcmp(file_ext, ".odg") == 0
                            || strcmp(file_ext, ".fodg") == 0 || strcmp(file_ext, ".odf") == 0 || strcmp(file_ext, ".pub") == 0
                            || strcmp(file_ext, ".ppt") == 0 || strcmp(file_ext, ".ott") == 0 || strcmp(file_ext, ".sxw") == 0
                            || strcmp(file_ext, ".stw") == 0 || strcmp(file_ext, ".docm") == 0 || strcmp(file_ext, ".dotx") == 0
                            || strcmp(file_ext, ".dotm") == 0 || strcmp(file_ext, ".dot") == 0 || strcmp(file_ext, ".wps") == 0
                            || strcmp(file_ext, ".wpd") == 0 || strcmp(file_ext, ".lwp") == 0 || strcmp(file_ext, ".htm") == 0
                            || strcmp(file_ext, ".html") == 0 || strcmp(file_ext, ".xhtml") == 0 || strcmp(file_ext, ".css") == 0
                            || strcmp(file_ext, ".abw") == 0 || strcmp(file_ext, ".zabw") == 0 || strcmp(file_ext, ".cwk") == 0
                            || strcmp(file_ext, ".pdb") == 0 || strcmp(file_ext, ".mw") == 0 || strcmp(file_ext, ".mcw") == 0
                            || strcmp(file_ext, ".ots") == 0 || strcmp(file_ext, ".sxc") == 0 || strcmp(file_ext, ".stc") == 0
                            || strcmp(file_ext, ".xls") == 0 || strcmp(file_ext, ".xlsx") == 0 || strcmp(file_ext, ".xlsm") == 0
                            || strcmp(file_ext, ".xlt") == 0 || strcmp(file_ext, ".xltx") == 0 || strcmp(file_ext, ".xltm") == 0
                            || strcmp(file_ext, ".pdf") == 0 || strcmp(file_ext, ".ps") == 0 || strcmp(file_ext, ".wdb") == 0
                            || strcmp(file_ext, ".xlc") == 0 || strcmp(file_ext, ".xlm") == 0 || strcmp(file_ext, ".xlw") == 0
                            || strcmp(file_ext, ".dif") == 0 || strcmp(file_ext, ".dbf") == 0 || strcmp(file_ext, ".wb2") == 0
                            || strcmp(file_ext, ".wk1") == 0 || strcmp(file_ext, ".wks") == 0 || strcmp(file_ext, ".123") == 0
                            || strcmp(file_ext, ".pps") == 0 || strcmp(file_ext, ".ouf") == 0 || strcmp(file_ext, ".uop") == 0
                            || strcmp(file_ext, ".sxi") == 0 || strcmp(file_ext, ".sti") == 0 || strcmp(file_ext, ".sxd") == 0
                            || strcmp(file_ext, ".potm") == 0 || strcmp(file_ext, ".potx") == 0 || strcmp(file_ext, ".pptx") == 0
                            || strcmp(file_ext, ".pptm") == 0 || strcmp(file_ext, ".ppsx") == 0 || strcmp(file_ext, ".key") == 0
                            || strcmp(file_ext, ".wpg") == 0 || strcmp(file_ext, ".dxf") == 0 || strcmp(file_ext, ".blend") == 0
                            || strcmp(file_ext, ".eps") == 0 || strcmp(file_ext, ".pm") == 0 || strcmp(file_ext, ".pm6") == 0
                            || strcmp(file_ext, ".pm65") == 0 || strcmp(file_ext, ".pmd") == 0 || strcmp(file_ext, ".log") == 0
                            || strcmp(file_ext, ".tex") == 0 || strcmp(file_ext, ".pages") == 0 || strcmp(file_ext, ".msg") == 0
                            || strcmp(file_ext, ".csv") == 0 || strcmp(file_ext, ".srt") == 0 || strcmp(file_ext, ".3ds") == 0
                            || strcmp(file_ext, ".3dm") == 0 || strcmp(file_ext, ".max") == 0 || strcmp(file_ext, ".indd") == 0
                            || strcmp(file_ext, ".pct") == 0 || strcmp(file_ext, ".xlr") == 0 || strcmp(file_ext, ".chm") == 0
                            || strcmp(file_ext, ".hlp") == 0 || strcmp(file_ext, ".jsp") == 0 || strcmp(file_ext, ".asp") == 0
                            || strcmp(file_ext, ".aspx") == 0 || strcmp(file_ext, ".csr") == 0 || strcmp(file_ext, ".rss") == 0
                            || strcmp(file_ext, ".h") == 0 || strcmp(file_ext, ".a") == 0 || strcmp(file_ext, ".cxx") == 0
                            || strcmp(file_ext, ".hxx") == 0 || strcmp(file_ext, ".xps") == 0 || strcmp(file_ext, ".oxps") == 0 )
                    FG_BRIGHT_WHITE();
                else if(strcmp(file_ext, ".bat") == 0 || strcmp(file_ext, ".cmd") == 0 || strcmp(file_ext, ".btm") == 0)
                    FG_LIGHT_RED();
                else if(strcmp(file_ext, ".com") == 0 || strcmp(file_ext, ".msc") == 0 )
                    FG_LIGHT_GREEN();
                else if(strcmp(file_ext, ".bas") == 0 || strcmp(file_ext, ".pas") == 0 || strcmp(file_ext, ".js") == 0
                            || strcmp(file_ext, ".jse") == 0 || strcmp(file_ext, ".vbs") == 0 || strcmp(file_ext, ".vbe") == 0
                            || strcmp(file_ext, ".wsf") == 0 || strcmp(file_ext, ".php") == 0 || strcmp(file_ext, ".py") == 0
                            || strcmp(file_ext, ".pl") == 0 || strcmp(file_ext, ".rb") == 0 || strcmp(file_ext, ".xsl") == 0
                            || strcmp(file_ext, ".tcl") == 0 || strcmp(file_ext, ".wsh") == 0)
                    FG_GREEN();
                else if(strcmp(file_ext, ".mp3") == 0 || strcmp(file_ext, ".mpg") == 0 || strcmp(file_ext, ".mpeg") == 0
                            || strcmp(file_ext, ".jpg") == 0 || strcmp(file_ext, ".jpeg") == 0 || strcmp(file_ext, ".gif") == 0
                            || strcmp(file_ext, ".png") == 0 || strcmp(file_ext, ".tif") == 0 || strcmp(file_ext, ".tiff") == 0
                            || strcmp(file_ext, ".psd") == 0 || strcmp(file_ext, ".xcf") == 0 || strcmp(file_ext, ".svg") == 0
                            || strcmp(file_ext, ".mp4") == 0 || strcmp(file_ext, ".mkv") == 0 || strcmp(file_ext, ".avi") == 0
                            || strcmp(file_ext, ".mov") == 0 || strcmp(file_ext, ".pcx") == 0 || strcmp(file_ext, ".wav") == 0
                            || strcmp(file_ext, ".aif") == 0 || strcmp(file_ext, ".aiff") == 0 || strcmp(file_ext, ".emf") == 0
                            || strcmp(file_ext, ".ico") == 0 || strcmp(file_ext, ".xpm") == 0 || strcmp(file_ext, ".jpe") == 0
                            || strcmp(file_ext, ".wmf") == 0 || strcmp(file_ext, ".lmb") == 0 || strcmp(file_ext, ".bmp") == 0
                            || strcmp(file_ext, ".tga") == 0 || strcmp(file_ext, ".xbm") == 0 || strcmp(file_ext, ".pnm") == 0
                            || strcmp(file_ext, ".pbm") == 0 || strcmp(file_ext, ".pgm") == 0 || strcmp(file_ext, ".ff") == 0
                            || strcmp(file_ext, ".ppm") == 0 || strcmp(file_ext, ".mng") == 0 || strcmp(file_ext, ".cur") == 0
                            || strcmp(file_ext, ".ani") == 0 || strcmp(file_ext, ".svgz") == 0 || strcmp(file_ext, ".ai") == 0
                            || strcmp(file_ext, ".flac") == 0 || strcmp(file_ext, ".ogg") == 0 || strcmp(file_ext, ".ogv") == 0
                            || strcmp(file_ext, ".oga") == 0 || strcmp(file_ext, ".asx") == 0 || strcmp(file_ext, ".wm") == 0
                            || strcmp(file_ext, ".wma") == 0 || strcmp(file_ext, ".wmx") == 0 || strcmp(file_ext, ".m3u") == 0
                            || strcmp(file_ext, ".aac") == 0 || strcmp(file_ext, ".asf") == 0 || strcmp(file_ext, ".wmv") == 0
                            || strcmp(file_ext, ".m2ts") == 0 || strcmp(file_ext, ".m2t") == 0 || strcmp(file_ext, ".qt") == 0
                            || strcmp(file_ext, ".wtv") == 0 || strcmp(file_ext, ".dvr-ms") == 0 || strcmp(file_ext, ".m4v") == 0
                            || strcmp(file_ext, ".mpe") == 0 || strcmp(file_ext, ".m1v") == 0 || strcmp(file_ext, ".mp2") == 0
                            || strcmp(file_ext, ".mpv2") == 0 || strcmp(file_ext, ".mod") == 0 || strcmp(file_ext, ".vob") == 0
                            || strcmp(file_ext, ".voc") == 0 || strcmp(file_ext, ".wdp") == 0 || strcmp(file_ext, ".raw") == 0
                            || strcmp(file_ext, ".hdp") == 0 || strcmp(file_ext, ".flv") == 0 || strcmp(file_ext, ".mid") == 0
                            || strcmp(file_ext, ".mpa") == 0 || strcmp(file_ext, ".m4a") == 0 || strcmp(file_ext, ".iff") == 0
                            || strcmp(file_ext, ".3gp") == 0 || strcmp(file_ext, ".3g2") == 0 || strcmp(file_ext, ".m4v") == 0
                            || strcmp(file_ext, ".rm") == 0 || strcmp(file_ext, ".ram") == 0 || strcmp(file_ext, ".swf") == 0
                            || strcmp(file_ext, ".vob") == 0 || strcmp(file_ext, ".pspimge") == 0 || strcmp(file_ext, ".thm") == 0
                            || strcmp(file_ext, ".yuv") == 0 || strcmp(file_ext, ".divx") == 0 || strcmp(file_ext, ".m4p") == 0
                            || strcmp(file_ext, ".mts") == 0 || strcmp(file_ext, ".pam") == 0)
                    FG_LIGHT_YELLOW();
                else if( strcmp(file_ext, ".7z") == 0 || strcmp(file_ext, ".zip") == 0 || strcmp(file_ext, ".gz") == 0
                            || strcmp(file_ext, ".tar") == 0 || strcmp(file_ext, ".bz2") == 0 || strcmp(file_ext, ".rar") == 0
                            || strcmp(file_ext, ".arc") == 0 || strcmp(file_ext, ".devpak") == 0 || strcmp(file_ext, ".xz") == 0
                            || strcmp(file_ext, ".lzma") == 0 || strcmp(file_ext, ".iso") == 0 || strcmp(file_ext, ".lz") == 0
                            || strcmp(file_ext, ".lzo") == 0 || strcmp(file_ext, ".rz") == 0 || strcmp(file_ext, ".sz") == 0
                            || strcmp(file_ext, ".z") == 0 || strcmp(file_ext, ".Z") == 0 || strcmp(file_ext, ".arj") == 0
                            || strcmp(file_ext, ".b1") == 0 || strcmp(file_ext, ".cab") == 0 || strcmp(file_ext, ".cfs") == 0
                            || strcmp(file_ext, ".dmg") == 0 || strcmp(file_ext, ".ear") == 0 || strcmp(file_ext, ".jar") == 0
                            || strcmp(file_ext, ".lzh") == 0 || strcmp(file_ext, ".lha") == 0 || strcmp(file_ext, ".kgb") == 0
                            || strcmp(file_ext, ".lzx") == 0 || strcmp(file_ext, ".pea") == 0 || strcmp(file_ext, ".partimg") == 0
                            || strcmp(file_ext, ".pim") == 0 || strcmp(file_ext, ".sda") == 0 || strcmp(file_ext, ".sea") == 0
                            || strcmp(file_ext, ".sfx") == 0 || strcmp(file_ext, ".shk") == 0 || strcmp(file_ext, ".sit") == 0
                            || strcmp(file_ext, ".sitx") == 0 || strcmp(file_ext, ".sqx") == 0 || strcmp(file_ext, ".tgz") == 0
                            || strcmp(file_ext, ".tbz2") == 0 || strcmp(file_ext, ".tlz") == 0 || strcmp(file_ext, ".war") == 0
                            || strcmp(file_ext, ".har") == 0 || strcmp(file_ext, ".wim") == 0 || strcmp(file_ext, ".xp3") == 0
                            || strcmp(file_ext, ".yz1") == 0 || strcmp(file_ext, ".zipx") == 0 || strcmp(file_ext, ".zoo") == 0
                            || strcmp(file_ext, ".zpaq") == 0 || strcmp(file_ext, ".zz") == 0 ||strcmp(file_ext, ".ecc") == 0
                            || strcmp(file_ext, ".par") == 0 || strcmp(file_ext, ".par2") == 0 || strcmp(file_ext, ".img") == 0
                            || strcmp(file_ext, ".hqx") == 0 || strcmp(file_ext, ".hcx") == 0 || strcmp(file_ext, ".hex") == 0
                            || strcmp(file_ext, ".deb") == 0 || strcmp(file_ext, ".rpm") == 0 || strcmp(file_ext, ".mdf") == 0
                            || strcmp(file_ext, ".cue") == 0 || strcmp(file_ext, ".bin") == 0 || strcmp(file_ext, ".apk") == 0)
                    FG_YELLOW();
                else FG_GRAY();  /** (everything else) */
            } else FG_GRAY();  /** (no extension) */
        } /** First if/else */

        /** Pause if console screen is full */
        if(++line_count == console_info->height) {
            line_count = 0;
            GetConsoleScreenBufferInfo(console_info->console_handle, &console_screen_buffer_info);
            attributes = console_screen_buffer_info.wAttributes;
            FG_GRAY(); system("PAUSE");
            /** Restore Color */
            SetConsoleTextAttribute(console_info->console_handle, attributes);
        }

        /** "DARK FG_RED" for hidden files */
        if(lpFindFileData->dwFileAttributes & FILE_ATTRIBUTE_HIDDEN) {
            FG_RED();
        }

        /** Display file name */
        printf("%-*s", console_info->width / 2 - 8, lpFindFileData->cFileName);
/*        //printf("%s\n", file_ext);*/

        /** Display <dir> for directories */
        if(lpFindFileData->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            printf("  <dir> ");

        /** Otherwise display file size */
        } else {
            file_size = (double) (lpFindFileData->nFileSizeHigh * MAXDWORD
                                    + lpFindFileData->nFileSizeLow);
            total_size += file_size;
            FG_GRAY();

            if(file_size > 1023)  /** KB */
                if((file_size /= 1024.0) > 1023)  /** MB */
                    if((file_size /= 1024.0) > 1023)  /** GB */
                        if((file_size /= 1024.0) > 1023)  /** TB */
                            printf("% 5.1f TB", file_size);
                        else printf("% 5.1f GB", file_size);
                    else printf("% 5.1f MB", file_size);
                else printf("% 5.1f KB", file_size);
            else printf("% 5d B ", (int) file_size);

/*            //g_total_consumed += (float)((*lpFileSizeHigh * (MAXDWORD+1)) + GetCompressedFileSize(g_file_data_t.cFileName, lpFileSizeHigh));*/
        }

        FG_AQUA(); printf("\263 \n");  /** Print | */
    } while( FindNextFile(search_handle, lpFindFileData) != 0 );
    /** End do */

    FindClose(search_handle);
    (void) total_size;
    return file_count;
}


int
restore_console(struct console_info * console_info)
{
    SetConsoleTextAttribute(console_info->console_handle, (WORD) (console_info->colors_original));
    return 0;
}
