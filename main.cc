#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <CLI/CLI.hpp>

#include <boost/multi_index_container.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/ordered_index.hpp>

enum class Level
{
    Low,
    Medium,
    High,
};

struct name{};
struct lv{};

using EnumRow = std::pair<std::string, Level>;

typedef boost::multi_index_container<
    EnumRow,
    boost::multi_index::indexed_by<
        boost::multi_index::ordered_unique<
            boost::multi_index::tag<name>, BOOST_MULTI_INDEX_MEMBER(EnumRow, std::string, first)>,
        boost::multi_index::ordered_non_unique<
            boost::multi_index::tag<lv>, BOOST_MULTI_INDEX_MEMBER(EnumRow, Level, second)>
    >
> EnumMap;


std::map<std::string, Level> map = {{"High", Level::High},
                                    {"Medium", Level::Medium},
                                    {"Low", Level::Low}};

EnumMap orderedMap(map.begin(), map.end());

int main(int argc, char* argv[])
{
    bool foo, bar;
    Level level, a = Level::Low, b = Level::High;
    CLI::App app{"cli", "testing cli"};
    app.add_flag_callback("--version", [](void) {
        std::cout << "cli v1.8.0-48-g704e169" << std::endl; },
        "print out version");

    if (std::less<Level>()(a, b))
        std::cout << (int)a << " < " << (int)b << std::endl;

    orderedMap.find(std::string{"Low"});
    for (auto p : orderedMap) {
        std::cout << "pair: " << p.first << ", " << (int)p.second << std::endl;
    }
    app.add_flag("-f,--foo", foo, "Set foo");
    app.add_flag("-b,--bar", bar, "Set bar");

    app.add_option("-l,--level", level, "Level settings")
        ->transform(CLI::CheckedTransformer(orderedMap, CLI::ignore_case));

    CLI11_PARSE(app, argc, argv);
    std::cout << "level: " << static_cast<int>(level) << "\n" <<
                 "foo: " << (foo ? "YES" : "NO") << "\n" <<
                 "bar: " << (bar ? "YES" : "NO") << std::endl;
    return 0;
}
