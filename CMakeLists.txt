cmake_minimum_required(VERSION 3.6.0)
project(Obamna)
include_directories(
	${PROJECT_SOURCE_DIR}/include
	${PROJECT_SOURCE_DIR}/src
)
file(GLOB SRCS
	"${PROJECT_SOURCE_DIR}/include/*"
	"${PROJECT_SOURCE_DIR}/src/*"
)


	find_package(SDL3 REQUIRED CONFIG COMPONENTS SDL3)
	find_package(SDL3_image REQUIRED CONFIG)
	add_executable(Obamna main.cpp
			lcy_Obamna.h
			lcy_Obamna.cpp)
	target_link_libraries(Obamna PUBLIC SDL3_image::SDL3_image-shared SDL3::SDL3)

