cmake_minimum_required(VERSION 3.1) 


project(svwm_test)

set(SOURCE_EXE test.c)			# Установка переменной со списком исходников

include_directories(src)			# Расположение заголовочных файлов

add_executable(svwm_test ${SOURCE_EXE})	# Создает исполняемый файл с именем main

add_subdirectory(src)				# Добавление подпроекта, указывается имя дирректории

target_link_libraries(svwm_test svwm)		# Линковка программы с библиотекой