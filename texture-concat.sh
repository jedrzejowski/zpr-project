#!/usr/bin/sh


convert res/texture/block/cobblestone.png \
        res/texture/block/dirt.png \
        res/texture/block/stone.png \
        res/texture/block/sand.png \
        -append res/texture1.png

convert res/texture/block/oak_log.png \
        res/texture/block/oak_log_top.png \
        -append res/texture2.png

convert res/texture1.png \
        res/texture2.png  \
        -background none \
        +append res/block.png

rm res/texture1.png \
   res/texture2.png