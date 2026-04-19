# Shade & Spark — Design Specification

**Date:** 2026-04-19  
**Status:** Approved by stakeholder  
**Language:** Flow-Wing (.fg) with raylib module  
**Target Platform:** Desktop (Windows/macOS/Linux via LLVM AOT compilation)

---

## 1. Game Concept

### Title
*Shade & Spark*

### Tagline
"The world went dark... but you brought snacks."

### Story Premise
You play as **Luma**, a tiny mischievous creature who accidentally swallowed the last ember of light in the universe. Now everything is covered in shadows — and Luma discovers they can teleport between them! The goal: restore light to 5 corrupted realms, each with its own personality, while making friends (and occasional frenemies) along the way.

### Tone & Style
- **Playful humor** throughout — NPCs have snarky one-liners, Luma does silly animations when idle
- **Charming characters** — memorable sidekicks and enemies with distinct personalities
- **Fun sound effects** — satisfying "boop", "whoosh", "sparkle" sounds for every action
- **Visual style:** Hand-drawn 2D art with vibrant colors, smooth animations (60fps), expressive character faces

### Success Criteria
1. Game is playable as a single continuous executable compiled from Flow-Wing source
2. Core Shadow Step mechanic feels responsive and satisfying (< 50ms input latency)
3. At least one realm has full puzzle + chase sequence variety
4. Player can complete the game in ~6-8 hours, with replay value for speedruns

---

## 2. Technical Architecture

### Module Structure

```
games/shade-and-spark/
├── shade-and-spark.fg      # Main entry point — game loop & state machine
├── config.fg               # Constants: screen dimensions, speeds, colors
├── player/
│   ├── luma.fg             # Player character class (physics, shadow step logic)
│   └── abilities.fg        # Shadow Step, Light Dash, Echo Clone implementations
├── world/
│   ├── realm.fg            # Realm manager — loads levels, tracks progress
│   ├── level.fg            # Level data structures & loading
│   ├── shadow.fg           # Shadow entity class (teleport targets)
│   └── platform.fg         # Platform types: static, moving, colored
├── entities/
│   ├── npc.fg              # NPC base class with dialogue system
│   ├── enemy.fg            # Enemy AI states & behaviors
│   └── collectible.fg      # Light shards, power-ups, secrets
├── ui/
│   ├── hud.fg              # HUD: Ember meter, score, timer display
│   ├── menu.fg             # Main menu, pause screen, level select
│   └── overlay.fg          # Death screen, victory screen, endings
├── assets/                 # Image/textures directory (loaded at runtime)
│   ├── luma.png            # Player sprite sheet (32x32 per frame, 8 frames)
│   ├── backgrounds/        # Per-realm background textures
│   └── ui/                 # HUD elements, icons, buttons
└── data/                   # Level definition files (.json via json module)
    ├── realm1_gloom_grove.json
    ├── realm2_clockwork_caverns.json
    └── ...
```

### Core Systems

| System | Module | Responsibility |
|--------|--------|----------------|
| **Game Loop** | `shade-and-spark.fg` | Main loop, state transitions (MENU → PLAYING → PAUSED → GAME_OVER) |
| **Physics** | `player/luma.fg` | Gravity, velocity, collision detection with platforms/shadows |
| **Shadow Step** | `player/abilities.fg` | Raycast to find nearest shadow, teleport animation, Ember cost deduction |
| **Echo System** | `player/abilities.fg` | Store last 3 Shadow Steps as ghost echoes; replay them on next step |
| **Level Loader** | `world/realm.fg` | Parse JSON level data, instantiate entities, set up initial state |
| **Collision** | `world/platform.fg` | AABB collision resolution between player and platforms/enemies/collables |
| **Dialogue** | `entities/npc.fg` | Text box system with typewriter effect, NPC-specific dialogue trees |

### Data Flow

```
[JSON Level File] → [Level Loader] → [Entity Instances] → [Game Loop Update]
       ↓                    ↓                  ↓                ↓
   (Static Data)      (Runtime Objects)  (Physics/AI)    (Render to raylib Window)
```

---

## 3. Core Mechanics — Detailed Design

### Shadow Step (Primary Ability)

**Input:** Left mouse click or Spacebar  
**Cost:** 15 Ember per teleport  
**Cooldown:** None (instant), but limited by Ember meter  

| Aspect | Detail |
|--------|--------|
| **Mechanic** | Click anywhere on screen — Luma teleports to the nearest shadow within range. If no shadow exists in direction of click, Luma performs a short hop toward that point. |
| **Shadow Detection** | Raycast from player position toward click direction; first dark surface hit becomes teleport target. Shadows are defined by `shadow` entities placed in level data or computed from platform collision bounds. |
| **Teleport Animation** | 150ms: Luma fades out → brief particle burst → fade in at destination. During animation, player is invulnerable to damage. |
| **Distance Scaling** | Teleports > 200px cost +5 Ember (bonus). This rewards skilled positioning. |

### Light Dash (Secondary Ability)

**Input:** Right mouse button or Shift  
**Cost:** 30 Ember per dash  
**Cooldown:** 1 second  

