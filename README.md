# CLI11 IsMember Test

\[Update\]
> Okay, it turns out that the enum example has been updated to use CheckedTransformer.
> Fix the sample below and keep this repo as a reference.
> Ref: [#239](https://github.com/CLIUtils/CLI11/pull/239) and [#263](https://github.com/CLIUtils/CLI11/issues/263).

[CLI11](https://github.com/CLIUtils/CLI11) added map support to IsMember since [#228](https://github.com/CLIUtils/CLI11/pull/228).
~However, I cannot have the example running.~

Here is a sample:

```C++
std::map<std::string, Level> map = {{"High", Level::High},
                                    {"Medium", Level::Medium},
                                    {"Low", Level::Low}};

app.add_flag("-f,--foo", foo, "Set foo");
app.add_flag("-b,--bar", bar, "Set bar");
app.add_option("-l,--level", level, "Level settings")
      ->transform(CLI::CheckedTransformer(map, CLI::ignore_case));
// Deprecated:
//    ->transform(CLI::IsMember(map, CLI::ignore_case)
//              | CLI::IsMember({Level::High, Level::Medium, Level::Low}));
```

And the output:
```bash
$ ./cli --foo -l 0 # Works correctly
level: 0
foo: YES
bar: NO

$ ./cli --foo -l Low # Works correctly as well
level: 0
foo: YES
bar: NO

# No more exceptions.
# $ ./cli --foo -l Low # Exception
# --level: Low
# Run with --help for more information.

```

~Note the exception raised when using text "Low".~

This sample is built with:
```text
$ clang++ -std=c++11 -I cli11/include main.cc -o cli

$ clang++ --version
Apple clang version 11.0.0 (clang-1100.0.33.12)
Target: x86_64-apple-darwin18.7.0
```

