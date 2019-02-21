#pragma once

#include <Windows.h>

namespace dx12ge
{
	enum E_MouseCode {
		DX12GE_MOUSE_CODE_START = 0,

		DX12GE_MOUSE_CODE_LBUTTON	= MK_LBUTTON,//	Left mouse button
		DX12GE_MOUSE_CODE_RBUTTON	= MK_RBUTTON,//	Right mouse button
		DX12GE_MOUSE_CODE_SHIFT		= MK_SHIFT,// SHIFT key
		DX12GE_MOUSE_CODE_CTRL		= MK_CONTROL,// CTRL key
		DX12GE_MOUSE_CODE_MBUTTON	= MK_MBUTTON,//	Middle mouse button
		DX12GE_MOUSE_CODE_XBUTTON1	= MK_XBUTTON1,//X1 mouse button
		DX12GE_MOUSE_CODE_XBUTTON2	= MK_XBUTTON2,//X2 mouse button
		DX12GE_MOUSE_CODE_MOVE,	// Mouse move
		DX12GE_MOUSE_CODE_WHEEL,// Mouse wheel

		DX12GE_MOUSE_CODE_END
	};

	enum E_KeyCode {
		DX12GE_KEY_CODE_START = 0,

		DX12GE_KEY_MOUSE_LEFT				= VK_LBUTTON,//Left mouse button
		DX12GE_KEY_MOUSE_RIGHT				= VK_RBUTTON,//Right mouse button
		DX12GE_KEY_CANCEL					= VK_CANCEL,//Control - break processing
		DX12GE_KEY_MOUSE_MIDDLE				= VK_MBUTTON,//Middle mouse button(three - button mouse)
		DX12GE_KEY_MOUSE_X1					= VK_XBUTTON1,//X1 mouse button
		DX12GE_KEY_MOUSE_X2					= VK_XBUTTON2,//X2 mouse button

		DX12GE_KEY_UNDEFINED0				= 0x07,//Undefined

		DX12GE_KEY_BACKSPACE				= VK_BACK,//BACKSPACE key
		DX12GE_KEY_TAB						= VK_TAB,//TAB key

		DX12GE_KEY_RESERVED0				= 0x0A,//Reserved
		DX12GE_KEY_RESERVED1				= 0x0B,//Reserved

		DX12GE_KEY_CLEAR					= VK_CLEAR,//CLEAR key
		DX12GE_KEY_ENTER					= VK_RETURN,//ENTER key

		DX12GE_KEY_UNDEFINED1				= 0x0E,//Undefined
		DX12GE_KEY_UNDEFINED2				= 0x0F,//Undefined

		DX12GE_KEY_SHIFT					= VK_SHIFT,//SHIFT key
		DX12GE_KEY_CTRL						= VK_CONTROL,//CTRL key
		DX12GE_KEY_ALT						= VK_MENU,//ALT key
		DX12GE_KEY_PAUSE					= VK_PAUSE,//PAUSE key
		DX12GE_KEY_CAPS_LOCK				= VK_CAPITAL,//CAPS LOCK key
		DX12GE_KEY_IME_MODE_KANA			= VK_KANA,//IME Kana mode
		//DX12GE_KEY_IME_MODE_HANGUL		= VK_HANGUL,//IME Hangul mode

		DX12GE_KEY_UNDEFINED3				= 0x16,//Undefined

		DX12GE_KEY_IME_MODE_JUNJA			= VK_JUNJA,//IME Junja mode
		DX12GE_KEY_IME_MODE_FINAL			= VK_FINAL,//IME final mode
		//DX12GE_KEY_IME_MODE_HANJA			= VK_HANJA,//IME Hanja mode
		DX12GE_KEY_IME_MODE_KANJI			= VK_KANJI,//IME Kanji mode

		DX12GE_KEY_UNDEFINED4				= 0x1A,//Undefined

