# 🎧 WaveKit
## A Tiny DAW Engine

The goal for **WaveKit** is to be a lightweight, modular digital audio workstation (DAW) backend library — 
designed to be embedded, extended, and adapted for custom audio tools and creative applications.

This project was originally created as a university assignment, however I loved the process so much that 
I wanted to rebuild the project and extend it based on my own specification.

The plan is to create a clean, minimal, and open starting point for DAW-like processing on the backend. I
imagine that the scope of the project will become more focussed once I discover how best a library like this 
could be used.

At present it features a simple, testable architecture with the hope to possibly support multiple frontends 
(native apps, audio plugins, web tools, etc.) via a stable core. This is why I have setup the project
architecture as it is.

---

## 🚀 Current Features

- 🎛️ Modular engine design for basic audio track management, processing, and I/O
- 🧩 Clean separation between **Core logic**, **App frontend**, and the **Test suite**
- 🔧 Cross-platform build system using [Premake5](https://premake.github.io/)
- 📦 File-level open-source licensing (MPL-2.0) — use freely, share improvements

---

## 🧱 Project Structure
```plaintext
WaveKit/
├── Core/                   # The WaveKit engine: reusable backend code
│   ├── Include/                # Public headers
│   ├── Source/
│   └── Build-Core.lua          # Build script
├── Demo/                   # Example application that links against core
|   ├── Source/
│   └── Build-Demo.lua
|── Scripts/                 # Setup scripts for generating project (start here❗)
|   ├── Setup-Linux.sh
|   ├── Setup-Mac.sh            (Coming soon!)
│   └── Setup-Windows.bat
├── Tests/                  # Test suite for engine functionality
|   ├── Source/
│   └── Build-Tests.lua
├── Vendor/                  # Premake binaries (version 5.0-beta2)
|   └── Binaries/               
│       └── Premake/
|           ├── Linux/
|           ├── macOS/
|           └── Windows/
├── Build.lua               # Top‑level workspace build script
└── LICENSE                 # MPL‑2.0 license
```

- Only `Core/` is required when using WaveKit as a library for an external project
---

## 🛠️ Project Tracking
### Status 💾
WaveKit is in early development/migration and currently includes:

✅ Core track utilities and a heap buffer system

✅ File read/write for .wav files at a fixed sample rate and bit depth

✅ Cross-correlation algorithm for detecting sound snippets in other audio tracks

🟡 Basic Premake5 support for Linux, and Windows

### Audio Formats 📦
**WaveKit currently supports**:

✅ .wav files

✅ Mono audio only

✅ Fixed sample rate (8 kHz.)

**Planned**: WaveKit is designed with extensibility in mind. Future versions will introduce support for:

🧭 Multichannel (stereo/surround) audio

🧭 Variable sample rates and format conversion

🧭 Possible Additional formats like .flac, .ogg, and .mp3

### Future Plans (in progress) 🔭
**Project**
**Core**
**Test Suite**

---

## ⚙️ TODO: Getting Started

---

## 🔌 TODO: Using WaveKit in a Project

---

### 📜 License

WaveKit is licensed under the **Mozilla Public License 2.0 (MPL-2.0)**.

You are free to use, modify, and distribute WaveKit, including in commercial and proprietary projects. If you make changes to individual source files in `Core/`, you must publish those modified files under the same license — but your entire project does **not** have to be open source.

See [`LICENSE`](./LICENSE) for full terms.

---

### ✍️ Author

**WaveKit** was created by An Spiteri (an@anspiteri.com). Contributions and feedback are very welcome!

---

### 🙌 Contributing

If you're interested in helping extend WaveKit, add a frontend, or give feedback — feel free to fork and submit a PR, or open an issue for discussion. WaveKit is a learning-focused project and open to ideas.