target_sources(${MGR_TARGET} PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/main.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/css.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/qmgr_lib.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/builder.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/widget.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/notebook.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/message_box.c"
)

add_subdirectory(callbacks)