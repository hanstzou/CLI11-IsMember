#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <CLI/CLI.hpp>

#include <boost/multi_index_container.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/ordered_index.hpp>

template <class E_>
using EnumRow = std::pair<std::string, E_>;

template <class E_>
using EnumDB = boost::multi_index_container<
    EnumRow<E_>,
    boost::multi_index::indexed_by<
      boost::multi_index::ordered_non_unique<
        BOOST_MULTI_INDEX_MEMBER(EnumRow<E_>, E_, second)>>
>;

template <class E_>
using EnumView = std::vector<EnumRow<E_>>;


enum class Level {
    Low,
    Medium,
    High,
};
std::map<std::string, Level> mLevels = {
    {"Low",    Level::Low},
    {"High",   Level::High},
    {"Medium", Level::Medium},
};
EnumDB<Level> mLevelDB{mLevels.begin(), mLevels.end()};
EnumView<Level> vLevels{mLevelDB.rbegin(), mLevelDB.rend()};

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
