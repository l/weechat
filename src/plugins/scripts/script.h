/*
 * Copyright (c) 2003-2008 by FlashCode <flashcode@flashtux.org>
 * See README for License detail, AUTHORS for developers list.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __WEECHAT_SCRIPT_H
#define __WEECHAT_SCRIPT_H 1

/* constants which defines return types for weechat_<lang>_exec functions */
#define WEECHAT_SCRIPT_EXEC_INT    1
#define WEECHAT_SCRIPT_EXEC_STRING 2

#define WEECHAT_SCRIPT_MSG_NOT_INITIALIZED(__function)                  \
    weechat_printf (NULL,                                               \
                    weechat_gettext("%s%s: unable to call function "    \
                                    "\"%s\", script is not "            \
                                    "initialized"),                     \
                    weechat_prefix ("error"), weechat_plugin->name,     \
                    __function)
#define WEECHAT_SCRIPT_MSG_WRONG_ARGUMENTS(__function)                  \
    weechat_printf (NULL,                                               \
                    weechat_gettext("%s%s: wrong arguments for "        \
                                    "function \"%s\""),                 \
                    weechat_prefix ("error"), weechat_plugin->name,     \
                    __function)

struct t_plugin_script
{
    /* script variables */
    char *filename;                      /* name of script on disk          */
    void *interpreter;                   /* interpreter for script          */
    char *name;                          /* script name                     */
    char *author;                        /* author name/mail                */
    char *version;                       /* plugin version                  */
    char *license;                       /* script license                  */
    char *description;                   /* plugin description              */
    char *shutdown_func;                 /* function when script is unloaded*/
    char *charset;                       /* script charset                  */
    
    struct t_script_callback *callbacks; /* callbacks for script            */
    
    struct t_plugin_script *prev_script; /* link to previous script         */
    struct t_plugin_script *next_script; /* link to next script             */
};

extern void script_init (struct t_weechat_plugin *weechat_plugin,
                         int (*callback_command)(void *data,
                                                 struct t_gui_buffer *buffer,
                                                 int argc, char **argv,
                                                 char **argv_eol),
                         int (*callback_completion)(void *data, char *completion,
                                                    struct t_gui_buffer *buffer,
                                                    struct t_weelist *list),
                         int (*callback_signal_debug_dump)(void *data,
                                                           char *signal,
                                                           char *type_data,
                                                           void *signal_data),
                         int (*callback_load_file)(void *data, char *filename));
extern char *script_ptr2str (void *pointer);
extern void *script_str2ptr (char *pointer_str);
extern void script_auto_load (struct t_weechat_plugin *weechat_plugin,
                              int (*callback)(void *data, char *filename));
extern struct t_plugin_script *script_search (struct t_weechat_plugin *weechat_plugin,
                                              struct t_plugin_script *scripts,
                                              char *name);
extern char *script_search_full_name (struct t_weechat_plugin *weechat_plugin,
                                      char *filename);
extern struct t_plugin_script *script_add (struct t_weechat_plugin *weechat_plugin,
                                           struct t_plugin_script **scripts,
                                           char *filename, char *name,
                                           char *author, char *version,
                                           char *license, char *description,
                                           char *shutdown_func, char *charset);
extern void script_remove (struct t_weechat_plugin *weechat_plugin,
                           struct t_plugin_script **scripts,
                           struct t_plugin_script *script);
extern void script_completion (struct t_weechat_plugin *weechat_plugin,
                               struct t_weelist *list,
                               struct t_plugin_script *scripts);
extern void script_display_list (struct t_weechat_plugin *weechat_plugin,
                                 struct t_plugin_script *scripts,
                                 char *name, int full);
extern void script_print_log (struct t_weechat_plugin *weechat_plugin,
                              struct t_plugin_script *scripts);

#endif /* script.h */
