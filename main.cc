#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <CLI/CLI.hpp>

enum class Level
{
    Low,
    Medium,
    High,
};

std::map<std::string, Level> map = {{"High", Level::High},
                                    {"Medium", Level::Medium},
                                    {"Low", Level::Low}};

int main(int argc, char* argv[])
{
    bool foo, bar;
    Level level;
    CLI::App app{"cli", "testing cli"};
    app.add_flag_callback("--version", [](void) {
        std::cout << "cli v1.8.0-48-g704e169" << std::endl; },
        "print out version");

    app.add_flag("-f,--foo", foo, "Set foo");
    app.add_flag("-b,--bar", bar, "Set bar");

    app.add_option("-l,--level", level, "Level settings")
        ->transform(CLI::CheckedTransformer(map, CLI::ignore_case));

    CLI11_PARSE(app, argc, argv);
    std::cout << "level: " << static_cast<int>(level) << "\n" <<
                 "foo: " << (foo ? "YES" : "NO") << "\n" <<
                 "bar: " << (bar ? "YES" : "NO") << std::endl;
    return 0;
}
