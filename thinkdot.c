/*
 * thinkdot - Turn on and off the ThinkPad lid dot
 * Copyright (C) 2025  Connor Thomson
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    FILE *f;

    if (argc != 2) {
        fprintf(stderr, "thinkdot: usage: %s [on|off]\n", argv[0]);
        return 1;
    }

    if (geteuid() != 0) {
        fprintf(stderr, "thinkdot: must be run as root\n");
        return 1;
    }

    f = fopen("/sys/class/leds/tpacpi::lid_logo_dot/brightness", "w");
    if (!f) {
        perror("thinkdot: failed to open brightness");
        return 1;
    }

    if (strcmp(argv[1], "on") == 0) {
        fputs("1", f);
	fprintf(stderr, "thinkdot: turned on\n");
    } else if (strcmp(argv[1], "off") == 0) {
        fputs("0", f);
	fprintf(stderr, "thinkdot: turned off\n");
    } else {
        fprintf(stderr, "invalid argument: %s\n", argv[1]);
        fclose(f);
        return 1;
    }

    fclose(f);
    return 0;
}
