cmake_minimum_required(VERSION 3.14.0)

option(SMTG_ENABLE_VST3_PLUGIN_EXAMPLES "Enable VST 3 Plug-in Examples" OFF)
option(SMTG_ENABLE_VST3_HOSTING_EXAMPLES "Enable VST 3 Hosting Examples" OFF)

set(CMAKE_OSX_DEPLOYMENT_TARGET 10.13 CACHE STRING "")

set(vst3sdk_SOURCE_DIR "D:/Files/Dev/VST/Tools/VST_SDK/vst3sdk")
if(NOT vst3sdk_SOURCE_DIR)
    message(FATAL_ERROR "Path to VST3 SDK is empty!")
endif()

project(Knob
    # This is your plug-in version number. Change it here only.
    # Version number symbols usable in C++ can be found in
    # source/version.h and ${PROJECT_BINARY_DIR}/projectversion.h.
    VERSION 1.0.0.0 
    DESCRIPTION "Knob VST 3 Plug-in"
)

set(SMTG_VSTGUI_ROOT "${vst3sdk_SOURCE_DIR}")

add_subdirectory(${vst3sdk_SOURCE_DIR} ${PROJECT_BINARY_DIR}/vst3sdk)
smtg_enable_vst3_sdk()

smtg_add_vst3plugin(Knob
    source/version.h
    source/Knobcids.h
    source/Knobprocessor.h
    source/Knobprocessor.cpp
    source/Knobcontroller.h
    source/Knobcontroller.cpp
    source/Knobentry.cpp
)

#- VSTGUI Wanted ----
if(SMTG_ENABLE_VSTGUI_SUPPORT)
    target_sources(Knob
        PRIVATE
            resource/Knobeditor.uidesc
    )
    target_link_libraries(Knob
        PRIVATE
            vstgui_support
    )
    smtg_target_add_plugin_resources(Knob
        RESOURCES
            "resource/Knobeditor.uidesc"
    )
endif(SMTG_ENABLE_VSTGUI_SUPPORT)
# -------------------

smtg_target_add_plugin_snapshots (Knob
    RESOURCES
        resource/A941DA315023534E851BB72336DF16A2_snapshot.png
        resource/A941DA315023534E851BB72336DF16A2_snapshot_2.0x.png
)

target_link_libraries(Knob
    PRIVATE
        sdk
)

smtg_target_configure_version_file(Knob)

if(SMTG_MAC)
    smtg_target_set_bundle(Knob
        BUNDLE_IDENTIFIER com.oxa.knob
        COMPANY_NAME "oxa"
    )
    smtg_target_set_debug_executable(Knob
        "/Applications/VST3PluginTestHost.app"
        "--pluginfolder;$(BUILT_PRODUCTS_DIR)"
    )
elseif(SMTG_WIN)
    target_sources(Knob PRIVATE 
        resource/win32resource.rc
    )
    if(MSVC)
        set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Knob)

        smtg_target_set_debug_executable(Knob
            "$(ProgramW6432)/Steinberg/VST3PluginTestHost/VST3PluginTestHost.exe"
            "--pluginfolder \"$(OutDir)/\""
        )
    endif()
endif(SMTG_MAC)
