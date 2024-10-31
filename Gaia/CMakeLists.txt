find_package(OpenGL REQUIRED)

project(Gaia)

if(WIN32)
    if(MLN_WITH_OSMESA)
        message(WARNING "gaia does not work with -DMLN_WITH_OSMESA=ON. If you want to build this target, don't use this option.")
        return()
    endif()

    find_package(glfw3 REQUIRED)
    find_package(libuv REQUIRED)
else()
    find_package(PkgConfig REQUIRED)

    pkg_search_module(GLFW glfw3 REQUIRED)
endif()

add_executable(
    gaia
        Gaia/src/Core/glfw_backend.hpp
        Gaia/src/Core/glfw_gl_backend.cpp
        Gaia/src/Core/glfw_gl_backend.hpp
        Gaia/src/Core/glfw_renderer_frontend.cpp
        Gaia/src/Core/glfw_renderer_frontend.hpp
        Gaia/src/Core/glfw_view.cpp
        Gaia/src/Core/glfw_view.hpp
        Gaia/src/Core/ny_route.hpp
        Gaia/src/Core/settings_json.cpp
        Gaia/src/Core/settings_json.hpp
        Gaia/src/main.cpp
        Gaia/src/ImGui/ImGuiBuild.cpp
        Gaia/src/ImGui/ImGuiLayer.cpp
        Gaia/src/ImGui/ImGuiLayer.h
        Gaia/src/Core/test_writer.cpp
        Gaia/src/Core/test_writer.hpp
)

set_property(
    SOURCE ${PROJECT_SOURCE_DIR}/Gaia/src/Core/glfw_view.cpp
    PROPERTY COMPILE_DEFINITIONS MAPBOX_PUCK_ASSETS_PATH=\"${PROJECT_SOURCE_DIR}/Gaia/assets/\"
)

if(MLN_WITH_OPENGL)
    target_sources(
        gaia
        PRIVATE ${PROJECT_SOURCE_DIR}/Gaia/src/Core/glfw_gl_backend.cpp
    )
    target_compile_definitions(
        gaia
        PRIVATE MLN_RENDER_BACKEND_OPENGL=1
    )
endif()

if(MLN_WITH_EGL)
    target_compile_definitions(
        gaia
        PRIVATE MBGL_WITH_EGL=1
    )
endif()

if(MLN_WITH_VULKAN)
    target_sources(
        gaia
        PRIVATE ${PROJECT_SOURCE_DIR}/platform/glfw/glfw_vulkan_backend.cpp
    )
    
    target_compile_definitions(
        gaia
        PRIVATE MLN_RENDER_BACKEND_VULKAN=1
    )
endif()

if(MLN_WITH_METAL)
    target_sources(
        gaia
        PRIVATE
        ${PROJECT_SOURCE_DIR}/platform/glfw/glfw_metal_backend.mm
        ${PROJECT_SOURCE_DIR}/platform/glfw/metal_backend.mm
        ${PROJECT_SOURCE_DIR}/platform/glfw/glfw_metal_backend.h
        ${PROJECT_SOURCE_DIR}/platform/glfw/metal_backend.h
    )
    target_compile_definitions(
        gaia
        PRIVATE MLN_RENDER_BACKEND_METAL=1
    )
    target_link_libraries(
        gaia
        PRIVATE
        mbgl-vendor-metal-cpp
    )
endif()

target_include_directories(
    gaia
    PRIVATE
        ${GLFW_INCLUDE_DIRS}
        # For /platform/default/src/mbgl/map/map_snapshotter.hpp
    PRIVATE ${PROJECT_SOURCE_DIR}/src
    PRIVATE ${PROJECT_SOURCE_DIR}/vendor/imgui
        PRIVATE ${PROJECT_SOURCE_DIR}/Gaia/src/Core
        PRIVATE ${PROJECT_SOURCE_DIR}/Gaia/src/ImGui
)

# Use target_link_directories when we move away from CMake 3.10.
target_link_libraries(
    gaia
    PRIVATE $<$<BOOL:${GLFW_LIBRARY_DIRS}>:-L${GLFW_LIBRARY_DIRS}>
)

if(WIN32)
    target_compile_definitions(
        gaia
        PRIVATE
            NOMINMAX
            CURL_STATICLIB
    )

    target_link_libraries(
        gaia
        PRIVATE
            glfw
            $<IF:$<TARGET_EXISTS:libuv::uv_a>,libuv::uv_a,libuv::uv>
    )
else()
    target_link_libraries(
        gaia
        PRIVATE
            ${GLFW_LIBRARIES}
    )
endif()

target_link_libraries(
    gaia
    PRIVATE
        Mapbox::Base::Extras::args
        Mapbox::Base::Extras::filesystem
        Mapbox::Base::Extras::rapidjson
        Mapbox::Map
        mbgl-compiler-options
        Mapbox::Base::cheap-ruler-cpp
)

target_link_libraries(
        gaia
        PRIVATE imgui
)

if(NOT WIN32 AND MLN_WITH_OPENGL)
    target_link_libraries(
        gaia
        PRIVATE OpenGL::GL
    )
endif()


set_property(TARGET gaia PROPERTY FOLDER MapLibre)

install(TARGETS gaia RUNTIME DESTINATION bin)
