macro(BUILD_LIB_MACRO lib_target)
    aux_source_directory(. SOURCE_CODE)
    list(REMOVE_ITEM SOURCE_CODE ${CMAKE_CURRENT_SOURCE_DIR}/main.c*)
    add_library(${lib_target} ${SOURCE_CODE})
    set_target_properties(${lib_target} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_INSTALL_PREFIX}/lib)
    set_target_properties(${lib_target} PROPERTIES VERSION 1.0)
endmacro(BUILD_LIB_MACRO lib_target)

macro(BUILD_SERVER_MACRO project_name)
    project(${project_name} CXX)
	aux_source_directory(. SOURCE_CODE)
	add_executable(${project_name} ${SOURCE_CODE})
    set_target_properties(${project_name} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_INSTALL_PREFIX})
endmacro(BUILD_SERVER_MACRO project_name)

macro(BUILD_MAIN_MACRO main_file)
        add_executable(${main_file} ${main_file}.cc)
    set_target_properties(${main_file} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_INSTALL_PREFIX}/test)
endmacro(BUILD_MAIN_MACRO main_file)