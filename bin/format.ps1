# Format all .cpp and .hpp files in the project using clang-format
# Exclude build and out directories
Get-ChildItem -Path . -Recurse -Include "*.cpp", "*.hpp" |
    Where-Object { $_.FullName -notmatch '\\build\\' -and $_.FullName -notmatch '\\out\\' } |
    ForEach-Object { clang-format -i $_.FullName }

Write-Host "Formatting complete."