#! /bin/bash
#
# fribidi
# bidirectional text layout
# http://fribidi.org
#
# notes on build system, reference links, etc

# array of build types supported by this formula
# you can delete this to implicitly support *all* types
FORMULA_TYPES=( "osx" "linux64")

VER=master

# download the source code and unpack it into LIB_NAME
function download() {
	git clone https://github.com/signal11/hidapi.git
	cd hidapi
	git reset --hard a6a622ffb680c55da0de787ff93b80280498330f

	if [ "$TYPE" == "osx" ] ; then
		curl -L "https://github.com/signal11/hidapi/pull/219.patch?full_index=1" > hidapi-osx.patch
	fi

}

function prepare() {
	if [ "$TYPE" == "osx" ] ; then
		patch -p1 -N --dry-run --silent < hidapi-osx.patch 2>/dev/null
		#If the patch has not been applied then the $? which is the exit status
		#for last command would have a success status code = 0
		if [ $? -eq 0 ]; then
			#apply the patch
			patch -p1 -N < hidapi-osx.patch
		fi
	fi
}


# executed inside the lib src dir
function build() {
	if [ "$TYPE" == "osx" ] || [ "$TYPE" == "linux64" ] ; then
		./bootstrap
		./configure --prefix=$BUILD_ROOT_DIR

		make -j${PARALLEL_MAKE}
		make install
	fi
}

# executed inside the lib src dir, first arg $1 is the dest libs dir root
function copy() {

	if [ "$TYPE" == "osx" ] || [ "$TYPE" == "linux64" ] ; then
		mkdir -p $1/include/hidapi
		cp -Rv $BUILD_ROOT_DIR/include/hidapi/* $1/include/hidapi/

		mkdir -p $1/lib/$TYPE/

		# if [ "$TYPE" == "osx" ] ; then
			cp -Rv $BUILD_ROOT_DIR/lib/libhidapi*.a $1/lib/$TYPE/
		# else
		# 	# Only copy the hidraw backend on linux.
		# 	cp -Rv $BUILD_ROOT_DIR/lib/libhidapi-hidraw.a $1/lib/$TYPE/
		# fi
	# fi

	# copy license file
	rm -rf $1/license # remove any older files if exists
	mkdir -p $1/license
	cp -v LICENSE* $1/license/

}

# executed inside the lib src dir
function clean() {
	make clean;
}
