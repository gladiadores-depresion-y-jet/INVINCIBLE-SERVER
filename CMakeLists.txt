cmake_minimum_required(VERSION 3.14)
project(RAID_5)

set(CMAKE_CXX_STANDARD 14)

add_executable(RAID_5 Main/main.cpp RAID/Disk.cpp RAID/Disk.h RAID/RAID_Controller.cpp RAID/RAID_Controller.h Structures/List.h Structures/Node.h Structures/Matrix.cpp Structures/Matrix.h RAID/FilePart.cpp RAID/FilePart.h)