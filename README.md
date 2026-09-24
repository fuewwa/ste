# ste

`ste` is a minimal terminal text editor with a two-mode workflow inspired by
modal editors, but stripped down to the smallest useful set of behavior.
Configuration is done the same way [dwm](https://dwm.suckless.org/) does it:
by editing `config.h` and recompiling, there is no runtime configuration. The default settings live in `config.def.h`.

## Building

Requirements:

- a C++17 compiler (`g++` or `clang++`)
- `ncurses` development headers

On Debian/Ubuntu:

```sh
sudo apt install build-essential libncurses-dev
```

On Arch linux:

```sh
sudo pacman -S base-devel ncurses
```

Then:

```sh
make
```

If `config.h` does not exist, `make` creates it by copying `config.def.h`.
If it already exists, it is used as is, so your changes are never overwritten.
To reset to the defaults, delete `config.h` and run `make` again.

This produces a single binary, `ste`, in the project root.

To install it system-wide:

```sh
sudo make install
```

This copies the binary to `/usr/local/bin/ste`. To remove it:

```sh
sudo make uninstall
```

To change the install prefix:

```sh
sudo make install PREFIX=/usr
```

## Usage

```sh
ste <file>
```

If `<file>` exists, it is opened. If it does not exist, `ste` starts with an
empty buffer and creates the file the first time you save.

## Modes

### General

This is the mode `ste` starts in. The cursor is drawn as a solid block.
Pressing a letter key does not insert it into the buffer; it only triggers a
command if that key is bound to one. Arrow keys move the cursor.

Default bindings (see `config.h`):

| Key | Action |
| --- | --- |
| `q` | quit `ste` |
| `w` | switch to `write` mode |
| `s` | save the file |
| arrows | move the cursor |

### Write

Entered from `general` mode by pressing the configured `writeMode` key. The
cursor is drawn as a thin vertical bar to make the mode visually obvious even
without looking at the status line. Every printable character you type is
inserted at the cursor position. `Backspace`, `Enter` and the arrow keys work
as you would expect from any plain text editor.

The only key that does not insert text in `write` mode is `Esc`, which
returns to `general` mode.

| Key | Action |
| --- | --- |
| `Esc` | switch back to `general` mode |
| any printable key | insert the character |
| `Backspace` | delete the character before the cursor |
| `Enter` | insert a new line |
| `Tab` | insert `tab` spaces (see `config.h`) |
| arrows | move the cursor |

## Status line

The bottom row of the terminal always shows the current mode, the file name,
whether the buffer has unsaved changes, and the cursor position (`line:col`,
one-indexed).

## Cursor shape

`ste` switches the terminal cursor shape between a steady block (`general`
mode) and a steady bar (`write` mode) using standard DECSCUSR escape
sequences. This works in most modern terminal emulators (e.g. xterm,
kitty, alacritty, foot, gnome-terminal, iTerm2). If your terminal does not
support DECSCUSR, the cursor shape simply stays whatever the terminal
defaults to; the mode is still visible on the status line.

## License

`ste` is licensed under the GNU Affero General Public License v3.0. See
`LICENSE` for the full text.
