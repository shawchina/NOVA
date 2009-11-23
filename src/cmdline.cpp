/*
 * Command Line Parser
 *
 * Copyright (C) 2006-2008, Udo Steinberg <udo@hypervisor.org>
 *
 * This file is part of the NOVA microhypervisor.
 *
 * NOVA is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * NOVA is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License version 2 for more details.
 */

#include "cmdline.h"
#include "string.h"

bool Cmdline::noacpi;
bool Cmdline::noapic;
bool Cmdline::nodmar;
bool Cmdline::noept;
bool Cmdline::nokeyb;
bool Cmdline::nomp;
bool Cmdline::noserial;
bool Cmdline::nosmx;
bool Cmdline::nospinner;
bool Cmdline::novga;
bool Cmdline::novpid;

struct param
{
    char const *string;
    bool *param;
} params[] INITDATA =
{
    { "noacpi",     &Cmdline::noacpi    },
    { "noapic",     &Cmdline::noapic    },
    { "nodmar",     &Cmdline::nodmar    },
    { "noept",      &Cmdline::noept     },
    { "nokeyb",     &Cmdline::nokeyb    },
    { "nomp",       &Cmdline::nomp      },
    { "noserial",   &Cmdline::noserial  },
    { "nosmx",      &Cmdline::nosmx     },
    { "nospinner",  &Cmdline::nospinner },
    { "novga",      &Cmdline::novga     },
    { "novpid",     &Cmdline::novpid    },
};

char *Cmdline::get_arg (char **line)
{
    for (; **line == ' '; ++*line) ;

    if (!**line)
        return 0;

    char *arg = *line;

    for (; **line != ' '; ++*line)
        if (!**line)
            return arg;

    *(*line)++ = 0;

    return arg;
}

void Cmdline::init (char *line)
{
    char *arg;

    while ((arg = get_arg (&line)))
        for (unsigned i = 0; i < sizeof params / sizeof *params; i++)
            if (!strcmp (static_cast<char const *>(phys_ptr (params[i].string)), arg))
                *static_cast<bool *>(phys_ptr (params[i].param)) = true;
}