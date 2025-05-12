# 🎧 WaveKit
## A Tiny DAW Engine

**WaveKit** is a personal learning project. It was originally created as a university project in C, however I 
wanted to continue working on the ideas involved in the project so I rebuilt it as WaveKit.

I'm still looking for a particular use-case, but for the moment the design is intended to be a lightweight, 
modular digital audio workstation (DAW) backend — designed for applications that require a lightweight 
ecosystem, with additional custom features.

For me, the key ideas that I'm interested in exploring are: 
- Project architecture, library / API design, and software distribution
- Low-level digital audio manipulation and processing
- Continue growing in my language and general programming skills

At present it features a simple, testable architecture with the hope to possibly support multiple frontends 
(native apps, audio plugins, web tools, etc.) via a stable core. This is why I have setup the project
architecture as it is.

*Note: (🔧) indicates a todo section.*

## 🚀 Current Features

- 🎛️ Modular engine design for basic audio track management, processing, and I/O
- 🧩 Clean separation between **core library**, **generic frontend**, and the **test suite**
- 🔧 Cross-platform build system using [Premake5](https://premake.github.io/)
- 📦 File-level open-source licensing (MPL-2.0) — use freely, share improvements

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

## 🛠️ Project Tracking
### Status 💾
WaveKit is in early development and currently includes:

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

### (🔧) Future Plans 🔭
**Project**
**Core**
**Test Suite**

## (🔧) Getting Started

## (🔧) Using WaveKit in a Project 🔌

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
If you've happened upon this repository and see something you can fix, make better or have any general feedback — feel free to fork and submit a PR or open an issue for discussion. WaveKit is a learning-focused project and I want to learn!
