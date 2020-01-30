// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
#include <bitcoin/infrastructure/unicode/ifstream.hpp>

#include <fstream>
#include <string>

#include <bitcoin/infrastructure/unicode/unicode.hpp>

namespace libbitcoin {

// Construct bc::ifstream.
ifstream::ifstream(std::string const& path, std::ifstream::openmode mode)
#ifdef _MSC_VER
  : std::ifstream(bc::to_utf16(path), mode)
#else
  : std::ifstream(path, mode)
#endif
{
}

} // namespace libbitcoin
