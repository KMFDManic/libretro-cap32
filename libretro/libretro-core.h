#ifndef LIBRETRO_CORE_H
#define LIBRETRO_CORE_H 1

#include <stdint.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

// DEVICE AMSTRAD
#define RETRO_DEVICE_AMSTRAD_KEYBOARD RETRO_DEVICE_SUBCLASS(RETRO_DEVICE_KEYBOARD, 0)
#define RETRO_DEVICE_AMSTRAD_JOYSTICK RETRO_DEVICE_SUBCLASS(RETRO_DEVICE_JOYPAD, 1)

#define PORTS_NUMBER 2
#define ID_PLAYER1 0
#define ID_PLAYER2 1

#define PADCFG_JOYSTICK 0
#define PADCFG_QAOP 1
#define PADCFG_INCENTIVE 2
#define PADCFG_JOYSTICK_2 3

extern unsigned amstrad_devices[ PORTS_NUMBER ];

#define CPC_SCREEN_WIDTH 384
#define CPC_SCREEN_HEIGHT 272

#define TEX_MAX_WIDTH CPC_SCREEN_WIDTH * 2
#define TEX_MAX_HEIGHT CPC_SCREEN_HEIGHT

// compile flags
#define NO_FLOPPY_SND
#define LOWRES
#define M16B // SCREEN 16BITS

#ifdef M16B
   #define PIXEL_RAW_DENSITY 2
   #define PIXEL_BYTES 1
   #define PIXEL_TYPE unsigned short
   #define PITCH 2
#else
   #define PIXEL_RAW_DENSITY 1
   #define PIXEL_BYTES 2
   #define PIXEL_TYPE unsigned int
   #define PITCH 4
#endif

#ifdef M16B
   #define RGB2COLOR(r, g, b)    ((b>>3) | ((g>>2)<<5) | ((r>>3)<<11))
   #define RGB2RED(colour)       (((colour>>11)<<3) & 0xFF)
   #define RGB2GREEN(colour)     (((colour>>5)<<2) & 0xFF)
   #define RGB2BLUE(colour)      ((colour<<3) & 0xFF)
   #define CURSOR_COLOR          0xCE79
#else
   #define RGB2COLOR(r, g, b)    (b | ((g << 8) | (r << 16)))
   #define RGB2RED(colour)       ((colour>>16) & 0xFF)
   #define RGB2GREEN(colour)     ((colour>>8) & 0xFF)
   #define RGB2BLUE(colour)      (colour & 0xFF)
   #define CURSOR_COLOR          0xCCCCCC
#endif

#define WINDOW_MAX_SIZE (TEX_MAX_WIDTH * TEX_MAX_HEIGHT)
#define EMULATION_INIT_AUTORUNDELAY 50

#ifdef LOWRES
#define SCREENMODE_STR " LO"
#define EMULATION_SCALE 1
#define EMULATION_SCREEN_WIDTH CPC_SCREEN_WIDTH
#define EMULATION_SCREEN_HEIGHT CPC_SCREEN_HEIGHT
#define CURSOR_MOVEMENT_X 2
#define CURSOR_MOVEMENT_Y 2
#else
#define SCREENMODE_STR " HI"
#define EMULATION_SCALE 2
#define EMULATION_SCREEN_WIDTH CPC_SCREEN_WIDTH * 2
#define EMULATION_SCREEN_HEIGHT CPC_SCREEN_HEIGHT
#define CURSOR_MOVEMENT_X 4
#define CURSOR_MOVEMENT_Y 2
#endif

//AUDIO
#define FRAME_PERIOD_MS        20.0 // check cap32.h
#define AUDIO_BYTES 2
#define AUDIO_CHANNELS 2
#define AUDIO_SAMPLE_SIZE 44100
#define AUDIO_BUFSIZE (AUDIO_SAMPLE_SIZE * FRAME_PERIOD_MS / 1000)

//LOG
#if  defined(__ANDROID__) || defined(ANDROID)
#include <android/log.h>
#define LOG_TAG "RetroArch.Frodo"
#define LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#else
#define LOGI printf
#endif

// BIT OPERATIONS - MACROS
#define BIT_SET(var, bit)    var  = 1 << bit
#define BIT_ADD(var, bit)    var |= 1 << bit
#define BIT_CLEAR(var, bit)  var &= ~(1 << bit)
#define BIT_CHECK(var, bit)  ((var >> bit) & 1)
#define BIT_TOGGLE(var, bit) var ^= 1 << bit

// COMPUTER/EMU STATUS
#define COMPUTER_OFF     0
#define COMPUTER_BOOTING 1
#define COMPUTER_READY   2
extern int emu_status;

#define STATUSBAR_HIDE    0
#define STATUSBAR_SHOW    1
#define STATUSBAR_OFF     2

typedef struct {
   int model;
   int ram; /*request only! beware: 6128 enforces minimum!*/
   int lang;
   uint32_t combokey;
   uint32_t statusbar;
   uint32_t padcfg[PORTS_NUMBER];
   bool is_dirty;
   bool floppy_snd;
} computer_cfg_t;
extern computer_cfg_t retro_computer_cfg;

//STRUCTURES
typedef struct{
     signed short x, y;
     unsigned short w, h;
} retro_Rect;

typedef struct{
     unsigned char *pixels;
     unsigned short w, h,pitch;
} retro_Surface;

typedef struct{
     unsigned char r,g,b;
} retro_pal;


void retro_message(const char *text);

//SCREEN FUNCTIONS
extern int retro_getStyle();
extern int retro_getGfxBpp();
extern int retro_getGfxBps();
extern int retro_getAudioBuffer();
extern unsigned int * retro_getScreenPtr();

#endif
