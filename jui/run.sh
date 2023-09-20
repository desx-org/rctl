#!/bin/bash
out/build/debug_cfg
echo -e "editor.hpp\ntests.cpp"|entr -s "ninja -C ./out/build/debug_cfg && ./out/build/debug_cfg/main_test"
