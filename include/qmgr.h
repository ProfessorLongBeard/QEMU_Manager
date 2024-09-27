#ifndef QMGR_H
#define QMGR_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdarg.h>

#include <gtk/gtk.h>
#include <json-c/json.h>

#include <css.h>
#include <builder.h>
#include <widget.h>
#include <notebook.h>
#include <qmgr_lib.h>
#include <message_box.h>

#include <callbacks/cb_exit.h>
#include <callbacks/cb_uefi_mode.h>
#include <callbacks/cb_open_fd.h>
#include <callbacks/cb_open_rom.h>
#include <callbacks/cb_hdd_create.h>
#include <callbacks/cb_save_vm.h>

#endif