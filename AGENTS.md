# Legend

Resolve `[XPORT_ROOT]` from `xport-project.json` and read `[XPORT_ROOT]/AGENTS.md`. Keep only stable game-specific facts and task-routing links here; put detailed evidence under `status`. Never create, edit, move, delete or regenerate `README.md`.

## Project facts

- Native short name: `L`; language: C
- Solution: `src/platform/win/L.sln`; Debug executable: `bin/L_debug.exe`; Release executable: `bin/L.exe`; working directory: `bin`; intermediates: `_build`
- Runtime data: `bin/DATA`; Red Book output when applicable: `bin/MUSIC`
- Reviewed original image: `SLES_007.30`; executable SHA-256 `148ffe8d7f5cbd906b8ed0cfee086ac0bd50a520ed532b8aa81bf105e3106670`
- Recording BIOS: user-selected `D:\Users\XProger\Documents\DuckStation\bios\scph5502.bin`; identity and authorization: [status/function-coverage/first/authorized-boundaries.json](status/function-coverage/first/authorized-boundaries.json)
- User permits explicit abort stubs for BIOS/SDK calls absent from xport; game algorithms require full translation and original MIPS audit
- Guest addresses remain 32-bit carriers; image-specific SDK address bindings belong to the game module, with complete audit evidence in [status/function-coverage/first/coverage-batch-0002-revision-0009.audit.json](status/function-coverage/first/coverage-batch-0002-revision-0009.audit.json)
- Coverage task state: [status/function-coverage/first/coverage.json](status/function-coverage/first/coverage.json); static coverage acceptance does not establish full-game runtime equivalence
- Before relying on them, record reviewed image identities, language decision, dummy scope, hooks/layouts, adapter contract and evidence links here