		DX12GE_KEY_ESC						= VK_ESCAPE,//ESC key
		DX12GE_KEY_IME_CONVERT				= VK_CONVERT,//IME convert
		DX12GE_KEY_IME_NONCONVERT			= VK_NONCONVERT,//IME nonconvert
		DX12GE_KEY_IME_ACCEPT				= VK_ACCEPT,//IME accept
		DX12GE_KEY_IME_MODE_CHANGE_REQUEST	= VK_MODECHANGE,//IME mode change request
		
		DX12GE_KEY_SPACEBAR					= VK_SPACE,//SPACEBAR
		DX12GE_KEY_PAGE_UP					= VK_PRIOR,//PAGE UP key
		DX12GE_KEY_PAGE_DOWN				= VK_NEXT,//PAGE DOWN key
		DX12GE_KEY_END						= VK_END,//END key
		DX12GE_KEY_HOME						= VK_HOME,//HOME key
		DX12GE_KEY_LEFT_ARROW				= VK_LEFT,//LEFT ARROW key
		DX12GE_KEY_UP_ARROW					= VK_UP,//UP ARROW key
		DX12GE_KEY_RIGHT_ARROW				= VK_RIGHT,//RIGHT ARROW key
		DX12GE_KEY_DOWN_ARROW				= VK_DOWN,//DOWN ARROW key
		DX12GE_KEY_SELECT					= VK_SELECT,//SELECT key
		DX12GE_KEY_PRINT					= VK_PRINT,//PRINT key
		DX12GE_KEY_EXECUTE					= VK_EXECUTE,//EXECUTE key
		DX12GE_KEY_PRINT_SCREEN				= VK_SNAPSHOT,//PRINT SCREEN key
		DX12GE_KEY_INS						= VK_INSERT,//INS key
		DX12GE_KEY_DEL						= VK_DELETE,//DEL key
		DX12GE_KEY_HELP						= VK_HELP,//HELP key

		DX12GE_KEY_0						= 0x30,//0 key
		DX12GE_KEY_1						= 0x31,//1 key
		DX12GE_KEY_2						= 0x32,//2 key
		DX12GE_KEY_3						= 0x33,//3 key
		DX12GE_KEY_4						= 0x34,//4 key
		DX12GE_KEY_5						= 0x35,//5 key
		DX12GE_KEY_6						= 0x36,//6 key
		DX12GE_KEY_7						= 0x37,//7 key
		DX12GE_KEY_8						= 0x38,//8 key
		DX12GE_KEY_9						= 0x39,//9 key

		DX12GE_KEY_UNDEFINED5				= 0x3A,//Undefined
		DX12GE_KEY_UNDEFINED6				= 0x3B,//Undefined
		DX12GE_KEY_UNDEFINED7				= 0x3C,//Undefined
		DX12GE_KEY_UNDEFINED8				= 0x3D,//Undefined
		DX12GE_KEY_UNDEFINED9				= 0x3E,//Undefined
		DX12GE_KEY_UNDEFINED10				= 0x3F,//Undefined

		DX12GE_KEY_A						= 0x41,//A key
		DX12GE_KEY_B						= 0x42,//B key
		DX12GE_KEY_C						= 0x43,//C key
		DX12GE_KEY_D						= 0x44,//D key
		DX12GE_KEY_E						= 0x45,//E key
		DX12GE_KEY_F						= 0x46,//F key
		DX12GE_KEY_G						= 0x47,//G key
		DX12GE_KEY_H						= 0x48,//H key
		DX12GE_KEY_I						= 0x49,//I key
		DX12GE_KEY_J						= 0x4A,//J key
		DX12GE_KEY_K						= 0x4B,//K key
		DX12GE_KEY_L						= 0x4C,//L key
		DX12GE_KEY_M						= 0x4D,//M key
		DX12GE_KEY_N						= 0x4E,//N key
		DX12GE_KEY_O						= 0x4F,//O key
		DX12GE_KEY_P						= 0x50,//P key
		DX12GE_KEY_Q						= 0x51,//Q key
		DX12GE_KEY_R						= 0x52,//R key
		DX12GE_KEY_S						= 0x53,//S key
		DX12GE_KEY_T						= 0x54,//T key
		DX12GE_KEY_U						= 0x55,//U key
		DX12GE_KEY_V						= 0x56,//V key
		DX12GE_KEY_W						= 0x57,//W key
		DX12GE_KEY_X						= 0x58,//X key
		DX12GE_KEY_Y						= 0x59,//Y key
		DX12GE_KEY_Z						= 0x5A,//Z key

