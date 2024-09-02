#ifndef __input_defenitions_h_
#define __input_defenitions_h_

#include "tut.h"

#ifndef SDL_MAIN_HANDLED
#define SDL_MAIN_HANDLED
#endif // SDL_MAIN_HANDLED
#include <SDL.h>

namespace tut::system::input
{
  // Types declarations
  class system;

  struct key
  {
  public:

    // Keys' codes - agreed TC4 code borrowing
    enum struct code : UINT16
    {
      eUnknown,

      // Alphabet
      eA,
      eB,
      eC,
      eD,
      eE,
      eF,
      eG,
      eH,
      eI,
      eJ,
      eK,
      eL,
      eM,
      eN,
      eO,
      eP,
      eQ,
      eR,
      eS,
      eT,
      eU,
      eV,
      eW,
      eX,
      eY,
      eZ,

      // Numbers
      e0,
      e1,
      e2,
      e3,
      e4,
      e5,
      e6,
      e7,
      e8,
      e9,

      // Functional keys
      eF1,
      eF2,
      eF3,
      eF4,
      eF5,
      eF6,
      eF7,
      eF8,
      eF9,
      eF10,
      eF11,
      eF12,
  
      // Page block
      ePageUp,
      ePageDown,
      eHome,
      eEnd,
      eInsert,
      eDelete,

      eReturn,
      eEnter = eReturn,
      eSpace,
      eBackspace,
      eTab,
      eCapsLock,
      eEscape,
      eGui,
      eApplication, // Conext menu

      // Upper block
      eNumLock,
      eScrollLock,
      ePause,
      ePrintScreen,

      // Arrows
      eUp,
      eDown,
      eLeft,
      eRight,

      eBackquote,    // `
      eMinus,        // -
      eEquals,       // =
      eBackslash,    // \ 
      eSlash,        // /
      eLeftBracket,  // [
      eRightBracket, // ]
      eApostrophe,   // '
      eSemicolon,    // ;
      eComma,        // ,
      ePeriod,       // .

      eValueCount,
    }; // End of 'key' enum struct

    enum mods : BYTE
    {
      eNone    = 0,
      eShift   = 1,
      eAlt     = 2,
      eControl = 4,
      eGui     = 8,
    }; // End of 'mods' enum struct

    BYTE Mods {mods::eNone};
    code Code {code::eUnknown};

