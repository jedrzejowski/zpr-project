#!/usr/bin/sh


convert res/texture/solid_block/cobblestone.png \
        res/texture/solid_block/dirt.png \
        res/texture/solid_block/stone.png \
        res/texture/solid_block/sand.png \
        -append res/texture1.png

convert res/texture/solid_block/oak_log.png \
        res/texture/solid_block/oak_log_top.png \
        res/texture/solid_block/bricks.png \
        res/texture/solid_block/grass.png \
        -append res/texture2.png

convert res/texture/solid_block/water.png \
        -append res/texture3.png

convert res/texture1.png \
        res/texture2.png  \
        res/texture3.png  \
        -background none \
        +append res/texture/solid_block.png

rm res/texture1.png \
   res/texture2.png \
   res/texture3.png