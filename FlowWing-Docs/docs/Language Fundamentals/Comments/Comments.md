---
sidebar_position: 1
title: Comments
sidebar_label: Comments
---

# Comments

Flow-Wing supports two comment styles.

## Single-Line Comments

Use `/;` to comment out the rest of a line:

```flowwing
/; This is a comment
print("Hello")  /; Everything after /; on this line is a comment
```

`/;` can appear anywhere on a line. Everything after it becomes a comment.

## Multi-Line Comments

Use `/#` to start and `#/` to end a comment block:

```flowwing
/#
This entire
block is a comment.
It can span multiple lines.
#/
print("Hello")
```

Multi-line comments **cannot nest**. A `/#` inside a multi-line comment is treated as text, not as a new comment start.
