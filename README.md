# Ask.fm Console Simulation (C++)

A console-based simulation of the Ask.fm platform built in **C++** as the final practical project from the course **Mostafa Saad – *C++ For Beginners*.

The program allows users to register, log in, send questions to other users, answer received questions, and interact with a simple question-answer system similar to Ask.fm.

# Features

* User registration and login system
* Ask questions to other users
* Answer received questions
* Delete questions
* Anonymous questions (if allowed by the receiver)
* Threaded questions (follow-up questions)
* View questions sent **to you**
* View questions sent **from you**
* List system users
* Feed showing answered questions
* Data persistence using **file storage**

# Technologies Used

* **C++**
* STL Containers

  * `vector`
  * `map`
* File handling

  * `ifstream`
  * `ofstream`
* Object-Oriented Programming
* Console-based UI

# Project Structure

Main components of the system:

* **Account System**

  * User creation
  * Login authentication
  * Unique username & email validation

* **Question System**

  * Create questions
  * Answer questions
  * Thread questions
  * Delete questions

* **Database Simulation**

  * Accounts stored in `Accounts.txt`
  * Questions stored in `Questions.txt`
  * Questions loaded and saved automatically

# How It Works

1. The user starts the program.
2. They can **sign up** or **log in**.
3. After logging in, the user can:

   * Ask questions
   * Answer questions
   * Delete questions
   * View their questions
   * View the public feed.

All data is stored in text files so it persists between runs.

# Example Menu

1. Print questions to me
2. Print questions from me
3. Answer question
4. Delete question
5. Ask question
6. List system users
7. Feed
8. Logout

# What I Learned

* Building a **multi-feature console application**
* Using **STL containers efficiently**
* Implementing **simple database persistence with files**
* Designing **modular C++ structures**
* Managing relationships between objects
* ⭐ **أفضل description للريبو ليجلب recruiters**

وغالبًا هذه الأشياء تفرق كثير عندما يراها شخص في GitHub.
