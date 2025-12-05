cmake_minimum_required(VERSION 3.10)
project(GPU_Engine_Project C CXX)

# configuration
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG")
set(CMAKE_CXX_FLAGS_DEBUG "-g")

set(LINUX_BUILD_DIR "${CMAKE_BINARY_DIR}/linux")
set(WIN_BUILD_DIR "${CMAKE_BINARY_DIR}/win")
set(DIST_DIR "${CMAKE_SOURCE_DIR}/dist")

if(WIN32)
    set(EXECUTABLE_NAME "app")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${WIN_BUILD_DIR})
else()
    set(EXECUTABLE_NAME "app")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${LINUX_BUILD_DIR})
endif()

# source files
file(GLOB_RECURSE ALL_CPP_SOURCES
    "src/*.cpp"
    "src/App/*.cpp"
    "src/Core/*.cpp"
    "src/Render/*.cpp"
    "src/Scene/*.cpp"
)

set(EXTERNAL_GLAD_DIR "external/glad")
file(GLOB GLAD_SOURCES "${EXTERNAL_GLAD_DIR}/*.c")

list(APPEND ALL_SOURCES ${ALL_CPP_SOURCES} ${GLAD_SOURCES})

# glad lib
add_library(glad_lib STATIC ${GLAD_SOURCES})
target_include_directories(glad_lib PUBLIC external/glad)

# executable
add_executable(${EXECUTABLE_NAME} ${ALL_SOURCES})
target_include_directories(${EXECUTABLE_NAME} PUBLIC
    include
    external/glm
    external/glad
    external/stb
    external/assimp/include
		external/GLFW/include
)

# linking
if(WIN32)
    target_link_libraries(${EXECUTABLE_NAME}
        opengl32
        glfw3
				glu32
        gdi32
        user32
        kernel32
        shell32
        advapi32

        ${CMAKE_SOURCE_DIR}/lib/win/libglfw3.a
        ${CMAKE_SOURCE_DIR}/lib/win/libassimp.a
        ${CMAKE_SOURCE_DIR}/lib/win/libzlibstatic.a

        glad_lib
    )

    # copy all required dlls to runtime folder
    add_custom_command(TARGET ${EXECUTABLE_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/lib/win
            $<TARGET_FILE_DIR:${EXECUTABLE_NAME}>
    )
else()
    target_link_libraries(${EXECUTABLE_NAME}
        glad_lib
        assimp
        glfw
        dl
        pthread
        GL
    )
endif()

# run target
add_custom_target(run
    COMMAND ${CMAKE_COMMAND} -E chdir ${CMAKE_SOURCE_DIR}
            ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${EXECUTABLE_NAME}
    DEPENDS ${EXECUTABLE_NAME}
)

# distribution targets
add_custom_target(dist-linux
    COMMAND ${CMAKE_COMMAND} -E make_directory ${DIST_DIR}/linux
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${EXECUTABLE_NAME} ${DIST_DIR}/linux/
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/assets ${DIST_DIR}/linux/assets
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/shaders ${DIST_DIR}/linux/shaders
    DEPENDS ${EXECUTABLE_NAME}
)

add_custom_target(dist-win
    COMMAND ${CMAKE_COMMAND} -E make_directory ${DIST_DIR}/win
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${EXECUTABLE_NAME}.exe ${DIST_DIR}/win/
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/assets ${DIST_DIR}/win/assets
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/shaders ${DIST_DIR}/win/shaders
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/lib/win ${DIST_DIR}/win/
    DEPENDS ${EXECUTABLE_NAME}
)

add_custom_target(dist
    COMMAND ${CMAKE_COMMAND} --build . --target dist-linux
    COMMAND ${CMAKE_COMMAND} --build . --target dist-win
)
