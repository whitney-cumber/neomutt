/**
 * @file
 * Struct to store the cursor position when entering text
 *
 * @authors
 * Copyright (C) 2017 Richard Russon <rich@flatcap.org>
 *
 * @copyright
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 2 of the License, or (at your option) any later
 * version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef MUTT_ENTER_STATE_H
#define MUTT_ENTER_STATE_H

#include <stddef.h>
#include <wchar.h> // IWYU pragma: keep

// Observers of #NT_ENTER will not be passed any Event data.
typedef uint8_t NotifyEnter;          ///< Flags, e.g. #NT_ENTER_CURSOR
#define NT_ENTER_NO_FLAGS         0   ///< No flags are set
#define NT_ENTER_CURSOR     (1 << 0)  ///< Cursor has moved
#define NT_ENTER_TEXT       (1 << 1)  ///< Text has changed
#define NT_ENTER_VIEW       (1 << 2)  ///< View has changed

/**
 * struct EnterState - Keep our place when entering a string
 */
struct EnterState
{
  wchar_t *wbuf;         ///< Buffer for the string being entered
  size_t wbuflen;        ///< Length of buffer
  size_t lastchar;       ///< Position of the last character
  size_t curpos;         ///< Position of the cursor
  mbstate_t mbstate;     ///< Multi-byte state
  struct Notify *notify; ///< Notifications: #NotifyEnter
};

void               enter_state_free(struct EnterState **ptr);
struct Notify *    enter_state_get_notify(struct EnterState *es);
struct EnterState *enter_state_new(void);
void               enter_state_resize(struct EnterState *es, size_t num);

#endif /* MUTT_ENTER_STATE_H */
