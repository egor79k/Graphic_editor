#ifndef _EVENT_HPP_
#define _EVENT_HPP_


/*enum Mouse_button
{
	Left,
	Right,
	Middle
};*/


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
/*

	struct Size
	{
		unsigned int width;  
		unsigned int height; 
	};

	struct Key
	{
		//Keyboard::Key code;    
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

	struct Mouse_button
	{
		Mouse_button button;
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
		Mouse_button     mouse_button;       
		Mouse_wheel      mouse_wheel;        
	};*/
};


#endif