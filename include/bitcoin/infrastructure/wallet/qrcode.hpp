// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
#ifndef KTH_INFRASTUCTURE_QRENCODE_HPP
#define KTH_INFRASTUCTURE_QRENCODE_HPP

#include <cstddef>
#include <cstdint>
#include <iostream>

#include <bitcoin/infrastructure/compat.hpp>
#include <bitcoin/infrastructure/define.hpp>
#include <bitcoin/infrastructure/utility/data.hpp>

#ifdef WITH_QRENCODE
#include <qrencode.h>

namespace libbitcoin {
namespace wallet {

class BI_API qr
{
public:
    typedef QRencodeMode encode_mode;
    typedef QRecLevel error_recovery_level;

    static constexpr uint32_t version = 0;
    static constexpr bool case_sensitive = true;
    static constexpr encode_mode mode = QR_MODE_8;
    static constexpr error_recovery_level level = QR_ECLEVEL_L;

    /**
     * A method that takes an input stream and writes the encoded qr data
     * to the specified output stream with default parameter values.
     */
    BI_API static bool encode(std::istream& in, std::ostream& out);

    /**
     * A method that takes a data chunk and returns the encoded qr data as
     * a data_chunk with default parameter values.
     */
    BI_API static data_chunk encode(data_chunk const& data);

    /**
     * A method that takes a data chunk and returns the encoded qr data as
     * a data chunk with the specified parameter values.
     */
    BI_API static data_chunk encode(data_chunk const& data,
        uint32_t version, const error_recovery_level level,
        encode_mode mode, bool case_sensitive);

    /**
     * A method that takes an input stream and writes the encoded qr data
     * to the output stream with the specified parameter values.
     */
    BI_API static bool encode(std::istream& in, uint32_t version,
        error_recovery_level level, encode_mode mode, bool case_sensitive,
        std::ostream& out);
};

} // namespace wallet
} // namespace libbitcoin

#endif // WITH_QRENCODE

#endif
