load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")

cc_library(
    name = "axis_motion_event",
    srcs = ["AxisMotionEvent.cpp"],
    hdrs = ["AxisMotionEvent.h"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "bmp",
    srcs = ["bmp.cpp"],
    hdrs = ["bmp.h"],
    visibility = ["//visibility:public"],
    deps = [
        ":config",
        ":image",
        ":logger",
        ":opengl",
        ":texture",
    ],
)

cc_library(
    name = "camera",
    srcs = ["camera.cpp"],
    hdrs = ["camera.h"],
    visibility = ["//visibility:public"],
    deps = [
        ":config",
        ":window",
    ],
)

cc_test(
    name = "camera_test",
    srcs = ["camera_test.cpp"],
    deps = [
        ":camera",
        ":config",
        "@TinyTest//:tinytest",
    ],
)

cc_library(
    name = "config",
    hdrs = ["config.h"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "console_logger",
    srcs = ["console_logger.cpp"],
    hdrs = ["console_logger.h"],
    visibility = ["//visibility:public"],
    deps = [
        ":config",
        ":logger",
    ],
)

cc_test(
    name = "console_logger_test",
    srcs = ["console_logger_test.cpp"],
    deps = [
        "console_logger",
        "@TinyTest//:tinytest",
    ],
)

cc_library(
    name = "ctrls",
    srcs = ["ctrls.cpp"],
    hdrs = ["ctrls.h"],
    visibility = ["//visibility:public"],
    deps = [
        ":config",
        ":keys",
        ":strmanip",
    ],
)

cc_library(
    name = "draw_event",
    srcs = ["DrawEvent.cpp"],
    hdrs = ["DrawEvent.h"],
    visibility = ["//visibility:public"],
    deps = [
        ":config",
        ":event",
        ":level",
        ":main",
    ],
)

cc_library(
    name = "event",
    srcs = ["Event.cpp"],
    hdrs = ["Event.h"],
    visibility = ["//visibility:public"],
    deps = [
        ":config",
        ":object",
    ],
)

cc_library(
    name = "event_manager",
    srcs = ["EventManager.cpp"],
    hdrs = ["EventManager.h"],
    visibility = ["//visibility:public"],
    deps = [
        ":config",
        ":event",
    ],
)

cc_library(
    name = "geometry",
    srcs = ["geometry.cpp"],
    hdrs = ["geometry.h"],
    visibility = ["//visibility:public"],
    deps = [
        ":mygl_texture",
        ":vector",
    ],
)

cc_library(
    name = "image",
    srcs = ["image.cpp"],
    hdrs = ["image.h"],
    visibility = ["//visibility:public"],
    deps = [
        ":config",
        ":logger",
        ":opengl",
        ":texture",
    ],
)

cc_library(
    name = "keys",
    srcs = ["keys.cpp"],
    hdrs = ["keys.h"],
    visibility = ["//visibility:public"],
    deps = [":config"],
)

cc_library(
    name = "key_press_event",
    srcs = ["KeyPressEvent.cpp"],
    hdrs = ["KeyPressEvent.h"],
    visibility = ["//visibility:public"],
    deps = [
        ":config",
        ":event",
        ":keys",
        ":main",
    ],
)

cc_library(
    name = "key_release_event",
    srcs = ["KeyReleaseEvent.cpp"],
    hdrs = ["KeyReleaseEvent.h"],
    visibility = ["//visibility:public"],
    deps = [
        ":config",
        ":event",
        ":keys",
        ":main",
    ],
)

cc_library(
    name = "level",
    srcs = ["level.cpp"],
    hdrs = ["level.h"],
    visibility = ["//visibility:public"],
    deps = [
        ":bmp",
        ":camera",
        ":config",
        ":geometry",
        ":keys",
        ":logger",
        ":mydefs",
        ":mygl_font",
        ":mygl_texture",
        ":player",
        ":strmanip",
        ":tga",
        ":vector",
        ":version",
    ],
)

cc_library(
    name = "linux",
    srcs = ["linux.cpp"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "logger",
    srcs = ["Logger.cpp"],
    hdrs = ["Logger.h"],
    visibility = ["//visibility:public"],
)

cc_binary(
    name = "macosx",
    srcs = ["macosx.cpp"],
    copts = ["-framework OpenGL"],
    target_compatible_with = ["@platforms//os:macos"],
    deps = [
        ":config",
        ":draw_event",
        ":event_manager",
        ":key_press_event",
        ":key_release_event",
        ":main",
        ":version",
        ":x11",
    ],
)

cc_library(
    name = "main",
    hdrs = ["main.h"],
    visibility = ["//visibility:public"],
    deps = [
        ":config",
        ":level",
        ":world_defs",
    ],
)

cc_library(
    name = "model",
    srcs = ["Model.cpp"],
    hdrs = ["Model.h"],
    visibility = ["//visibility:public"],
    deps = [":config"],
)

cc_library(
    name = "mydefs",
    hdrs = ["mydefs.h"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "mygl",
    srcs = ["mygl.cpp"],
    hdrs = ["mygl.h"],
    visibility = ["//visibility:public"],
    deps = [
        ":bmp",
        ":config",
        ":logger",
        ":strmanip",
        ":texture",
        ":tga",
        ":window",
    ],
)

cc_library(
    name = "mygl_font",
    srcs = ["myglFont.cpp"],
    hdrs = ["myglFont.h"],
    visibility = ["//visibility:public"],
    deps = [
        ":config",
        ":mygl",
    ],
)

cc_library(
    name = "mygl_texture",
    srcs = ["myglTexture.cpp"],
    hdrs = ["myglTexture.h"],
    visibility = ["//visibility:public"],
    deps = [
        ":config",
        ":logger",
        ":mygl",
    ],
)

cc_library(
    name = "opengl",
    hdrs = ["opengl.h"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "object",
    srcs = ["Object.cpp"],
    hdrs = ["Object.h"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "player",
    srcs = ["player.cpp"],
    hdrs = ["player.h"],
    visibility = ["//visibility:public"],
    deps = [
        ":camera",
        ":config",
        ":ctrls",
        ":event_manager",
    ],
)

cc_library(
    name = "point",
    srcs = ["Point.cpp"],
    hdrs = ["Point.h"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "rectangle",
    srcs = ["Rectangle.cpp"],
    hdrs = ["Rectangle.h"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "screen",
    srcs = ["screen.cpp"],
    hdrs = ["screen.h"],
    visibility = ["//visibility:public"],
    deps = [":config"],
)

cc_library(
    name = "strmanip",
    srcs = ["strmanip.cpp"],
    hdrs = ["strmanip.h"],
    visibility = ["//visibility:public"],
    deps = [
        ":config",
        ":keys",
    ],
)

cc_library(
    name = "texture",
    hdrs = ["texture.h"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "tga",
    srcs = ["tga.cpp"],
    hdrs = ["tga.h"],
    visibility = ["//visibility:public"],
    deps = [
        ":config",
        ":image",
        ":logger",
        ":opengl",
        ":texture",
    ],
)

cc_library(
    name = "vector",
    srcs = ["vector.cpp"],
    hdrs = ["vector.h"],
    visibility = ["//visibility:public"],
    deps = [":config"],
)

cc_library(
    name = "version",
    hdrs = ["version.h"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "window",
    srcs = ["window.cpp"],
    hdrs = ["window.h"],
    visibility = ["//visibility:public"],
    deps = [
        #<GL/gl.h> <GL/glu.h>
        ":config",
        ":opengl",
        ":screen",
        ":vector",
    ],
)

cc_binary(
    name = "windows",
    srcs = ["windows.cpp"],
    linkopts = ["/ENTRY:WinMainCRTStartup"],
    target_compatible_with = ["@platforms//os:windows"],
    deps = [
        ":bmp",
        ":camera",
        ":config",
        ":console_logger",
        ":ctrls",
        ":draw_event",
        ":event",
        ":event_manager",
        ":geometry",
        ":key_press_event",
        ":key_release_event",
        ":keys",
        ":level",
        ":logger",
        ":main",
        ":mydefs",
        ":mygl",
        ":mygl_font",
        ":mygl_texture",
        ":object",
        ":opengl",
        ":player",
        ":screen",
        ":strmanip",
        ":texture",
        ":tga",
        ":vector",
        ":version",
        ":windows_logger",
        ":world_defs",
        "//opengl:window",
    ],
)

cc_library(
    name = "windows_logger",
    srcs = ["WindowsLogger.cpp"],
    hdrs = ["WindowsLogger.h"],
    visibility = ["//visibility:public"],
    deps = [
        ":config",
        ":logger",
    ],
)

cc_library(
    name = "world_defs",
    hdrs = [":worlddefs.h"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "x11",
    srcs = [":x11.cpp"],
    hdrs = [":x11.h"],
    visibility = ["//visibility:public"],
    deps = [":config"],
)
