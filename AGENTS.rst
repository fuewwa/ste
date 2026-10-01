AGENTS
======

This document describes the conventions and rules for agents (human or AI)
working on the **ste** project.

Project Overview
----------------

``ste`` is a vim-like text editor. The project has its own website located in
the ``docs/`` directory.

Code Style
----------

- Use **4 spaces** for indentation.
- **No tabs.**
- **No trailing whitespace.**

Keybindings
-----------

When adding or changing a hotkey / keybinding, you **must** update it in
**both** places:

1. ``config.def.h`` — the source of truth for the keybinding configuration.
2. The interactive board in ``docs/index.html`` — the website's interactive
   keybinding display.

Keeping these in sync is mandatory; a keybinding change is not complete until
both files reflect it.

Naming Conventions
------------------

- **No source or header file** may be prefixed with the project name.

  - Correct: ``editor.cpp``
  - Incorrect: ``ste_editor.cpp``

- The same rule applies to **functions** and **classes**: no ``ste`` or
  ``Ste`` prefix anywhere.

  - Correct: ``class Editor``, ``void redraw()``
  - Incorrect: ``class SteEditor``, ``void ste_redraw()``

The project name should never leak into identifiers. Treat ``ste`` as the name
of the repository/binary, not as a namespace prefix for symbols.
