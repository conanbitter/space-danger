#ifndef _APP_H_
#define _APP_H_

void appInit(const char* title, int scale);
void appFinish();
int appProcessEvents();
void appBeginRender();
void appEndRender();
void appPresent();

#define APP_MAIN(t, s)                 \
    int main(int argc, char* argv[]) { \
        appInit(t, s);                 \
        appBeginRender();              \
        setup();                       \
        appEndRender();                \
        while (appProcessEvents()) {   \
            appBeginRender();          \
            loop();                    \
            appEndRender();            \
            appPresent();              \
        }                              \
        appFinish();                   \
        return 0;                      \
    }

#endif