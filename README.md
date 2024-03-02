# WXTris ('wex-tris')

## Purpose
Just for fun, revisiting an old favorite GUI library and ditto game.
To make it interesting, Engaging sounds and animations. Would be fun
to add some extra's, like earned fluids and bombs.

So, WXTrix, not proper Tetris, just my own for-fun-project.

## Design

The actual game-logic in class Tetrix, viewed by simple and straight forward wxWidgets frontend for now. Maybe I'l implement something console-only in future to assert proper separation.

Still only basic playable, no scores is work in progress. Planning to introduce some event-system to support logging and scanners for patterns in the grid. This is to support different approach to self-playing using different kind of AI approaches. Not there yet though...

## Builds

Currently using Conan 2 to build, `cmake` is the default, so what the heck...

I have one runner for **X86_64** and one for **ARM64** both running Debian 12 with GNome - desktop.
