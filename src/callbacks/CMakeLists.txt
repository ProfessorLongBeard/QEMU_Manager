target_sources(${MGR_TARGET} PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/cb_exit.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/cb_uefi_mode.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/cb_open_fd.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/cb_open_rom.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/cb_hdd_create.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/cb_save_vm.c"
)