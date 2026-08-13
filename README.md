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

## ⚙️ How It Works

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
