# 📚 Inverted Search Engine 🚀

Welcome to the **Inverted Search Engine**, a high-performance C-based application that powers lightning-fast word searches across multiple text files using an inverted index data structure. Whether you're indexing documents or hunting for specific words, this project makes it easy, efficient, and fun! 🎉

---

## 🌟 Project Overview

The Inverted Search Engine is designed to create, manage, and query a database of words extracted from text files. It uses a hash table to organize words, their frequencies, and the files they appear in, enabling quick lookups and detailed insights. Perfect for developers, researchers, or anyone curious about text indexing! 🔍

---

## ✨ Key Features

- **📝 Create Database**: Build an inverted index from text files in a snap.
- **📊 Display Database**: View your database in a sleek, tabulated format.
- **🔎 Search Words**: Find words across files with detailed file and frequency info.
- **🔄 Update Database**: Seamlessly add new files or load from existing database files.
- **💾 Save Database**: Export your database to a file for future use.
- **🗂️ File Management**: Track active and deleted files with ease.

---

## 🛠️ Project Structure

The project is modular and well-organized, with each file serving a specific purpose:

- **`main.c`**: The heart of the program, featuring a user-friendly menu interface.
- **`inverted_search.h`**: Defines structures and function prototypes.
- **`create_database.c`**: Handles database creation and file list management.
- **`display_database.c`**: Renders the database in a clean, tabular view.
- **`search.c`**: Powers the word search functionality.
- **`save_database.c`**: Saves the database to a file.
- **`update.c`**: Manages database updates and file list deletions.

---

## 🚀 Getting Started

### Prerequisites
- A C compiler (e.g., `gcc`)
- Standard C libraries (`stdio.h`, `stdlib.h`, `string.h`, `ctype.h`)

### Installation
1. Clone the repository:
   ```bash
   git clone https://github.com/your-username/inverted-search.git
   cd inverted-search
   ```
2. Compile the project:
   ```bash
   gcc -o inverted_search main.c create_database.c display_database.c search.c save_database.c update.c
   ```
3. Run the magic:
   ```bash
   ./inverted_search file1.txt file2.txt ...
   ```

---

## 🎮 How to Use

1. **Launch the Program**:
   Run with text files as arguments:
   ```bash
   ./inverted_search sample1.txt sample2.txt
   ```

2. **Explore the Menu**:
   Interact with the intuitive menu:
   ```
   🌟 Inverted Search Engine 🌟
   --------------------------------
   1. Create Database 📝
   2. Display Database 📊
   3. Update Database 🔄
   4. Search Word 🔎
   5. Save Database 💾
   0. Exit 🚪
   Enter your choice: 
   ```

3. **Available Actions**:
   - **Create Database**: Indexes words from input files.
   - **Display Database**: Shows a table of keys, words, file counts, and more.
   - **Update Database**: Add new files or load from a saved database.
   - **Search Word**: Find a word and see where it appears.
   - **Save Database**: Store the database in a text file.
   - **Exit**: Gracefully exit the program.

---

## 📂 Database Structure

The database uses a hash table with 28 slots:
- **Keys 1-26**: Map to letters (a-z or A-Z).
- **Key 0**: For words starting with digits.
- **Key 27**: For words starting with special characters.

Each slot links to a list of **main nodes** (words), containing:
- The word.
- A count of files it appears in (`file_count`).
- A linked list of **sub-nodes**, each with a file name and word count.

**Saved Database Format**:
- Starts with `#`, followed by semicolon-separated file names (deleted and active), ending with `#`.
- Word entries: `#key;word;file_count;file1;count1;file2;count2;...#`.

---

## 🎉 Example in Action

**Input Files**:
- `sample1.txt`: "hello world"
- `sample2.txt`: "hello there"

**Run the Program**:
```bash
./inverted_search sample1.txt sample2.txt
```

**Menu Interaction**:
```
🌟 Inverted Search Engine 🌟
--------------------------------
1. Create Database 📝
2. Display Database 📊
3. Update Database 🔄
4. Search Word 🔎
5. Save Database 💾
0. Exit 🚪
Enter your choice: 1
INFO: Successfully Created Database

Enter your choice: 2
-------------------------------------------------------------------------------------------------------------------
KEY                 WORD                            FILE COUNT            FILE NAME                       WORD COUNT
-------------------------------------------------------------------------------------------------------------------
7                  hello                          2                     sample1.txt                     1
                                                 sample2.txt                     1
23                 there                          1                     sample2.txt                     1
27                 world                          1                     sample1.txt                     1
-------------------------------------------------------------------------------------------------------------------

Enter your choice: 4
Enter the word: hello
INFO: Found The Word "hello" In Database
-------------------------------------------------------------------------------------------------------------------
KEY                 WORD                            FILE COUNT            FILE NAME                       WORD COUNT
-------------------------------------------------------------------------------------------------------------------
7                  hello                          2                     sample1.txt                     1
                                                 sample2.txt                     1
-------------------------------------------------------------------------------------------------------------------
```

---

## 💡 Tips & Notes
- **File Requirements**: Use `.txt` files only, and ensure they’re not empty.
- **Duplicate Handling**: Duplicate files are automatically skipped.
- **Database File**: Ensure saved database files follow the correct format for updates.
- **Memory Management**: The project handles memory carefully, but large datasets may require ample memory.

---

## 🤝 Contributing

We love contributions! 🎉
1. Fork the repository.
2. Create a feature branch (`git checkout -b feature/awesome-feature`).
3. Commit your changes (`git commit -m 'Add awesome feature'`).
4. Push to the branch (`git push origin feature/awesome-feature`).
5. Open a pull request.

Report bugs or suggest ideas via GitHub Issues! 🐛

---

## 📜 License

This project is licensed under the MIT License. See the `LICENSE` file for details.

---

## 🌈 Why This Project?

The Inverted Search Engine is more than just code—it’s a tool to explore the power of indexing and searching! Whether you're a student learning data structures or a developer building a search system, this project is a fun and educational journey. Dive in and start indexing! 🚀