/*  SSNES - A Super Nintendo Entertainment System (SNES) Emulator frontend for libsnes.
 *  Copyright (C) 2010-2011 - Hans-Kristian Arntzen
 *
 *  Some code herein may be based on code found in BSNES.
 * 
 *  SSNES is free software: you can redistribute it and/or modify it under the terms
 *  of the GNU General Public License as published by the Free Software Found-
 *  ation, either version 3 of the License, or (at your option) any later version.
 *
 *  SSNES is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 *  without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 *  PURPOSE.  See the GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along with SSNES.
 *  If not, see <http://www.gnu.org/licenses/>.
 */

#include "gfx_common.h"
#include "general.h"
#include <sys/time.h>

static float tv_to_fps(const struct timeval *tv, const struct timeval *new_tv, int frames)
{
   float time = new_tv->tv_sec - tv->tv_sec + (new_tv->tv_usec - tv->tv_usec)/1000000.0;
   return frames/time;
}

bool gfx_window_title(char *buf, size_t size)
{
   static int frames = 0;
   static struct timeval tv;
   struct timeval new_tv;
   bool ret = false;

   if (frames == 0)
   {
      gettimeofday(&tv, NULL);
      snprintf(buf, size, "%s", g_extern.title_buf);
      ret = true;
   }

   if ((frames % 180) == 0 && frames > 0)
   {
      gettimeofday(&new_tv, NULL);
      struct timeval tmp_tv = tv;
      tv = new_tv;

      float fps = tv_to_fps(&tmp_tv, &new_tv, 180);

      snprintf(buf, size, "%s || FPS: %6.1f || Frames: %d", g_extern.title_buf, fps, frames);
      ret = true;
   }

   frames++;
   return ret;
}


