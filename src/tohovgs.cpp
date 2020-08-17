/*
東方BGM on VGS for コマンドライン (macOS)

MIT License

Copyright (c) 2020 Yoji Suzuki

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "sound-ios.h"
#include "vgsdec.h"
#include "vgsmml.h"
#include <IOKit/hid/IOHIDManager.h>
#include <ctype.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct PlayList {
    char path[1024];
    int loop;
    char title[1024];
    struct PlayList* next;
};

static struct PlayList* fs_listHead;
static struct PlayList* fs_listTail;
static void* fs_sound;
static void* fs_vgsdec;

static void trimstring(char* src)
{
    int i, j;
    int len;
    for (i = 0; ' ' == src[i]; i++)
        ;
    if (i) {
        for (j = 0; src[i] != '\0'; j++, i++) {
            src[j] = src[i];
        }
        src[j] = '\0';
    }
    for (len = (int)strlen(src) - 1; 0 <= len && ' ' == src[len]; len--) {
        src[len] = '\0';
    }
}

static int parsePlayList(const char* filename)
{
    char line[4096];
    FILE* fp = fopen(filename, "r");
    if (!fp) {
        puts("File open error");
        return -1;
    }
    while (fgets(line, sizeof(line), fp)) {
        char* crlf = strchr(line, '\r');
        if (crlf) *crlf = '\0';
        crlf = strchr(line, '\n');
        if (crlf) *crlf = '\0';
        trimstring(line);
        if (line[0] == '#' || line[0] == '\0') continue;
        char* loop = strchr(line, ',');
        if (!loop) continue;
        *loop = '\0';
        loop++;
        char* title = strchr(loop, ',');
        if (!title) continue;
        *title = '\0';
        title++;
        trimstring(line);
        trimstring(loop);
        trimstring(title);
        struct PlayList* newRec = (struct PlayList*)malloc(sizeof(struct PlayList));
        if (!newRec) {
            puts("No memory");
            fclose(fp);
            return -1;
        }
        memset(newRec, 0, sizeof(struct PlayList));
        strncpy(newRec->path, line, sizeof(newRec->path) - 1);
        strncpy(newRec->title, title, sizeof(newRec->title) - 1);
        newRec->loop = atoi(loop);
        if (fs_listTail) {
            fs_listTail->next = newRec;
            fs_listTail = newRec;
        } else {
            fs_listHead = newRec;
            fs_listTail = newRec;
        }
    }
    if (!fs_listHead) {
        puts("No soung data.");
        return -1;
    }
    return 0;
}

static volatile bool playThreadFlag;
static volatile int playThreadLoop;
static volatile CFRunLoopRef playThreadRL;
void* playThread(void* arg)
{
    short sbuf[441];
    bool fadeout = 0 < playThreadLoop;
    while (playThreadFlag) {
        vgsdec_execute(fs_vgsdec, sbuf, sizeof(sbuf));
        sound_enqueue(fs_sound, sbuf, sizeof(sbuf));
        while (playThreadFlag && 4096 < sound_buffer_left(fs_sound)) {
            usleep(1000);
        }
        if (playThreadFlag) {
            if (fadeout && playThreadLoop == vgsdec_get_value(fs_vgsdec, VGSDEC_REG_LOOP_COUNT)) {
                // Start fadeout
                vgsdec_set_value(fs_vgsdec, VGSDEC_REG_FADEOUT, 1);
                fadeout = false;
            }
            if (0 == vgsdec_get_value(fs_vgsdec, VGSDEC_REG_PLAYING)) {
                // HALT playing
                playThreadFlag = false;
                CFRunLoopStop(playThreadRL);
                break;
            }
        }
    }
    return NULL;
}

static void play(struct PlayList* list)
{
    printf("Playing %s ... ", list->title);
    VgsMmlErrorInfo err;
    VgsBgmData* bgm = vgsmml_compile_from_file(list->path, &err);
    if (!bgm) {
        puts("MML compile error");
        return;
    }
    if (vgsdec_load_bgm_from_memory(fs_vgsdec, bgm->data, bgm->size)) {
        puts("Decode error");
        return;
    }
    vgsmml_free_bgm_data(bgm);
    puts("OK");
    pthread_t tid;
    playThreadFlag = true;
    playThreadLoop = list->loop;
    playThreadRL = CFRunLoopGetCurrent();
    pthread_create(&tid, NULL, playThread, NULL);
    struct sched_param param;
    memset(&param, 0, sizeof(param));
    param.sched_priority = 46;
    pthread_setschedparam(tid, SCHED_OTHER, &param);
    CFRunLoopRun(); // Wait for HALT playing
    playThreadFlag = false;
    pthread_join(tid, NULL);
}

int main(int argc, char* argv[])
{
    if (argc < 2) {
        puts("usage: tohovgs playlist.csv");
        return 1;
    }
    if (parsePlayList(argv[1])) return -1;
    fs_vgsdec = vgsdec_create_context();
    fs_sound = sound_create();

    struct PlayList* cursor = fs_listHead;
    while (cursor) {
        play(cursor);
        cursor = cursor->next;
    }

    sound_destroy(fs_sound);
    vgsdec_release_context(fs_vgsdec);
    struct PlayList* next;
    for (cursor = fs_listHead; cursor; cursor = next) {
        next = cursor->next;
        free(cursor);
    }
    return 0;
}
