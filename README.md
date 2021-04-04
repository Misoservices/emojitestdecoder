# emojitestdecoder

## Simple code to decode Unicode emoji-test.txt annotations

In https://www.unicode.org/Public/emoji/ , you can retrieve emoji-test.txt file for ordering and groupings of emoji.

This converts the TXT file to multiple XCode files. Including a strings file for groups, and multiple swift files for groups, subgroups, ordering, as well as a file to determine the CLDR annotations version (which is always the last minimal one).

Your mileage may vary using this file (code quality is horrendous too). The Swift compiler doesn't like that many lines in a switch-case, so it tend to either error because it's too long to test the cases, or warn because you add a default one. Also, using the files as-is aren't working adequately because the Swift compiler somehow doesn't understand too many different extensions at once. At least, it automates most of the tasks.


## License and usage

We took a few minutes to write this and it might help some people getting a starting point

Please modify it and adapt it to your own usage. If you improve it, please do pull requests.

Original file licensing stays with Unicode licensing for the initial files. Please respect their copyright in your derived products.

This tool is public domain otherwise.
