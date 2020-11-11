CXX = g++
LDLIBS = -lsfml-graphics -lsfml-window -lsfml-system
OBJDIR = object

link: main.cpp $(OBJDIR)/application.o $(OBJDIR)/button.o $(OBJDIR)/color.o $(OBJDIR)/scrollbar.o $(OBJDIR)/SFML_engine.o $(OBJDIR)/window.o
	$(CXX) $^ $(LDLIBS) -o main


$(OBJDIR)/application.o: graphics/source/application.cpp graphics/include/application.hpp
	$(CXX) -c graphics/source/application.cpp -o $(OBJDIR)/application.o

$(OBJDIR)/button.o: graphics/source/button.cpp graphics/include/button.hpp
	$(CXX) -c graphics/source/button.cpp -o $(OBJDIR)/button.o

$(OBJDIR)/color.o: graphics/source/color.cpp graphics/include/color.hpp
	$(CXX) -c graphics/source/color.cpp -o $(OBJDIR)/color.o

$(OBJDIR)/scrollbar.o: graphics/source/scrollbar.cpp graphics/include/scrollbar.hpp
	$(CXX) -c graphics/source/scrollbar.cpp -o $(OBJDIR)/scrollbar.o

$(OBJDIR)/SFML_engine.o: graphics/source/SFML_engine.cpp graphics/include/SFML_engine.hpp
	$(CXX) -c graphics/source/SFML_engine.cpp -o $(OBJDIR)/SFML_engine.o

$(OBJDIR)/window.o: graphics/source/window.cpp graphics/include/window.hpp
	$(CXX) -c graphics/source/window.cpp -o $(OBJDIR)/window.o