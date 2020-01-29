/**
 * Copyright (c) 2016-2020 Knuth Project.
 *
 * This file is part of Knuth Project.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef KNUTH_INFRASTRUCTURE_PNG_HPP
#define KNUTH_INFRASTRUCTURE_PNG_HPP

#include <cstdint>
#include <istream>

#include <bitcoin/infrastructure/compat.hpp>
#include <bitcoin/infrastructure/define.hpp>
#include <bitcoin/infrastructure/utility/color.hpp>
#include <bitcoin/infrastructure/utility/data.hpp>

#ifdef WITH_PNG
#include <png.h>

namespace libbitcoin {

class BI_API png
{
public:
    static constexpr uint32_t margin = 2;
    static constexpr uint32_t dots_per_inch = 72;
    static constexpr uint32_t inches_per_meter = (100.0 / 2.54);

    static const color get_default_foreground()
    {
        static constexpr color default_foreground{ 0, 0, 0, 255 };
        return default_foreground;
    }

    static const color get_default_background()
    {
        static constexpr color default_background{ 255, 255, 255, 255 };
        return default_background;
    }

    /**
     * A method that takes encoded qrcode as a data chunk and writes it to
     * an output stream in png format with the default parameters.  The
     * size parameter specifies the number of dots (pixels) per qr code
     * modules.
     */
    static bool write_png(data_chunk const& data, uint32_t size,
        std::ostream& out);

    /**
     * A method that takes encoded qrcode data as a data chunk and writes
     * it to an output stream in png format with the specified parameters.
     */
    static bool write_png(data_chunk const& data, uint32_t size,
        uint32_t dots_per_inch, uint32_t margin, uint32_t inches_per_meter,
        const color& foreground, const color& background, std::ostream& out);

    /**
     * A method that reads encoded qrcode data via an input stream and
     * writes it to an output stream in png format with the default
     * parameters.  The size parameter specifies the number of dots
     * (pixels) per qr code modules.
     */
    static bool write_png(std::istream& in, uint32_t size, std::ostream& out);

    /**
     * A method that reads encoded qrcode data via an input stream and
     * writes it to an output stream in png format with the specified
     * parameters.
     */
    static bool write_png(std::istream& in, uint32_t size,
        uint32_t dots_per_inch, const uint32_t margin,
        uint32_t inches_per_meter, const color& foreground,
        const color& background, std::ostream& out);
};

} // namespace libbitcoin

#endif // WITH_PNG

#endif
