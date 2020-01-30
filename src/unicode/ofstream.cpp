// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
#include <bitcoin/infrastructure/unicode/ofstream.hpp>

#include <fstream>
#include <string>

#include <bitcoin/infrastructure/unicode/unicode.hpp>

namespace libbitcoin {

// Construct bc::ofstream.
ofstream::ofstream(std::string const& path, std::ofstream::openmode mode)
#ifdef _MSC_VER
  : std::ofstream(bc::to_utf16(path), mode)
#else
  : std::ofstream(path, mode)
#endif
{
}

} // namespace libbitcoin
