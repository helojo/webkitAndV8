#!/bin/bash

g++ main.cc -o main `pkg-config --cflags --libs webkitgtk-3.0 gtk+-3.0`