		DX12GE_KEY_WINDOWS_LEFT				= VK_LWIN,//Left Windows key(Natural keyboard)
		DX12GE_KEY_WINDOWS_RIGHT			= VK_RWIN,//Right Windows key(Natural keyboard)
		DX12GE_KEY_APPLICATIONS				= VK_APPS,//Applications key(Natural keyboard)

		DX12GE_KEY_RESERVED2				= 0x5E,//Reserved

		DX12GE_KEY_SLEEP					= VK_SLEEP,//Computer Sleep key

		DX12GE_KEY_NUMPAD0					= VK_NUMPAD0,//Numeric keypad 0 key
		DX12GE_KEY_NUMPAD1					= VK_NUMPAD1,//Numeric keypad 1 key
		DX12GE_KEY_NUMPAD2					= VK_NUMPAD2,//Numeric keypad 2 key
		DX12GE_KEY_NUMPAD3					= VK_NUMPAD3,//Numeric keypad 3 key
		DX12GE_KEY_NUMPAD4					= VK_NUMPAD4,//Numeric keypad 4 key
		DX12GE_KEY_NUMPAD5					= VK_NUMPAD5,//Numeric keypad 5 key
		DX12GE_KEY_NUMPAD6					= VK_NUMPAD6,//Numeric keypad 6 key
		DX12GE_KEY_NUMPAD7					= VK_NUMPAD7,//Numeric keypad 7 key
		DX12GE_KEY_NUMPAD8					= VK_NUMPAD8,//Numeric keypad 8 key
		DX12GE_KEY_NUMPAD9					= VK_NUMPAD9,//Numeric keypad 9 key

		DX12GE_KEY_MULTIPLY					= VK_MULTIPLY,//Multiply key
		DX12GE_KEY_ADD						= VK_ADD,//Add key
		DX12GE_KEY_SEPARATOR				= VK_SEPARATOR,//Separator key
		DX12GE_KEY_SUBTRACT					= VK_SUBTRACT,//Subtract key
		DX12GE_KEY_DECIMAL					= VK_DECIMAL,//Decimal key
		DX12GE_KEY_DIVIDE					= VK_DIVIDE,//Divide key

		DX12GE_KEY_F1						= VK_F1,//F1 key
		DX12GE_KEY_F2						= VK_F2,//F2 key
		DX12GE_KEY_F3						= VK_F3,//F3 key
		DX12GE_KEY_F4						= VK_F4,//F4 key
		DX12GE_KEY_F5						= VK_F5,//F5 key
		DX12GE_KEY_F6						= VK_F6,//F6 key
		DX12GE_KEY_F7						= VK_F7,//F7 key
		DX12GE_KEY_F8						= VK_F8,//F8 key
		DX12GE_KEY_F9						= VK_F9,//F9 key
		DX12GE_KEY_F10						= VK_F10,//F10 key
		DX12GE_KEY_F11						= VK_F11,//F11 key
		DX12GE_KEY_F12						= VK_F12,//F12 key
		DX12GE_KEY_F13						= VK_F13,//F13 key
		DX12GE_KEY_F14						= VK_F14,//F14 key
		DX12GE_KEY_F15						= VK_F15,//F15 key
		DX12GE_KEY_F16						= VK_F16,//F16 key
		DX12GE_KEY_F17						= VK_F17,//F17 key
		DX12GE_KEY_F18						= VK_F18,//F18 key
		DX12GE_KEY_F19						= VK_F19,//F19 key
		DX12GE_KEY_F20						= VK_F20,//F20 key
		DX12GE_KEY_F21						= VK_F21,//F21 key
		DX12GE_KEY_F22						= VK_F22,//F22 key
		DX12GE_KEY_F23						= VK_F23,//F23 key
		DX12GE_KEY_F24						= VK_F24,//F24 key

