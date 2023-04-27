load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")

cc_library(
    name = "axis_motion_event",
    srcs = ["AxisMotionEvent.cpp"],
    hdrs = ["AxisMotionEvent.h"],
)

cc_library(
    name = "bmp",
    srcs = ["bmp.cpp"],
    hdrs = ["bmp.h"],
    deps = ["texture"],
)

cc_library(
    name = "camera",
    srcs = ["camera.cpp"],
    hdrs = ["camera.h"],
    deps = [
        "window",
    ],
)

cc_library(
    name = "ctrls",
    srcs = ["ctrls.cpp"],
    hdrs = ["ctrls.h"],
    deps = [
        "keys",
        "strmanip",
    ],
)

cc_library(
    name = "draw_event",
    srcs = ["DrawEvent.cpp"],
    hdrs = ["DrawEvent.h"],
    deps = [
        "event",
        "level",
        "main",
    ],
)

cc_library(
    name = "event",
    srcs = ["Event.cpp"],
    hdrs = ["Event.h"],
    deps = ["object"],
)

cc_library(
    name = "event_manager",
    srcs = ["EventManager.cpp"],
    hdrs = ["EventManager.h"],
    deps = [
        "event",
        "list",
    ],
)

cc_library(
    name = "geometry",
    hdrs = ["geometry.h"],
)

cc_library(
    name = "image",
    hdrs = ["image.h"],
)

cc_library(
    name = "keys",
    srcs = ["keys.cpp"],
    hdrs = ["keys.h"],
)

cc_library(
    name = "key_press_event",
    srcs = ["KeyPressEvent.cpp"],
    hdrs = ["KeyPressEvent.h"],
    deps = [
        "event",
        "keys",
        "main",
    ],
)

cc_library(
    name = "key_release_event",
    srcs = ["KeyReleaseEvent.cpp"],
    hdrs = ["KeyReleaseEvent.h"],
    deps = [
        "event",
        "keys",
        "main",
    ],
)

cc_library(
    name = "level",
    srcs = ["level.cpp"],
    hdrs = ["level.h"],
    deps = [
        "bmp",
        "camera",
        "geometry",
        "keys",
        "list",
        "mydefs",
        "mygl_font",
        "mygl_texture",
        "player",
        "strmanip",
        "tga",
        "vector",
        "version",
    ],
)

cc_library(
    name = "linux",
    srcs = ["linux.cpp"],
)

cc_library(
    name = "list",
    hdrs = ["list.h"],
)

cc_library(
    name = "logger",
    hdrs = ["Logger.h"],
)

cc_binary(
    name = "macosx",
    srcs = ["macosx.cpp"],
    copts = ["-framework OpenGL"],
    deps = [
        "draw_event",
        "event_manager",
        "key_press_event",
        "key_release_event",
        "main",
        "version",
        "x11",
    ],
)

cc_library(
    name = "main",
    hdrs = ["main.h"],
    deps = [
        "level",
        "world_defs",
    ],
)

cc_library(
    name = "model",
    srcs = ["Model.cpp"],
    hdrs = ["Model.h"],
)

cc_library(
    name = "mydefs",
    hdrs = ["mydefs.h"],
)

cc_library(
    name = "mygl",
    srcs = ["mygl.cpp"],
    hdrs = ["mygl.h"],
    deps = [
        "bmp",
        "strmanip",
        "texture",
        "tga",
        "window",
    ],
)

cc_library(
    name = "mygl_font",
    srcs = ["myglFont.cpp"],
    hdrs = ["myglFont.h"],
    deps = ["mygl"],
)

cc_library(
    name = "mygl_texture",
    srcs = ["myglTexture.cpp"],
    hdrs = ["myglTexture.h"],
    deps = ["mygl"],
)

cc_library(
    name = "null_video_plugin",
    srcs = ["NullVideoPlugin.cpp"],
    hdrs = ["NullVideoPlugin.h"],
    deps = [
        "video_plugin",
    ],
)

cc_library(
    name = "object",
    srcs = ["Object.cpp"],
    hdrs = ["Object.h"],
)

cc_library(
    name = "player",
    srcs = ["player.cpp"],
    hdrs = ["player.h"],
    deps = [
        "camera",
        "ctrls",
        "event_manager",
    ],
)

cc_library(
    name = "plugin",
    hdrs = ["Plugin.h"],
)

cc_library(
    name = "plugin_manager",
    srcs = ["PluginManager.cpp"],
    hdrs = ["PluginManager.h"],
    deps = [
        "list",
        "null_video_plugin",
        "plugin",
        "video_plugin",
    ],
)

cc_library(
    name = "point",
    srcs = ["Point.cpp"],
    hdrs = ["Point.h"],
)

cc_library(
    name = "rectangle",
    srcs = ["Rectangle.cpp"],
    hdrs = ["Rectangle.h"],
)

cc_library(
    name = "screen",
    srcs = ["screen.cpp"],
    hdrs = ["screen.h"],
)

cc_library(
    name = "strmanip",
    srcs = ["strmanip.cpp"],
    hdrs = ["strmanip.h"],
    deps = ["keys"],
)

cc_library(
    name = "texture",
    hdrs = ["texture.h"],
)

cc_library(
    name = "tga",
    srcs = ["tga.cpp"],
    hdrs = ["tga.h"],
    deps = ["texture"],
)

cc_library(
    name = "vector",
    srcs = ["vector.cpp"],
    hdrs = ["vector.h"],
)

cc_library(
    name = "version",
    hdrs = ["version.h"],
)

cc_library(
    name = "video_plugin",
    hdrs = ["VideoPlugin.h"],
    deps = [
        "plugin",
        "window",
    ],
)

cc_library(
    name = "window",
    srcs = ["window.cpp"],
    hdrs = ["window.h"],
    deps = [
        "screen",
        "vector",
    ],
)

cc_library(
    name = "windows",
    srcs = ["windows.cpp"],
)

cc_library(
    name = "windows_logger",
    srcs = ["WindowsLogger.cpp"],
    hdrs = ["WindowsLogger.h"],
    deps = ["logger"],
)

cc_library(
    name = "world_defs",
    hdrs = ["worlddefs.h"],
)

cc_library(
    name = "x11",
    srcs = ["x11.cpp"],
    hdrs = ["x11.h"],
)
