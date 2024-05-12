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
$ make # Debug build
$ ./Azzian
$ make release # Release build
$ ./Azzian
```

## Dependencies
- [`raylib`](https://www.raylib.com/#supported-platforms)
- `libc`

### TODO 2024-01-26 - DONE
- [x] Create a Title Screen
- [x] Spawn chappal
- [x] Tree spawning logic
- [x] Bug fix: Diagonal movement

### TODO 2024-01-27
- [x] Implement collision
- [x] Implement chappal rain
- [ ] Design levels {Garden, School, Home} -> Only change the textures and tiles.
- [ ] Enemy random encounter
- [x] Complete Title Screen
- [x] Implement Pause menu & score
- [x] Menu to Game transition
- [x] Implement hearts
- [ ] Implement SFX
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
