#!/bin/bash

gcc helloworld.c -o helloworld  `pkg-config --cflags --libs gtk+-2.0`

gcc gtkWebkit.c -o gtkWebkit  `pkg-config --cflags --libs gtk+-2.0` `pkg-config --cflags --libs webkit-1.0`
