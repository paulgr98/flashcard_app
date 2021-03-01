cmake_minimum_required(VERSION 3.17)
project(vocabulary_quiz)

set(CMAKE_GENERATOR_PLATFORM "x86")
set(CMAKE_VS_PLATFORM_NAME "x86")

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_BUILD_TYPE Debug)
#set(CMAKE_BUILD_TYPE Release)

set(EXECUTABLE_NAME "vocabulary_quiz")

add_executable(vocabulary_quiz
		source/mainQuiz.cpp
		headers/quiz.h
		source/quiz.cpp)

add_executable(question_maker
		source/mainQuestionMaker.cpp
		headers/QuestionManager.h
		source/QuestionManager.cpp)


set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
