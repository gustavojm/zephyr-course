Zephyr builds the target name from the board hardware model:

- `board.yml` says `our_board` uses SoC `stm32h755xx`
- the STM32H755 SoC definition in Zephyr says that SoC has CPU core variants `m7` and `m4`
- so the full valid targets become:
  - `our_board/stm32h755xx/m7`
  - `our_board/stm32h755xx/m4`

That’s why plain `our_board` was rejected. In Zephyr’s current hardware model, a bare board name only works when the board is single-SoC and has no CPU-cluster/variant qualifiers.

In your case, the build system derived that from the board/SoC YAML metadata and then looked for matching board files with that qualifier suffix.
