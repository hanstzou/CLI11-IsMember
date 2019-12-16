#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <CLI/CLI.hpp>

struct EnumMapSorter
{
    template<typename T_, typename E_>
    bool operator() (std::pair<T_, E_> a, std::pair<T_, E_> b) const
    {
        return a.second < b.second;
    }

    template<typename T_, typename E_>
    static std::vector<std::pair<T_, E_>> sort(std::map<T_, E_> const& map)
    {
        std::vector<std::pair<T_, E_>> vEs{map.begin(), map.end()};
        std::sort(vEs.begin(), vEs.end(), EnumMapSorter{});
        return vEs;
    }
};


enum class Level {
    Low,
    Medium,
    High,
};
std::map<std::string, Level> const mLevels = {
    {"Low",    Level::Low},
    {"High",   Level::High},
    {"Medium", Level::Medium},
};
auto const& vLevels = EnumMapSorter::sort(mLevels);

int main(int argc, char* argv[])
{
    bool foo, bar;
    Level level, a = Level::Low, b = Level::High;
    CLI::App app{"cli", "testing cli"};
    app.add_flag_callback("--version", [](void) {
        std::cout << "cli v1.8.0-48-g704e169" << std::endl; },
        "print out version");

    app.add_flag("-f,--foo", foo, "Set foo");
    app.add_flag("-b,--bar", bar, "Set bar");
    app.add_option("-l,--level", level, "Level settings")
        ->transform(CLI::CheckedTransformer(vLevels, CLI::ignore_case));

    CLI11_PARSE(app, argc, argv);
    std::cout << "level: " << static_cast<int>(level) << "\n" <<
                 "foo: " << (foo ? "YES" : "NO") << "\n" <<
                 "bar: " << (bar ? "YES" : "NO") << std::endl;
    return 0;
}
