cmake_minimum_required(VERSION 3.9)
project(seacraft_simulation)

set(CMAKE_CXX_STANDARD 11)

add_executable(seacraft_simulation main.cpp Controller.cpp Controller.h Model.cpp Model.h Seacraft.cpp Seacraft.h Port.cpp Port.h Cruiser.cpp Cruiser.h Freighter.cpp Freighter.h PatrolBoat.cpp PatrolBoat.h View.cpp View.h Geometry.cpp Geometry.h SeaObject.cpp SeaObject.h SeacraftFactory.cpp SeacraftFactory.h)