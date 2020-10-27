#include "../include/SFML_engine.hpp"


sf::RenderWindow SFML_engine::window (sf::VideoMode (100, 100), "Text");


void SFML_engine::initialize (int width, int height, const char *window_header)
{
	window.create (sf::VideoMode (width, height), window_header);
}


bool SFML_engine::poll_event (Event &event)
{
	const static Event::Event_type Event_match[] = {
		Event::Closed,
		Event::Resized,
		Event::Unfocused,
		Event::Focused,
		Event::Text_entered,
		Event::Key_pressed,
		Event::Key_released,
		Event::Mouse_wheel_moved,
		Event::Unused_event,
		Event::Mouse_pressed,
		Event::Mouse_released,
		Event::Mouse_moved,
		Event::Mouse_went_in,
		Event::Mouse_went_out,
		Event::Unused_event,
		Event::Unused_event,
		Event::Unused_event,
		Event::Unused_event,
		Event::Unused_event,
		Event::Unused_event,
		Event::Unused_event,
		Event::Unused_event,
		Event::Unused_event,
		Event::Unused_event
	};

	sf::Event sf_event;

	if (window.pollEvent (sf_event))
	{
		event.type = Event_match[sf_event.type];
		//Event_match[sf_event.type].SFML_engine::Match (event, sf_event);
		return true;
	}

	return false;
}


bool SFML_engine::working ()
{
	return window.isOpen ();
}


void SFML_engine::flush_screen ()
{
	window.display ();
}


void SFML_engine::exit ()
{
	window.close ();
}