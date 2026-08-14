# Web-crawler
An experimental web crawler and search engine written in C using libcurl, featuring webpage fetching, link extraction, keyword matching, and recursive crawling.

# C Web Crawler / Search Engine

An experimental web crawler and search engine written in **C** using **libcurl**.

The program starts from a specified website, downloads webpage content, extracts links, searches pages for user-provided keywords, and follows relevant links to discover additional pages.

## 🚀 Features

- HTTP requests using `libcurl`
- Webpage downloading
- Link extraction from HTML
- Keyword matching
- Recursive webpage crawling
- Command-line search terms
- Basic link relevance filtering
- Dynamic memory allocation
- Automatic following of discovered links


## ⚙️ Crawler Architecture

The crawler uses multiple processes to perform crawling in parallel.

Four child processes are created using `fork()`, with each process starting from a different seed URL. This allows multiple websites to be crawled concurrently instead of relying on a single crawling process.

```text
                    Crawler
                       │
          ┌────────────┼────────────┐------------
          │            │            │            |
       Process 1    Process 2    Process 3    Process 4
          │            │            │            │
       Seed URL     Seed URL     Seed URL     Seed URL
          │            │            │            │
          └────────────┴────────────┴────────────┘
                         │
                    HTML processing
                         │
                    Content filtering
                         │
                    Search / indexing


```

## ⚙️ How It Works

The crawler starts from a seed URL and uses libcurl to retrieve webpage
content. It extracts links from the downloaded data, evaluates them
against the supplied search terms, and recursively follows relevant links.

The main processing flow is:

1. Fetch webpage using libcurl
2. Extract URLs from the returned content
3. Filter and evaluate links using search keywords
4. Store candidate links
5. Recursively crawl selected links
6. Display matching URLs



The crawler follows this pipeline:

```text
Search Terms
     │
     ▼
Remove Common Words
     │
     ▼
Starting Website
     │
     ▼
Download HTML using libcurl
     │
     ▼
Extract Links
     │
     ▼
Search Page for Keywords
     │
     ▼
Select Relevant Links
     │
     ▼
Follow Links Recursively
     │
     ▼
Display Relevant URLs

```
## 🧠 Custom Memory System

The project also uses a custom memory abstraction through `memory.h`.
This was developed as part of my experiments with low-level memory
management and shared data between system components.


## 🚧 Project Status

This project is an experimental web crawler and search engine developed
to explore networking, webpage retrieval, link extraction, recursive
crawling, keyword matching, and low-level memory management.

The current implementation is functional for its intended experiments.
Future improvements may include multithreaded crawling, improved HTML
parsing, better URL deduplication, and more efficient search/ranking.


## 👤 Author

**Aravind**

Computer Science Engineering student interested in C/C++, systems
programming, networking, programming languages, and virtual machines.

GitHub: [Aravind066390](https://github.com/Aravind066390)
