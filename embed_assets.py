import re
from sys import argv
from pathlib import Path


PATTERN = re.compile(r'\b(Load\w+)\s*\(\s*"([^"]+)"')


def include_bytes(file: str) -> tuple[str, int]:
    resource = Path(file)
    assert resource.is_file()

    content = resource.read_bytes()
    length = len(content)

    content = "".join(f"\\x{x:02x}" for x in content)
    return (f'"{content}"', length)


def file_type(file: str) -> str:
    resource = Path(file)
    suffix = resource.suffix
    assert suffix
    return suffix


def replacer(m: re.Match) -> str:
    func, file = m.groups()
    bytes_content, length = include_bytes(file)
    return f'{func}FromMemory("{file_type(file)}", (const unsigned char *) {bytes_content}, {length}'


def process_file(file: str):
    file = Path(file)
    assert file.is_file()

    content = file.read_text()
    new_content = PATTERN.sub(replacer, content)
    file.write_text(new_content)


def main():
    for file in argv[1:]:
        assert file.endswith(".c")
    for file in argv[1:]:
        process_file(file)


if __name__ == "__main__":
    raise SystemExit(main())
