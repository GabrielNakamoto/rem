# Rem

Simple CLI note taking app.
Written for fun and to keep track of my chaotic mind.

## Usage

## Note Storage

Currently stores notes in `HOME/.remsource` using [std::getenv](https://en.cppreference.com/w/cpp/utility/program/getenv)

### Creating new note
```
./rem -t This is the title -b This is the body
```

### Viewing Notes
```
./rem -v
```

**Output**

![Screen Shot 2024-12-20 at 3 28 47 PM](https://github.com/user-attachments/assets/15bce19e-f2df-4912-a614-0e3358e6231e)

## Todo

- [ ] Clean up code
- [ ] Configuration File
  - [ ]  Style options
  - [ ]  Custom target file
- [ ] Rewrite in Haskell?