    // It is implementation dependent but better than just constructor
    inline static key FromSDL( SDL_Keycode KeyCode, UINT16 KeyMods ) noexcept
    {
      // Oh yes   how many lines of code
      constexpr std::array<code, SDL_NUM_SCANCODES> CodesMap {
        code::eUnknown,      // SDL_SCANCODE_UNKNOWN
        code::eUnknown,      // 1
        code::eUnknown,      // 2
        code::eUnknown,      // 3
        code::eA,            // 4  SDL_SCANCODE_A
        code::eB,            // 5  SDL_SCANCODE_B
        code::eC,            // 6  SDL_SCANCODE_C
        code::eD,            // 7  SDL_SCANCODE_D
        code::eE,            // 8  SDL_SCANCODE_E
        code::eF,            // 9  SDL_SCANCODE_F
        code::eG,            // 10 SDL_SCANCODE_G
        code::eH,            // 11 SDL_SCANCODE_H
        code::eI,            // 12 SDL_SCANCODE_I
        code::eJ,            // 13 SDL_SCANCODE_J
        code::eK,            // 14 SDL_SCANCODE_K
        code::eL,            // 15 SDL_SCANCODE_L
        code::eM,            // 16 SDL_SCANCODE_M
        code::eN,            // 17 SDL_SCANCODE_N
        code::eO,            // 18 SDL_SCANCODE_O
        code::eP,            // 19 SDL_SCANCODE_P
        code::eQ,            // 20 SDL_SCANCODE_Q
        code::eR,            // 21 SDL_SCANCODE_R
        code::eS,            // 22 SDL_SCANCODE_S
        code::eT,            // 23 SDL_SCANCODE_T
        code::eU,            // 24 SDL_SCANCODE_U
        code::eV,            // 25 SDL_SCANCODE_V
        code::eW,            // 26 SDL_SCANCODE_W
        code::eX,            // 27 SDL_SCANCODE_X
        code::eY,            // 28 SDL_SCANCODE_Y
        code::eZ,            // 29 SDL_SCANCODE_Z

        code::e1,            // 30 SDL_SCANCODE_1
        code::e2,            // 31 SDL_SCANCODE_2
        code::e3,            // 32 SDL_SCANCODE_3
        code::e4,            // 33 SDL_SCANCODE_4
        code::e5,            // 34 SDL_SCANCODE_5
        code::e6,            // 35 SDL_SCANCODE_6
        code::e7,            // 36 SDL_SCANCODE_7
        code::e8,            // 37 SDL_SCANCODE_8
        code::e9,            // 38 SDL_SCANCODE_9
        code::e0,            // 39 SDL_SCANCODE_0

        code::eReturn,       // 40 SDL_SCANCODE_RETURN
        code::eEscape,       // 41 SDL_SCANCODE_ESCAPE
        code::eBackspace,    // 42 SDL_SCANCODE_BACKSPACE
        code::eTab,          // 43 SDL_SCANCODE_TAB
        code::eSpace,        // 44 SDL_SCANCODE_SPACE

        code::eMinus,        // 45 SDL_SCANCODE_MINUS
        code::eEquals,       // 46 SDL_SCANCODE_EQUALS
        code::eLeftBracket,  // 47 SDL_SCANCODE_LEFTBRACKET
        code::eRightBracket, // 48 SDL_SCANCODE_RIGHTBRACKET
        code::eBackslash,    // 49 SDL_SCANCODE_BACKSLASH
        code::eUnknown,      // 50 SDL_SCANCODE_NONUSHASH
        code::eSemicolon,    // 51 SDL_SCANCODE_SEMICOLON
        code::eApostrophe,   // 52 SDL_SCANCODE_APOSTROPHE
        code::eBackquote,    // 53 SDL_SCANCODE_GRAVE
        code::eComma,        // 54 SDL_SCANCODE_COMMA
        code::ePeriod,       // 55 SDL_SCANCODE_PERIOD
        code::eSlash,        // 56 SDL_SCANCODE_SLASH

        code::eCapsLock,     // 57 SDL_SCANCODE_CAPSLOCK

        code::eF1,           // 58 SDL_SCANCODE_F1
        code::eF2,           // 59 SDL_SCANCODE_F2
        code::eF3,           // 60 SDL_SCANCODE_F3
        code::eF4,           // 61 SDL_SCANCODE_F4
        code::eF5,           // 62 SDL_SCANCODE_F5
        code::eF6,           // 63 SDL_SCANCODE_F6
        code::eF7,           // 64 SDL_SCANCODE_F7
        code::eF8,           // 65 SDL_SCANCODE_F8
        code::eF9,           // 66 SDL_SCANCODE_F9
        code::eF10,          // 67 SDL_SCANCODE_F10
        code::eF11,          // 68 SDL_SCANCODE_F11
        code::eF12,          // 69 SDL_SCANCODE_F12

        code::ePrintScreen,  // 70 SDL_SCANCODE_PRINTSCREEN
        code::eScrollLock,   // 71 SDL_SCANCODE_SCROLLLOCK
        code::ePause,        // 72 SDL_SCANCODE_PAUSE
        code::eInsert,       // 73 SDL_SCANCODE_INSERT
        code::eHome,         // 74 SDL_SCANCODE_HOME
        code::ePageUp,       // 75 SDL_SCANCODE_PAGEUP
        code::eDelete,       // 76 SDL_SCANCODE_DELETE
        code::eEnd,          // 77 SDL_SCANCODE_END
        code::ePageDown,     // 78 SDL_SCANCODE_PAGEDOWN
        code::eRight,        // 79 SDL_SCANCODE_RIGHT
        code::eLeft,         // 80 SDL_SCANCODE_LEFT
        code::eDown,         // 81 SDL_SCANCODE_DOWN
        code::eUp,           // 82 SDL_SCANCODE_UP

        // Following are unused
        // TODO add key pad support

        code::eNumLock,      // 83 SDL_SCANCODE_NUMLOCKCLEAR

        code::eUnknown,      // 84 SDL_SCANCODE_KP_DIVIDE
        code::eUnknown,      // 85 SDL_SCANCODE_KP_MULTIPLY
        code::eUnknown,      // 86 SDL_SCANCODE_KP_MINUS
        code::eUnknown,      // 87 SDL_SCANCODE_KP_PLUS
        code::eUnknown,      // 88 SDL_SCANCODE_KP_ENTER
        code::eUnknown,      // 89 SDL_SCANCODE_KP_1
        code::eUnknown,      // 90 SDL_SCANCODE_KP_2
        code::eUnknown,      // 91 SDL_SCANCODE_KP_3
        code::eUnknown,      // 92 SDL_SCANCODE_KP_4
        code::eUnknown,      // 93 SDL_SCANCODE_KP_5
        code::eUnknown,      // 94 SDL_SCANCODE_KP_6
        code::eUnknown,      // 95 SDL_SCANCODE_KP_7
        code::eUnknown,      // 96 SDL_SCANCODE_KP_8
        code::eUnknown,      // 97 SDL_SCANCODE_KP_9
        code::eUnknown,      // 98 SDL_SCANCODE_KP_0
        code::eUnknown,      // 99 SDL_SCANCODE_KP_PERIOD

        code::eUnknown,      // 100 SDL_SCANCODE_NONUSBACKSLASH

        code::eApplication,  // 101 SDL_SCANCODE_APPLICATION windows contextual menu, compose
        
        // The rest are unused and will have code::eUnknown
        // Mods buttons will be checked later
        // Documentation says there is SDL_NUM_SCANCODES = 512 scan codes
      };

      key OutKey;

      OutKey.Code = CodesMap[KeyCode];
      OutKey.Mods = ((KeyMods & KMOD_CTRL)  ? mods::eControl : 0) |
                    ((KeyMods & KMOD_SHIFT) ? mods::eShift   : 0) |
                    ((KeyMods & KMOD_ALT)   ? mods::eAlt     : 0) |
                    ((KeyMods & KMOD_GUI)   ? mods::eGui     : 0);

      return OutKey;
    } // End of 'FromSDL' function

  }; // End of 'key' struct

  class state
  {
  private:

  }; // End of 'input_state' class
} // end of 'tut::system::input' namespace

#endif // __input_defenitions_h_