		DX12GE_KEY_UNASSIGNED0				= 0x88,//Unassigned
		DX12GE_KEY_UNASSIGNED1				= 0x89,//Unassigned
		DX12GE_KEY_UNASSIGNED2				= 0x8A,//Unassigned
		DX12GE_KEY_UNASSIGNED3				= 0x8B,//Unassigned
		DX12GE_KEY_UNASSIGNED4				= 0x8C,//Unassigned
		DX12GE_KEY_UNASSIGNED5				= 0x8D,//Unassigned
		DX12GE_KEY_UNASSIGNED6				= 0x8E,//Unassigned
		DX12GE_KEY_UNASSIGNED7				= 0x8F,//Unassigned

		DX12GE_KEY_NUM_LOCK					= VK_NUMLOCK,//NUM LOCK key
		DX12GE_KEY_SCROLL_LOCK				= VK_SCROLL,//SCROLL LOCK key

		DX12GE_KEY_OEM_SPESIFIC_0			= 0x92,//OEM specific
		DX12GE_KEY_OEM_SPESIFIC_1			= 0x93,//OEM specific
		DX12GE_KEY_OEM_SPESIFIC_2			= 0x94,//OEM specific
		DX12GE_KEY_OEM_SPESIFIC_3			= 0x95,//OEM specific
		DX12GE_KEY_OEM_SPESIFIC_4			= 0x96,//OEM specific

		DX12GE_KEY_UNASSIGNED8				= 0x97,//Unassigned
		DX12GE_KEY_UNASSIGNED9				= 0x98,//Unassigned
		DX12GE_KEY_UNASSIGNED10				= 0x99,//Unassigned
		DX12GE_KEY_UNASSIGNED11				= 0x9A,//Unassigned
		DX12GE_KEY_UNASSIGNED12				= 0x9B,//Unassigned
		DX12GE_KEY_UNASSIGNED13				= 0x9C,//Unassigned
		DX12GE_KEY_UNASSIGNED14				= 0x9D,//Unassigned
		DX12GE_KEY_UNASSIGNED15				= 0x9E,//Unassigned
		DX12GE_KEY_UNASSIGNED16				= 0x9F,//Unassigned

		DX12GE_KEY_SHIFT_LEFT				= VK_LSHIFT,//Left SHIFT key
		DX12GE_KEY_SHIFT_RIGHT				= VK_RSHIFT,//Right SHIFT key
		DX12GE_KEY_CONTROL_LEFT				= VK_LCONTROL,//Left CONTROL key
		DX12GE_KEY_CONTROL_RIGHT			= VK_RCONTROL,//Right CONTROL key
		DX12GE_KEY_ALT_LEFT					= VK_LMENU,//Left ALT key
		DX12GE_KEY_ALT_RIGHT				= VK_RMENU,//Right ALT key
		DX12GE_KEY_BROWSER_BACK				= VK_BROWSER_BACK,//Browser Back key
		DX12GE_KEY_BROWSER_FORWARD			= VK_BROWSER_FORWARD,//Browser Forward key
		DX12GE_KEY_BROWSER_REFRESH			= VK_BROWSER_REFRESH,//Browser Refresh key
		DX12GE_KEY_BROWSER_STOP				= VK_BROWSER_STOP,//Browser Stop key
		DX12GE_KEY_BROWSER_SEARCH			= VK_BROWSER_SEARCH,//Browser Search key
		DX12GE_KEY_BROWSER_FAVORITES		= VK_BROWSER_FAVORITES,//Browser Favorites key
		DX12GE_KEY_BROWSER_START_AND_HOME	= VK_BROWSER_HOME,//Browser Start and Home key
		DX12GE_KEY_VOLUME_MUTE				= VK_VOLUME_MUTE,//Volume Mute key
		DX12GE_KEY_VOLUME_DOWN				= VK_VOLUME_DOWN,//Volume Down key
		DX12GE_KEY_VOLUME_UP				= VK_VOLUME_UP,//Volume Up key
		DX12GE_KEY_MEDIA_TRACK_NEXT			= VK_MEDIA_NEXT_TRACK,//Next Track key
		DX12GE_KEY_MEDIA_TRACK_PREVIOUS		= VK_MEDIA_PREV_TRACK,//Previous Track key
		DX12GE_KEY_MEDIA_STOP				= VK_MEDIA_STOP,//Stop Media key
		DX12GE_KEY_MEDIA_PLAY_OR_PAUSE		= VK_MEDIA_PLAY_PAUSE,//Play / Pause Media key
		DX12GE_KEY_MAIL_START				= VK_LAUNCH_MAIL,//Start Mail key
		DX12GE_KEY_MEDIA_SELECT				= VK_LAUNCH_MEDIA_SELECT,//Select Media key
		DX12GE_KEY_START_APPLICATION_1		= VK_LAUNCH_APP1,//Start Application 1 key
		DX12GE_KEY_START_APPLICATION_2		= VK_LAUNCH_APP2,//Start Application 2 key

