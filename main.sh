set -e

BUILD_DIR="build"
cd "$BUILD_DIR"

cmake -DCMAKE_BUILD_TYPE=Debug ..
cmake --build . --parallel

./main