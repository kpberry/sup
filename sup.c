#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>

int get_terminal_col_count() {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return w.ws_col;
}

#ifdef WIN32
#include <windows.h>
#elif _POSIX_C_SOURCE >= 199309L
#include <time.h>   // for nanosleep
#else
#include <unistd.h> // for usleep
#endif

void sleep_ms(int milliseconds) // cross-platform sleep function
{
#ifdef WIN32
    Sleep(milliseconds);
#elif _POSIX_C_SOURCE >= 199309L
    struct timespec ts;
    ts.tv_sec = milliseconds / 1000;
    ts.tv_nsec = (milliseconds % 1000) * 1000000;
    nanosleep(&ts, NULL);
#else
    usleep(milliseconds * 1000);
#endif
}

size_t charlen(const char* text) {
    size_t i = 0;
    for (const unsigned char* c = text; *c != '\0'; c++) {
        if ((*c & 0x80) == 0x00 || (*c & 0xE0) == 0xC0 || (*c & 0xF0) == 0xE0) {
            i += 1;
        } else if ((*c & 0xC0) != 0x80) {
            return -1;
        }
    }
    return i;
}

void tfill(const char* text, int delay) {
    // TODO make this work with unicode; issues with difference
    //      between num bytes and num graphemes
    int col_count = get_terminal_col_count();
    size_t text_bytes = strlen(text);
    int num_texts = col_count / text_bytes;
    int buf_len = num_texts * text_bytes;
    char* cur_text = malloc(buf_len * sizeof(char));
    for (int num_drawn = 0; num_drawn < num_texts; num_drawn++) {
        int fixed = num_drawn * text_bytes;
        for (int right_edge = 0; right_edge < buf_len - fixed - text_bytes; right_edge++) {
            for (int i = 0; i < buf_len - fixed - 1; i++) {
                if (i < right_edge) {
                    cur_text[i] = '~';
                } else {
                    cur_text[i] = text[i - right_edge];
                }
            }
            printf("\r%s", cur_text);
            fflush(stdout);
            sleep_ms(delay);
        }
    }
    free(cur_text);
}

int main(int argc, char** argv) {
    static char* t = "|Test!|";
    static char* leonard = "( ͡° ͜ʖ ͡°)";
    static char* sup_son = "¯\\_(ツ)_/¯";
    printf("\e[?25l");
    tfill(t, 10);
    printf("\n\e[?25h");
    return 0;
}