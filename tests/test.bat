cd /d "%~dp0.."

cmake --build build --config Release

echo --- Running Unit Tests (Catch2) ---
ctest --test-dir build --output-on-failure