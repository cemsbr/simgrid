/* module handling                                                          */

/* Copyright (c) 2006-2013. The SimGrid Team.
 * All rights reserved.                                                     */

/* This program is free software; you can redistribute it and/or modify it
 * under the terms of the license (GNU LGPL) which comes with this package. */

#include "xbt/misc.h"
#include "simgrid_config.h"     /*HAVE_MMAP _XBT_WIN32 */
#include "internal_config.h"        /* MMALLOC_WANT_OVERRIDE_LEGACY */

#include "xbt/sysdep.h"
#include "xbt/log.h"
#include "xbt/dynar.h"
#include "xbt/config.h"

#include "xbt/module.h"         /* this module */

#include "xbt_modinter.h"       /* prototype of other module's init/exit in XBT */

#include "simgrid/sg_config.h"

XBT_LOG_NEW_CATEGORY(xbt, "All XBT categories (simgrid toolbox)");
XBT_LOG_NEW_DEFAULT_SUBCATEGORY(module, xbt, "module handling");

XBT_LOG_NEW_CATEGORY(smpi, "All SMPI categories"); /* lives here even if that's a bit odd to solve linking issues: this is used in xbt_log_file_appender to detect whether SMPI is used (and thus whether we should unbench the writing to disk) */


char *xbt_binary_name = NULL;   /* Name of the system process containing us (mandatory to retrieve neat backtraces) */
xbt_dynar_t xbt_cmdline = NULL; /* all we got in argv */

int xbt_initialized = 0;
int _sg_do_clean_atexit = 1;

/* Declare xbt_preinit and xbt_postexit as constructor/destructor of the library.
 * This is crude and rather compiler-specific, unfortunately.
 */
static void xbt_preinit(void) _XBT_GNUC_CONSTRUCTOR(200);
static void xbt_postexit(void);

#ifdef _XBT_WIN32
# undef _XBT_NEED_INIT_PRAGMA
#endif

#ifdef _XBT_NEED_INIT_PRAGMA
#pragma init (xbt_preinit)
#endif

#ifdef _XBT_WIN32
#include <windows.h>

#ifndef __GNUC__
/* Dummy prototype to make gcc happy */
BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason,
                    LPVOID lpvReserved);

/* Should not be necessary but for some reason,
 * DllMain is called twice at attachment and
 * at detachment.*/
static int xbt_dll_process_is_attached = 0;

/* see also http://msdn.microsoft.com/en-us/library/ms682583%28VS.85%29.aspx */
/* and http://www.microsoft.com/whdc/driver/kernel/DLL_bestprac.mspx */
BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason,
                    LPVOID lpvReserved)
{
  if (fdwReason == DLL_PROCESS_ATTACH
      && xbt_dll_process_is_attached == 0) {
    xbt_dll_process_is_attached = 1;
    xbt_preinit();
  } else if (fdwReason == DLL_PROCESS_DETACH
      && xbt_dll_process_is_attached == 1) {
    xbt_dll_process_is_attached = 0;
  }
  return 1;
}
#endif

#endif

static void xbt_preinit(void) {
  unsigned int seed = 2147483647;

#ifdef MMALLOC_WANT_OVERRIDE_LEGACY
  mmalloc_preinit();
#endif
  xbt_log_preinit();
  xbt_backtrace_preinit();
  xbt_os_thread_mod_preinit();
  xbt_fifo_preinit();
  xbt_dict_preinit();
   
  srand(seed);
#ifndef _WIN32
  srand48(seed);
#endif

  atexit(xbt_postexit);
}

static void xbt_postexit(void)
{
  if(!_sg_do_clean_atexit) return;
  xbt_backtrace_postexit();
  xbt_fifo_postexit();
  xbt_dict_postexit();
  xbt_os_thread_mod_postexit();
  xbt_dynar_free(&xbt_cmdline);
  xbt_log_postexit();
  free(xbt_binary_name);
#ifdef MMALLOC_WANT_OVERRIDE_LEGACY
  mmalloc_postexit();
#endif
}

/** @brief Initialize the xbt mechanisms. */
void xbt_init(int *argc, char **argv)
{
  if (xbt_initialized++) {
    XBT_DEBUG("XBT was initialized %d times.", xbt_initialized);
    return;
  }

  xbt_binary_name = xbt_strdup(argv[0]);
  xbt_cmdline = xbt_dynar_new(sizeof(char*),NULL);
  int i;
  for (i=0;i<*argc;i++) {
    xbt_dynar_push(xbt_cmdline,&(argv[i]));
  }
  
  xbt_log_init(argc, argv);
}

/** @brief Finalize the xbt mechanisms.
 *  @warning this function is deprecated. Just don't call it, there is nothing more to do to finalize xbt*/
void xbt_exit()
{
  XBT_WARN("This function is deprecated, you shouldn't use it");
}


/* these two functions belong to xbt/sysdep.h, which have no corresponding .c file */
/** @brief like free, but you can be sure that it is a function  */
XBT_PUBLIC(void) xbt_free_f(void *p)
{
  free(p);
}

/** @brief should be given a pointer to pointer, and frees the second one */
XBT_PUBLIC(void) xbt_free_ref(void *d)
{
  free(*(void **) d);
}