| Aspect | Detail |
|--------|--------|
| **Mechanic** | Burst forward in the facing direction at high speed for 200ms. Passes through darkness corridors that block normal movement. Can be used mid-air (reduces fall distance by 50%). |
| **Visual Effect** | Trail of golden particles behind Luma; screen flash on activation. |

### Echo Clone Combo (Advanced Mechanic)

**Input:** Automatic — triggered when Shadow Step is used within 2 seconds of a previous step  

| Aspect | Detail |
|--------|--------|
| **Mechanic** | When performing a Shadow Step, if another echo exists from the last 3 steps, that echo replays its path. Each additional echo adds +1 to combo multiplier (score × Ember restore). |
| **Max Echoes:** 3 simultaneously active  
| **Combo Bonus:** At 3+ echoes, Luma gains temporary invulnerability for 500ms and restores 20% of max Ember on each teleport. This is the "mastery" mechanic — players chain teleports to build combos during chase sequences. |

---

## 4. Level Structure & Progression

### Realm Overview

| # | Name | Theme | New Mechanic Twist | Puzzle Style | Chase Type |
|---|------|-------|---------------------|--------------|------------|
| **1** | Gloom Grove | Enchanted forest, glowing mushrooms | Basic shadow teleporting (tutorial) | Simple platform sequences — place shadows to cross gaps | None — gentle intro with NPC introductions |
| **2** | Clockwork Caverns | Underground mechanical caves with gears and pistons | Moving shadows (timed platforms that shift position every 3 seconds) | Gear-based puzzles — align rotating shadow platforms to create paths | Maze chase: enemy pursues through rotating walls; player must time Shadow Steps to stay ahead |
| **3** | Neon Bazaar | Surreal marketplace with neon signs, floating stalls | Colored shadow zones (red = fast teleport, blue = slow/slippery, green = normal) | Color-matching puzzles — stand in correct colored shadows to activate switches | Rooftop parkour chase: platforming under time pressure while being pursued by a merchant thief |
| **4** | Mirror Citadel | Upside-down palace with reflective surfaces | Dual-shadow puzzles (must use Echo Clone to occupy two shadow positions simultaneously) | Logic gate puzzles — open doors by placing echoes on pressure plates across rooms | Boss fight against "Mirror Self" — copy player's moves; defeat by outsmarting with echo combos |
| **5** | The Last Ember | Final realm — world collapsing into darkness | All mechanics combined + new "Light Burst" ultimate ability (press E to unleash stored Ember as AoE light pulse) | Multi-stage puzzle combat — combine puzzles and enemy encounters in one level | Epic final chase through collapsing architecture, ending with a multi-phase boss battle against the Shadow King |

### Level Format (JSON Schema)

Each realm has 3 levels: **Story**, **Secrets**, **Challenge**. Total = 15 base levels + bonus content.

```json
{
  "realm": 2,
  "levelName": "Clockwork Caverns — The Turning Gear",
  "width": 2048,
  "height": 768,
  "gravity": -600.0f,
  "entities": [
    {"type": "platform", "x": 100, "y": 500, "w": 300, "h": 40},
    {"type": "shadow", "id": "s1", "x": 250, "y": 460, "w": 80, "h": 40},
    {"type": "moving_shadow", "id": "ms1", "startX": 500, "endX": 700, "interval": 3.0f},
    {"type": "enemy_patrol", "x": 900, "y": 480, "speed": 60.0f, "patrolRange": [850, 1050]},
    {"type": "npc", "id": "gear_keeper", "x": 300, "y": 420, "dialogueKey": "realm2_intro"},
    {"type": "light_shard", "x": 680, "y": 100},
    {"type": "exit_portal", "x": 1950, "y": 300}
  ],
  "dialogueTree": {
    "realm2_intro": [
      {"speaker": "Gear Keeper", "text": "Welcome to the Clockwork Caverns! Watch out — shadows move here!"},
      {"speaker": "Luma", "text": "Move? That's... actually perfect for me."}
    ]
  }
}
```

---

## 5. Progression & Replayability Systems

### Ember Upgrades (Permanent)

| Upgrade | Cost | Effect | Unlock Condition |
|---------|------|--------|------------------|
| **Ember Reservoir I** | 10 shards | +20% max Ember capacity | Complete Gloom Grove Story |
| **Shadow Sprint** | 15 shards | Shadow Step range +30% | Collect first 5 light shards |
| **Echo Mastery** | 20 shards | Max echoes increased from 3 to 4 | Complete Clockwork Caverns Secrets |
| **Light Burst** | 25 shards | Unlock Light Dash ability | Reach Neon Bazaar |

### Cosmetic Unlocks (Optional)

| Skin | Requirement | Visual Change |
|------|-------------|---------------|
| Default Luma | Starting skin | Orange glow, round body |
| Firefly | Complete Gloom Grove without dying | Green-yellow particle trail |
| Moonstone | Collect all light shards in realm 2 | Blue-white shimmer effect |
| Ember Lord | Beat Mirror Citadel boss on Hard mode | Red-orange aura with flame particles |

