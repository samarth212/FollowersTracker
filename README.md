# FollowersTracker

Compare your Instagram followers and following lists and print the accounts
you follow that do not follow you back lol.

## Requirements
- C++17 compiler (clang++ or g++)
- `json.hpp` in the same directory as `main.cpp` (included in this repo)

## Build
```sh
clang++ -std=c++17 -O2 -Wall -Wextra main.cpp -o followers
```

## Run
```sh
./followers
```

You will be prompted for file paths:
```
File path of followers.json:/full/path/to/followers_1.json
File path of following.json:/full/path/to/following.json
```

The program prints one username per line for accounts you follow that do not
follow you back.

## Input files
This expects the Instagram data export files:
- `followers_1.json` (array with `string_list_data[0].value`)
- `following.json` (object with `relationships_following[*].title`)

In the Instagram export, these are typically under:
`connections/followers_and_following/`.

## Troubleshooting
- Linker errors mentioning `std::__1` usually mean you compiled with `clang`
  instead of `clang++`. Use the build command above.
- "Could not find file path" means the path you entered is wrong or has spaces
  that were not escaped/quoted in your shell.
