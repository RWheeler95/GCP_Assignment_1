cmake_minimum_required(VERSION 2.6)

project(GCP_Assignment_1)

if(MSVC)
  include_directories(
	contrib/msvc-windows-x86
    contrib/msvc-windows-x86/SDL2/include
  )

  link_directories(
    ${CMAKE_SOURCE_DIR}/contrib/msvc-windows-x86/SDL2/lib
  )
endif()

if(MSVC)
  add_definitions(-DSDL_MAIN_HANDLED)
endif()

add_executable(raytracer
  src/main.cpp
  src/Camera.cpp
  src/Camera.h
  src/Object.cpp
  src/Object.h
  src/Ray.cpp
  src/Ray.h
  src/Tracer.cpp
  src/Tracer.h
  src/Sphere.cpp
  src/Sphere.h
  src/Renderer.cpp
  src/Renderer.h
  src/Window.cpp
  src/Window.h
)

if(MSVC)
  target_link_libraries(raytracer
    SDL2
  )
else()
  target_link_libraries(raytracer
    SDL2
  )
endif()

if(MSVC)
  add_custom_command(TARGET raytracer POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
      "${CMAKE_SOURCE_DIR}/contrib/msvc-windows-x86/SDL2/bin/SDL2.dll"
      "$<TARGET_FILE_DIR:raytracer>"
  )
endif()