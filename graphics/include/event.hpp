#ifndef _EVENT_HPP_
#define _EVENT_HPP_


struct Mouse
{
	enum Button
	{
		Left,
		Right,
		Middle
	};
};


struct Keyboard
{
	enum Key
	{
		Unknown = -1,
		A = 0,
		B,
		C,
		D,
		E,
		F,
		G,
		H,
		I,
		J,
		K,
		L,
		M,
		N,
		O,
		P,
		Q,
		R,
		S,
		T,
		U,
		V,
		W,
		X,
		Y,
		Z,
		Num0,
		Num1,
		Num2,
		Num3,
		Num4,
		Num5,
		Num6,
		Num7,
		Num8,
		Num9,
		Escape,
		LControl,
		LShift,
		LAlt,
		LSystem,
		RControl,
		RShift,
		RAlt,
		RSystem,
		Menu,
		LBracket,
		RBracket,
		Semicolon,
		Comma,
		Period,
		Quote,
		Slash,
		Backslash,
		Tilde,
		Equal,
		Hyphen,
		Space,
		Enter,
		Backspace,
		Tab,
		PageUp,
		PageDown,
		End,
		Home,
		Insert,
		Delete,
		Add,
		Subtract,
		Multiply,
		Divide,
		Left,
		Right,
		Up,
		Down,
		Numpad0,
		Numpad1,
		Numpad2,
		Numpad3,
		Numpad4,
		Numpad5,
		Numpad6,
		Numpad7,
		Numpad8,
		Numpad9,
		F1,
		F2,
		F3,
		F4,
		F5,
		F6,
		F7,
		F8,
		F9,
		F10,
		F11,
		F12,
		F13,
		F14,
		F15,
		Pause
	};
};


struct Event
{
	enum Event_type
	{
		Closed,
		Resized,
		Unfocused,
		Focused,
		Text_entered,
		Key_pressed,
		Key_released,
		Mouse_wheel_moved,
		Mouse_pressed,
		Mouse_released,
		Mouse_moved,
		Mouse_went_in,
		Mouse_went_out,
		Unused_event
	};

	Event_type type;


	struct Size
	{
		unsigned int width;  
		unsigned int height; 
	};

	struct Key
	{
		Keyboard::Key code;    
		bool alt;     
		bool control; 
		bool shift;   
		bool system;  
	};

	struct Text
	{
		uint32_t unicode; 
	};

	struct Mouse_move
	{
		int x; 
		int y; 
	};

	struct Mouse_click
	{
		Mouse::Button button;
		int           x;      
		int           y;      
	};

	struct Mouse_wheel
	{
		int delta; 
		int x;     
		int y;     
	};


	union
	{
		Size             size;              
		Key              key;               
		Text             text;              
		Mouse_move       mouse_move;         
		Mouse_click      mouse_click;       
		Mouse_wheel      mouse_wheel;        
	};
};


#endif