// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
#ifndef KTH_INFRASTUCTURE_CONFIG_PARAMETER_HPP
#define KTH_INFRASTUCTURE_CONFIG_PARAMETER_HPP

#include <string>
#include <utility>
#include <vector>

#include <boost/program_options.hpp>

#include <bitcoin/infrastructure/define.hpp>

/* NOTE: don't declare 'using namespace foo' in headers. */

namespace kth {
namespace config {

/**
 * Shorthand for property declarations in parameter class.
 */
#define BI_PROPERTY(type, name) \
    public: type get_##name() const { return name##_; } \
    public: void set_##name(type const& value) { name##_ = value; } \
    private: type name##_

/**
 * A tuple to represent a positional argument name count.
 */
using argument_pair = std::pair<std::string const, int>;

/**
 * A type to represent the list of positional argument name counts.
 */
using argument_list = std::vector<argument_pair>;

/**
 * A type to represent a list of parameter structures.
 */
class parameter;
using parameter_list = std::vector<parameter>;

/**
 * Normalized storage for command line arguments and options.
 * TEST: option_metadata does not provide virtual methods so must wrap to mock.
 */
class BI_API parameter {
private:

    /**
     * Enumerated options for selecting the canonical name.
     */
    enum search_options : int {
        /** --name/-n */
        dashed_both_prefer_long = 1,

        /** name/-n */
        dashed_short_prefer_long = 2,

        /** -n/name */
        dashed_short_prefer_short = 4
    };

public:

    /**
     * Sentinel - the option is not a positional argument.
     */
    static 
    int const not_positional;

    /**
     * Sentinel - there is no short name.
     */
    static 
    char const no_short_name;

    /**
     * The character used to prefix command line options.
     */
    static 
    char const option_prefix_char;

    /**
     * Populate with normalized parameter data.
     * @param[in]  option     The metadata of the option to test.
     * @param[in]  arguments  The list of supported positional arguments.
     */
    void initialize(
        boost::program_options::option_description const& option,
        argument_list const& arguments);

    /**
     * Determine if the option is an argument by testing for it by name in the
     * positional options collection and if so return the position.
     * @param[in]  option     The metadata of the option to position.
     * @param[in]  arguments  The list of supported positional arguments.
     * @return                Relative position or -1 if not positional.
     */
    int position(
        boost::program_options::option_description const& option,
        argument_list const& arguments) const;

    /**
     * Get the value for the args_limit property.
     * @param[in]  position   The option's position (or -1 of arg).
     * @param[in]  option     The option.
     * @param[in]  arguments  The argument names list.
     * @return                The arguments limit value for the option.
     */
    unsigned arguments_limit(int position,
        boost::program_options::option_description const& option,
        argument_list const& arguments) const;

    /**
     * Get the option's short name character or zero.
     * @param[in]  option  The metadata of the option to test.
     * @return             The short name character or null character.
     */
    char short_name(boost::program_options::option_description const& option) const;

    /**
     * Virtual property declarations.
     */
    //TODO(fernando): remove these macros
    BI_PROPERTY(int, position);
    BI_PROPERTY(bool, required);
    BI_PROPERTY(char, short_name);
    BI_PROPERTY(unsigned, args_limit);
    BI_PROPERTY(std::string, long_name);
    BI_PROPERTY(std::string, description);
    BI_PROPERTY(std::string, format_name);
    BI_PROPERTY(std::string, format_parameter);
};

#undef BI_PROPERTY

} // namespace config
} // namespace kth

#endif
