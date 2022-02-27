cmake_minimum_required(VERSION 3.5)
project(cpp_pubsub)

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()


include_directories(${PROJECT_SOURCE_DIR})
include_directories(${openCV_INCLUDE_DIRS})


find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(OpenCV REQUIRED)
find_package(RapidJSON REQUIRED)


add_executable(RM src/main.cpp
        src/AutoAim/Armor/Armor.cpp
        src/AutoAim/Armor/Armor.h
        src/AutoAim/Detector/Detector.cpp
        src/AutoAim/Detector/Detector.h
        src/Camera/Camera_sdk.cpp
        src/Camera/Camera_sdk.h
        #        PowerRune/PowerRuneDetector/PowerRuneDetector.cpp
        #        PowerRune/PowerRuneDetector/PowerRuneDetector.h
        #src/Config/Config_reader.cpp
        #src/Config/Config_reader.h
        src/Utility/exceptions.h
        src/Utility/utility.h
        src/Utility/utility.cpp
        src/Communication/communication.cpp
        src/Communication/communication.h
        src/ThreadManagement/threadManagement.cpp
        src/ThreadManagement/threadManagement.h)


add_executable(talker src/publisher_member_function.cpp)
ament_target_dependencies(talker rclcpp std_msgs)
add_executable(listener src/subscriber_member_function.cpp)
ament_target_dependencies(listener rclcpp std_msgs)

target_link_libraries(talker ${OpenCV_LIBS})
target_link_libraries(RM ${OpenCV_LIBS} )

install(TARGETS
  talker
  listener
  DESTINATION lib/${PROJECT_NAME})

ament_package()

if (${CMAKE_SYSTEM_PROCESSOR} MATCHES "aarch64")
  message(STATUS "The current platform is arm")
  SET(CMAKE_BUILD_TYPE Release)
  message(STATUS "CMAKE_BUILD_TYPE='${CMAKE_BUILD_TYPE}' is defined")
  message(STATUS "The debug flag is ${CMAKE_CXX_FLAGS_DEBUG}")
else ()
  message(STATUS "The current platform is x86_64")
  SET(CMAKE_BUILD_TYPE Debug)
  message(STATUS "CMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} is defined")
  message(STATUS "The release flag is ${CMAKE_CXX_FLAGS_RELEASE}")
endif ()
