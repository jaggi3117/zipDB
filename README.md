```markdown
# 🚀 zipDB server

---

**👨‍💻 Created by:** Jagmohan Sharma  

---

## 📌 Overview

A lightweight, in-memory data store implemented in modern C++. This project supports strings, lists, and hashes, parses RESP (Redis Serialization Protocol), handles multiple clients concurrently, and periodically persists to disk.

---

## 🧠 Key Features

- **Command Support**: Common commands (PING, GET, SET, etc.)
- **RESP Protocol**: Full support for Redis protocol parsing
- **Data Types**: Strings, Lists, and Hashes
- **Concurrency**: Multi-client support via threads
- **Persistence**: Saves data to disk every 180 seconds and on shutdown

---

## 🔧 Project Details

**Executable Name:** `zipDB`  
**Default Port:** `6440`  

---

## 🗂️ Folder Structure

```

├── include/                # Header files
│   ├── RedisCommandHandler.h
│   ├── RedisDatabase.h
│   └── RedisServer.h
├── src/                    # Source files
│   ├── RedisCommandHandler.cpp
│   ├── RedisDatabase.cpp
│   ├── RedisServer.cpp
│   └── main.cpp
├── Makefile                # Build system
├── README.md               # You are here

````

---

## ⚙️ Installation

**Compile with Makefile:**

```bash
make
````

**Or compile manually:**

```bash
g++ -std=c++17 -pthread -Iinclude src/*.cpp -o zipDB
```

**Clean build:**

```bash
make clean
```

---

## ▶️ Running the Server

```bash
./zipDB         # Uses default port 6379
./zipDB 6441   # Uses custom port
```

On startup, it attempts to load from `dump.my_rdb` if available.

Gracefully shutdown with `Ctrl+C` to save data.

---

## 📚 Supported Commands

### 🔁 Common

* `PING`, `ECHO <msg>`, `FLUSHALL`

### 🧾 Key-Value

* `SET`, `GET`, `DEL`, `EXPIRE`, `KEYS`, `TYPE`, `RENAME`, `UNLINK`

### 📋 Lists

* `LPUSH`, `RPUSH`, `LPOP`, `RPOP`, `LLEN`, `LGET`, `LREM`, `LINDEX`, `LSET`

### 🧩 Hashes

* `HSET`, `HGET`, `HDEL`, `HKEYS`, `HVALS`, `HEXISTS`, `HGETALL`, `HMSET`, `HLEN`

---

## 🏗️ Architecture & Design

* **Concurrency**: `std::thread` per client
* **Synchronization**: Global `std::mutex` (`db_mutex`)
* **Data Stores**:

  * `unordered_map<string, string>` for strings
  * `unordered_map<string, vector<string>>` for lists
  * `unordered_map<string, unordered_map<string, string>>` for hashes
* **TTL Handling**: Lazy cleanup with `expiry_map`
* **Persistence**: File-based dump every 300s + on shutdown (`dump.my_rdb`)
* **Singleton Pattern**: Central database instance via `RedisDatabase::getInstance()`
* **RESP Protocol**: Parser in `RedisCommandHandler` (handles inline & array modes)

---

## 🙋‍♂️ About Me

**Jagmohan Sharma**
Pre-final year student of Computer Science and Engineering.
Project built as part of my deep dive into C++ networking, system design, and concurrency.
