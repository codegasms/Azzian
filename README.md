# Azzian
A funny pixel game about an Asian boy who is chased around by slippers and constantly taunted by family, peers and the game itself.

## Instructions

### Embedding assets in source files
> WARNING: The following instructions will modify the source files so make sure to save your changes.

This step is optional and it is only recommended if you want to be able to execute the application from any working directory without relying on any external asset files.

```shell
$ python embed_assets.py src/*.c
```

If you would like to revert back the embedding of assets then either restore to the latest commit or clone the repo again.

### Building and execution
```shell
$ make BUILD_MODE=release  # Debug build
$ ./Azzian

$ make BUILD_MODE=release  # Release build
$ ./Azzian

$ make PLATFORM=PLATFORM_WEB BUILD_MODE=release web  # WASM build
$ python -m http.server 6969  # Run some HTTP server to serve the Azzian.html file
$ # Now visit http://0.0.0.0:6969/Azzian.html in your web browser

$ make clean  # Clean up build artifacts
```

## Dependencies

- [`raylib`](https://www.raylib.com/#supported-platforms)
- `libc`

## Dependencies (Web)

- [`raylib`](https://www.raylib.com/#supported-platforms)
- `libc`
- `emscripten-sdk`: <https://emscripten.org/docs/getting_started/downloads.html>

## Roadmap

<details>
<summary>Click me</summary>

### TODO 2024-01-26 - DONE
- [x] Create a Title Screen
- [x] Spawn chappal
- [x] Tree spawning logic
- [x] Bug fix: Diagonal movement

### TODO 2024-01-27
- [x] Implement collision
- [x] Implement chappal rain
- [ ] Design levels {Garden, School, Home} -> Only change the textures and tiles.
- [x] Enemy random encounter
- [x] Complete Title Screen
- [x] Implement Pause menu & score
- [x] Menu to Game transition
- [x] Implement hearts
- [x] Implement SFX
- [ ] ~Implement Parry (maybe?)~

#### Design
- [ ] ~School Texture~
- [ ] ~School elements~
- [x] House Texture
- [x] House Elements
- [x] Search funny SFX
- [ ] Get "inpsiration" from Steven He

### TODO 2024-01-28
- [x] Design levels {Garden, Home} -> Only change the textures and tiles.
- [x] Transition b/w levels
- [ ] UI/UX development in screen transition
- [x] Enemy random encounter
- [x] Generate QnA which are to be shown on encounter with enemy
- [x] Search funny SFX
- [x] Implement SFX
- [ ] Get "inpsiration" from Steven He & other Asian Youtubers

#### SFX
- [x] Add quack on credits "I don't give a duck".
- [x] Play HAIYAAAA (Uncle Roger) on language button.
- [x] Play roblox death sound on Damage

</details>
