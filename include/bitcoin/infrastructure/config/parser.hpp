/**
 * Copyright (c) 2011-2017 libbitcoin developers (see AUTHORS)
 *
 * This file is part of libbitcoin.
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
#ifndef LIBBITCOIN_INFRASTUCTURE_CONFIG_PARSER_HPP
#define LIBBITCOIN_INFRASTUCTURE_CONFIG_PARSER_HPP

#include <iostream>
#include <sstream>
#include <string>

#include <boost/algorithm/string.hpp>
#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>
#include <boost/throw_exception.hpp>

#include <bitcoin/infrastructure/config/checkpoint.hpp>
#include <bitcoin/infrastructure/define.hpp>
#include <bitcoin/infrastructure/unicode/ifstream.hpp>

namespace libbitcoin {

// These are just annoyingly long.
using variables_map = boost::program_options::variables_map;
using option_metadata = boost::program_options::option_description;
using options_metadata = boost::program_options::options_description;
using arguments_metadata = boost::program_options::positional_options_description;

namespace config {

enum class load_error { 
    non_existing_file = -1, 
    default_config = 0, 
    success = 1 
};

// using namespace boost::filesystem;
// using namespace boost::program_options;
// using namespace boost::system;

using boost::filesystem::path;
using boost::program_options::command_line_parser;
using boost::program_options::reading_file;
using boost::system::error_code;

/// Parse configurable values from environment variables, settings file, and
/// command line positional and non-positional options.
template <typename ConcreteParser>
class BI_API parser {
public:
    ConcreteParser& derived() {
        return static_cast<ConcreteParser&>(*this);
    }

    ConcreteParser const& derived() const {
        return static_cast<ConcreteParser const&>(*this);
    }

    // The error is obtained from boost, which circumvents our localization.
    // English-only hack to patch missing arg name in boost exception message.
    static 
    std::string format_invalid_parameter(std::string const& message) {
        std::string clean_message(message);
        boost::replace_all(clean_message, "for option is invalid", "is invalid");
        return "Error: " + clean_message;
    }

    static 
    bool get_option(variables_map& variables, std::string const& name) {
        // Read settings from the map so we don't require an early notify call.
        auto const& variable = variables[name];

        // prevent exception in the case where the settings variable is not set.
        if (variable.empty()) {
            return false;
        }

        return variable.as<bool>();
    }    

    static 
    path get_config_option(variables_map& variables, std::string const& name) {
        // read config from the map so we don't require an early notify
        auto const& config = variables[name];
        // prevent exception in the case where the config variable is not set
        if (config.empty()) {
            // return path();
            return {};
        }
        return config.as<path>();
    }



    // /// Load command line options (named).
    // virtual 
    // options_metadata load_options() = 0;

    // /// Load command line arguments (positional).
    // virtual 
    // arguments_metadata load_arguments() = 0;

    // /// Load environment variable settings.
    // virtual 
    // options_metadata load_environment() = 0;

    // /// Load configuration file settings.
    // virtual 
    // options_metadata load_settings() = 0;



protected:
    // virtual
    void load_command_variables(variables_map& variables, int argc, char const* argv[]) {
        // auto const options = load_options();
        // auto const arguments = load_arguments();

        auto const options = derived().load_options();
        auto const arguments = derived().load_arguments();

        auto command_parser = command_line_parser(argc, argv).options(options)
            /*.allow_unregistered()*/.positional(arguments);
        store(command_parser.run(), variables);
    }

    // virtual
    // int load_configuration_variables(variables_map& variables, std::string const& option_name);
    load_error load_configuration_variables(variables_map& variables, std::string const& option_name) {
        auto const config_path = get_config_option(variables, option_name);
        return load_configuration_variables_path(variables, config_path);
    }

    // virtual
    load_error load_configuration_variables_path(variables_map& variables, path const& config_path) {
        // auto const config_settings = load_settings();
        auto const config_settings = derived().load_settings();

        // If the existence test errors out we pretend there's no file :/.
        error_code code;
        if ( ! config_path.empty()) {
            if (exists(config_path, code)) {
                auto const& path = config_path.string();
                bc::ifstream file(path);

                if ( ! file.good()) {
                    BOOST_THROW_EXCEPTION(reading_file(path.c_str()));
                }

                auto const config = parse_config_file(file, config_settings);
                store(config, variables);
                return load_error::success;
            } 
            return load_error::non_existing_file;
        }

        // Loading from an empty stream causes the defaults to populate.
        std::stringstream stream;
        auto const config = parse_config_file(stream, config_settings);
        store(config, variables);
        return load_error::default_config;
    }

    // virtual
    void load_environment_variables(variables_map& variables, std::string const& prefix) {
        // auto const& environment_variables = load_environment();
        auto const& environment_variables = derived().load_environment();
        auto const environment = parse_environment(environment_variables, prefix);
        store(environment, variables);
    }
};

}} // namespace libbitcoin::config

#endif
