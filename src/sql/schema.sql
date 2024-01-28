-- https://cj.rs/blog/sqlite-pragma-cheatsheet-for-performance-and-consistency/
PRAGMA journal_mode = wal; -- different implementation of the atomicity properties
PRAGMA synchronous = normal; -- synchronise less often to the filesystem
PRAGMA foreign_keys = on; -- check foreign key reference, slightly worst performance
CREATE TABLE treasuries
(
    cusip TEXT COLLATE NOCASE primary key
) STRICT;