cmake_minimum_required(VERSION 3.1)

project(svwm)

set(SOURCE_LIB svwm.c)		

add_library(svwm STATIC ${SOURCE_LIB})