/*
 * User Thread Control Block (UTCB): Architecture-Independent
 *
 * Copyright (C) 2009-2011 Udo Steinberg <udo@hypervisor.org>
 * Economic rights: Technische Universitaet Dresden (Germany)
 *
 * Copyright (C) 2012-2013 Udo Steinberg, Intel Corporation.
 * Copyright (C) 2019-2020 Udo Steinberg, BedRock Systems, Inc.
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

#pragma once

#include "buddy.hpp"
#include "utcb_arch.hpp"

class Utcb
{
    private:
        union {
            mword mr[Mtd_user::items];
            Utcb_arch state;
        };

    public:
        inline auto arch() { return &state; }

        inline void copy (Mtd_user mtd, Utcb *dst) const
        {
            for (unsigned i = 0; i < mtd.count(); i++)
                dst->mr[i] = mr[i];
        }

        static inline void *operator new (size_t) noexcept
        {
            return Buddy::alloc (0, Buddy::Fill::BITS0);
        }

        static inline void operator delete (void *ptr)
        {
            if (EXPECT_TRUE (ptr))
                Buddy::free (ptr);
        }
};
