#!/bin/bash
g++ main.cpp graphics/source/SFML_engine.cpp graphics/source/application.cpp graphics/source/window.cpp graphics/source/color.cpp -o main -lsfml-graphics -lsfml-window -lsfml-system