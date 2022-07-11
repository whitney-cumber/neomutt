/**
 * @file
 * Test code for mutt_mb_wcstombs()
 *
 * @authors
 * Copyright (C) 2019 Richard Russon <rich@flatcap.org>
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

#define TEST_NO_MAIN
#include "config.h"
#include "acutest.h"
#include <string.h>
#include <wchar.h>
#include "mutt/lib.h"

void test_mutt_mb_wcstombs(void)
{
  // void mutt_mb_wcstombs(char *dest, size_t dlen, const wchar_t *src, size_t slen);

  {
    wchar_t src[32] = L"apple";
    mutt_mb_wcstombs(src, 5, NULL);
    TEST_CHECK_(1, "mutt_mb_wcstombs(NULL, 10, src, 5)");
  }

  {
    struct Buffer *buf = mutt_buffer_pool_get();
    mutt_mb_wcstombs(NULL, 3, buf);
    TEST_CHECK_(1, "mutt_mb_wcstombs(buf, sizeof(buf), NULL, 3)");
    mutt_buffer_pool_release(&buf);
  }

  {
    struct WideTest
    {
      char *name;
      wchar_t *src;
      char *expected;
    };

    struct WideTest test[] = {
      // clang-format off
      { "Greek",     L"Οὐχὶ ταὐτὰ παρίσταταί μοι γιγνώσκειν, ὦ ἄνδρες ᾿Αθηναῖοι",         "Οὐχὶ ταὐτὰ παρίσταταί μοι γιγνώσκειν, ὦ ἄνδρες ᾿Αθηναῖοι" },
      { "Georgian",  L"გთხოვთ ახლავე გაიაროთ რეგისტრაცია Unicode-ის მეათე საერთაშორისო",  "გთხოვთ ახლავე გაიაროთ რეგისტრაცია Unicode-ის მეათე საერთაშორისო" },
      { "Russian",   L"Зарегистрируйтесь сейчас на Десятую Международную Конференцию по", "Зарегистрируйтесь сейчас на Десятую Международную Конференцию по" },
      { "Thai",      L"๏ แผ่นดินฮั่นเสื่อมโทรมแสนสังเวช พระปกเกศกองบู๊กู้ขึ้นใหม่",                     "๏ แผ่นดินฮั่นเสื่อมโทรมแสนสังเวช พระปกเกศกองบู๊กู้ขึ้นใหม่" },
      { "Ethiopian", L"ሰማይ አይታረስ ንጉሥ አይከሰስ።",                                             "ሰማይ አይታረስ ንጉሥ አይከሰስ።" },
      { "Braille",   L"⡍⠜⠇⠑⠹ ⠺⠁⠎ ⠙⠑⠁⠙⠒ ⠞⠕ ⠃⠑⠛⠔ ⠺⠊⠹⠲ ⡹⠻⠑ ⠊⠎ ⠝⠕ ⠙⠳⠃⠞",                      "⡍⠜⠇⠑⠹ ⠺⠁⠎ ⠙⠑⠁⠙⠒ ⠞⠕ ⠃⠑⠛⠔ ⠺⠊⠹⠲ ⡹⠻⠑ ⠊⠎ ⠝⠕ ⠙⠳⠃⠞" },
      { NULL },
      // clang-format on
    };

    struct Buffer *buf = mutt_buffer_pool_get();
    for (size_t i = 0; test[i].src; i++)
    {
      mutt_buffer_reset(buf);
      TEST_CASE(test[i].name);
      size_t len = wcslen(test[i].src);
      mutt_mb_wcstombs(test[i].src, len, buf);

      TEST_CHECK(mutt_str_equal(mutt_buffer_string(buf), test[i].expected));
    }
    mutt_buffer_pool_release(&buf);
  }
}
