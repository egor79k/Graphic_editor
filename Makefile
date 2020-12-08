CXX = g++
LDLIBS = -lsfml-graphics -lsfml-window -lsfml-system
OBJDIR = object


link: main.cpp $(OBJDIR)/application.o $(OBJDIR)/button.o $(OBJDIR)/color.o $(OBJDIR)/SFML_engine.o $(OBJDIR)/window.o $(OBJDIR)/event_system.o $(OBJDIR)/pixel_array.o $(OBJDIR)/gred_tools.o
	$(CXX) $^ $(LDLIBS) -o main

make_all:
	$(CXX) main.cpp graphics/source/application.cpp graphics/source/button.cpp graphics/source/color.cpp graphics/source/SFML_engine.cpp graphics/source/window.cpp graphics/source/event_system.cpp graphics/source/pixel_array.cpp graphics/source/gred_tools.cpp $^ $(LDLIBS) -o main


$(OBJDIR)/application.o: graphics/source/application.cpp graphics/include/application.hpp
	$(CXX) -c graphics/source/application.cpp -o $(OBJDIR)/application.o

$(OBJDIR)/button.o: graphics/source/button.cpp graphics/include/button.hpp
	$(CXX) -c graphics/source/button.cpp -o $(OBJDIR)/button.o

$(OBJDIR)/color.o: graphics/source/color.cpp graphics/include/color.hpp
	$(CXX) -c graphics/source/color.cpp -o $(OBJDIR)/color.o

$(OBJDIR)/SFML_engine.o: graphics/source/SFML_engine.cpp graphics/include/SFML_engine.hpp
	$(CXX) -c graphics/source/SFML_engine.cpp -o $(OBJDIR)/SFML_engine.o

$(OBJDIR)/window.o: graphics/source/window.cpp graphics/include/window.hpp
	$(CXX) -c graphics/source/window.cpp -o $(OBJDIR)/window.o

$(OBJDIR)/event_system.o: graphics/source/event_system.cpp graphics/include/event_system.hpp
	$(CXX) -c graphics/source/event_system.cpp -o $(OBJDIR)/event_system.o

$(OBJDIR)/pixel_array.o: graphics/source/pixel_array.cpp graphics/include/pixel_array.hpp
	$(CXX) -c graphics/source/pixel_array.cpp -o $(OBJDIR)/pixel_array.o

$(OBJDIR)/gred_tools.o: graphics/source/gred_tools.cpp graphics/include/gred_tools.hpp
	$(CXX) -c graphics/source/gred_tools.cpp -o $(OBJDIR)/gred_tools.o