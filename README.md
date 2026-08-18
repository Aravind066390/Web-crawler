# 🕷️ C Web Crawler & Mini Search Engine

> An experimental web crawler and keyword-based search engine built from scratch using **C/C++**, **libcurl**, process-based parallelism, and custom memory-management experiments.

[![Language](https://img.shields.io/badge/Language-C%2FC%2B%2B-blue)](https://github.com/Aravind066390/Web-crawler)
[![Networking](https://img.shields.io/badge/Networking-libcurl-orange)](https://curl.se/libcurl/)
[![License](https://img.shields.io/badge/License-MIT-green)](LICENSE)

---

## 📌 Overview

This project started as an experiment to understand how a basic search engine can discover webpages, inspect their contents, identify relevant links, and continue searching through the web.

Instead of relying on a high-level crawling framework, the project implements the core crawling logic using **C/C++ and libcurl**.

The current architecture separates **user interaction and configuration** from the actual crawling engine.

```text
                    ┌──────────────────────┐
                    │      User Input      │
                    │  Search terms /      │
                    │  crawler settings    │
                    └──────────┬───────────┘
                               │
                               ▼
                    ┌──────────────────────┐
                    │      Manager.c       │
                    │                      │
                    │ • Input handling     │
                    │ • Command handling   │
                    │ • Depth control      │
                    │ • Input validation   │
                    └──────────┬───────────┘
                               │
                         launches crawler
                               │
                               ▼
                    ┌──────────────────────┐
                    │     Crawler.cpp      │
                    │                      │
                    │ • libcurl requests   │
                    │ • HTML processing    │
                    │ • URL extraction     │
                    │ • Keyword matching   │
                    │ • Link filtering     │
                    │ • Recursive crawl    │
                    └──────────┬───────────┘
                               │
                               ▼
                    ┌──────────────────────┐
                    │   Relevant URLs      │
                    │      / Results       │
                    └──────────────────────┘
```

---

## ✨ Features

### 🌐 Web Crawling

* HTTP/HTTPS webpage retrieval using **libcurl**
* Automatic redirect following
* HTML content retrieval
* Hyperlink extraction
* Recursive discovery of webpages

### 🔎 Keyword-Based Search

The crawler accepts user-provided search terms and examines downloaded webpage content for relevant keywords.

Common words are filtered before the search process begins, reducing unnecessary matching work.

Pages containing sufficient keyword matches can contribute URLs to the result set.

### ⚙️ Search Control

The crawler can be configured through the manager interface.

The user can control the crawler's search limit using the `Depth` command instead of having to manually modify source code.

Example:

```text
enter>Depth
5

enter>computer networking
```

This allows the crawler's workload/search extent to be adjusted interactively.

### 🧑‍💻 User-Facing Manager

`Manager.c` acts as the front-end control layer.

It provides commands such as:

```text
help
Depth
exit
```

The manager:

1. Reads user input.
2. Recognizes supported commands.
3. Validates crawler parameters.
4. Maintains the current search configuration.
5. Constructs the crawler invocation.
6. Starts the crawler with the selected configuration.

This separates **user interaction** from **crawler implementation**.

---

# 🏗️ Project Structure

```text
Web-crawler/
│
├── src/
│   ├── Manager.c
│   └── Crawler.cpp
│
├── bin/
│   ├── Manager
│   └── new
│
├── LICENSE
└── README.md
```

### `Manager.c`

The management/interface layer.

Responsibilities:

* Interactive command processing
* Search input handling
* Depth configuration
* Basic validation
* Help system
* Program termination
* Launching the crawler

The manager was introduced to avoid forcing the user to manually provide or modify crawler configuration every time.

### `Crawler.cpp`

The core crawler/search engine.

Responsibilities:

* Initializing libcurl
* Fetching webpages
* Processing downloaded HTML
* Extracting URLs
* Searching webpage content
* Filtering discovered links
* Maintaining crawl state
* Recursively visiting discovered URLs
* Returning relevant URLs

---

# 🔄 How the Crawler Works

The current crawler follows approximately this pipeline:

```text
             User Search Query
                    │
                    ▼
              Manager.c
                    │
                    │ configuration
                    ▼
              Crawler.cpp
                    │
                    ▼
          Remove common words
                    │
                    ▼
             Select seed URL
                    │
                    ▼
          Fetch webpage with
               libcurl
                    │
                    ▼
             Download HTML
                    │
                    ▼
             Extract URLs
                    │
                    ▼
        Inspect page for keywords
                    │
                    ▼
          Relevance evaluation
                    │
             ┌──────┴──────┐
             │             │
          Relevant      Irrelevant
             │             │
             ▼             └──────► Discard
       Store URL
             │
             ▼
       Discover more links
             │
             ▼
        Continue crawling
             │
             ▼
        Display results
```

---

# 🚀 Parallel Crawling

One of the experimental parts of the project is the use of **multiple processes**.

The crawler creates four child processes using `fork()` and assigns each process a different starting website.

```text
                         Crawler
                            │
          ┌─────────────────┼─────────────────┐
          │                 │                 │
          ▼                 ▼                 ▼
      Process 1         Process 2         Process 3        Process 4
          │                 │                 │                │
          ▼                 ▼                 ▼                ▼
        VTU             YouTube          Wikipedia         data.gov
          │                 │                 │                │
          └─────────────────┴─────────────────┴────────────────┘
                            │
                            ▼
                     HTML Processing
                            │
                            ▼
                    Keyword Evaluation
                            │
                            ▼
                     Relevant URLs
```

The four starting points currently used by the crawler are:

* `vtu.ac.in`
* `youtube.com`
* `wikipedia.org`
* `data.gov`

The goal of this design was to experiment with **process-based parallel crawling** rather than running the entire crawl sequentially.

---

# 🔎 Search / Relevance Model

This is not a traditional search engine index such as Google's.

Instead, it uses an experimental keyword-matching approach.

The crawler:

1. Receives search terms.
2. Removes selected common words.
3. Downloads a webpage.
4. Examines relevant HTML content.
5. Counts keyword occurrences.
6. Uses the match count to determine whether a discovered URL should be retained.
7. Continues exploring selected links.

Conceptually:

```text
Search Query
     │
     ▼
Keyword extraction
     │
     ▼
Webpage retrieval
     │
     ▼
Keyword matching
     │
     ▼
Relevance threshold
     │
     ├── Match ───────► Keep URL
     │
     └── No match ────► Ignore
```

---

# 🎛️ Manager Commands

The manager provides an interactive interface instead of requiring all configuration to be supplied manually.

| Command         | Purpose                                   |
| --------------- | ----------------------------------------- |
| `help`          | Display available commands                |
| `Depth`         | Configure the crawler's search/work limit |
| `exit`          | Exit the manager                          |
| Any other input | Treated as a search query                 |

Example:

```text
enter>help

1. use exit to exit.
2. use Depth to enter search depth.
3. just use ctrl+c to exit forcefully.
```

Configure the crawler:

```text
enter>Depth
10
```

Then search:

```text
enter>computer science
```

---

# 🧠 Custom Memory Experiments

The project also contains experiments with custom memory abstractions.

A custom `memory.h` system was developed as part of the broader exploration of:

* Dynamic memory management
* Low-level memory handling
* Data sharing between components
* Manual resource management

This is one of the reasons the project is intentionally implemented close to the system level rather than using a high-level crawling framework.

---

# 🛠️ Technologies Used

| Technology          | Purpose                                 |
| ------------------- | --------------------------------------- |
| **C**               | Manager / low-level system programming  |
| **C++**             | Core crawler implementation             |
| **libcurl**         | HTTP/HTTPS communication                |
| **fork()**          | Process-based parallel crawling         |
| **Dynamic memory**  | Runtime data management                 |
| **HTML processing** | Page and URL extraction                 |
| **Git/GitHub**      | Version control and project development |

---

# 📚 What I Learned

This project has mainly been a learning exercise in combining several low-level concepts into one system.

### Systems Programming

* Processes
* `fork()`
* Memory management
* Dynamic allocation
* Process control

### Networking

* HTTP requests
* libcurl
* Webpage retrieval
* Redirect handling

### Data Processing

* String processing
* URL extraction
* Keyword matching
* Filtering

### Software Structure

The introduction of `Manager.c` also pushed the project toward a more modular design:

```text
User Interface
      ↓
Configuration / Validation
      ↓
Crawler Engine
      ↓
Web Retrieval
      ↓
Content Processing
      ↓
Search / Filtering
      ↓
Results
```

This separation makes the project easier to extend than having all user interaction and crawler logic inside one file.

---

# ⚠️ Current Limitations

This is an **experimental crawler**, not a production search engine.

Current limitations include:

* Basic HTML parsing
* Experimental URL extraction
* Limited URL deduplication
* Keyword-based relevance rather than sophisticated ranking
* Fixed seed websites
* Process-based rather than thread-based crawling
* Limited handling of modern dynamic websites
* Crawl limits are experimental
* No persistent search index/database yet

These limitations are intentional parts of the project's current development stage.

---

# 🔮 Possible Future Improvements

Some areas I would like to explore:

* [ ] Better HTML parsing
* [ ] Robust URL normalization
* [ ] Improved duplicate detection
* [ ] More accurate relevance scoring
* [ ] Persistent search index
* [ ] Configurable seed URLs
* [ ] Thread-based crawling
* [ ] Better crawl scheduling
* [ ] Robots.txt support
* [ ] Improved error handling
* [ ] Search ranking
* [ ] Result metadata
* [ ] Larger-scale crawling experiments

---

# 🎯 Project Goal

The long-term goal of this project is not simply to create another web scraper.

It is an experiment in understanding **how the fundamental components behind a search system can be built from lower-level programming concepts**.

Starting from:

```text
User Query
```

and eventually reaching:

```text
Web Discovery
      ↓
Crawling
      ↓
Content Processing
      ↓
Indexing
      ↓
Relevance
      ↓
Search Results
```

The project is being developed incrementally, with each iteration used to explore a different systems or networking concept.

---

# 📌 Project Status

**Status: Experimental / Actively Developing**

The current version is functional for experimentation with:

* Web crawling
* Keyword-based searching
* Link extraction
* Recursive discovery
* Process-based crawling
* Interactive crawler configuration

The architecture will continue to evolve as new crawling, searching, networking, and memory-management techniques are explored.

---

## 👤 Author

**Aravind**

Computer Science student interested in:

* C/C++
* Systems programming
* Networking
* Algorithms
* Programming languages
* Virtual machines
* Low-level software development

---

## 📜 License

This project is licensed under the **MIT License**.

See [`LICENSE`](LICENSE) for details.

---

## ⭐ If You Find It Interesting

Feel free to explore the source code, experiment with the crawler, or suggest improvements.