		DX12GE_KEY_RESERVED3				= 0xB8,//Reserved
		DX12GE_KEY_RESERVED4				= 0xB9,//Reserved

		DX12GE_KEY_OEM_1					= VK_OEM_1,//Used for miscellaneous characters; it can vary by keyboard. For the US standard keyboard, the ';:' key
		DX12GE_KEY_PLUS						= VK_OEM_PLUS,//For any country / region, the '+' key
		DX12GE_KEY_COMMA					= VK_OEM_COMMA,//For any country / region, the ',' key
		DX12GE_KEY_MINUS					= VK_OEM_MINUS,//For any country / region, the '-' key
		DX12GE_KEY_PERIOD					= VK_OEM_PERIOD,//For any country / region, the '.' key
		DX12GE_KEY_OEM_2					= VK_OEM_2,//Used for miscellaneous characters; it can vary by keyboard. For the US standard keyboard, the '/?' key
		DX12GE_KEY_OEM_3					= VK_OEM_3,//Used for miscellaneous characters; it can vary by keyboard. For the US standard keyboard, the '`~' key

		DX12GE_KEY_RESERVED5				= 0xC1,//Reserved
		DX12GE_KEY_RESERVED6				= 0xC2,//Reserved
		DX12GE_KEY_RESERVED7				= 0xC3,//Reserved
		DX12GE_KEY_RESERVED8				= 0xC4,//Reserved
		DX12GE_KEY_RESERVED9				= 0xC5,//Reserved
		DX12GE_KEY_RESERVED10				= 0xC6,//Reserved
		DX12GE_KEY_RESERVED11				= 0xC7,//Reserved
		DX12GE_KEY_RESERVED12				= 0xC8,//Reserved
		DX12GE_KEY_RESERVED13				= 0xC9,//Reserved
		DX12GE_KEY_RESERVED14				= 0xCA,//Reserved
		DX12GE_KEY_RESERVED15				= 0xCB,//Reserved
		DX12GE_KEY_RESERVED16				= 0xCC,//Reserved
		DX12GE_KEY_RESERVED17				= 0xCD,//Reserved
		DX12GE_KEY_RESERVED18				= 0xCE,//Reserved
		DX12GE_KEY_RESERVED19				= 0xCF,//Reserved
		DX12GE_KEY_RESERVED20				= 0xD0,//Reserved
		DX12GE_KEY_RESERVED21				= 0xD1,//Reserved
		DX12GE_KEY_RESERVED22				= 0xD2,//Reserved
		DX12GE_KEY_RESERVED23				= 0xD3,//Reserved
		DX12GE_KEY_RESERVED24				= 0xD4,//Reserved
		DX12GE_KEY_RESERVED25				= 0xD5,//Reserved
		DX12GE_KEY_RESERVED26				= 0xD6,//Reserved
		DX12GE_KEY_RESERVED27				= 0xD7,//Reserved

		DX12GE_KEY_UNASSIGNED17				= 0xD8,//Unassigned
		DX12GE_KEY_UNASSIGNED18				= 0xD9,//Unassigned
		DX12GE_KEY_UNASSIGNED19				= 0xDA,//Unassigned

