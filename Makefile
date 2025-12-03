
build: setup build/src/plmc build/src/hecye

setup: build/build.ninja

run: build
	build/src/hecye

build/build.ninja: meson.build
	meson setup build

build/src/plmc build/src/hecye:
	ninja -C build

# vim: noet