### Multiple Endings (3 Total)

| Ending | Requirement | Description |
|--------|-------------|-------------|
| **Ending A — Spark Restored** | Complete all 5 realms Story levels | Standard ending: light returns to the world, Luma becomes a hero. Playful tone with NPCs celebrating. |
| **Ending B — The Hidden Ember** | Collect ALL light shards (30 total) + complete Secrets levels | Secret ending: Luma discovers they can become the new Light Keeper — choosing to stay in the shadow realm to protect it forever. Emotional moment. |
| **Ending C — True Dawn** | Complete Challenge modes for all realms + find hidden "Ember Core" item | True ending: Luma restores light AND gains control over both light and shadow, becoming a bridge between worlds. Epic final scene with all NPCs appearing. |

### Leaderboard Integration

Each realm level stores best completion time in `data/leaderboards.json` (persisted to disk via file module). Times are sorted ascending — faster is better. Displayed on the level select screen.

---

## 6. Audio Design

### Sound Effects (Generated at runtime or loaded as assets)

| Action | SFX Description | Trigger |
|--------|-----------------|---------|
| Shadow Step | Soft "whoosh" + subtle chime | Player teleports |
| Light Dash | Rising tone burst | Player dashes |
| Echo Clone | Reverse cymbal swell → click | New echo appears |
| Combo (3+) | Ascending arpeggio flourish | 3+ echo combo achieved |
| Collect Shard | Bright "ting!" bell sound | Picking up light shard |
| Take Damage | Low thud + crackle | Player hit by enemy |
| Death | Descending tone → silence | Player dies (respawn at checkpoint) |
| Victory | Upbeat fanfare with sparkles | Level complete |

### Music (Adaptive, 4 Tracks Per Realm)

Each realm has 2 music tracks that crossfade based on gameplay state:

1. **Exploration Track** — Calm, melodic, playful instrumentation (flute + light percussion)
2. **Chase/Combat Track** — Faster tempo, driving rhythm, added strings for tension

Crossfading happens seamlessly when entering chase sequences or puzzle zones. Music is loaded as `.ogg` files via raylib's audio module (or generated procedurally using simple sine wave oscillators if external assets aren't available).

---

## 7. Implementation Phases

### Phase 1 — Foundation (Week 1)
- Set up project structure in `games/shade-and-spark/`
- Implement core game loop with raylib Window
- Create Luma player class with basic movement (gravity, jumping)
- Build shadow entity system and Shadow Step ability
- Load one test level from JSON

### Phase 2 — Core Gameplay (Week 2)
- Add Light Dash ability
- Implement Echo Clone combo system
- Build platform collision resolution
- Create Gloom Grove realm (Story + Secrets levels)
- Implement HUD: Ember meter, score display

### Phase 3 - Content & Polish (Week 3)
- Add Clockwork Caverns and Neon Bazaar realms
- Implement NPC dialogue system with typewriter effect
- Build enemy AI (patrol, chase, attack states)
- Create menu system (main menu, pause screen, level select)
- Add collectible light shards and upgrade shop

### Phase 4 — Endgame & Replayability (Week 4)
- Implement Mirror Citadel boss fight
- Complete The Last Ember realm with final boss
- Build all 3 endings based on player progress
- Add leaderboards (file-based persistence)
- Polish: particle effects, screen shake, sound integration

---

## 8. Constraints & Technical Notes

### Flow-Wing Language Limitations to Account For
- **No built-in JSON parsing** — use the `json` module for level data loading; verify it supports nested objects and arrays at runtime
- **Array bounds checking** — Flow-Wing may have different array access patterns than standard languages; test with small arrays first
- **Memory management** — AOT compilation via LLVM means no garbage collector; manage entity lifecycles explicitly (create/destroy in game loop)
- **Module imports** — Use `bring raylib` and custom module structure (`import {Luma} from "./player/luma.fg"`)

### Performance Targets
| Metric | Target | Notes |
|--------|--------|-------|
| Frame rate | 60 FPS minimum | raylib handles vsync; ensure game loop doesn't block |
| Input latency | < 50ms | Shadow Step teleport should feel instant — no animation delay before movement starts |
| Memory usage | < 100 MB total | Keep texture sizes reasonable (max 2K per background); entity count capped at ~200 |

### File I/O Strategy
- Level data: Load JSON files from `data/` directory using the `file` module's `readText()` function, then parse with `json::parse()`
- Save data: Write leaderboards and upgrade progress to `save.json` in user's home directory via `file::writeText()`

---

## 9. Success Metrics (Post-Launch)

| Metric | Target | Measurement |
|--------|--------|-------------|
| Playtime per session | > 30 minutes average | In-game timer tracking |
| Completion rate | > 40% of players finish at least one realm | Save file analysis |
| Replay value | > 25% replay a level within first week | Leaderboard submissions + save data |
| Secret discovery | > 15% find Ending B (all shards) | Shard count in saved progress |

---

*End of specification. Next step: Implementation planning via writing-plans skill.*