		DX12GE_KEY_OEM_4					= VK_OEM_4,//Used for miscellaneous characters; it can vary by keyboard. For the US standard keyboard, the '[{' key
		DX12GE_KEY_OEM_5					= VK_OEM_5,//Used for miscellaneous characters; it can vary by keyboard. For the US standard keyboard, the '\|' key
		DX12GE_KEY_OEM_6					= VK_OEM_6,//Used for miscellaneous characters; it can vary by keyboard. For the US standard keyboard, the ']}' key
		DX12GE_KEY_OEM_7					= VK_OEM_7,//Used for miscellaneous characters; it can vary by keyboard. For the US standard keyboard, the 'single-quote/double-quote' key
		DX12GE_KEY_OEM_8					= VK_OEM_8,//Used for miscellaneous characters; it can vary by keyboard.

		DX12GE_KEY_RESERVED36				= 0xE0,//Reserved

		DX12GE_KEY_OEM_SPESIFIC_5			= 0xE1,//OEM specific
		DX12GE_KEY_BRACKETS_OR_BACKLASH		= VK_OEM_102,//Either the angle bracket key or the backslash key on the RT 102 - key keyboard
		DX12GE_KEY_OEM_SPESIFIC_6			= 0xE3,//OEM specific
		DX12GE_KEY_OEM_SPESIFIC_7			= 0xE4,//OEM specific
		DX12GE_KEY_IME_PROCESS				= VK_PROCESSKEY,//IME PROCESS key
		DX12GE_KEY_OEM_SPESIFIC_8			= 0xE6,//OEM specific
		DX12GE_KEY_PACKET					= VK_PACKET,//Used to pass Unicode characters as if they were keystrokes.The VK_PACKET key is the low word of a 32 - bit Virtual Key value used for non - keyboard input methods.For more information, see Remark in KEYBDINPUT, SendInput, WM_KEYDOWN, and WM_KEYUP

		DX12GE_KEY_UNASSIGNED20				= 0xE8,//Unassigned

		DX12GE_KEY_OEM_SPESIFIC_9			= 0xE9,//OEM specific
		DX12GE_KEY_OEM_SPESIFIC_10			= 0xEA,//OEM specific
		DX12GE_KEY_OEM_SPESIFIC_11			= 0xEB,//OEM specific
		DX12GE_KEY_OEM_SPESIFIC_12			= 0xEC,//OEM specific
		DX12GE_KEY_OEM_SPESIFIC_13			= 0xED,//OEM specific
		DX12GE_KEY_OEM_SPESIFIC_14			= 0xEE,//OEM specific
		DX12GE_KEY_OEM_SPESIFIC_15			= 0xEF,//OEM specific
		DX12GE_KEY_OEM_SPESIFIC_16			= 0xF0,//OEM specific
		DX12GE_KEY_OEM_SPESIFIC_17			= 0xF1,//OEM specific
		DX12GE_KEY_OEM_SPESIFIC_18			= 0xF2,//OEM specific
		DX12GE_KEY_OEM_SPESIFIC_19			= 0xF3,//OEM specific
		DX12GE_KEY_OEM_SPESIFIC_20			= 0xF4,//OEM specific
		DX12GE_KEY_OEM_SPESIFIC_21			= 0xF5,//OEM specific

		DX12GE_KEY_ATTN						= VK_ATTN,//Attn key
		DX12GE_KEY_CRSEL					= VK_CRSEL,//CrSel key
		DX12GE_KEY_EXSEL					= VK_EXSEL,//ExSel key
		DX12GE_KEY_ERASE_EOF				= VK_EREOF,//Erase EOF key
		DX12GE_KEY_PLAY						= VK_PLAY,//Play key
		DX12GE_KEY_ZOOM						= VK_ZOOM,//Zoom key

		DX12GE_KEY_NONAME					= VK_NONAME,//Reserved

		DX12GE_KEY_PA1						= VK_PA1,//PA1 key
		DX12GE_KEY_OEM_CLEAR				= VK_OEM_CLEAR,//Clear key

		DX12GE_KEY_CODE_END
	};
}