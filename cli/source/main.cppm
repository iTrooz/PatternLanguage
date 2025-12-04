module;
#include<vector>
#include<string>

#include <wolv/io/file.hpp>

#include <CLI/CLI.hpp>
#include <CLI/App.hpp>

#include <fmt/format.h>

export module pl.cli.lib;
import pl.cli.sub.format;
import pl.cli.sub.info;
import pl.cli.sub.run;
import pl.cli.sub.docs;

// Available subcommands
export namespace pl::cli {

    // Run the pattern language CLI
    // first argument (args[0]) is the subcommand, not the executable name
    int executeCommandLineInterface(std::vector<std::string> args) {
        CLI::App app("Pattern Language CLI");
        app.require_subcommand();

        // Add subcommands
        sub::addFormatSubcommand(&app);
        sub::addRunSubcommand(&app);
        sub::addDocsSubcommand(&app);
        sub::addInfoSubcommand(&app);

        // Print help message if not enough arguments were provided
        if (args.size() == 0) {
            fmt::print("{}", app.help());
            return EXIT_FAILURE;
        } else if (args.size() == 1) {
            std::string subcommand = args[0];
            if (subcommand == "-h" || subcommand == "--help") {
                fmt::print("{}", app.help());
                return EXIT_FAILURE;
            } else if (subcommand == "--version") {
                fmt::print("{}", "v1.0.0");
                return EXIT_SUCCESS;
            }

            try {
                fmt::print("{}\n", app.get_subcommand(subcommand)->help());
            } catch (CLI::OptionNotFound &) {
                fmt::print("Invalid subcommand '{}'\n", subcommand);
            }

            return EXIT_FAILURE;
        }

        // Parse command line input
        try {
            std::reverse(args.begin(), args.end()); // wanted by CLI11
            app.parse(args);
        } catch(const CLI::ParseError &e) {
            return app.exit(e, std::cout, std::cout);
        }

        return EXIT_SUCCESS;
    }
}

#if defined (LIBPL_CLI_AS_EXECUTABLE)

extern "C++"  int main(int argc, char** argv) {
    std::vector<std::string> args;
    for (int i = 1; i < argc; i++) {
        args.push_back(argv[i]);
    }

    return pl::cli::executeCommandLineInterface(args);
}

#endif