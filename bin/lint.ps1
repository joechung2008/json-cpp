#Requires -Version 5.1

# Minimal lint helper for clang-tidy. Opinionated and simple.
# Usage: .\lint.ps1

$BUILD_DIR = "build"
$JOBS = 0

if ($args.Count -ne 0) {
    Write-Error "lint.ps1 takes no arguments. If you want to run clang-tidy manually, call clang-tidy directly."
    exit 2
}

if (!(Get-Command clang-tidy -ErrorAction SilentlyContinue)) {
    Write-Error "clang-tidy not found in PATH"
    exit 2
}

if (!(Test-Path "$BUILD_DIR/compile_commands.json")) {
    Write-Error "compile_commands.json not found in ${BUILD_DIR}. Run: cmake -S . -B ${BUILD_DIR} -DCMAKE_EXPORT_COMPILE_COMMANDS=ON"
    exit 2
}

# Build file list: .cpp and .hpp under src/ and tests/
$FILES = Get-ChildItem -Path "src", "tests" -Recurse -Include "*.cpp", "*.hpp" | Select-Object -ExpandProperty FullName

if ($FILES.Count -eq 0) {
    Write-Host "No source files found under src/ or tests/"
    exit 0
}

# Default header-filter: show all non-system headers except doctest
$DEFAULT_HEADER_FILTER = '-header-filter=^(?!.*doctest).*$'

# We intentionally don't support parallelism or extra args here. Keep behavior
# simple and reproducible: run clang-tidy per file with a conservative
# header-filter so system headers are ignored by default.

# Run clang-tidy serially (simple, predictable). This script intentionally
# does not accept extra args; to override behavior, invoke clang-tidy yourself.
$CLANG_ARGS = @("-p", $BUILD_DIR, $DEFAULT_HEADER_FILTER)
$overall_rc = 0

foreach ($f in $FILES) {
    $tmpf = New-TemporaryFile
    try {
        & clang-tidy $CLANG_ARGS $f > $tmpf 2>&1
        $rc = $LASTEXITCODE
        # Filter noisy summary/hint lines that clang-tidy prints when it suppresses diagnostics.
        # Use Select-String with -NotMatch to filter lines
        Get-Content $tmpf | Where-Object { $_ -notmatch '^\s*Suppressed \d+ warnings|header-filter|system-headers|\d+ warning[s]?( and \d+ errors)? generated\.?$' } | ForEach-Object { Write-Host $_ }
    } finally {
        Remove-Item $tmpf -Force
    }
    if ($rc -ne 0) { $overall_rc = $rc }
}

if ($overall_rc -ne 0) {
    exit $overall_rc
}

# Exit with success (clang-tidy results are printed; use exit codes externally if needed)
exit 0