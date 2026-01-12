# Repository Guidelines

## Project Structure & Module Organization
- Date-stamped folders (e.g., `20251209/`, `20251223/`) hold individual C exercises and homework files.
- `class/` contains lecture examples and small modules (e.g., `LinkedList/`, `file_control/`).
- `oj/` groups online judge solutions by contest or problem set ID, often with input fixtures like `.dic` or `.txt`.
- `accoding/` holds practice sets by chapter or topic.
- `test/` is for scratch programs and ad-hoc tests.
- Root scripts (`build-all.sh`, `clean.sh`, `sync-codes.sh`, `collect_codes.py`) automate common chores.

## Build, Test, and Development Commands
- `./build-all.sh`: recursively compiles every `*.c` with `gcc -Wall`; auto-adds `-lm` when `math.h` is used.
- `gcc path/to/file.c -Wall -o path/to/file` (add `-lm` if needed): compile a single file.
- `./clean.sh`: removes compiled binaries with no file extension (prompts before deletion).
- Run programs directly, optionally with redirected input: `./oj/1104/A < oj/1104/stud.dic`.

## Coding Style & Naming Conventions
- C is the primary language; follow the existing 4-space indentation and Allman-style braces.
- Prefer descriptive filenames (`TestSortStrings.c`, `SortStudents.c`) and keep `Test*.c` for test harnesses.
- Use `snake_case` for local variables and keep function names consistent within each folder/module.

## Testing Guidelines
- There is no centralized test framework; most validation is done by compiling and running specific files.
- Use `test/` programs and `Test*.c` files as lightweight checks.
- Input fixtures live alongside solutions (`*.dic`, `*.txt`, `*.in`); run with stdin redirection when applicable.

## Commit & Pull Request Guidelines
- Git history shows short timestamp-style messages or brief notes; there is no strict convention enforced.
- Keep commits small and descriptive (include the exercise name or folder); prefer one topic per commit.
- PRs should include a short summary, any relevant input files used, and compile/run notes if behavior changes.
