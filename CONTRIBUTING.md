# Contributing to ste

Thanks for considering a contribution. `ste` is intentionally small, and
that is a feature, not a limitation waiting to be fixed. Please read this
before opening a pull request.

## Philosophy first

- `ste` follows the `dwm` approach to configuration: behavior that can be a
  compile-time constant in `config.h` should be, instead of a runtime
  option, a flag, or a config file format.
- Two modes only, `general` and `write`. Do not propose a third mode; if
  something needs a new mode, it probably belongs in a different editor.
- No dependencies beyond a C++17 compiler and `ncurses`. Do not add a
  library to solve something that can be solved in fifty lines of plain
  code.
- Small, focused changes are preferred over large ones. If your idea is
  substantial, open an issue first so it can be discussed before you write
  code.

## Before you start

Check open issues and pull requests to avoid duplicate work. If you want to
add a feature that is not already tracked, open an issue describing it
before submitting a pull request, unless the change is trivial (a typo fix,
a small bug fix, a build fix).

## Building and testing your changes

```sh
sudo apt install build-essential libncurses-dev
make clean
make
./ste some-test-file.txt
```

There is no automated test suite yet. Manually verify at minimum:

- opening an existing file and a non-existent file
- switching between `general` and `write` modes
- every hotkey defined in `config.h`
- saving and reopening the file to confirm content round-trips correctly
- resizing the terminal while `ste` is running

## Code style

Match the existing code exactly. In particular:

- C++17, no exceptions used for control flow, no RTTI.
- 4 spaces for indentation, no tabs, no trailing whitespace.
- Classes are `PascalCase` (`Editor`, `Buffer`). Functions, methods, and
  variables are `camelCase`. Constants in `config.h` are `camelCase` as
  well, matching the existing entries.
- No source or header file is prefixed with the project name. Use
  `editor.cpp`, not `ste_editor.cpp`. Same rule for functions and classes:
  no `ste` or `Ste` prefix anywhere.
- No comments in source files. If code needs a comment to be understood,
  rewrite it so it does not: extract a well-named function, rename a
  variable, simplify the control flow. Explanations belong in the pull
  request description and in `README.md`, not in the code.
- Header guards use `#pragma once`.
- Keep functions short and single-purpose. `Editor` already separates input
  handling, cursor logic, and rendering into distinct methods; follow that
  split rather than adding logic to `render()` or to the input handlers
  directly.
- New user-facing behavior that can reasonably be a constant belongs in
  `config.h`, following the existing naming and formatting there.

## Commit messages

- Written in English.
- Present tense, short summary line (50 characters or fewer if possible),
  followed by a blank line and further detail if needed.
- One logical change per commit. Do not mix a feature with an unrelated
  refactor.

## Pull requests

- Describe what the change does and why, not just what files were touched.
- Mention how you tested it (see the manual checklist above).
- Keep the diff focused on the stated goal. Unrelated formatting or
  reordering changes make review harder and will likely be asked to be
  split out or dropped.
- Update `README.md` if the change affects usage, keybindings, or something else that used before.

## Reporting bugs

Open an issue with:

- the exact steps to reproduce
- what you expected to happen
- what happened instead
- your terminal emulator and OS, since cursor-shape and key-timing issues
  are often terminal-specific

## License

`ste` is licensed under AGPLv3. By submitting a contribution, you agree
that it will be distributed under the same license.
